#include <SoftwareSerial.h>;
#include <math.h>;

int bluetoothTx = 4;
int bluetoothRx = 2;

unsigned int MOTOR2_PIN1 = 3;
unsigned int MOTOR2_PIN2 = 5;
unsigned int MOTOR1_PIN1 = 6;
unsigned int MOTOR1_PIN2 = 9;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

const int pinTemperatura = A0;
const int pinUmiditate = A3;
const int pinLuminozitate = A4;
const double distanta = 29.5;
const int grade = 40;

int recive;
int g=0;
double fx=0;
double fy=0;

void setup(){

  Serial.begin(9600);
  bluetooth.begin(115200);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("U,9600,N");
  bluetooth.begin(9600);

}

void loop() {
  recive=0;
  if (bluetooth.available())
  {
    recive = bluetooth.read();
    float d = 0;
    if (recive == 49) // inainte
    {
      go(170, 142);
      delay(600);
      d = distanta;
    }
    else if (recive == 50) //inapoi
    {
      go(-170 , -170);
      delay(600);
      d = -distanta;
    }
    else if (recive == 52) //dreapta
    {
      go(170, -155);
      delay(300);
      if((g+grade)>=360){
        g=(g+grade)-360;
      }
      else
        g += grade;
    }
    else if (recive == 51) //stanga
    {
      go(-170, 155);
      delay(300);
      if(g-grade<0)
        g=g-grade+360;
      else
        g -= grade;
    }
    else if(recive == 54)
    returnto00(g , fx , fy);
    go(0, 0);
    if(d!=0){
      calcxy(d , g);
    }
  }
  float T = citesteTempInCelsius(23);
  float U = citesteUmid();
  float L = citesteLum();
  Serial.print(T);
  Serial.print(" ");
  Serial.print(U);
  Serial.print(" ");
  Serial.print(L);
  Serial.print(" ");
  Serial.print(fx);
  Serial.print(":");
  Serial.print(fy);
  Serial.print(" ");
  Serial.print(g);
  Serial.println();
  if(recive!=0)
  Serial.println(recive);
}

void calcxy(int dist , double deg){
  double x=0, y=0;
  if(deg>=0 && deg<90){
     x=1;
     y=-1;
  }
  else if(deg>=90 && deg<180){
     x=-1;
     y=-1;
  }
  else if(deg>=180 && deg<270){
     x=-1;
     y=1;
  }
  else if(deg>=270 && deg<=360){
    x=1;
    y=1;
  }
  if(dist<0){
    x*=-1;
    y*=-1;
  }
  double rez = sin(deg * 0.0174532925);
  y *= rez * dist;
  x *= sqrt((dist * dist) - (y * y));
  fy+=y;
  fx+=x;
}

void returnto00(int orientare , double coordonatax , double coordonatay){
  double gperms=40/300;
  double march=sqrt((coordonatax*coordonatax)+(coordonatay*coordonatay));
  double cmperms=29.5/600;
  double sinalpha=coordonatay/march;
  double arch=asin(sinalpha);
  int cadran=0;
  double a=coordonatax;
  double b=coordonatay;
  if(a>0 && b>0)
    cadran=4;
  else if(a<0 && b>0)
    cadran=3;
  else if(a<0 && b<0)
    cadran=2;
  else if(a>0 && b<0)
    cadran=1;
  else 
    cadran=5;
  double time;
  if(cadran==1){
    if(orientare<arch)
      orientare+=360;
    double time = (orientare-arch)/gperms;
  }
  else if(cadran==2){
    arch=180-arch;
    if(orientare<arch)
      orientare+=360;
    double time = (orientare-arch)/gperms;
  }
  else if(cadran==3){
    if(orientare<(arch+180))
      double time = (orientare+180-arch)/gperms;
    else 
      double time = (orientare-180-arch)/gperms;
  }
  else if(cadran==4){
    if(orientare>(360-arch))
      double time = (orientare-360+arch)/gperms;
    else 
      double time = (orientare+arch)/gperms;
  }
  else if(cadran==5){
    double time = orientare/gperms;
  }
  go(-170, 155);
  delay(time);
  go(0, 0);
  time = march/cmperms;
  go(-170, -170);
  delay(time);
  go(0, 0);
  fy=0;
  fx=0;
}

void go(int speedLeft, int speedRight)
{
  if (speedLeft > 0)
  {
    analogWrite(MOTOR1_PIN1, speedLeft);
    analogWrite(MOTOR1_PIN2, 0);
  }
  else
  {
    analogWrite(MOTOR1_PIN1, 0);
    analogWrite(MOTOR1_PIN2, -speedLeft);
  }

  if (speedRight > 0)
  {
    analogWrite(MOTOR2_PIN1, speedRight);
    analogWrite(MOTOR2_PIN2, 0);
  }
  else
  {
    analogWrite(MOTOR2_PIN1, 0);
    analogWrite(MOTOR2_PIN2, -speedRight);
  }
}

float citesteTempInCelsius(int count)
{
  float temperaturaMediata = 0;
  float sumaTemperatura = 0;
  for (int i = 0; i < 20; i++) {
    delay(2);
    int reading = analogRead(pinTemperatura);
    float voltage = reading * 5.0;
    voltage /= 1024.0;
    float temperatureCelsius = (voltage - 0.5) * 100 ;
    sumaTemperatura = sumaTemperatura + temperatureCelsius;
  }
  return sumaTemperatura / (float)count + 1;
}

float citesteLum()
{
  float nivel;
  float nivelLum;

  for (int i = 0; i < 20; ++i)
  {
    delay(2);
    nivel = analogRead(pinLuminozitate);
    nivelLum += nivel / 10.24;
  }
  return nivelLum /= (float)20;
}

float citesteUmid()
{
  float nivelU;
  float nivelUmiditate;

  for (int i = 0; i < 20; ++i)
  {
    delay(2);
    nivelU = analogRead(pinUmiditate);
    //nivelUmiditate += 100 - nivelU/10.24;
    nivelUmiditate += 130 - nivelU / 10.24;
  }
  return nivelUmiditate /= (float)20;
}

