#if !defined(vrcommon_h)
#define vrcommon_h

//#include <VrApi_Ext.h>
#include <VrApi_Input.h>

#include <android/log.h>

//#include "../darkplaces/mathlib.h"

#define LOG_TAG "QuakeQuest"

#ifndef NDEBUG
#define DEBUG 1
#endif

#define ALOGE(...) __android_log_print( ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__ )

#if DEBUG
#define ALOGV(...) __android_log_print( ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__ )
#else
#define ALOGV(...)
#endif

float playerHeight;
float playerYaw;

#ifdef VEC_64
typedef double vec_t;
#else
typedef float vec_t;
#endif
typedef vec_t vec3_t[3];


float radians(float deg);
float degrees(float rad);
double GetTimeInMilliSeconds();
float length(float x, float y);
float nonLinearFilter(float in);
bool between(float min, float val, float max);
void QuatToYawPitchRoll(ovrQuatf q, float pitchAdjust, vec3_t out);
//qboolean useScreenLayer();


#endif //vrcommon_h