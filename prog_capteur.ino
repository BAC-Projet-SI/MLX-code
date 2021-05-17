#include <Wire.h>
#include <mlx.h>

#define trigPin 3
#define echoPin 2
#define numReading 10
#define potentiometer 0
mlxInfra mlx = mlxInfra();

const String location = "Default";
double distance;
double minDist = 10;
double Temperture_room = 0;
double Temperture_obj = 0;
float offset = 6;


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(potentiometer, INPUT);
  Serial.begin(9600);
  mlx.begin();
  Serial.println("Setup done");
}

void loop() {

 Temperture_room = mlx.readAmbiantTemp();
 Temperture_obj = mlx.readObjTemp();

//an offset is needed for humain temperture as the inside temperture is quite different from the surface temperture
Temperture_obj = Temperture_obj + offset;

// send to the API that there is no more gel in stock and that it need a refil
if(IsEmpty()){
  //Send to the API
}

// stop the program from running if theres nobody there
while (DistanceFromUser() > minDist){
  
  Serial.println("L'utilisateur est trop loin !");
  delay(800);

}

if(Body_Temperture_average() > 37)
{
  Send_ToAPI();
  Serial.println("/!\\ Temperature trop élevé !");
}
else
{
  Serial.println("");
  Serial.print("Temperature Objet: "); Serial.println(Body_Temperture_average());
}

delay(800);
}

// calculate the temperture average over multiple mesurements to avoid errors
double Body_Temperture_average(){
  double tempReading = 0;
  double average = 0;
  for(int i = 0; i <= numReading; i++){
    tempReading = tempReading + Temperture_obj;
    delay(1);
  }
  average = tempReading / numReading;
  return average;
}

//calculate the distance btw the user and the ultrasonic sensor
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

//check if the gel container is empty
bool IsEmpty() {
  int _distance = 0;
  _distance = analogRead(potentiometer);

  if(_distance < 80){
    return true;
  }else {
    return false;
  }
}

//send HTTP request to the API
void Send_ToAPI(){

}