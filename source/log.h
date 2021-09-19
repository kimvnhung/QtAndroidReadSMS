#ifndef LOG_H
#define LOG_H

#include <errno.h>

//#ifdef ANDROID

#ifndef LOG_TAG
#define LOG_TAG __FUNCTION__
#endif

#include <android/log.h>

#define D LOGD
#define E LOGE

//#ifdef DEBUG_MODE
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , LOG_TAG, __VA_ARGS__)

#endif // LOG_H
