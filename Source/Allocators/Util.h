#pragma once

#define checkf(x, ...) \
{ \
	if(!x) \
	{ \
		printf("Assertion Failed: %s \n", __VA_ARGS__);\
		printf("File: %s | Line: %d \n", __FILE__, __LINE__);\
		 __debugbreak();\
	}\
}\
