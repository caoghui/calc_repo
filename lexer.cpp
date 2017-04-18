/*************************************************************************
	> File Name: lexer.c
	> Author: 
	> Mail: 
	> Created Time: 2017年04月18日 星期二 10时26分25秒
 ************************************************************************/

#include "lexer.h"
#include "error.h"
#include "driver.h"
#include <iostream>
#include <cctype>

Lexer::Token_value Lexer::curr_tok;
double Lexer::number_value;
std::string Lexer::string_value;

//去读一个字符，根据它决定需要去组合的是哪种单词，而后返回表示被读单词的Token_value值
Lexer::Token_value Lexer::get_token()
{
	using Driver::input;
	//char ch = 0;
	//cin>>ch;  
	//用读入单个字符的代码来代替基于类型的默认输入操作，将换行符看做与分号等价，当做表达式结束。
	char ch;
	do
	{
		//跳过空白，除了'\n'
		if(!(*input).get(ch))
		{
			return curr_tok = END;
		}
	}while(ch != '\n' && isspace(ch));
	
	switch(ch)
	{
		case ';':
		case '\n':
			return curr_tok = PRINT;
		case '*':
		case '/':
		case '+':
		case '-':
		case '(':
		case ')':
			return curr_tok = Token_value(ch);
		case '0':case '1':case '2':case '3':case '4':
		case '5':case '6':case '7':case '8':case '9':
		case '.':
			(*input).putback(ch);
			(*input)>>number_value;
			return curr_tok = NUMBER;
		default:   //NAME, NAME=, or error
			if(isalpha(ch))
			{
				//cin.putback(ch);
				//cin>>string_value; //采用>>读入字符串直到遇到空白会引起问题.这一问题可以通过一次读一个字符，直到遇到非字母非数字
				//字符的方式解决.
				string_value = ch;
				while((*input).get(ch) && isalnum(ch))
				{
					string_value.push_back(ch);
				}
				(*input).putback(ch);
				return curr_tok = NAME;
			}
			throw Error::Syntax_error("bad token");
	}
}



