/*************************************************************************
	> File Name: parser.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年04月18日 星期二 10时40分12秒
 ************************************************************************/

#include "parser_impl.h"
#include "table.h"
#include "error.h"
#include "lexer.h"
	
using Lexer::curr_tok;
using Lexer::get_token;

double Parser::prim(bool get)
{
	if(get)
		get_token();
	
	switch(curr_tok)
	{
		case Lexer::NUMBER:
			get_token();
			return Lexer::number_value;
		case Lexer::NAME:
		{
			double& v = table[Lexer::string_value];
			if(get_token() == Lexer::ASSIGN)
			{
				v = expr(true);
			}
			return v;
		}
		case Lexer::MINUS:
			return -prim(true);
		case Lexer::LP:
		{
			double e = expr(true);
			if(curr_tok != Lexer::RP)
			{
				throw Error::Syntax_error(") expected");
			}
			get_token();
			return e;
		}
		case Lexer::END:
			return 1;
		default:
			throw Error::Syntax_error("primary expected");
	}
}

double Parser::term(bool get)
{
	double left = prim(get);
	for(;;)
	{
		switch(Lexer::curr_tok)
		{
			case Lexer::MUL:
				left *= prim(true);
				break;
			case Lexer::DIV:
				if(double d = prim(true))
				{
					left /= d;
					break;
				}
				throw Error::Zero_divide();
			default:
				return left;
				
		}
	}
	return 0;
}

double Parser::expr(bool get)
{
	double left = term(get);
	
	for(;;)
	{
		switch(curr_tok)
		{
		case Lexer::PLUS:
			left += term(true);
			break;
		case Lexer::MINUS:
			left -= term(true);
			break;
		default:
			return left;
		}
	}
}



