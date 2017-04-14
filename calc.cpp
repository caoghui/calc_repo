/*************************************************************************
	> File Name: calc.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年04月11日 星期二 14时14分35秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <map>
#include <cctype>
#include <vector>
#include "util.h"
#include "log.h"

using namespace std;

//利用命名空间改造程序

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
	int no_of_errors;
	istream* input;
	
	void skip();
	int run(int argc, char** argv);
}

namespace Lexer
{
	enum Token_value {
		NAME, NUMBER, END,
		PLUS='+', MINUS='-', MUL='*', DIV='/',
		PRINT=';', ASSIGN='=', LP='(', RP=')'
	};
	
	Token_value curr_tok;
	double number_value;
	string string_value;
	
	Token_value get_token();
	
	using Driver::input;
}

namespace Parser
{
	map<string, double> table;
	
	double expr(bool);
	double prim(bool);
	double term(bool);
	
	using Lexer::curr_tok;
	using Lexer::get_token;
	using namespace Error;
}

namespace Parser_interface
{
	double expr(bool);
}

double Parser_interface::expr(bool get)
{
	return Parser::expr(get);
}

//每个分析函数都有一个bool参数，指明该函数是否需要调用get_token()去取得下一个单词。每个分析函数都将对它的表达式求值并返回这个值。

//double term(bool get);  //乘和除
//double expr(bool get);  //expr()处理加和减。它由一个查找被加减的项的循环组成.
//double prim(bool get);

//Token_value get_token();
//double error(const string& msg);

int main(int argc, char** argv)
{
	//cout<<"desktop calc running...."<<endl;
    vector<string> args(argv, argv + argc);
    copy(args.begin(), args.end(), ostream_iterator<string>(cout, "\n"));
    
    return Driver::run(argc, argv);
}

int Driver::run(int argc, char** argv)
{
    using namespace Driver;
    using namespace Parser;
    using namespace Lexer;
    using namespace Error;
    
    switch(argc)
    {
    	case 1:
    		input = &cin;
    		break;
    	case 2:
    		input = new istringstream(argv[1]);
    		break;
    	default:
    		cerr<<"too many arguments"<<endl;
    		return 1;
    }
    
    LOG("desktop calc running, please input expression : ");
	table["pi"] = 3.1415926535897932385;
	table["e"]  = 2.7182818284590452354;
	
	while(*input)
	{
		try
		{
			Lexer::get_token();
			if(Lexer::curr_tok == Lexer::END)
			{
				break;
			}
			if(Lexer::curr_tok == Lexer::PRINT)
			{
				cout<<"input token : PRINT"<<endl;
				continue;
			}	
			cout<<Parser_interface::expr(false)<<endl;
		}
		catch(Error::Zero_divide)
		{
			cerr<<"attempt to divide by zero"<<endl;
			if(Lexer::curr_tok != Lexer::PRINT) 
				skip();
		}
		catch(Error::Syntax_error e)
		{
			cerr<<"syntax error : "<<e.p<<endl;
			if(Lexer::curr_tok != Lexer::PRINT) 
				skip();
		}
	}
	if(input != &cin)
		delete input;
		
    return no_of_errors;
}

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

void Driver::skip()
{
	no_of_errors++;
	while(*input)
	{
		char ch;
		input->get(ch);
		switch(ch)
		{
			case '\n':
			case ';':
				return;
		}
	}
}

//去读一个字符，根据它决定需要去组合的是哪种单词，而后返回表示被读单词的Token_value值
Lexer::Token_value Lexer::get_token()
{
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



