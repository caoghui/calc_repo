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
#include "dc.h"

using namespace std;
  
int Driver::no_of_errors = 0;
istream* Driver::input = 0;


int main(int argc, char** argv)
{
    vector<string> args(argv, argv + argc);
    copy(args.begin(), args.end(), ostream_iterator<string>(cout, "\n"));
    
    return Driver::run(argc, argv);
}

int Driver::run(int argc, char** argv)
{    
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


