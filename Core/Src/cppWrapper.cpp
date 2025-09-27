/*
 * cppTest.cpp
 *
 *  Created on: Sep 27, 2025
 *      Author: ratty
 */

#include "main.h"
#include "cppWrapper.hpp"
#include "app.hpp"

void cppLoop(){
    APP_Init();
    while(1){
        APP_Loop();
    }
}

extern "C" {

void cLoop(){
    cppLoop();
}

}
