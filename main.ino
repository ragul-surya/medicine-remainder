#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
const char *ssid     = "homespot";
const char *password = "betheforce";
const long utcOffsetInSeconds = 19800;
const int buttonPin = 16; 
int buttonState = 0;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const int BUZZER = 4;
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
#define BOT_TOKEN "5190712461:AAFxhTUOpd_FwIxpO5iohLV8QQQPljXvWi0"
// Use @myidbot (IDBot) to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "1047594662"
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Declaring the display name (display)
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
void buzzer()
{
  //int buttonState = 0;
    buttonState = digitalRead(buttonPin);
     Serial.println(buttonState);
     bot.sendMessage(CHAT_ID, "Pillbox notified User for meds", "");
     while ( buttonState == LOW )
     {
     display.clearDisplay();
  
  display.setTextSize(1);                    
  display.setTextColor(WHITE);             
  display.setCursor(0,4);                
  display.println("Please Take pills"); 
  display.display();
  
   digitalWrite(BUZZER, HIGH); 
  delay(500);
   digitalWrite(BUZZER, LOW); 
   //delay(500);
  
   
    buttonState = digitalRead(buttonPin);
   // while( buttonstate == LOW){
      buttonState = digitalRead(buttonPin);
     }
         display.clearDisplay();
  
  display.setTextSize(1);                    
  display.setTextColor(WHITE);             
  display.setCursor(0,4);                
  display.println("Thank you"); 
  display.display();

  delay(10000);
  display.clearDisplay();
  
  display.setTextSize(1);                    
  display.setTextColor(WHITE);             
  display.setCursor(0,4);                
  display.println("Please take temperature reading"); 
  display.display();
  delay(6000);
  display.clearDisplay();
  
  display.setTextSize(1);                    
  display.setTextColor(WHITE);             
  display.setCursor(0,4);                
  display.println("Place your hand above sensor"); 
  display.display();
    delay(7000);
     display.clearDisplay();
  display.setTextSize(1);                    
  display.setTextColor(WHITE);             
  display.setCursor(0,20);                
  display.println("TEMP"); 
  
  display.setTextSize(2);
  display.setCursor(50,17);
  display.println(mlx.readObjectTempF(),1);
  
  display.setCursor(110,17);
  display.println("F");
  display.display();
  delay(5000);
  display.clearDisplay();

   display.setTextSize(1);                    
  display.setTextColor(WHITE);             
  display.setCursor(0,4);                
  display.println("Temperature reported to doctor"); 
  delay(20000);
  display.display();
  display.clearDisplay();

   display.setTextSize(1);                    
  display.setTextColor(WHITE);             
  display.setCursor(0,4);                
  display.println("Thank you"); 
  delay(10000);
  display.display();
  int a = mlx.readObjectTempF();
  String b = String(a);
  bot.sendMessage(CHAT_ID, "b", "");
     
  
  }

void setup() {  
  Serial.begin(115200);
   pinMode(buttonPin, INPUT);
  pinMode(BUZZER, OUTPUT);
    digitalWrite(BUZZER, LOW);

WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
    timeClient.begin();
  mlx.begin(); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Start the OLED display
  display.clearDisplay();
  display.display();
  
 secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
   bot.sendMessage(CHAT_ID, "pillbox connected", "");

}

void loop() {
   timeClient.update();
   int h = timeClient.getHours();
    int s = timeClient.getMinutes();
   String sh = String(h);
   String ss = String(s);
   String t = sh + ":" +ss;

    String time = "2:15";
   //delay(5000);
   if (time == t){
  buzzer();
   }
   Serial.println(t);
  display.clearDisplay();
  
  display.setTextSize(1.5);                    
  display.setTextColor(WHITE);             
  display.setCursor(0,4);                
  display.println("Smart Pillbox"); 
   display.display();
   delay(5000);
    display.clearDisplay();
  
  display.setTextSize(1);                    
  display.setTextColor(WHITE);             
  display.setCursor(0,20);                
  display.println("Alert AT"); 
  
  display.setTextSize(2);
  display.setCursor(50,17);
  display.println(time);
  

  
  display.display();
  
  
  delay(5000);

}
