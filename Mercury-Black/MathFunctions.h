#pragma once

#include <math.h>

float lerp(float position, float target, float amount) {
	return position + ((target - position) * amount);
}