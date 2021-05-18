//#include <SoftwareSerial.h>
#include <ArduinoJson.h>
//#include <Adafruit_Sensor.h>
#include "DHT.h"
//
//#include <Wire.h> // responsável pela comunicação com a interface i2c
#include <LiquidCrystal_I2C.h> // responsável pela comunicação com o display LCD
//
////Pinagem da Lora E32 433T30D
//#define TX D5
//#define RX D6
#define DHTPIN 10 //Pinagem DHT11/DHT22
////#define DHTTYPE DHT11 
#define DHTTYPE DHT22  
#define DHTINTERVAL 2000
#define HIGRO A0 //Pinagem Higrometro A0
//
//// carregando softserial
//SoftwareSerial loraSerial (TX,RX);
//LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
DHT dht(DHTPIN, DHTTYPE);
// 
int hs = 0;
//String output = "";
//String input = "";
//String response  = "";
//
//
//void initDisplay(){
//  lcd.begin (16,2);
//  lcd.setCursor(0,0);
//  lcd.print("Cliente");
//  lcd.setCursor(0,0);
//  lcd.print("Iniciando...");
//  delay(3000);
//  lcd.clear();
//}
//
String check_temperature(){
    StaticJsonBuffer<256> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    String temp = "";    
    delay(DHTINTERVAL);
//    hs = analogRead(HIGRO);
    hs = constrain(hs,400,1023);  
    hs = map(hs,400,1023,100,0);
    root["humidade"] = dht.readHumidity();
    root["temperatura"] = dht.readTemperature();
//    root["humidade-solo"] = hs;
    root.printTo(temp);
//    root.prettyPrintTo(Serial);
    return temp;
    
}
//
//void execLora(){
////   while (!loraSerial.available()) {execDisplay("Em espera.","Aguardando "); execDisplay("conexao","...");}
////   while (!loraSerial.available()){;}
//   if (loraSerial.available()) {    
//        // String output = loraSerial.readString(); //receive command  
//        // Serial.println(output);              
////         if (output.substring(0, 17) == "check-temperature") {
////           execDisplay("Recebendo","Comando...");
//           loraSerial.println(check_temperature());
////           execDisplay("Recebendo","Comando...");
////           delay(2000);
////           execDisplay("Enviando","Dados...");
//           delay(3000);                
//         //} 
//   }
//   Serial.println(" Resposta loraSerial:"+loraSerial.available());
//}
//
//
//void execDisplay(String titulo, String texto){
//  //acende o backlight do LCD
//  lcd.setBacklight(HIGH);
//  //posiciona o cursor para escrita
//  lcd.setCursor(0,0);
//  lcd.print(titulo);
//  lcd.setCursor(0,1);
//  lcd.print(texto);
//  delay(2000); //intervalo de 2s
//  lcd.clear();
//}
//
//

//
//void test_lora() {
//  // put your main code here, to run repeatedly:
//  if( Serial.available()){
//     String input = Serial.readString();
//     loraSerial.println(input); 
//  }
//  if( loraSerial.available()){
//     String input = loraSerial.readString();
//     Serial.println(input);  
//  }
//  loraSerial.println("ping client");
//  delay(3000);
//}
//
//
//void setup() {
//  //inicializando comunicacao com a lora
////  dht.begin();
//  initSerialLora();
//  //initDisplay();
////  pinMode(HIGRO, INPUT);
//  pinMode(LED_BUILTIN, OUTPUT);
//  Serial.println("Cliente Iniciando."); 
//}
//
//
//void loop() {
//  digitalWrite(LED_BUILTIN, LOW);   
//  delay(1000);                      
//  digitalWrite(LED_BUILTIN, HIGH); 
//  delay(2000);  
////  execLora();
//  test_lora();
//}



#include <SoftwareSerial.h>
#define TX D5
#define RX D6


SoftwareSerial loraSerial(TX,RX);

void initSerialLora(){
  Serial.begin(9600);
  loraSerial.begin(9600);
  while(!loraSerial){;}
  while(!Serial){;} 
}

void setup() {
  initSerialLora();
  Serial.println("Inicializando a Client");
}

void loop() {
  // put your main code here, to run repeatedly:
  if( Serial.available()){
     String input = Serial.readString();
     loraSerial.println(input);     
  }
  if( loraSerial.available()){
     String input = loraSerial.readString();
     Serial.println(input);  
  }
  loraSerial.println(check_temperature());
  Serial.println(check_temperature());
  delay(1000);
}
