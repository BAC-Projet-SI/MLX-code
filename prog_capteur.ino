#include <Wire.h>
#include <mlx.h>

#define trigPin 3
#define echoPin 2

mlxInfra mlx = mlxInfra();

double distance;
double minDist = 10;
double Temperture_room = 0;
double Temperture_obj = 0;
float offset = 6;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
  mlx.begin();
  Serial.println("Setup done");
}

void loop() {

 Temperture_room = mlx.readAmbiantTemp();
 Temperture_obj = mlx.readObjTemp();

//apply Temperture correction
Temperture_obj = Temperture_obj + offset;

while (DistanceFromUser() > minDist){
  //Serial.println(DistanceFromUser());
  Serial.println("L'utilisateur est trop loin !");
  delay(800);
}

Serial.println("");
Serial.print("Temperature Objet: "); Serial.println(Temperture_obj);
delay(800);

//if(mlx.readObjTemp() >= 482.19 || mlx.readObjTemp() >=-300){
  //Serial.println("Error");
  //return setup();
//}

}

float Body_Temperture_average(){
  float t = 0;
  for(int i=0; i<10; i++){
    t = t + Temperture_obj;
    delay(20);
  }
  t = t/10;
  //Serial.println(t);
  return t;
}

double DistanceFromUser(){
  long duration;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}
