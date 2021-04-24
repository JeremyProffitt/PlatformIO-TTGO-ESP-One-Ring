/*
The MIT License (MIT)

Copyright © 2018 Médéric NETTO

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#define ILI9341_TFTWIDTH 320  ///< ILI9341 max TFT width
#define ILI9341_TFTHEIGHT 240 ///< ILI9341 max TFT height

#include <Arduino.h>
#include <ArduinoJson.h>

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <App.hpp>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>


#include <TimeLib.h>
#include <PrintUtils.h>
#include <Bitmaps.h>
#include <BoardConfig.hpp>
#include <OtaHandler.hpp>

Adafruit_ILI9341 tft =
    Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

// Colors
int ILI9341_COLOR;
#define CUSTOM_DARK 0x4228 // Background color


unsigned long previousMillis = 0;
unsigned long progressTimestamp = 0;
long interval = 0;

 

void setup() {

  Serial.begin(115200);

  pinMode(TFT_BL, OUTPUT);
  pinMode(BUTTON_L, INPUT_PULLUP);
  pinMode(BUTTON_M, INPUT_PULLUP);
  pinMode(BUTTON_R, INPUT_PULLUP);

  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_BLUE);
  tft.setTextWrap(true);
  tft.setCursor(0, 170);
  tft.setTextSize(2);

  tft.println("Connecting to: ");
  tft.println(" ");
  tft.println(WIFI_SSID);
  Serial.println("start");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  digitalWrite(TFT_BL, true);

  
  Serial.println("\nConnected");
  Serial.println(WiFi.localIP());
  tft.println(" ");
  tft.println("WiFi connected");
  tft.println("IP address: ");
  tft.println(WiFi.localIP());

  InitializeOTA();

  delay(1500);
  tft.fillScreen(ILI9341_BLACK); // Clear Screen
  tft.setTextColor(0x0BBF);
  tft.setCursor(0, 150);
  tft.setTextSize(2);
  tft.println("Crypto Money Ticker");
  tft.drawLine(0, 130, 240, 130, ILI9341_WHITE);
  tft.drawLine(0, 185, 240, 185, ILI9341_WHITE);

  tft.setTextSize(1);
  tft.setCursor(5, 307);
  tft.setTextColor(ILI9341_WHITE);
  tft.println("Data from: CoinMarketCap.com");
}

void loop() {

  ArduinoOTA.handle();

  bool refresh = false;

  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(1, 10);

  if (digitalRead(BUTTON_L) == LOW) {
    Serial.println("BUTTON_L pressed");
    refresh = true;
  }

  if (digitalRead(BUTTON_M) == LOW) {
    Serial.println("BUTTON_M pressed");
    refresh = true;
  }

  if (digitalRead(BUTTON_R) == LOW) {
    Serial.println("BUTTON_R pressed");
    refresh = true;
  }

  if (refresh == true) {
    printTransition();
  }

  unsigned long currentMillis = millis();

  if( currentMillis - progressTimestamp >= 250 )
  {
    progressTimestamp = currentMillis;
    int progress = (int)(currentMillis - previousMillis);
    progress /= 250.0 ;
    tft.drawPixel( progress, 319,  ILI9341_WHITE );
  }
  
  if (currentMillis - previousMillis >= interval || refresh == true) {

    previousMillis = currentMillis;
    interval = 60000; //                              <<<--------------------

    

    tft.drawFastHLine( 0, 319, 240, ILI9341_GREEN );



    
    previousMillis = millis();
  }
}

