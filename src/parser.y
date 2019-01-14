/* Compiler for simple iterative language SIL
 *	TODO: Add class for getting variables in different forms (var, arr(var), arr(const))
 */
%{
	#include <iostream>
	#include <string>
	#include "../src/utils/Variable.h"
	#include "../src/utils/Inserter.h"
	#include "../src/utils/Labeler.h"
	#include "../src/utils/OperationGenerator.h"
	#include "../src/utils/main.h"

	int yylex();
	int yyerror(const char *p);
	extern int yylineno;

	using namespace std;

	//bool DEBUG = false;
	bool DEBUG = true;
%}

%union{
	char* sval;
	class Variable* var;
}

%type <var> id
%type <var> value
%type <var> expression

%token <sval> DECLARE /* Declarations block */
%token <sval> IN END /* Code block */
%token <sval> IF THEN ELSE ENDIF /* Conditional block */
%token <sval> WHILE DO ENDWHILE ENDDO /* While-do and Do-while loop block */
%token <sval> FOR FROM TO DOWNTO ENDFOR /* For loop block */
%token <sval> READ WRITE
%token <sval> ASSIGN
%token <sval> ADD SUB MUL DIV MOD /* Arithmetic operators */
%token <sval> EQ NEQ LT GT LE GE /* Boolean operators */
%token <sval> L_BRACKET R_BRACKET SEMICOLON COLON /* Symbols */
%token <sval> NUM
%token <sval> PID

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
							{
								Variable* tmp = new Variable($1, -1);
								tmp->isNum = true;
							}
						|	id
						;

id					:	PID
							{
								Variable* tmp = new Variable($1, -1);
								tmp->isVar = true;
							}
						|	PID L_BRACKET PID R_BRACKET
							{
								// TODO: Getting variable from table if exists
								$$ = new Variable($1, -1);
							}
						|	PID	L_BRACKET NUM R_BRACKET
							{
								// TODO: Getting variable from table if exists
								$$ = new Variable($1, -1);
							}
						;

%%
int main()
{
  yyparse();
  return 0;
}

int yyerror(const char *p)
{
	cerr << "Error: " << p << " in line " << yylineno << endl;
	exit(1);
	return 1;
}
