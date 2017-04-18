/*************************************************************************
	> File Name: driver.h
	> Author: 
	> Mail: 
	> Created Time: 2017年04月18日 星期二 15时18分13秒
 ************************************************************************/

#ifndef _DRIVER_H
#define _DRIVER_H

#include <sstream>

namespace Driver
{
	extern int no_of_errors;
	extern std::istream* input;
	
	void skip();
	int run(int argc, char** argv);
}

#endif
