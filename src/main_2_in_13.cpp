/* Includes ------------------------------------------------------------------*/
#include "DEV_Config.h"
#include "EPD.h"
#include "GUI_Paint.h"
#include "imagedata.h"
#include <stdlib.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;     // 建立ESP8266WiFiMulti对象,对象名称是'wifiMulti'
 
ESP8266WebServer esp8266_server(80);// 建立ESP8266WebServer对象，对象名称为esp8266_server
                                    // 括号中的数字是网路服务器响应http请求的端口号
                                    // 网络服务器标准http端口号为80，因此这里使用80为端口号
/* Entry point ----------------------------------------------------------------*/
//void paint_time(start,mode);
/*void setup()
{
	printf("EPD_2in13_V3_test Demo\r\n");
	DEV_Module_Init();

	printf("e-Paper Init and Clear...\r\n");
	EPD_2in13_V3_Init();
	EPD_2in13_V3_Clear();

	//Create a new image cache
	UBYTE *BlackImage;
	UWORD Imagesize = ((EPD_2in13_V3_WIDTH % 8 == 0)? (EPD_2in13_V3_WIDTH / 8 ): (EPD_2in13_V3_WIDTH / 8 + 1)) * EPD_2in13_V3_HEIGHT;
	if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) 
	{
		printf("Failed to apply for black memory...\r\n");
		while (1);
	}
	printf("Paint_NewImage\r\n");
	Paint_NewImage(BlackImage, EPD_2in13_V3_WIDTH, EPD_2in13_V3_HEIGHT, 90, WHITE);
	Paint_Clear(WHITE);

#if 1   //show image for array    
	Debug("show image for array\r\n");
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);
	
	Paint_DrawBitMap(gImage_1);

	EPD_2in13_V3_Display(BlackImage);
	DEV_Delay_ms(10000);
#endif
*/

//
/*
#if 1  // Drawing on the image
	Paint_NewImage(BlackImage, EPD_2in13_V3_WIDTH, EPD_2in13_V3_HEIGHT, 90, WHITE);  	
	Debug("Drawing\r\n");
	//1.Select Image
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);

	// 2.Drawing on the image
	Paint_DrawPoint(5, 10, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
	Paint_DrawPoint(5, 25, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
	Paint_DrawPoint(5, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
	Paint_DrawPoint(5, 55, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);

	Paint_DrawLine(20, 10, 70, 60, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(70, 10, 20, 60, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawRectangle(20, 10, 70, 60, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
	Paint_DrawRectangle(85, 10, 135, 60, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

	Paint_DrawLine(45, 15, 45, 55, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
	Paint_DrawLine(25, 35, 70, 35, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
	Paint_DrawCircle(45, 35, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
	Paint_DrawCircle(110, 35, 20, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);

	Paint_DrawString_EN(140, 15, "waveshare", &Font16, BLACK, WHITE);
	Paint_DrawNum(140, 40, 123456789, &Font16, BLACK, WHITE);

	Paint_DrawString_CN(140, 60, "你好abc", &Font12CN, BLACK, WHITE);
	Paint_DrawString_CN(5, 65, "微雪电子", &Font24CN, WHITE, BLACK);

	EPD_2in13_V3_Display_Base(BlackImage);
	DEV_Delay_ms(3000);
#endif
*/
/*
#if 1   //Partial refresh, example shows time
	Paint_NewImage(BlackImage, EPD_2in13_V3_WIDTH, EPD_2in13_V3_HEIGHT, 90, WHITE);  
	Debug("Partial refresh\r\n");
	Paint_SelectImage(BlackImage);

	PAINT_TIME sPaint_time;
	sPaint_time.Hour = 12;
	sPaint_time.Min = 34;
	sPaint_time.Sec = 56;
	UBYTE num = 10;
	for (;;) 
	{
		sPaint_time.Sec = sPaint_time.Sec + 1;
		if (sPaint_time.Sec == 60) 
		{
			sPaint_time.Min = sPaint_time.Min + 1;
			sPaint_time.Sec = 0;
			if (sPaint_time.Min == 60) 
			{
				sPaint_time.Hour =  sPaint_time.Hour + 1;
				sPaint_time.Min = 0;
				if (sPaint_time.Hour == 24) 
				{
					sPaint_time.Hour = 0;
					sPaint_time.Min = 0;
					sPaint_time.Sec = 0;
				}
			}
		}
		Paint_ClearWindows(150, 80, 150 + Font20.Width * 7, 80 + Font20.Height, WHITE);
		Paint_DrawTime(150, 80, &sPaint_time, &Font20, WHITE, BLACK);

		num = num - 1;
		if(num == 0) 
		{
			break;
		}
		EPD_2in13_V3_Display_Partial(BlackImage);
		DEV_Delay_ms(500);//Analog clock 1s
	}
#endif
*/
/*
	printf("Clear...\r\n");
	EPD_2in13_V3_Init();
	EPD_2in13_V3_Clear();

	printf("Goto Sleep...\r\n");
	EPD_2in13_V3_Sleep();
	free(BlackImage);
	BlackImage = NULL;
	DEV_Delay_ms(2000);//important, at least 2s
	// close 5V
	printf("close 5V, Module enters 0 power consumption ...\r\n");

}*/

/* The main loop -------------------------------------------------------------*/
//void loop()
//{
//  //
//}

/*
void paint_time(start,mode){
	PAINT_TIME this;

	this.Hour=0;
}
*/