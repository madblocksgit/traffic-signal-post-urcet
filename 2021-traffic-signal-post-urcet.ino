#include "WiFi.h"
#include <HTTPClient.h>
const char* ssid ="Traffic";
const char* pwd ="123456789";
String request_string;
WiFiClient client;
HTTPClient http;
int road1,road2,road3,road4;
void setup()
{
  pinMode(23,INPUT);//ir1-road1
  pinMode(22,INPUT);//ir2-road2
  pinMode(21,INPUT);//ir3-road3
  pinMode(19,INPUT);//ir4-road4
  Serial.begin(9600);
  connect_wifi();
}

void loop() 
{
  road1_data();
}
void road1_data()
{
  if(digitalRead(23)==0)
  {
    road1=0;road2=45;road3=90;road4=135;
    for(int i=0;i<45;i++)
    {
      road2=road2-1;road3=road3-1;road4=road4-1;
      upload_data(String(road1)+","+String(road2)+","+String(road3)+","+String(road4));
    }
  }
  if(digitalRead(22)==0)
  {
    road1=135;road2=0;road3=45;road4=90;
    for(int i=0;i<45;i++)
    {
      road1=road1-1;road3=road3-1;road4=road4-1;
      upload_data(String(road1)+","+String(road2)+","+String(road3)+","+String(road4));
    }
  }
  if(digitalRead(21)==0)
  {
    road1=90;road2=135;road3=0;road4=45;
    for(int i=0;i<45;i++)
    {
      road1=road1-1;road2=road2-1;road4=road4-1;
      upload_data(String(road1)+","+String(road2)+","+String(road3)+","+String(road4));
    }
  }
  if(digitalRead(19)==0)
  {
    road1=45;road2=90;road3=135;road4=0;
    for(int i=0;i<45;i++)
    {
      road1=road1-1;road2=road2-1;road3=road3-1;
      upload_data(String(road1)+","+String(road2)+","+String(road3)+","+String(road4));
    }
  }
}
void upload_data(String data)
{
     if (client.connect("madblocks.tech",80))
     {
        Serial.println("Uploading Data");
        request_string = "https://madblocks.tech/projects/traffic-urcet/device_push.php?status=";
        request_string += data;
        http.begin(request_string);
        http.GET();
        http.end();
        Serial.println("Data Uploaded");
     }
     delay(500);
}
void connect_wifi()
{
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  delay(1000);
  WiFi.begin(ssid,pwd);

  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }

  Serial.println();
  Serial.println("WiFi Connected");
  delay(1000);
  Serial.print("IP Address:");
  Serial.println(WiFi.localIP());
  delay(1000);
}
