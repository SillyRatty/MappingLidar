/*
 * VL53L0XHandler.cpp
 *
 *  Created on: Oct 2, 2025
 *      Author: ratty
 */

#include "VL53L0XHandler.hpp"

VL53L0XHandler::VL53L0XHandler(I2C_HandleTypeDef *hi2c, GPIO_TypeDef *xshutPort, uint16_t xshutPin){
    this->hi2c = hi2c;
    this->xshutPort = xshutPort;
    this->xshutPin = xshutPin;

    this->apiDev.I2cHandle = this->hi2c;
    this->apiDev.I2cDevAddr = this->deviceAddress;
}

VL53L0XHandler::VL53L0XHandler(I2C_HandleTypeDef *hi2c, GPIO_TypeDef *xshutPort, uint16_t xshutPin, GPIO_TypeDef *gpioPort, uint16_t gpioPin){
    this->hi2c = hi2c;
    this->xshutPort = xshutPort;
    this->xshutPin = xshutPin;
    this->gpioPort = gpioPort;
    this->gpioPin = gpioPin;

    this->apiDev.I2cHandle = this->hi2c;
    this->apiDev.I2cDevAddr = this->deviceAddress;
}

void VL53L0XHandler::turnOff(){
    HAL_GPIO_WritePin(this->xshutPort, this->xshutPin, GPIO_PIN_RESET);
}
void VL53L0XHandler::turnOn(){
    HAL_GPIO_WritePin(this->xshutPort, this->xshutPin, GPIO_PIN_SET);
}

void VL53L0XHandler::setDeviceAddress(uint8_t deviceAddress){
    if(!this->initialized){
        return;
    }
    this->deviceAddress = deviceAddress;
    this->apiDev.I2cDevAddr = this->deviceAddress;
}

void VL53L0XHandler::setDeviceRangingMode(rangingModes_t rangingMode){
    if(!this->initialized){
        return;
    }
}

void VL53L0XHandler::setDeviceRangingProfile(rangingProfiles_t rangingProfile){
    if(!this->initialized){
        return;
    }
}

void VL53L0XHandler::readDistance_mm(){
    if(!this->initialized){
        return;
    }
}

bool VL53L0XHandler::apiInit(){
    // Reset the sensor
    this->turnOff();
    HAL_Delay(20);
    this->turnOn();
    HAL_Delay(20);

    // VL53L0X init for Single Measurement

    VL53L0X_Error status = VL53L0X_ERROR_NONE;
    status = VL53L0X_WaitDeviceBooted(&this->apiDev);
    if(status != VL53L0X_ERROR_NONE){
        return false;
    }

    status = VL53L0X_DataInit(&this->apiDev);
    if(status != VL53L0X_ERROR_NONE){
        return false;
    }

    status = VL53L0X_StaticInit(&this->apiDev);
    if(status != VL53L0X_ERROR_NONE){
        return false;
    }

    status = VL53L0X_PerformRefCalibration(&this->apiDev, &this->VhvSettings, &PhaseCal);
    if(status != VL53L0X_ERROR_NONE){
        return false;
    }

    status = VL53L0X_PerformRefSpadManagement(&this->apiDev, &refSpadCount, &isApertureSpads);
    if(status != VL53L0X_ERROR_NONE){
        return false;
    }

    switch(this->rangingMode){
        case SINGLE_RANGING:
            status = VL53L0X_SetDeviceMode(&this->apiDev, VL53L0X_DEVICEMODE_SINGLE_RANGING);
            break;
        case CONTINUOUS_RANGING:
            status = VL53L0X_SetDeviceMode(&this->apiDev, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);
            break;
        case TIMED_RANGING:
            status = VL53L0X_SetDeviceMode(&this->apiDev, VL53L0X_DEVICEMODE_CONTINUOUS_TIMED_RANGING);
            break;
        default:
            return false;
    }
    if(status != VL53L0X_ERROR_NONE){
        return false;
    }

    // Enable/Disable Sigma and Signal checkRANGING
    status = VL53L0X_SetLimitCheckEnable(&this->apiDev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1);
    if(status != VL53L0X_ERROR_NONE){
        return false;
    }

    status = VL53L0X_SetLimitCheckEnable(&this->apiDev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1);
    if(status != VL53L0X_ERROR_NONE){
        return false;
    }

    status = VL53L0X_SetLimitCheckValue(&this->apiDev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, (FixPoint1616_t) (0.1 * 65536));
    if(status != VL53L0X_ERROR_NONE){
        return false;
    }

    status = VL53L0X_SetLimitCheckValue(&this->apiDev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, (FixPoint1616_t) (60 * 65536));
    if(status != VL53L0X_ERROR_NONE){
        return false;
    }

    status = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(&this->apiDev, 33000);
    if(status != VL53L0X_ERROR_NONE){
        return false;
    }

    status = VL53L0X_SetVcselPulsePeriod(&this->apiDev, VL53L0X_VCSEL_PERIOD_PRE_RANGE, 18);
    if(status != VL53L0X_ERROR_NONE){
        return false;
    }

    status = VL53L0X_SetVcselPulsePeriod(&this->apiDev, VL53L0X_VCSEL_PERIOD_FINAL_RANGE, 14);
    if(status != VL53L0X_ERROR_NONE){
        return false;
    }

    this->initialized = true;
    return true;
}
