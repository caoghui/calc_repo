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
	
	桌面计算器，可以将它看做是由5个部分组成：
	1 一个分析器，完成语法分析。
	2 一个词法处理器，由字符组合出单词。
	3 一个符号表，保存字符串和值的对偶。
	4 一个驱动程序main()。
	5 一个错误处理器。
	
	
	
	一种物理组织方式是让每一个逻辑模块有自己的头文件，其中定义它所提供的功能。这样，每个.c文件用一个对应的.h文件描述它所提供的东西
(它的界面)。每个.c文件包含它自己的.h文件，或许还需要包含其他.h文件，如果那里描述了本.c文件为实现自己在界面中说明的服务所需要的有关其他
文件的信息。这种物理组织对应于模块的逻辑组织，为用户提供的界面放在它的.h文件里，为实现部分所用的界面放在另外的以_impl.h为后缀的文件里，
而模块中的函数，变量等的定义则放在.c文件里。
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
    
