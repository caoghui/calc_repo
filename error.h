/*************************************************************************
	> File Name: error.h
	> Author: 
	> Mail: 
	> Created Time: 2017年04月18日 星期二 14时59分13秒
 ************************************************************************/

#ifndef _ERROR_H
#define _ERROR_H

namespace Error
{	
	struct Zero_divide {};
	
	struct Syntax_error
	{
		const char* p;
		Syntax_error(const char* q) { p = q; }
	};
}

#endif
