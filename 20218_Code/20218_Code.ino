#include "hx711.h"
#define DOUT  A5
#define SCK  A1
Hx711 scale( DOUT, SCK);
int triglength = 9;
int echolength = 8;
int trigwidth = 12;
int echowidth = 11;
int buzzer = A0;
int ledred = 10;
int ledblue = 13;
int tmp = A2;
int heat_pin= A4;
int ENA_pin1 = 6;
int motor1pin1 = 2;
int motor1pin2 = 3;
int motor2pin1 = 4;
int motor2pin2 = 5;
long duration;
int distanceCm;
float temp;
int L;
int W;
int ThermistorPin = 0;
int Vo;
float R1 = 120;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
Serial.begin(9600);
pinMode(triglength, OUTPUT);
pinMode(echolength, INPUT);
pinMode(trigwidth, OUTPUT);
pinMode(echowidth, INPUT);
pinMode(buzzer, OUTPUT);
pinMode(ledred, OUTPUT);
pinMode(ledblue, OUTPUT);
pinMode(motor1pin1, OUTPUT);
pinMode(motor1pin2, OUTPUT);
pinMode(motor2pin1, OUTPUT);
pinMode(motor2pin2, OUTPUT);
pinMode(ENA_pin1, OUTPUT);
pinMode(heat_pin, OUTPUT);
Serial.println("Length:"); 
Serial.println(L);
Serial.println("Width:");
Serial.println(W);
delay(3000);

}

void loop() {
  motor_start();

Serial.print(scale.getGram(), 1);
Serial.println("g");
if ((scale.getGram(), 1) == 0.025 && (scale.getGram(), 1) == 0.035) {
    Serial.print(scale.getGram(), 1);
    Serial.println("meet design requiremnt");
    Serial.println("g");
    digitalWrite(buzzer, LOW);
    digitalWrite(ledblue,HIGH);
    digitalWrite(ledred, LOW);
  }
else {
  Serial.print(scale.getGram(), 1);
  Serial.println("Over weighted");
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledred, HIGH);
  digitalWrite(ledblue, LOW);
  tone(buzzer, 400);
}  
temp = analogRead(tmp);
temp = temp * 0.48828125;
digitalWrite(triglength, LOW);
delayMicroseconds(2);
digitalWrite(triglength, HIGH);
delayMicroseconds(10);
digitalWrite(triglength, LOW);
digitalWrite(trigwidth, LOW);
delayMicroseconds(2);
digitalWrite(trigwidth, HIGH);
delayMicroseconds(10);
digitalWrite(trigwidth, LOW);
duration = pulseIn(echolength, HIGH);
duration = pulseIn(echowidth, HIGH);
distanceCm= duration*0.034/2;
L=180-distanceCm;
W=180-distanceCm;

delay(300);
Serial.println("Set 0:"); 
Serial.println(L); 
Serial.println(W);
Serial.println("centimeter");
delay(300);
if(L>=6 && L<=6.5)
{
   Serial.println("Length:");
   Serial.println(L);
   Serial.println("cm");
   digitalWrite(buzzer,LOW);
   digitalWrite(ledblue, HIGH);
   digitalWrite(ledred,LOW);
   delay(300);
   
}
else {
  Serial.println("Doesn't exist in the design requirments");
  Serial.println(L);
  Serial.println("cm");
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledred, HIGH);
  digitalWrite(ledblue, LOW);
  tone(buzzer, 400);
  delay(300);
}
if(W>=3 && W<=3.5)
{
   Serial.println("width:");
   Serial.println(W);
   Serial.println("cm");
   digitalWrite(buzzer, LOW);
   digitalWrite(ledblue, HIGH);
   digitalWrite(ledred, LOW);
   delay(300);
   
}
else {
  Serial.println("Doesn't exist in the design requirments");
  Serial.println(W);
  Serial.println("cm");
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledred, HIGH);
  digitalWrite(ledblue, LOW);
  tone(buzzer, 400);
  delay(300);
}
if(temp >= 35){
  
  Serial.print("TEMPRATURE = ");
  Serial.print(temp);
  Serial.print(" Celcius");
  Serial.println();
  digitalWrite(ledred, HIGH);
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledblue, LOW);
  tone(buzzer,400);
  delay(300);
}
else {
  Serial.print("TEMPRATURE = ");
  Serial.print(temp);
  Serial.print(" Celcius");
  Serial.println();
  digitalWrite(ledblue, HIGH);
  digitalWrite(buzzer, LOW);
  digitalWrite(ledred, LOW);
  delay(300);  
}
}
void motor_start(){
  
analogWrite(ENA_pin1, 200 );   
digitalWrite(motor1pin1, HIGH );
digitalWrite(motor1pin2, LOW);
digitalWrite(motor2pin1, HIGH);
digitalWrite(motor2pin2, LOW);
Serial.println("MOTOR STAR "); 
   
delay (100);
}
void motor_stop(){
    
digitalWrite(motor1pin1, LOW );
digitalWrite(motor1pin2, LOW);
digitalWrite(motor2pin1, LOW);
digitalWrite(motor2pin2, LOW);
analogWrite(ENA_pin1, 0 ); 
Serial.println("MOTOR STOP "); 
delay (100);
}
void temp_2 (){

Vo = analogRead(ThermistorPin);
R2 = R1 * (1023.0 / (float)Vo - 1.0);
logR2 = log(R2);
T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
Tc = T - 273.15;
Serial.print("Temperature: "); 
Serial.print(Tc);
Serial.println(" C");  
if (Tc ==350) {
    digitalWrite(heat_pin, LOW );
  }
else {
    digitalWrite(heat_pin, HIGH );
  }
delay(1000);
}          
