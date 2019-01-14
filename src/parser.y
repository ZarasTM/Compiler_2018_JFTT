/* Compiler for simple iterative language SIL */
%{
	#include <iostream>
	#include <string>
	#include "../src/utils/Variable.h"
	#include "../src/utils/Inserter.h"
	#include "../src/utils/Labeler.h"
	#include "../src/utils/OperationGenerator.h"
	#include "../src/utils/main.h"

	using namespace std;

	int yylex();
	int yyerror(const char *p)
	{
		cerr << "Error!" << endl;
		exit(1);
		return 1;
	}
%}

%union{
	char* sval;
	char* ival;
	struct VarType* varType;
}

%type <varType> id
%type <varType> value
%type <varType> expression

%token <varType> DECLARE /* Declarations block */
%token <varType> IN END /* Code block */
%token <varType> IF THEN ELSE ENDIF /* Conditional block */
%token <varType> WHILE DO ENDWHILE ENDDO /* While-do and Do-while loop block */
%token <varType> FOR FROM TO DOWNTO ENDFOR /* For loop block */
%token <varType> READ WRITE
%token <varType> ASSIGN
%token <varType> ADD SUB MUL DIV MOD /* Arithmetic operators */
%token <varType> EQ NEQ LT GT LE GE /* Boolean operators */
%token <varType> L_BRACKET R_BRACKET SEMICOLON COLON /* Symbols */
%token <varType> NUM
%token <varType> PID

%%

program			:	DECLARE declaration IN commands END
						;

declaration	:	declaration PID SEMICOLON
						|	declaration PID L_BRACKET NUM COLON NUM R_BRACKET SEMICOLON
						| %empty
						;

commands		:	commands command
						|	command
						;

command			:	id ASSIGN expression SEMICOLON
						|	IF condition THEN commands
							ELSE commands ENDIF
						|	IF condition THEN commands ENDIF
						|	WHILE	condition DO commands ENDWHILE
						|	DO commands WHILE condition ENDDO
						|	FOR PID FROM value TO value	DO commands ENDFOR
						|	FOR PID FROM value DOWNTO value	DO commands ENDFOR
						|	READ id SEMICOLON
						|	WRITE value SEMICOLON
						;

expression	:	value
						|	value ADD value
						|	value SUB value
						|	value MUL value
						|	value DIV value
						|	value MOD value
						;

condition		:	value EQ value
						|	value NEQ value
						|	value LT value
						|	value GT value
						|	value LE value
						|	value GE value
						;

value				:	NUM
						|	id
						;

id					:	PID
						|	PID L_BRACKET PID R_BRACKET
						|	PID	L_BRACKET NUM R_BRACKET
						;

%%
int main()
{
  yyparse();

	Variable* var = new Variable("asd", 5);
  return 0;
}
