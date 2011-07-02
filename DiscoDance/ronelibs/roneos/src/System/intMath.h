/** @file intMath.h
 * @addtogroup kernel
 * @{
 */

#ifndef intMath_h
#define intMath_h


/******** Defines ********/
#define __PI 3.14159

/* Angles */
#define MILLIRAD_HALF_PI			1571
#define MILLIRAD_PI					(MILLIRAD_HALF_PI * 2)
#define MILLIRAD_2PI				(MILLIRAD_HALF_PI * 4)

#define MILLIRAD_DEG_0				0
#define MILLIRAD_DEG_15				(MILLIRAD_HALF_PI / 6)
#define MILLIRAD_DEG_30				(MILLIRAD_HALF_PI / 3)
#define MILLIRAD_DEG_45				(MILLIRAD_HALF_PI / 2)
#define MILLIRAD_DEG_90				MILLIRAD_HALF_PI
#define MILLIRAD_DEG_180			MILLIRAD_PI
#define MILLIRAD_DEG_270			(MILLIRAD_PI + MILLIRAD_HALF_PI)
#define MILLIRAD_DEG_360			MILLIRAD_2PI

#define MILLIRAD_TRIG_SCALER		32767


/******** Structs ********/

typedef struct Pose {
	int32 x;
	int32 y;
	int32 theta;
} Pose;


/******** Macros ********/
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

/******** Functions ********/


//General math
uint32 sqrtInt(uint32 val);
uint32 decToZero(uint32 val);
int32 average(int32 val1, int32 val2);
uint8 countBits(uint32 val);
int32 	boundAbs(int32 val, int32 bound);
int32 	bound(int32 val, int32 lowerBound, int32 upperBound);

// trig and angles
int16 sinMilliRad(int16 angle);
int16 cosMilliRad(int16 angle);
int16 atan2MilliRad(int32 y, int32 x);
int16 normalizeAngleMilliRad(int16 angle);
int16 normalizeAngleMilliRad2(int16 angle);
int32 normalizeAngleMicroRad(int32 angle);
int16 smallestAngleDifference(int16 thetaGoal, int16 theta);


// averageing and arrays
int32 filterIIR(int32 sample, int32 average, int32 alpha);
int16 averageAngles(int16 angle1, int16 angle2);
int32 averageAnglesMicroRad(int32 theta1, int32 theta2);
int16 averageArrayAngle(int16 angleArray[], int32 size);


// byte packing
void pack16(uint8 * arrayPtr, uint32 dataWord);
void pack24(uint8 * arrayPtr, uint32 dataWord);
void pack32(uint8 * arrayPtr, uint32 dataWord);
uint16 unpack16(uint8 * arrayPtr);
uint32 unpack24(uint8 * arrayPtr);
uint32 unpack32(uint8 * arrayPtr);


#if 0
// overflow checking math
#define add32(v1, v2) add32func(v1, v2, __FILE__, __LINE__)
#define sub32(v1, v2) sub32func(v1, v2, __FILE__, __LINE__)
#define mul32(v1, v2) mul32func(v1, v2, __FILE__, __LINE__)
#define div32(v1, v2) div32func(v1, v2, __FILE__, __LINE__)

uint8 msb32(uint32 val);
int32 add32func(int32 v1, int32 v2, const char * filePathName, unsigned int lineNum);
int32 sub32func(int32 v1, int32 v2, const char * filePathName, unsigned int lineNum);
int32 mul32func(int32 v1, int32 v2, const char * filePathName, unsigned int lineNum);
int32 div32func(int32 v1, int32 v2, const char * filePathName, unsigned int lineNum);

#define add64(v1, v2) add64func(v1, v2, __FILE__, __LINE__)
#define sub64(v1, v2) sub64func(v1, v2, __FILE__, __LINE__)
#define mul64(v1, v2) mul64func(v1, v2, __FILE__, __LINE__)
#define div64(v1, v2) div64func(v1, v2, __FILE__, __LINE__)

int64 abs64(int64 val);
uint8 msb64(uint64 val);
int64 add64func(int64 v1, int64 v2, const char * filePathName, unsigned int lineNum);
int64 sub64func(int64 v1, int64 v2, const char * filePathName, unsigned int lineNum);
int64 mul64func(int64 v1, int64 v2, const char * filePathName, unsigned int lineNum);
int64 div64func(int64 v1, int64 v2, const char * filePathName, unsigned int lineNum);
#endif

#endif // #ifndef intMath_h

