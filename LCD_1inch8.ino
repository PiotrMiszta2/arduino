#include <SPI.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include "image.h"
#include "messages_micro.h"

void setup()
{
  Config_Init();
  LCD_Init();
  LCD_Clear(WHITE);
  LCD_SetBacklight(1000);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(WHITE);
  pinMode(4, OUTPUT);
  Serial.begin(9600);
}
void switch_action(MessageMicroReqTypeE reqType);

void loop()
{
  int incomingByte;
  if (Serial.available() > 0) {
      incomingByte = Serial.read();
      switch_action((MessageMicroReqTypeE)(incomingByte));
      }
      
}

void switch_action(MessageMicroReqTypeE reqType) {
  switch(reqType) {
    case MESSAGE_MICRO_REQ_TYPE_LD1:
      set_ld_1();
      break;
    case MESSAGE_MICRO_REQ_TYPE_LD2:
      set_ld_2();
      break;
    case MESSAGE_MICRO_REQ_TYPE_IM1:
      set_image_1();
      break;
    case MESSAGE_MICRO_REQ_TYPE_IM2:
      set_image_2();
      break;
    case MESSAGE_MICRO_REQ_TYPE_IM3:
      set_image_3();
      break;
    case MESSAGE_MICRO_REQ_TYPE_GT:
      get_temp();
      break;
  }
}

void set_image_1() {
  Paint_Clear(GREEN);
}

void set_image_2() {
  Paint_Clear(WHITE);
}

void set_image_3() {
  Paint_Clear(BLACK);
}

void set_ld_1() {
  digitalWrite(4, HIGH);
}

void set_ld_2() {
  digitalWrite(4, LOW);
}

void get_temp() {
  float temp = 0;
  float volt = 0;
  int read_value = analogRead(A1);
  volt = (read_value * 5) / 1024.0;
  temp = (volt - 0.5) * 10;
  char buff[21] = "TEMP = ";
  int temp_to_print = (int)temp;
  snprintf(buff, 20, "TEMP = %d", temp_to_print);
  Paint_DrawString_EN(1, 50, buff, &Font20, 0xF000, 0x0FFF);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
