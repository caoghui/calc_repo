# calc_repo
calc_repo

该桌面计算器提供了四种作为浮点数的中缀运算符的标准算术运算。
所接受的语言的语法：

program:
    END
    expr_list END

expr_list:
	expression PRINT       //PRINT是分号
	expression PRINT expr_list

expression:
	expression + term
	expression - term
	term
	
term:
	term / primary
	term * primary
	primary

primary:
	NUMBER
	NAME
	NAME = expression
	- primary
	(expression)		

　　一个程序是由分号分隔的一系列表达式。表达式的基本单元是数，名字和运算符*,/,+,-(包括一元的和二元的)和=.
　　名字在使用前无需声明。
　　语法分析采用通常称为递归下降的风格，这是一种很流行的直截了当的自顶向下技术。对于语法中的每个产生式存在着一个函数，它还要调用其他的函数。
终结符(例如END,NUMBER,+和-)由词法分析程序get_token()识别，而非终结符则由语法分析函数expr(),term()和prim()识别。一旦一个(子)表达式的
两个运算对象都已经知道了，就立即对这个表达式求值。
	分析器利用函数get_token()取得输入，最后一次调用get_token()得到的值可以在全局变量curr_tok里找到。curr_tok的类型是枚举Token_value。
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
    
