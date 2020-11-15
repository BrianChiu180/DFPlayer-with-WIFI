
/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This example shows how you can process commands from player widget

  App project setup:
    Player widget attached to V5 and running project.
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <Wire.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include "Arduino.h"
#include <BlynkSimpleEsp32.h>
#include "DFRobotDFPlayerMini.h"

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "Your Blynk AuthToken";                                                 //   Your Blynk AuthToken

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "WIFI SSID";                                                           //WIFI SSID
char pass[] = "WIFI Password";                                                       //WIFI Password




HardwareSerial myHardwareSerial(1);                                                //ESP32 can announce H/W Serail port
DFRobotDFPlayerMini myDFPlayer;                                                    //Enable DFPlayer
void printDetail(uint8_t type, int value);                                         // Announce player


BLYNK_WRITE(V6)
{
 uint8_t pinValue = param.asInt(); 
 uint8_t volume = pinValue;

  myDFPlayer.volume(volume);   
  Blynk.setProperty(V6, "label", volume);
  Serial.print(volume);
  Serial.println();

}

BLYNK_WRITE(V5)
{
  String action = param.asStr();

  if (action == "play") 
  {
    // Do something
     myDFPlayer.play();
      
    Serial.println("test1");
    myDFPlayer.playMp3Folder(1);                                                  //Play SD card file-0001.mp3    
  }
  if (action == "stop") 
  {
    // Do something
    myDFPlayer.pause();  
  }
  if (action == "next") 
  {
    // Do something
   myDFPlayer.next();    
  }
  if (action == "prev") 
  {
    // Do something
   myDFPlayer.previous();   
  }

  Blynk.setProperty(V5, "label", action);
  Serial.print(action);
  Serial.println();
}

void setup()
{

  Serial.begin(115200);                              // Debug console

  Blynk.begin(auth, ssid, pass);                     // Blynk link your WIFI SSID and password

  // Initial WIFI
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) //Wait for connection ok
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected"); //WIFI cooection ok

  // Begin MP3 connection
  myHardwareSerial.begin(9600, SERIAL_8N1,12 , 13);                                      // Set Serial TX,RX

  Serial.println("Initializing DFPlayer ... (May take 1-2 seconds)");
  myDFPlayer.begin(myHardwareSerial);                                                   //Initial DFPlayer and control it by HardwareSerial
  delay(500);
  
  myDFPlayer.volume(15);                                                                //Set Audio value (0-30)

}


void loop()
{
  Blynk.run();
  BLYNK_WRITE(V6);
  BLYNK_WRITE(V5);

}
