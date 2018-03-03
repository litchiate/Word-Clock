//////////////////////////////////////////////////////////////////
//
// Word Clock
// 
// This code presents the time in words.
// Original code by John Missikos and Damien Brombal (c) 2013
//
// modified by litchiate to run in ESP8266
//
// Libraries used include:
// Adafruit_NeoPixel
// WifiManager
// NTPClient
///////////////////////////////////////////////////////////////////
#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "WordClock.h"

WordClock WordClock; 
Ticker ticker;
WiFiManager wifi;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 28800, 60000);
unsigned long prev, interval = 1000;        // 1000 mS
unsigned char rand_R,rand_G,rand_B;

void setup() {

    Serial.begin(115200);
    Serial.println();
    Serial.println("Connecting to  Saved SSID");
    
    rand_R  = (unsigned char)random(0, 255);
    rand_G  = (unsigned char)random(0, 255);
    rand_B  = (unsigned char)random(0, 255);
 
    WordClock.init();
    WordClock.setColor( rand_R,rand_G,rand_B );
    WordClock.displayEL();    
 
    wifi.autoConnect("Ma");
 
    if(WiFi.status() == WL_CONNECTED) {     // OK
        Serial.println("Done");
      } 
    else {                                 // fail
       Serial.println("Smart Config");
       smartConfig();
       WiFi.begin(WiFi.SSID().c_str(),WiFi.psk().c_str());
       delay(500);
       wifi.setSSID(WiFi.SSID().c_str());
       wifi.setPassword(WiFi.psk().c_str());
     } 
    
    timeClient.begin();
    timeClient.update();
    
}

void smartConfig() {
  WiFi.mode(WIFI_STA);
  Serial.println("\r\nWait for Smartconfig");
  WiFi.beginSmartConfig();
  
  int counter = 0;
  while (1)
  {
    delay(500);
    Serial.print(".");
    counter++;
    if (WiFi.smartConfigDone())
    {
      Serial.println("SmartConfig Success");
      Serial.printf("SSID:%s\r\n", WiFi.SSID().c_str());
      Serial.printf("PSW:%s\r\n", WiFi.psk().c_str());
      delay(1000);delay(1000);delay(1000);delay(1000);
      break;
    }
    delay(1000);
  }
}

void loop() {
    String timeString = "hh:mm:ss";
    int Hour,Minute,Second ;
    unsigned long now = millis();
    
    if (now - prev > interval) {      
        timeClient.update();     
        timeString = timeClient.getFormattedTime();
        Serial.println(timeString);
        Hour = timeClient.getHours();
        Minute = timeClient.getMinutes();
        Second = timeClient.getSeconds();
        
        if( (Minute % 5 == 0) && (Second == 0) ) {   // random Color , Every 5 Minutes
            rand_R  = (unsigned char)random(0, 255);
            rand_G  = (unsigned char)random(0, 255);
            rand_B  = (unsigned char)random(0, 255);
            WordClock.setColor( rand_R,rand_G,rand_B );
        }
        
        WordClock.convertTime( Hour, Minute );      // convert time to word
        WordClock.displayTime();                    // display time
        prev = now;    
    }
}

