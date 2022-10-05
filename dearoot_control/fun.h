#ifndef FUN_H
#define FUN_H

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>

#include <dirent.h>

#define DEBUG 0
#ifdef DEBUG
#define  debug_printf(fmt, ...) printf(fmt, ##__VA_ARGS__ )
#else
#define debug_printf(fmt, ...)
#endif


#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif // FUN_H

