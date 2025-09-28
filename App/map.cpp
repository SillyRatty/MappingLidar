/*
 * map.cpp
 *
 *  Created on: Sep 28, 2025
 *      Author: ratty
 */

#include "map.hpp"

float map(float value, float fromMin, float fromMax, float toMin, float toMax){
    return (value - fromMin) * (toMax - toMin) / (fromMax - fromMin) + toMin;
}
