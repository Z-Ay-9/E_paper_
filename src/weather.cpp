#include<ESP8266WiFi.h>
#include<ArduinoJson.h>
#include "DEV_Config.h"
#include "EPD.h"
#include "GUI_Paint.h"
#include "imagedata.h"
#include <stdlib.h>

const char* ssid ="HUAWEI-9VRSQC_HiLink";//输入热点名称
const char* password ="zh111222";//输入热点密码

const char* host ="api.seniverse.com";
const char* APIKEY ="SNDGn_5Jl8xjd8uU1";//输入自己申请的知心天气私钥
const char* city ="zhengzhou";//可根据需要改为其余城市的拼音
const char* language ="zh-Hans";

const char* power_root = "";

const unsigned long BAUD_RATE=115200;
const unsigned long HTTP_TIMEOUT=5000;
const size_t MAX_CONTENT_SIZE=1000;


UBYTE *BlackImage;

struct WeatherData_now{//存储天气数据的结构体，可根据需要自行添加成员变量
  char city[16];
  char weather[32];
  char temp[16];
  char udate[32];
  
};


WiFiClient client;//创建了一个网络对象
char response[MAX_CONTENT_SIZE];
char endOfHeaders[]="\r\n\r\n";

//初始化
void wifiConnect();
bool sendRequest(const char* host,const char* cityid,const char* apiKey);
bool skipResponseHeaders();
void readReponseContent(char* content,size_t maxSize);
bool parseUserData(char* content,struct WeatherData_now* weatherData);
void printUserData(const struct WeatherData_now* weatherData);
void stopConnect();
void clrEsp8266ResponseBuffer(void);


void setup() {
  	Serial.begin(BAUD_RATE);
  	wifiConnect();//连接WiFi
  	client.setTimeout(HTTP_TIMEOUT);
  	DEV_Module_Init();

	printf("e-Paper Init and Clear...\r\n");
	EPD_2in13_V3_Init();
	EPD_2in13_V3_Clear();
  
  
  
	//Create a new image cache
	
	UWORD Imagesize = ((EPD_2in13_V3_WIDTH % 8 == 0)? (EPD_2in13_V3_WIDTH / 8 ): (EPD_2in13_V3_WIDTH / 8 + 1)) * EPD_2in13_V3_HEIGHT;
	if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) 
	{
		printf("Failed to apply for black memory...\r\n");
		while (1);
	}
	printf("Paint_NewImage\r\n");
	Paint_NewImage(BlackImage, EPD_2in13_V3_WIDTH, EPD_2in13_V3_HEIGHT, 90, WHITE);  	
	Debug("Drawing\r\n");
	//1.Select Image
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);

  //Paint_DrawString_CN(140, 60, "你好abc", &Font12CN, BLACK, WHITE);
	//Paint_DrawString_CN(5, 65, "郑州", &Font24CN, WHITE, BLACK);

	//EPD_2in13_V3_Display_Base(BlackImage);
  Debug("show image for array\r\n");
	
	Paint_DrawBitMap(gImage_role);

	EPD_2in13_V3_Display(BlackImage);
	DEV_Delay_ms(2000);
	DEV_Delay_ms(3000);

  //attachInterrupt(D2, d2_in,RISING);
}

void loop() {
  
  //连接成功，发送GET请求
  
  if(sendRequest(host,city,APIKEY)&&skipResponseHeaders())
  {
    
    //发送http请求 并且跳过响应头
    clrEsp8266ResponseBuffer();//清除缓存
    readReponseContent(response,sizeof(response));//从HTTP服务器响应中读取正文
    WeatherData_now weatherData;
    if(parseUserData(response,&weatherData)){//判断Json数据包是否分析成功
      printUserData(&weatherData);//输出读取到的天气信息
    }

  	stopConnect();
    
  Paint_NewImage(BlackImage, EPD_2in13_V3_WIDTH, EPD_2in13_V3_HEIGHT, 90, WHITE);  	
	Debug("Drawing\r\n");
	//1.Select Image
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);
  Paint_DrawString_EN(140, 15, "weatherData.temp", &Font24, WHITE, BLACK);

  EPD_2in13_V3_Display_Base(BlackImage);
	DEV_Delay_ms(3000);

  EPD_2in13_V3_Init();
	EPD_2in13_V3_Clear();

	printf("Goto Sleep...\r\n");
	EPD_2in13_V3_Sleep();
	free(BlackImage);
	BlackImage = NULL;
	DEV_Delay_ms(2000);//important, at least 2s
	delay(5000);
	}
}

//WiFi连接
void wifiConnect(){
  WiFi.mode(WIFI_STA);//设置esp8266工作模式
  Serial.print("Connecting to");
  Serial.println(ssid);
  WiFi.begin(ssid,password);//连接WiFi
  WiFi.setAutoConnect(true);
  while(WiFi.status()!=WL_CONNECTED){//该函数返回WiFi的连接状态
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  delay(500);
  Serial.println("IP address:");
  Serial.println(WiFi.localIP());
}

//发送http请求
bool sendRequest(const char* host,const char* cityid,const char* apiKey){
  while(!client.connected()){
    if(!client.connect(host,80)){//尝试建立连接
      Serial.println("connection....");
      delay(500);
    }
  }
  String GetUrl="/v3/weather/now.json?key=";
  GetUrl+=APIKEY;
  GetUrl+="&location=";
  GetUrl+=city;
  GetUrl+="&language=";
  GetUrl+=language;
  GetUrl+="&unit=c ";
  client.print(String("GET ")+GetUrl+"HTTP/1.1\r\n"+"Host:"+host+"\r\n"+"Connection:close\r\n\r\n");
  Serial.println("create a request:");
  Serial.println(String("GET ")+GetUrl+"HTTP/1.1\r\n"+"Host:"+host+"\r\n"+"Connection:close\r\n\r\n");
  delay(1000);
  return true;
}

bool power_root_request(){
  
  client.connect("",80);

}

//跳过响应头
bool skipResponseHeaders(){
  bool ok=client.find(endOfHeaders);
  if(!ok){
    Serial.println("No response of invalid response!");
  }
  return ok;
}

//读取响应的正文信息
void readReponseContent(char* content,size_t maxSize){
  size_t length=client.readBytes(content,maxSize);
  delay(100);
  Serial.println("Get the data from Internet");
  content[length]=0;
  Serial.println(content);//输出读取到的数据
  Serial.println("Read data Over!");
  client.flush();//刷新客户端
}

//分析 Json 数据包
bool parseUserData(char* content,struct WeatherData_now* weatherData){
  DynamicJsonBuffer jsonBuffer;//创建一个动态缓冲区实例
  JsonObject&root=jsonBuffer.parseObject(content);//根据需要解析的数据来计算缓冲区的大小
  if(!root.success()){
    Serial.println("JSON parsing failed!");
    return false;
  }
  //复制数据包中所需的字符串
  JsonObject&DATA = root["results"][0];
  strcpy(weatherData->city,root["results"][0]["location"]["name"]);
  strcpy(weatherData->weather,root["results"][0]["now"]["text"]);
  strcpy(weatherData->temp,root["results"][0]["now"]["temperature"]);
  strcpy(weatherData->udate,root["results"][0]["last_update"]);

  return true;
}

//串口输出
void printUserData(const struct WeatherData_now* weatherData){
  Serial.println("Print parsed data:");
  Serial.print("City:");
  Serial.print(weatherData->city);
  Serial.print("  Weather:");
  Serial.print(weatherData->weather);
  Serial.print("  Temp:");
  Serial.print(weatherData->temp);
  Serial.print("℃");
  Serial.print("  UpdateTime:");
  Serial.println(weatherData->udate);
}
//停止客户端访问
void stopConnect(){
  Serial.println("Disconnect");
  client.stop();//停止客户端访问
}
//清除缓存
void clrEsp8266ResponseBuffer(void){
  memset(response,0,MAX_CONTENT_SIZE);
}


void d2_in(void){


}
