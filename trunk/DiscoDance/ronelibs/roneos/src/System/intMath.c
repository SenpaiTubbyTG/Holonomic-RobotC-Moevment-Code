/**
 * @file intMath.c
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "roneos.h"

#include "intMathTrigLookup.c"

/**
 * @brief Continually decrements the input value by one until it is closest to zero.
 *
 * @param val the value to be decremented
 * @returns the decremented value (within the range of 0 <= val < 1)
 */
uint32 decToZero(uint32 val) {
	if (val > 0) {
		val--;
	}
	return(val);
}

/**
 * @brief Circularly increments the index by 1.
 *
 * Increments the index by 1. Resets index to 0 if it exceeds the maximum index
 * Circular meaning it goes back to 0.
 * @param index is the index to be incremented
 * @param maxIndex is the maximum index
 * @returns the incremented circular index
 */
uint32 circularInc(uint32 index, uint32 maxIndex) {
	index++;
	if (index > maxIndex) {
		index = 0;
	}
	return index;
}

/**
 * @brief Circularly decrements the index by 1.
 *
 * Decrements the index by 1. If the index reaches 0, resets it to maximum index.
 * Circular meaning it goes back to maximum index.
 * @param index the index to be decremented
 * @param maxIndex the maximum index
 * @returns the decremented circular index
 */
uint32 circularDec(uint32 index, uint32 maxIndex) {
	if (index == 0) {
		index = maxIndex;
	}
	else {
		index--;
	}
	return index;
}

/**
 *	@brief Compute the integer square root of a number.
 *
 *	Based on Microchip app note TB040.
 *	Can't take the root of numbers higher than MAX_INT32.
 *	@param val is the number to be computed
 *	@returns the computed integer square root
 */
uint32 sqrtInt(uint32 val) {
	uint32 g;
	uint32 bit = 0x8000;
	uint32 result = 0;
	uint32 test;


	// can't take the root of numbers higher than MAX_INT32
	if (val >= 0x80000000) {
		result = 46341;
	}
	else {
		while (bit != 0) {
			g = result | bit;
			test = g * g;
			if (test == val) {
				// we're done!
				result = g;
				break;
			}else if (test < val) {
				// our guess is too small, keep the temp bit
				result |= bit;
			}
			// shift the bit down one
			bit >>= 1;
		}
	}
	return result;
}

/**
 * @brief Pack a 32-bit dataWord into 8-bit, pointed to by char pointer arrayPtr.
 *
 * @param arrayPtr points to the packed 8-bit dataWord
 * @param dataWord 32-bit data to be packed
 * @returns void
 */
void pack32(uint8 * arrayPtr, uint32 dataWord) {
	*arrayPtr++ = (uint8)((dataWord >> 24) & 0xFF);
	*arrayPtr++ = (uint8)((dataWord >> 16) & 0xFF);
	*arrayPtr++ = (uint8)((dataWord >> 8) & 0xFF);
	*arrayPtr++ = (uint8)((dataWord) & 0xFF);
}


/**
 * @brief Pack a 24-bit dataWord into 8-bit, pointed to by char pointer arrayPtr.
 *
 * @param arrayPtr points to the packed 8-bit dataWord
 * @param dataWord 24-bit data to be packed
 * @returns void
 */
void pack24(uint8 * arrayPtr, uint32 dataWord) {
	*arrayPtr++ = (uint8)((dataWord >> 16) & 0xFF);
	*arrayPtr++ = (uint8)((dataWord >> 8) & 0xFF);
	*arrayPtr++ = (uint8)((dataWord) & 0xFF);
}


/**
 * @brief Pack a 16-bit dataWord into 8-bit, pointed to by char pointer arrayPtr.
 *
 * @param arrayPtr points to the packed 8-bit dataWord
 * @param dataWord 16-bit data to be packed
 * @returns void
 */
void pack16(uint8 * arrayPtr, uint32 dataWord) {
	*arrayPtr++ = (uint8)((dataWord >> 8) & 0xFF);
	*arrayPtr++ = (uint8)((dataWord) & 0xFF);
}


/**
 * @brief Unpacks an 8-bit data into 16 bit.
 *
 * @param arrayPtr points to data with 8-bit wordlength
 * @returns unpacked input data with 16-bit wordlength
 */
uint16 unpack16(uint8 * arrayPtr) {
	uint16 dataWord = (((uint32)arrayPtr[0]) << 8) | (((uint32)arrayPtr[1]));
	return(dataWord);
}


/**
 * @brief Unpacks an 8-bit data into 24 bit.
 *
 * @param arrayPtr points to data with 8-bit wordlength
 * @returns unpacked input data with 24-bit wordlength
 */
uint32 unpack24(uint8 * arrayPtr) {
	uint32 dataWord = unpack16(&arrayPtr[1]);
	dataWord |= (((uint32)arrayPtr[0]) << 16);
	return(dataWord);
}


/**
 * @brief Unpacks an 8-bit data into 32 bit.
 *
 * @param arrayPtr points to data with 8-bit wordlength
 * @returns unpacked input data with 32-bit wordlength
 */
uint32 unpack32(uint8 * arrayPtr) {
	uint32 dataWord = unpack24(&arrayPtr[1]);
	dataWord |= (((uint32)arrayPtr[0]) << 24);
	return(dataWord);
}

/**
 * @brief Normalizes the angle.
 *
 * Normalizes the angle to make it stay in the range of 0 <= angle < millirad_2PI
 * @param angle the angle to be normalized
 * @returns the normalized angle
 */
int16 normalizeAngleMilliRad(int16 angle) {
	while (angle < 0) {
		angle += MILLIRAD_2PI;
	}

	while (angle >= MILLIRAD_2PI) {
		angle -= MILLIRAD_2PI;
	}
	return(angle);
}

/**
 * @brief  Normalizes the angle.
 *
 * Normalizes the angle to make it stay in the range of -millirad_PI <= angle < millirad_PI.
 * @param angle angle to be normalized
 * @returns the normalized angle
 */
int16 normalizeAngleMilliRad2(int16 angle) {
	while (angle < -MILLIRAD_PI) {
		angle += MILLIRAD_2PI;
	}

	while (angle >= MILLIRAD_PI) {
		angle -= MILLIRAD_2PI;
	}
	return(angle);
}

/**
 * @brief Normalizes the angle.
 *
 * Normalizes the angle to make it stay in the range of 0 <= angle < microrad_2PI.
 * @param angle the angle to be normalized
 * @returns the normalized angle
 */
int32 normalizeAngleMicroRad(int32 angle) {
	while (angle < 0) {
		angle += (MILLIRAD_2PI * 1000);
	}

	while (angle >= (MILLIRAD_2PI * 1000)) {
		angle -= (MILLIRAD_2PI * 1000);
	}
	return(angle);
}

/**
 * @brief Interprets the angle as milli-radian of sine.
 *
 * @param angle the angle to be interpreted
 * @returns angle as milli-radian of sine
 */
int16 sinMilliRad(int16 angle) {
	int16 angleTemp = normalizeAngleMilliRad(angle);
	int16 sign = 1;

	if (angleTemp < MILLIRAD_HALF_PI) {
		/* 0 <= angle < pi/2 */
		angleTemp = angleTemp;
	}
	else if (angleTemp < MILLIRAD_PI) {
		/* pi/2 <= angle < pi */
		angleTemp = MILLIRAD_PI - angleTemp;
	}
	else if (angleTemp < (MILLIRAD_PI + MILLIRAD_HALF_PI)) {
		/* pi <= angle < 3pi/2 */
		angleTemp = angleTemp - MILLIRAD_PI;
		sign = -1;
	}
	else {
		/* 3pi/2 <= angle < 2pi */
		angleTemp = MILLIRAD_2PI - angleTemp;
		sign = -1;
	}

	angleTemp = angleTemp >> 1;
	if (angleTemp > 786) {
		return(0);
	}
	else {
	 	return(sign * trigMilliRadLookup[angleTemp]);
	}
}

/**
 * Interprets the angle as milli-randian of cosine.
 *
 * @param angle the angle to be interpreted
 * @returns angle as milli-radian of cosine
 */
int16 cosMilliRad(int16 angle) {
 	return sinMilliRad(angle + MILLIRAD_HALF_PI);
}

/**
 * @brief Calculates the smallest angle difference between the two input angles.
 *
 * The difference will be within the range of -MILLIRAD_PI <- difference <= MILLIRAD_PI
 * @param thetaGoal first angle
 * @param theta second angle
 * @returns the difference between two angles
 */
int16 smallestAngleDifference(int16 thetaGoal, int16 theta) {
	int16 thetaDelta;

	if (thetaGoal > theta) {
		// case 1
		thetaDelta = thetaGoal - theta;
		if (thetaDelta > MILLIRAD_PI) {
			// case 2
			thetaDelta -= MILLIRAD_2PI;
		}
	}
	else {
		// thetaGoal < theta
		// case 3
		thetaDelta = thetaGoal - theta;
		if (thetaDelta < -MILLIRAD_PI) {
			// case 4
			thetaDelta += MILLIRAD_2PI;
		}
	}
	return(thetaDelta);
}

/**
 * @brief Bounds the value with one specified bound as both lower and upper bound.
 *
 * Bounds the input value so that it stays within the range of -bound <= value <= bound.
 * If it exceeds the bound, set it to the bound.
 * @param val is the value to be bounded
 * @param bound is the lower and upper bound
 * @returns the bounded value
 */
int32 boundAbs(int32 val, int32 bound) {
	if (val > bound) {
		val = bound;
	}
	else if (val < -bound){
		val = -bound;
	}
	return(val);
}


/**
 * @brief Bounds the value with specified lower and upper bound.
 *
 * Bounds the value so that it stays within the range of lowerBound <= value <= upperBound.
 * If it exceeds the bound, set it to the lower/upper bound.
 * @param val is the value to be bounded
 * @param lowerBound is the lower bound
 * @param upperBound is the upper bound
 * @returns the bounded value
 */
int32 bound(int32 val, int32 lowerBound, int32 upperBound) {
	if (val < lowerBound) {
		val = lowerBound;
	}
	else if (val > upperBound) {
		val = upperBound;
	}
	return val;
}

/**
 * @brief Counts how many bits the value has
 *
 * Ignores leading zeros.
 * @param val is the value to be counted
 * @returns the number of bits of the input value
 */
uint8 countBits(uint32 val) {
	uint32 bitMask;
	uint8 returnVal = 0;

	for (bitMask = 1; bitMask != 0; bitMask = bitMask << 1) {
		if (val & bitMask) {
			returnVal++;
		}
	}
	return(returnVal);
}


//TODO check for overflow
int32 filterIIR(int32 sample, int32 average, int32 alpha) {
	int32 temp = (average * (alpha - 1)) + sample;
	return(temp / alpha);
}


/**
 * 	@brief Gets atan2 approximation in miiliradians.
 *
 *  Originally developed by John Aspinal at iRobot. It is quite good.
 *  @param y y-coordinate of the point to be calculated
 *  @param x x-coordinate of the point to be calculated
 *  @returns atan2 approximation of the input point, specified by (x,y) coordinate
 */
int16 atan2MilliRad(int32 y, int32 x) {
	boolean x_fold = FALSE;
	boolean y_fold = FALSE;
	boolean deg_45_fold = FALSE;
	uint32 val, denom, ux, uy;

	/* argument folding */
	if (x < 0) {
		x_fold = TRUE;
		x = -x;
	}
	if (y < 0) {
		y_fold = TRUE;
		y = -y;
	}
	if (y > x) {
		int32 tmp;
		deg_45_fold = TRUE;
		tmp = x;
		x = y;
		y = tmp;
	}

	uy = (uint32)y;
	ux = (uint32)x;

    /* atan2 approximation for 0 <= y/x <= 1
        basic formula is
        (60937 * y * x) /
        ((61 * x * x) + (17 * y * y))
      we check the size of ux to know how much to truncate args so we don't overflow
	  ux and uy must be 8-bit numbers to prevent overflow
      x > y so we only need to check x
    */
	while (ux & ~0x000000FF) {
		ux = ux >> 1;
		uy = uy >> 1;
	}
	val = (60937L * uy * ux);
	denom = (61L * ux * ux) + (17L * uy * uy);

	if (denom != 0) {
		val = val / denom;
		/* argument unfolding */
		if (deg_45_fold) {
		 	val = MILLIRAD_DEG_90 - val;
		}
		if (x_fold) {
		 	val = MILLIRAD_PI - val;
		}
		if (y_fold && (val > 0)) {
		 	val = MILLIRAD_2PI - val;
		}
	}
	else {
		// denom = 0 iff x = y = 0, but then function is undefined.  Return 0.
		val = 0;
	}

	return((int16)val);
}

/**
 * @brief Calculates the average of the two angles in microrad,
 *
 * @param theta1 is the first angle to be averaged
 * @param theta2 is the second angle to be averaged
 * @returns the average angle
 */
int32 averageAnglesMicroRad(int32 theta1, int32 theta2) {
	int32 thetaDelta;
    int32 mean;

	if (theta2 > theta1) {
		/* case 1 */
		thetaDelta = theta2 - theta1;
		if (thetaDelta > (MILLIRAD_PI * 1000)) {
			/* case 2 */
			thetaDelta -= (MILLIRAD_2PI * 1000);
		}
	}
	else {
		/* theta2 < theta1 */
		/* case 3 */
		thetaDelta = theta2 - theta1;
		if (thetaDelta < -(MILLIRAD_PI * 1000)) {
			/* case 4 */
			thetaDelta += (MILLIRAD_2PI * 1000);
		}
	}
    mean = theta1 + thetaDelta / 2;
	return(normalizeAngleMicroRad(mean));
}

/**
 * @brief Calculates the average of the two angles in millirad.
 *
 * @param angle1 is the first angle to be averaged
 * @param angle2 is the second angle to be averaged
 * @returns the average angle
 */
int16 averageAngles(int16 angle1, int16 angle2) {
	int32 y, x, average;

	x = cosMilliRad(angle1) + cosMilliRad(angle2);
	y = sinMilliRad(angle1) + cosMilliRad(angle2);
	average = atan2MilliRad(y, x);
	return(normalizeAngleMilliRad(average));
}

/**
 * @brief Calculates the average of the angles in the array.
 *
 * Calculates the average of the first "size (a number)" of angles in angleArray.
 * @param angleArray[] is the array of angles to be averaged
 * @param size specifies how many elements in the array (starting from the first) should be averaged
 * @returns the average of the angles in the array (returns 0 if given a nonpositive size)
 */
int16 averageArrayAngle(int16 angleArray[], int32 size) {
	int32 ysum = 0;
	int32 xsum = 0;
	int32 average, i;

	if (size > 0) {
		for (i = 0; i < size; i++) {
			ysum += sinMilliRad(angleArray[i]);
			xsum += cosMilliRad(angleArray[i]);
		}
		average = atan2MilliRad(ysum, xsum);
	}
	else {
		average = 0;
	}
	return(normalizeAngleMilliRad(average));
}


//void posePrint(Pose* posePtr, char* string) {
//	sprintf(string, "{%d,%d,%d}", posePtr->x, posePtr->y, posePtr->theta);
//}


#if 0
/*
 * overflowCheck...
 * ----------------
 * Overflow check functions for integer calculations.
 */
uint8 msb8fast(uint8 val) {
	if (val & b11110000) {
		//1111----
		if (val & b11000000) {
			//11------
			if (val & b10000000) {
				//1-------
				return(7);
			}
			else {
				//01------
				return(6);
			}
		}
		else {
			//0011----
			if (val & b00100000) {
				//1-------
				return(5);
			}
			else {
				//01------
				return(4);
			}
		}
	}
	else {
		//0000----
		if (val & b00001100) {
			//000011--
			if (val & b00001000) {
				//1-------
				return(3);
			}
			else {
				//000001--
				return(2);
			}
		}
		else {
			//0011----
			if (val & b00000010) {
				//0000001-
				return(1);
			}
			else {
				//00000001
				return(0);
			}
		}
	}
}


uint8 msb32fast(uint32 val) {
	if (val & 0xFFFF0000) {
		//1111----
		if (val & 0xFF000000) {
			//11------
			return(msb8fast((uint8)(val >> 24)) + 24);
		}
		else {
			//0011----
			return(msb8fast((uint8)(val >> 16)) + 16);
		}
	}
	else {
		//0000----
		if (val & 0x0000FF00) {
			//000011--
			return(msb8fast((uint8)(val >> 8)) + 8);
		}
		else {
			//00000011
			return(msb8fast((uint8)val));
		}
	}
}


uint8 msb32(uint32 val) {
	uint32 bitMask;
	uint8 returnVal = 31;
	for (bitMask = 0x80000000; bitMask != 0; bitMask = bitMask >> 1) {
		if (val & bitMask) {
			break;
		}
		returnVal--;
	}
	return(returnVal);
}


int32 add32func(int32 v1, int32 v2, const char * filePathName, unsigned int lineNum) {
  uint8 p1 = msb32(abs(v1)) + 1;
  uint8 p2 = msb32(abs(v2)) + 1;
  uint8 p = max(p1, p2);
  if ((p + 1) > 31) {
    cprintf(COLOR_ERROR "add32 overflow v1=%d, v2=%d in %s at line %d\n", v1, v2, sysGetFilenameFromPath((char *)filePathName), lineNum);
  	return(0);
  }
  else {
  	return(v1 + v2);
  }
}


int32 sub32func(int32 v1, int32 v2, const char * filePathName, unsigned int lineNum) {
  return(add32func(v1, -v2, filePathName, lineNum));
}


int32 mul32func(int32 v1, int32 v2, const char * filePathName, unsigned int lineNum) {
  uint8 p1 = msb32(abs(v1) + 1);
  uint8 p2 = msb32(abs(v2) + 1);
  if ((p1 + p2) > 31) {
    cprintf(COLOR_ERROR "mul32 overflow v1=%d, v2=%d in %s at line %d\n", v1, v2, sysGetFilenameFromPath((char *)filePathName), lineNum);
	  return(0);
  }
  else {
  	return(v1 * v2);
  }
}



int32 div32func(int32 v1, int32 v2, const char * filePathName, unsigned int lineNum) {
  if (v1 == 0) {
	return(0);
  }

  if (abs(v2) > abs(v1)) {
    // check for underflow
    cprintf(COLOR_ERROR "div32 underflow v1=%d, v2=%d in %s at line %d\n", v1, v2, sysGetFilenameFromPath((char *)filePathName), lineNum);
    return(0);
  }
  else {
//    // check for loss of precision
//    uint8 p1 = msb32(abs(v1));
//    uint8 p2 = msb32(abs(v2));
//    if ((p1 - p2) < 4) {
//      cprintf(COLOR_ERROR "div32 precision loss v1=%d, v2=%d in %s at line %d\n", v1, v2, getFilename((char *)filePathName), lineNum);
//  	  return(0);
//    }
//    else {
//  	  return(v1 / v2);
//    }
	  return(v1 / v2);
  }
}


uint8 msb64(uint64 val) {
	uint64 bitMask;
	uint8 returnVal = 63;
	for (bitMask = 0x8000000000000000LL; bitMask != 0; bitMask = bitMask >> 1) {
		if (val & bitMask) {
			break;
		}
		returnVal--;
	}
	return(returnVal);
}


int64 abs64(int64 val) {
	if (val < 0) {
		return -val;
	}
	else {
		return val;
	}
}


int64 add64func(int64 v1, int64 v2, const char * filePathName, unsigned int lineNum) {
  uint8 p1 = msb64(abs(v1)) + 1;
  uint8 p2 = msb64(abs(v2)) + 1;
  uint8 p = max(p1, p2);
  if ((p + 1) > 63) {
	char temp[200];
	sprintf(temp, COLOR_ERROR "add64 overflow v1=%lld, v2=%lld in %s at line %d\n", v1, v2, sysGetFilenameFromPath((char *)filePathName), lineNum);
    cprintf(temp);
  	return(0);
  }
  else {
  	return(v1 + v2);
  }
}


int64 sub64func(int64 v1, int64 v2, const char * filePathName, unsigned int lineNum) {
  return(add64func(v1, -v2, filePathName, lineNum));
}


int64 mul64func(int64 v1, int64 v2, const char * filePathName, unsigned int lineNum) {
  uint8 p1 = msb64(abs64(v1) + 1);
  uint8 p2 = msb64(abs64(v2) + 1);
  if ((p1 + p2) > 63) {
	char temp[200];
	sprintf(temp, COLOR_ERROR "mul64 overflow v1=%lld, v2=%lld in %s at line %d\n", v1, v2, sysGetFilenameFromPath((char *)filePathName), lineNum);
    cprintf(temp);
    return(0);
  }
  else {
  	return(v1 * v2);
  }
}



int64 div64func(int64 v1, int64 v2, const char * filePathName, unsigned int lineNum) {
  if (v1 == 0) {
	  return(0);
  }

  if (abs64(v2) > abs64(v1)) {
    // check for underflow
	char temp[200];
	sprintf(temp, COLOR_ERROR "div64 underflow v1=%lld, v2=%lld in %s at line %d\n", v1, v2, sysGetFilenameFromPath((char *)filePathName), lineNum);
    cprintf(temp);
    return(0);
  }
  else {
//    // check for loss of precision
//    uint8 p1 = msb64(abs(v1));
//    uint8 p2 = msb64(abs(v2));
//    if ((p1 - p2) < 4) {
//      cprintf(COLOR_ERROR "div64 precision loss v1=%lld, v2=%lld in %s at line %d\n", v1, v2, getFilename((char *)filePathName), lineNum);
//  	  return(0);
//    }
//    else {
//  	  return(v1 / v2);
//    }
	  return(v1 / v2);
  }
}
#endif
