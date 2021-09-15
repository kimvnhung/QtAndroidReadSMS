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
//#else
//#define LOGV(...)
//#define LOGD(...)
//#define LOGI(...)
//#define LOGW(...)
//#define LOGE(...)
//#endif

//#else /* ANDROID */

//#include <stdio.h>
//#include <stdlib.h>
//#include <stdarg.h>

//#if DEBUG == 1

//#define LOG_FUNCTION_NAME \
//    fprintf(stderr, "\033[0;1;31m__func__: %s\033[0;0m\n", __FUNCTION__);

//#else

//#define LOG_FUNCTION_NAME

//#endif

//static void
//D(const char *msg, ...)
//{
//    va_list ap;

//    va_start (ap, msg);
//    vfprintf(stdout, msg, ap);
//    fprintf(stdout, "\n");
//    va_end (ap);
//    fflush(stdout);
//}

//static void
//E(const char *msg, ...)
//{
//    va_list ap;

//    va_start (ap, msg);
//    vfprintf(stderr, msg, ap);
//    fprintf(stderr, ", %s", strerror(errno));
//    fprintf(stderr, "\n");
//    va_end (ap);
//}

//#endif /* ANDROID */


#endif // LOG_H
