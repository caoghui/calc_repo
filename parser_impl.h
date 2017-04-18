/*************************************************************************
	> File Name: parser_impl.h
	> Author: 
	> Mail: 
	> Created Time: 2017年04月18日 星期二 14时57分48秒
 ************************************************************************/

#ifndef _PARSER_IMPL_H
#define _PARSER_IMPL_H

#include "parser.h"
#include "error.h"
#include "lexer.h"

namespace Parser
{	
	double expr(bool);
	double prim(bool);
	double term(bool);
	
	using Lexer::curr_tok;
	using Lexer::get_token;
}

#endif
