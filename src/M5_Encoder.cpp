#include "M5_Encoder.h"


#define MODE_REG     0x00
#define ENCODER_REG  0x10
#define BUTTON_REG   0x20
#define RGB_LED_REG  0x30

/*! @brief Initialize the Encoder. */
void M5_Encoder::begin() {

}

/*! @brief Write a certain length of data to the specified register address. */
void M5_Encoder::writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                              uint8_t length) {
    _wire.beginTransmission(addr);
    _wire.write(reg);
    for (int i = 0; i < length; i++) {
        _wire.write(*(buffer + i));
    }
    _wire.endTransmission();
}

/*! @brief Read a certain length of data to the specified register address. */
void M5_Encoder::readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                             uint8_t length) {
    uint8_t index = 0;
    _wire.beginTransmission(addr);
    _wire.write(reg);
    _wire.endTransmission();
    _wire.requestFrom(addr, length);
    for (int i = 0; i < length; i++) {
        buffer[index++] = _wire.read();
    }
}



void M5_Encoder::update() {
    // Read encoder value
    int16_t previous = _value;
    uint8_t data[2];
    readBytes(_addr, ENCODER_REG, data, 2);
    _value = (int16_t)((data[0]) | (data[1]) << 8);
    _change = _value - previous;
    // Read button state
    readBytes(_addr, BUTTON_REG, &_buttonState, 1);
}

/*! @brief Read the encoder rotation.
    @return The value of the encoder that was read */
int16_t M5_Encoder::getEncoderRotation() {
    return _value;
}

int16_t M5_Encoder::getEncoderChange() {

    return _change;
}

/*! @brief Get the current status of the rotary encoder keys.
    @return 1 if the set was press, otherwise 0.. */
uint8_t M5_Encoder::getButtonState() {
    return _buttonState;
}

/*! @brief Set the color of the LED (3 values). */
void M5_Encoder::setLEDColor(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
    uint8_t data[4];
    data[3] = b;
    data[2] = g;
    data[1] = r;
    data[0] = index;
    writeBytes(_addr, RGB_LED_REG, data, 4);
}

    void M5_Encoder::setLEDColorBoth(uint8_t r, uint8_t g, uint8_t b) {
        setLEDColor(0, r, g, b) ;
    }
    void M5_Encoder::setLEDColorLeft(uint8_t r, uint8_t g, uint8_t b) {
        setLEDColor(1, r, g, b) ;
    }
    void M5_Encoder::setLEDColorRight(uint8_t r, uint8_t g, uint8_t b) {
        setLEDColor(2, r, g, b) ;
    }


void M5_Encoder::setWorkMode(uint8_t mode)
{
    writeBytes(_addr, MODE_REG, &mode, 1);
}
