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

//单词(token)用它们的字符所对应的整数表示.
enum Token_value
{
	NAME, NUMBER, END,
	PLUS='+', MINUS='-', MUL='*', DIV='/',
	PRINT=';', ASSIGN='=', LP='(', RP=')'
};

Token_value curr_tok = PRINT;


double number_value;
string string_value;
int no_of_errors;
map<string, double> table;
istream* input;    //指向输入流


//每个分析函数都有一个bool参数，指明该函数是否需要调用get_token()去取得下一个单词。每个分析函数都将对它的表达式求值并返回这个值。

double term(bool get);  //乘和除
double expr(bool get);  //expr()处理加和减。它由一个查找被加减的项的循环组成.
double prim(bool get);

Token_value get_token();

double error(const string& msg);


int main(int argc, char** argv)
{
    //cout<<"desktop calc running...."<<endl;
    vector<string> args(argv, argv + argc);
    copy(args.begin(), args.end(), ostream_iterator<string>(cout, "\n"));
    //return 0;

    
    switch(argc)
    {
    	case 1:
    		input = &cin;
    		break;
    	case 2:
    		input = new istringstream(argv[1]);
    		break;
    	default:
    		error("too many arguments");
    		return 1;
    }
    
    LOG("desktop calc running, please input expression : ");
	table["pi"] = 3.1415926535897932385;
	table["e"]  = 2.7182818284590452354;
	
	while(*input)
	{
		get_token();
		if(curr_tok == END)
		{
			break;
		}
		if(curr_tok == PRINT)
		{
			cout<<"input token : PRINT"<<endl;
			continue;
		}	
		cout<<expr(false)<<endl;
	}
	if(input != &cin)
		delete input;
    return no_of_errors;
}

double expr(bool get)  //加和减
{
	
	double left = term(get);
	
	for(;;)
	{
		switch(curr_tok)
		{
		case PLUS:
			left += term(true);
			break;
		case MINUS:
			left -= term(true);
			break;
		default:
			return left;
		}
	}
}

double term(bool get)
{
	double left = prim(get);
	for(;;)
	{
		switch(curr_tok)
		{
		case MUL:
			left *= prim(true);
			break;
		case DIV:
			if(double d = prim(true))
			{
				left /= d;
				break;
			}
			return error("divide by 0");
		default:
			return left;
		}
	}
}

double prim(bool get)  //处理初等项
{
	if(get) get_token();
	switch(curr_tok)
	{
		case NUMBER:
		{
			double v = number_value;
			get_token();
			return v;
		}
		case NAME:
		{
			double& v = table[string_value];
			if(get_token() == ASSIGN)
			{
				v = expr(true);
			}
			return v;
		}
		case MINUS:
			return -prim(true);
		case LP:
		{
			double e = expr(true);
			if(curr_tok != RP)
			{
				return error(") expected");
			}
			get_token();   //吃掉 )
			return e;
		}
		default:
			return error("primary expected");
	}
}

//去读一个字符，根据它决定需要去组合的是哪种单词，而后返回表示被读单词的Token_value值
Token_value get_token()
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
			return curr_tok=END;
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
			error("bad token");
			return curr_tok = PRINT;
		
	}
}

double error(const string& msg)
{
	no_of_errors++;
	cerr<<"error : "<<msg<<endl;
	return 1;
}

