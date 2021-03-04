#include "mlx.h"

mlxInfra::mlxInfra(uint8_t i2caddr) { _addr = i2caddr; }

//Begin I2C
bool mlxInfra::begin(void){
    Wire.begin();
    return true;
}

double mlxInfra::readObjTemp(void){
    return readTemp(TObj1);
}

double mlxInfra::readObjTemp2(void){
    return readTemp(TObj2);
}

double mlxInfra::readAmbiantTemp(void){
    return readTemp(Ambiantbyte);
}

double mlxInfra::readEmissivity(void){
    uint16_t ereg = read16(EmissivityByte);
    return ((double)ereg) / 65535.0;
}

double mlxInfra::readRawEmissivity(void){
    return read16(EmissivityByte);
}

double mlxInfra::readRawSensorData(void){
    return read16(IRdata1);
}

void mlxInfra::writeEmissivity(double emissivity){
    uint16_t ereg = (uint16_t)(0xffff * emissivity); // convertion de double a uint16 x 0xffff

    write16(EmissivityByte, 0); // reset en envoyant 0
    delay(10);
    write16(EmissivityByte, ereg);
    delay(10);
}

// transform temperture from kelvin to celcius
float mlxInfra::readTemp(uint8_t reg) {
    float temp;
    temp = read16(reg);
    temp *= .02;
    temp -= 273.15;
    return temp;
}

uint16_t mlxInfra::read16(uint8_t a){
    uint16_t returnval;

    Wire.beginTransmission(_addr);
    Wire.write(a); //send address to read from
    Wire.endTransmission(false);

    Wire.requestFrom(_addr, (size_t)3);
    returnval = Wire.read();
    returnval |= Wire.read() << 8;

    uint8_t pec = Wire.read();
    return returnval;
}

byte mlxInfra::crc8(byte *addr, byte len){
    byte crc = 0;
    while (len--){
        byte inbyte = *addr++;
        for (byte i = 8; i; i--){
            byte carry = (crc ^ inbyte) & 0x80;
            crc <<=1;
            if (carry)
                crc ^= 0x7;
            inbyte <<= 1;
        }
    }
    return crc;
}

void mlxInfra::write16(uint8_t a, uint16_t v) {
  uint8_t pec;
  uint8_t pecbuf[4];

  pecbuf[0] = _addr << 1;
  pecbuf[1] = a;
  pecbuf[2] = v & 0xff;
  pecbuf[3] = v >> 8;
  pec = crc8(pecbuf, sizeof pecbuf);

  Wire.beginTransmission(_addr); // start transmission to device
  Wire.write(a);                 // sends register address to write
  Wire.write(v & 0xff);          // lo
  Wire.write(v >> 8);            // hi
  Wire.write(pec);               // pec
  Wire.endTransmission(true);    // end transmission
}


