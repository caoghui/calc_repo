/*************************************************************************
	> File Name: calc.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年04月11日 星期二 14时14分35秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <map>

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

map<string, double> table;
//每个分析函数都有一个bool参数，指明该函数是否需要调用get_token()去取得下一个单词。每个分析函数都将对它的表达式求值并返回这个值。

double term(bool get);  //乘和除
double expr(bool get);  //expr()处理加和减。它由一个查找被加减的项的循环组成.
double prim(bool get);

Token_value get_token();

double error(const string& msg);


int main(int argc, char** argv)
{
    cout<<"desktop calc running...."<<endl;

    return 0;
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
	char ch = 0;
	cin>>ch;
}

double error(const string& msg)
{
	return 0;
}

