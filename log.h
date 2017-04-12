#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#define LOG(fmt, ...)	\
	printf(__FILE__ ":" STR(__LINE__) " " fmt "\n", ##__VA_ARGS__)

#define ERR(fmt, ...) \
	fprintf(stderr, "Error: " __FILE__ ":" STR(__LINE__) " " fmt "\n", ##__VA_ARGS__)

#endif

