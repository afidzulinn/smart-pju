#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <PZEM004Tv30.h>
#include "RTClib.h"


//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif


// Insert your network credentials
#define WIFI_SSID "Fathur"
#define WIFI_PASSWORD "12341234"

// Insert Firebase project API Key
#define API_KEY "AIzaSyDKd6HoEPu_Q5ddxpQHgdT5QadN6-8cJ7I"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://tsa-smartpju-default-rtdb.firebaseio.com/"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//RTC
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"MINGGU", "SENIN", "SELASA", "RABU", "KAMIS", "JUMAT", "SABTU"};

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//sensor voltage and current
PZEM004Tv30 pzem(Serial2, 16, 17); // (RX,TX)
float voltage;
float current;


  
//sensor cahaya
int ldr = 35;
int Sensor_LDR;
// status cahaya
int status = 0;
String STATUS_LAMPU = "OFF";;
//relay
int SW_LAMP = 32;
int LED = 27;
//Suhu
int suhupin = 33;
int suhu1;
  float millivolts=0.0; 
  float celsius =0.0; 
//milis
const unsigned long interval =100;
unsigned long previousTime_pengecekan,previousTime_AC = 0;

  String LDR_DATA ;
  String SUHU_DATA ;
  String VOLTAGE_DATA ;
  String ARUS_DATA ;
  String STATUS_DATA ;
  String JAM ;
  String HARI ;
  String jam_app;
  String tanggal_app;
 DateTime now;
void setup() {
  Serial.begin(115200);
  Serial2.begin(9600,SERIAL_8N1,16,17);
  Wire.begin();
  inisialisasi_wifi();
#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif
 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  delay(2000);
  display.clearDisplay(); 
   // January 21, 2014 at 3am you would call:
  pinMode(SW_LAMP, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(SW_LAMP, LOW);
  digitalWrite(LED, HIGH);
  for(int i = 3;i>0;i--)
  {
    
  display.setTextSize(2);
  display.setTextColor(WHITE);
  String Judul = "PJU KEL 10";
  display.setCursor(((10-Judul.length())/2)*13, 0);//(sumbu x,sumbu y) 
  // Display static text
  display.println(Judul);
  display.setTextSize(4);
   Judul = String(i);
   display.setCursor(50, 16);
   display.println(Judul);
   display.display(); 
   delay(1000);
   display.clearDisplay();
  }
  display.setTextSize(2);
  display.setTextColor(WHITE);
  String Judul = "PJU KEL 10";
  display.setCursor(((10-Judul.length())/2)*13, 0);//(sumbu x,sumbu y) 
  // Display static text
  display.println(Judul);
 display.display(); 
 
}






void loop() {
  now = rtc.now();
  suhu1 = analogRead(suhupin);
  millivolts = (suhu1/4095.0) * 5000; 
  celsius = millivolts/10; 
  Sensor_LDR = analogRead(ldr);
  voltage = pzem.voltage();
  current = pzem.current();
  jam_app = String(now.hour(),DEC)+ "|" +String(now.minute(),DEC);
  tanggal_app = String(now.day(),DEC)+ "|" +String(now.month(),DEC)+"|" +String(now.year(),DEC);
  //Tegangan dan ARUS ketika 0
  if(isnan(voltage) )
  {
    voltage = 0.0;
  }
  if(isnan(current))
  {
    current  = 0.0;
  }
  read_OLED();
  check_AC();
  kirim_firebase();
}


void read_OLED()
{
    //Pembacaan OLED
    unsigned long currentTime_pengecekan = millis();
    if(currentTime_pengecekan - previousTime_pengecekan >= interval )
  {
    previousTime_pengecekan = currentTime_pengecekan;
     display.clearDisplay();
   display.setTextSize(2);
  display.setTextColor(WHITE);
  String Judul = "PJU KEL 10";
  display.setCursor(((10-Judul.length())/2)*13, 0);//(sumbu x,sumbu y) 
  // Display static text
  display.println(Judul);
  display.drawLine(78,16,78,64,WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 16);//(sumbu x,sumbu y) 
  display.println("LDR   :");
  display.setCursor(0, 24);//(sumbu x,sumbu y) 
  display.println("SUHU  : ");
  display.setCursor(0, 32);//(sumbu x,sumbu y) 
  display.println("VOLT  :");
  display.setCursor(0, 40);//(sumbu x,sumbu y) 
  display.println("ARUS  : ");
  display.setCursor(0, 48);//(sumbu x,sumbu y) 
  display.println("STATUS: ");
  display.setTextSize(1);
  display.setTextColor(WHITE);
   LDR_DATA =  String(Sensor_LDR);
   SUHU_DATA = String(celsius,1)+"C";
   VOLTAGE_DATA = String(voltage,0)+"V";
   ARUS_DATA = String(current,1)+"A";
   STATUS_DATA = STATUS_LAMPU;
   JAM = String(now.hour(),DEC)+ ":" +String(now.minute(),DEC);
   HARI = daysOfTheWeek[now.dayOfTheWeek()];
  display.setCursor(45, 16);//(sumbu x,sumbu y) 
  display.println(LDR_DATA);
  display.setCursor(45, 24);//(sumbu x,sumbu y) 
  display.println(SUHU_DATA);
  display.setCursor(45, 32);//(sumbu x,sumbu y) 
  display.println(VOLTAGE_DATA);
  display.setCursor(45, 40);//(sumbu x,sumbu y) 
  display.println(ARUS_DATA);
  display.setCursor(45, 48);//(sumbu x,sumbu y) 
  display.println(STATUS_DATA);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(90, 16);//(sumbu x,sumbu y) 
  display.println(JAM);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(90, 40);//(sumbu x,sumbu y) 
  display.println(HARI);
 display.display(); 
  }
}


void check_AC()
{
  
  //PENGECEKAN AC
      if(Sensor_LDR >= 1000 ) // semakin banyal nilai LDR semakin gelap //smakin banyak cahaya yang masuk pada LDR maka berbanding terbalik dengan resistansi pada LDR(semakin kecil) 
      {
         if(status == 0)
        {
          delay(1000);
          if(Sensor_LDR >= 1000 )
          {
          digitalWrite(SW_LAMP, HIGH);//Relay mati karena NC
          status = 1;
          STATUS_LAMPU = "ON";
          digitalWrite(LED, LOW);
          Firebase.RTDB.setString(&fbdo, "tsa/JAM", jam_app);
    Firebase.RTDB.setString(&fbdo, "tsa/TANGGAL", tanggal_app);
          }   
        }
      }
      else
      {
        if(status == 1)
        {
          delay(1000);
          if(Sensor_LDR < 1000 )
          {
            digitalWrite(SW_LAMP, LOW);
            digitalWrite(LED, HIGH);
            Serial.println("Mati");
            status = 0;
            STATUS_LAMPU = "OFF";
            Firebase.RTDB.setString(&fbdo, "tsa/JAM", jam_app);
    Firebase.RTDB.setString(&fbdo, "tsa/TANGGAL", tanggal_app);
          }   
        }
      }
}

void inisialisasi_wifi()
{
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void kirim_firebase()
{

   if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
  
    // Write an Int number on the database path test/int
    Firebase.RTDB.setInt(&fbdo, "tsa/LDR", Sensor_LDR);
    Firebase.RTDB.setFloat(&fbdo, "tsa/SUHU", celsius);
    Firebase.RTDB.setInt(&fbdo, "tsa/TEGANGAN", voltage);
    Firebase.RTDB.setFloat(&fbdo, "tsa/ARUS", current);
    Firebase.RTDB.setString(&fbdo, "tsa/STATUS", STATUS_LAMPU);
   }
}