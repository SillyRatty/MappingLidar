/*
 * VL53L0XHandler.hpp
 *
 *  Created on: Sep 27, 2025
 *      Author: ratty
 */

#ifndef VL53L0X_VL53L0XHANDLER_HPP_
#define VL53L0X_VL53L0XHANDLER_HPP_

#include "vl53l0x_api.h"

typedef enum {
    SINGLE_RANGING,
    CONTINUOUS_RANGING,
    TIMED_RANGING
} rangingModes_t;

typedef enum {
    DEFAULT_PROFILE,
    HIGH_SPEED,
    HIGH_ACCURACY,
    LONG_RANGE
} rangingProfiles_t;

typedef enum {
    POLLING_MODE,
    INTERRUPT_MODE
} gpioModes_t;

class VL53L0XHandler{
    public:
        uint8_t deviceAddress = 0x52;
        I2C_HandleTypeDef *hi2c = NULL;
        rangingModes_t rangingMode = SINGLE_RANGING;
        rangingProfiles_t rangingProfile = DEFAULT_PROFILE;
        GPIO_TypeDef *gpioPort = NULL; // only used in interrupt mode
        uint16_t gpioPin = 0; // only used in interrupt mode
        gpioModes_t gpioMode = POLLING_MODE;
        GPIO_TypeDef *xshutPort = NULL;
        uint16_t xshutPin = 0;

        VL53L0XHandler(I2C_HandleTypeDef *hi2c, GPIO_TypeDef *xshutPort, uint16_t xshutPin);
        VL53L0XHandler(I2C_HandleTypeDef *hi2c, GPIO_TypeDef *xshutPort, uint16_t xshutPin, GPIO_TypeDef *gpioPort, uint16_t gpioPin);
        void turnOff();
        void turnOn();
        void setDeviceAddress(uint8_t deviceAddress);
        void setDeviceRangingMode(rangingModes_t rangingMode);
        void setDeviceRangingProfile(rangingProfiles_t rangingProfile);
        uint16_t readDistance_mm();
    private:
        bool initialized = false;
        VL53L0X_Dev_t apiDev;
        VL53L0X_RangingMeasurementData_t apiMeasurement;
        uint32_t refSpadCount;
        uint8_t isApertureSpads;
        uint8_t VhvSettings;
        uint8_t PhaseCal;

        bool apiInit();
};

#endif /* VL53L0X_VL53L0XHANDLER_HPP_ */
