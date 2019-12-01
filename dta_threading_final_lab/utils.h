#pragma once


#ifdef _DEBUG
#include <stdio.h>
#define DEBUGPRINT(fmt, ...) fprintf(stderr, fmt,__VA_ARGS__);
#else
#define DEBUGPRINT(fmt, ...)
#endif