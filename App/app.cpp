/*
 * app.cpp
 *
 *  Created on: Sep 27, 2025
 *      Author: ratty
 */

#include "app.hpp"
#include "VL53L0X/VL53L0X.hpp"

//#define LONG_RANGE
#define HIGH_SPEED

VL53L0X sensor(&hi2c1);

void APP_Init(void){
    sensor.setTimeout(500);
    if(!sensor.init(true)){
        while(1){
        }
    }

#if defined LONG_RANGE
      // lower the return signal rate limit (default is 0.25 MCPS)
      sensor.setSignalRateLimit(0.1);
      // increase laser pulse periods (defaults are 14 and 10 PCLKs)
      sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
      sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
#endif

#if defined HIGH_SPEED
    // reduce timing budget to 20 ms (default is about 33 ms)
    sensor.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
      // increase timing budget to 200 ms
      sensor.setMeasurementTimingBudget(200000);
#endif
    sensor.startContinuous();
}

uint16_t read = 0;
void APP_Loop(void){
    read = sensor.readRangeContinuousMillimeters();
    if(read < 1200){ // maximo do sensor
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
    }
    else{
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
    }
//    HAL_Delay(50);
}
