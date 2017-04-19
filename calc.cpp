/*************************************************************************
	> File Name: calc.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年04月11日 星期二 14时14分35秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include "driver.h"

using namespace std;

int main(int argc, char** argv)
{
    vector<string> args(argv, argv + argc);
    copy(args.begin(), args.end(), ostream_iterator<string>(cout, "\n"));
    
    return Driver::run(argc, argv);
}


