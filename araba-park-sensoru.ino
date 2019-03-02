#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Ultrasonic.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
Ultrasonic a_ultrasonic(6, 7); //triggerPin echoPin
Ultrasonic b_ultrasonic(12, 13); //triggerPin echoPin
Ultrasonic c_ultrasonic(4, 5); //triggerPin echoPin
int toplam,a_sensor,b_sensor,c_sensor;
int ledState = LOW;
unsigned long previousMillis = 0;

const long interval = 1000;
byte p20[8] = {
 B10000,
 B10000,
 B10000,
 B10000,
 B10000,
 B10000,
 B10000,
};
byte p40[8] = {
 B11000,
 B11000,
 B11000,
 B11000,
 B11000,
 B11000,
 B11000,
};
byte p60[8] = {
 B11100,
 B11100,
 B11100,
 B11100,
 B11100,
 B11100,
 B11100,
};
byte p80[8] = {
 B11110,
 B11110,
 B11110,
 B11110,
 B11110,
 B11110,
 B11110,
};

byte p100[8] = {
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
 B11111,
};
void setup(){
 Serial.begin(9600);
 pinMode(3, OUTPUT);

 lcd.begin();
 lcd.setBacklight((uint8_t)1);
 lcd.print("HOSGELDINIZ");
 lcd.setCursor(0,1);
 lcd.print("BEKLEYINIZ");

 delay(1000);
 //Make progress characters
 lcd.createChar(0, p20);
 lcd.createChar(1, p40);
 lcd.createChar(2, p60);
 lcd.createChar(3, p80);
 lcd.createChar(4, p100);
 lcd.clear();
}
void loop(){
 unsigned long currentMillis = millis();

 a_sensor = a_ultrasonic.read(CM);
 b_sensor = b_ultrasonic.read(CM);
 c_sensor = c_ultrasonic.read(CM);

 if(a_sensor>100){a_sensor=200;}
 if(b_sensor>100){b_sensor=200;}

 if(c_sensor>100){c_sensor=200;}

 toplam=a_sensor+b_sensor+c_sensor;
 toplam=toplam/3;
 seviye((toplam*16)/200);

 lcd.setCursor(0,1);
 lcd.print(" ");
 lcd.setCursor(0,1);
 lcd.print(String(a_sensor));
 lcd.setCursor(7,1);
 lcd.print(String(b_sensor));
 lcd.setCursor(13,1);
 lcd.print(String(c_sensor));
 if(a_sensor<50){
 if (currentMillis - previousMillis >= toplam) {
 previousMillis = currentMillis;

 if (ledState == LOW) {
 ledState = HIGH;
 } else {
 ledState = LOW;
 }
 if(toplam<5){digitalWrite(3, HIGH);}
 digitalWrite(3, ledState);
 }
 }else if(b_sensor<50){
 if (currentMillis - previousMillis >= toplam) {
 previousMillis = currentMillis;
 if (ledState == LOW) {
 ledState = HIGH;
 } else {
 ledState = LOW;
 }
 if(toplam<5){digitalWrite(3, HIGH);}

 digitalWrite(3, ledState);
 }}else if(c_sensor<50){
 if (currentMillis - previousMillis >= toplam) {
 previousMillis = currentMillis;
 if (ledState == LOW) {
 ledState = HIGH;
 } else {
 ledState = LOW;
 }
 if(toplam<5){digitalWrite(3, HIGH);}
 digitalWrite(3, ledState);
 }
 }else{digitalWrite(3, LOW);}

}
void seviye (int seviye){
 lcd.setCursor(0,0);
 lcd.print(" ");

for (int i = 0; i<seviye; i++){
 for (int j=0; j<5; j++){
 lcd.setCursor(i, 0);
 lcd.write(j);
 }
 }
}
