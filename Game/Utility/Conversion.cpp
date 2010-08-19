#include "Conversion.h"

Conversion::Conversion() {
}

float Conversion::to_degres(float angle) {
    return angle * 180 / PI;
}

float Conversion::to_radian(float angle) {
    return angle * PI / 180;
}


