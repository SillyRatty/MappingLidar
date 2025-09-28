/*
 * VL53L0XHandler.hpp
 *
 *  Created on: Sep 27, 2025
 *      Author: ratty
 */

#ifndef VL53L0X_VL53L0XHANDLER_HPP_
#define VL53L0X_VL53L0XHANDLER_HPP_

#include "VL53L0X.hpp"

typedef enum {
    SINGLE_RANGING, CONTINUOUS_RANGING, TIMED_RANGING
} rangingModes_t;

typedef enum {
    DEFAULT_PROFILE, HIGH_SPEED, HIGH_ACCURACY, LONG_RANGE
} rangingProfiles_t;

typedef enum {
    POLLING_MODE, INTERRUPT_MODE
} gpioModes_t;

class VL53L0XHandler{
    public:
        uint8_t deviceAddress;
        I2C_HandleTypeDef *hi2c;
        rangingModes_t rangingMode;
        rangingProfiles_t rangingProfile;
        GPIO_TypeDef *gpioPort; // only used in interrupt mode
        uint16_t gpioPin; // only used in interrupt mode
        gpioModes_t gpioMode;
        GPIO_TypeDef *xshutPort;
        uint16_t xshutPin;

        VL53L0XHandler(I2C_HandleTypeDef *hi2c, GPIO_TypeDef *xshutPort, uint16_t xshutPin);
        void turnOff();
        void turnOn();
        void setDeviceAddress(uint8_t deviceAddress);
        void setDeviceRangingMode(rangingModes_t rangingMode);
        void setDeviceRangingProfile(rangingProfiles_t rangingProfile);
        void readDistance_mm();
    private:
        VL53L0X sensor;
};

#endif /* VL53L0X_VL53L0XHANDLER_HPP_ */
