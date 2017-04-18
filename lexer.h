/*************************************************************************
	> File Name: lexer.h
	> Author: 
	> Mail: 
	> Created Time: 2017年04月18日 星期二 14时59分19秒
 ************************************************************************/

#ifndef _LEXER_H
#define _LEXER_H

#include <string>

namespace Lexer
{
	enum Token_value 
	{
		NAME, NUMBER, END,
		PLUS='+', MINUS='-', MUL='*', DIV='/',
		PRINT=';', ASSIGN='=', LP='(', RP=')'
	};
	
	extern Token_value curr_tok;
	extern double number_value;
	extern std::string string_value;
	
	Token_value get_token();
}

#endif
