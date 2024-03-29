#ifndef mlx_h
#define mlx_h
#endif

#include "Arduino.h"
#include "Wire.h"

/*
I2C lib read and write w/ A5 & A4 pins.
A4 = SDA (data pin)
A5 = SCL (clock line)
https://www.pololu.com/file/0J171/MLX90614_SMBus.pdf
*/
#define I2CADDR 0x5A

//le capteur a deux memoire l'EEPROM et la RAM

//EEPROM (valeurs accessibles a l'ecriture commencent a 0x20 !)
#define EmissivityByte 0x24 //defaut 0xFFFF 

//RAM registers (ne peux pas ecrire sur la ram, adresses en lecture seule)
#define Ambiantbyte 0x06
#define TObj1 0x07
#define TObj2 0x08 //pas implementer sur ce modéle de capteur

#define IRdata1 0x4
#define IRdata2 0x5 //pas implementer sur ce modéle de capteur

class mlxInfra {
public:
    mlxInfra(uint8_t addr = I2CADDR);
    bool begin();

    double readObjTemp(void);
    double readObjTemp2(void);
    double readRawSensorData(void);
    double readAmbiantTemp(void);
    double readEmissivity(void);
    double readRawEmissivity(void);
    void writeEmissivity(double emissivity);

private:
    float readTemp(uint8_t reg);

    byte crc8(byte *addr, byte len);
    uint16_t read16(uint8_t addr);
    uint8_t _addr;
    void write16(uint8_t addr, uint16_t data);
};

/* differentiel de temperature entre capteurs.

32 -> 36.2

*/
