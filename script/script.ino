#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define RX 2
#define TX 3
#define sw 5;
byte value_sw;
float latitude ;
float longitude;
String status;

#define NAME_WIFI "PARAMITA"
#define PASSWORD "084655"
#define FIREBASE_HOST "https://gps-stungun-esp-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "ZdeFDH6usR1rvaaVBHhVYPWh7uBd6Byula1uuW0N"

TinyGPSPlus gps;
Firebase firebase();
SoftwareSerial GPSpin(RX, TX);

void setup() {
  Serial.begin(115200);
  gps.begin(9600);

  pinMode(sw, INPUT);
  
  //Connecting to your wifi
  WiFi.begin(NAME_WIFI, PASSWORD);
  while(WiFi.status() != WL_CONNECTED){
    delay(200);
    serial.print(".");
  }
  Serial.print("Connect with IP: " + String(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // put your main code here, to run repeatedly:
  value_sw = digitalRead(sw);
  if(value_sw == 1){
    status = "Keadaan bahaya";
     if (gps.location.isValid())
     {
         latitude = gps.location.lat();
         longitude = gps.location.lng();
         if(Firebase.setFloat(firebaseData, "/GPS/latitude", latitude))
         {
          print_ok();
         }
         else
         {
          print_fail();
         }
         if(Firebase.setFloat(firebaseData, "/GPS/longitude", longitude))
         {
          print_ok();
         }
         else
         {
          print_fail();
         }
      }
      
  }else{
    status = "Aman";
    if(Firebase.setFloat(firebaseData, "/GPS/longitude", longitude))
         {
          print_ok();
         }
         else
         {
          print_fail();
         }
    if(Firebase.setFloat(firebaseData, "/GPS/latitude", latitude))
         {
          print_ok();
         }
         else
         {
          print_fail();
         }
    if(Firebase.setString(firebaseData, "/GPS/status", status))
        {
          print_ok();
         }
         else
         {
          print_fail();
         }
  }
}
