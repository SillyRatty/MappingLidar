/*
 * app.cpp
 *
 *  Created on: Sep 27, 2025
 *      Author: ratty
 */

#include "app.hpp"
#include "VL53L0X/VL53L0X.hpp"
#include "MPU6050/MPU6050.hpp"

//#define LONG_RANGE
#define HIGH_SPEED

VL53L0X distanceSensor(&hi2c1);
MPU6050 gyroscope;

void APP_Init(void){
//    distanceSensor.setTimeout(500);
//    if(!distanceSensor.init(true)){
//        while(1){
//        }
//    }
//
//#if defined LONG_RANGE
//      // lower the return signal rate limit (default is 0.25 MCPS)
//      distanceSensor.setSignalRateLimit(0.1);
//      // increase laser pulse periods (defaults are 14 and 10 PCLKs)
//      distanceSensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
//      distanceSensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
//#endif
//
//#if defined HIGH_SPEED
//    // reduce timing budget to 20 ms (default is about 33 ms)
//    distanceSensor.setMeasurementTimingBudget(20000);
//#elif defined HIGH_ACCURACY
//      // increase timing budget to 200 ms
//      distanceSensor.setMeasurementTimingBudget(200000);
//#endif
//    distanceSensor.startContinuous();

    gyroscope.initialize();
}

uint16_t read = 0;
void APP_Loop(void){
}
