#include <Wire.h>
#include <mlx.h>

mlxInfra mlx = mlxInfra();

double Temperture_room = 0;
double Temperture_obj = 0;
double Temperture_obj_raw = 0;
double Emissivity = 0;
float offset = 0;
uint16_t RawEmissivity = 0;

void setup() {
  Serial.begin(9600);
  mlx.begin();
}

void loop() {

 Temperture_room = mlx.readAmbiantTemp();
 Temperture_obj = mlx.readObjTemp();
 Temperture_obj_raw = mlx.readRawSensorData();
 Emissivity = mlx.readEmissivity();
 RawEmissivity = mlx.readRawEmissivity();

//apply Temperture correction
Temperture_obj = Temperture_obj + offset;

Serial.println("");
Serial.print("Temperature Objet: "); Serial.println(Temperture_obj);
Serial.print("Average body temperture: "); Serial.println(Body_Temperture_average());
Serial.print("Temperature raw: "); Serial.println(Temperture_obj_raw); 
Serial.println("");
Serial.print("Room Temperture: "); Serial.println(Temperture_room);
// Serial.print("Object Emissivity: "); Serial.println(Emissivity);
// Serial.print("raw Emissivity: "); Serial.println(RawEmissivity);

delay(800);
}

float Body_Temperture_average(){
  float t = 0;
  for(int i=0; i<10; i++){
    t = t + Temperture_obj;
  }
  t = t/10;
  //Serial.println(t);
  return t;
}
