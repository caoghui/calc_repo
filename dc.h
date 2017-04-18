/*************************************************************************
	> File Name: dc.h
	> Author: 
	> Mail: 
	> Created Time: 2017年04月18日 星期二 10时11分01秒
 ************************************************************************/

#ifndef _DC_H
#define _DC_H

//利用命名空间改造程序
#include <iostream>

namespace Error
{	
	struct Zero_divide {};
	
	struct Syntax_error
	{
		const char* p;
		Syntax_error(const char* q) { p = q; }
	};
}

namespace Driver
{
	extern int no_of_errors;
	extern std::istream* input;
	
	void skip();
	int run(int argc, char** argv);
}

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
	
	using Driver::input;
}

#include <map>

extern std::map<std::string, double> table;

namespace Parser
{	
	double expr(bool);
	double prim(bool);
	double term(bool);
	
	using Lexer::curr_tok;
	using Lexer::get_token;
}

namespace Parser_interface
{
	double expr(bool);
}

#endif
