
#ifndef _UNIT_ENCODER_H_
#define _UNIT_ENCODER_H_

#include <Arduino.h>
#include <Wire.h>

class M5_Encoder
{
private:
    uint8_t _addr = 0x40;
    void writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);
    void readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);
    TwoWire &_wire;
    int16_t _value;
    int16_t _change;
    uint8_t _buttonState;
    void setLEDColor(uint8_t index, uint8_t r, uint8_t g, uint8_t b);
public:
    M5_Encoder(TwoWire &wire = Wire, uint8_t addr = 0x40) : _wire(wire)
    {
        _addr = _addr;
    }
    void begin();
    void update();
    int16_t getEncoderRotation();
    int16_t getEncoderChange();
    uint8_t getButtonState();
    
    void setLEDColorBoth(uint8_t r, uint8_t g, uint8_t b);
    void setLEDColorLeft(uint8_t r, uint8_t g, uint8_t b);
    void setLEDColorRight(uint8_t r, uint8_t g, uint8_t b);

    void setWorkMode(uint8_t mode);
};

#endif
