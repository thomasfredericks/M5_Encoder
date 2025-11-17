
#ifndef _UNIT_ENCODER_H_
#define _UNIT_ENCODER_H_

#include "Arduino.h"


class Unit_Encoder {
private:
    uint8_t _addr;
    TwoWire* _wire;
    uint8_t _scl;
    uint8_t _sda;
    uint32_t _speed;
    void writeBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);
    void readBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);

public:
    void begin(TwoWire* wire = &Wire, uint8_t addr = 0x40, uint8_t sda = SDA, uint8_t scl = SCL,
               uint32_t speed = 200000L);
    signed short int getEncoderValue();
    bool getButtonStatus();
    void setLEDColor(uint8_t index, uint32_t color);
    void setWorkMode(uint8_t mode);
};

#endif
