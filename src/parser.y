/* Compiler for simple iterative language SIL
 *	TODO: Add class for getting variables in different forms (var, arr(var), arr(const))
 * Last two registers G, H and register A are sacred and no important data should be held there
 */
%{
	#include <iostream>
	#include <string>
	#include "../src/utils/Variable.h"
	#include "../src/utils/main.h"
	#include "../src/utils/utility.h"

	int yylex();
	int yyerror(const char *p);
	extern int yylineno;

	using namespace std;

	bool DEBUG = false;
	//bool DEBUG = true;
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
							{
								finish();
							}
						;

declaration	:	declaration PID SEMICOLON
							{
								if(DEBUG) cout << "Declaring variable " << $2 << endl;
								symTab->declare($2);
							}
						|	declaration PID L_BRACKET NUM COLON NUM R_BRACKET SEMICOLON
							{
								if(DEBUG) cout << "Declaring table " << $2 << " from " << $4 << " to " << $6 << endl;
								symTab->declareArray($2, $4, $6);
							}
						| %empty
						;

commands		:	commands command
						|	command
						;

command			:	id ASSIGN expression SEMICOLON
							{
								if(DEBUG){
									cout << "Assigning ";
									if($3->isArr){
										cout << $3->name << "(" << $3->varIndex << ") ";
									}else{
										cout << $3->name;
									}
									cout << " to ";
									if($1->isArr){
										cout << $1->name << "(" << $1->varIndex << ") " << endl;
									}else{
										cout << $1->name << endl;
									}
								}
								assign($1, $3);
							}
						|	IF condition THEN commands ELSE commands ENDIF
						|	IF condition THEN commands ENDIF
						|	WHILE	condition DO commands ENDWHILE
						|	DO commands WHILE condition ENDDO
						|	FOR PID FROM value TO value	DO commands ENDFOR
						|	FOR PID FROM value DOWNTO value	DO commands ENDFOR
						|	READ id SEMICOLON
						|	WRITE value SEMICOLON
							{
								if(DEBUG) {
									cout << "Writing ";
									if($2->isArr){
										cout << $2->name << "(" << $2->varIndex << ") " << endl;
									}else{
										cout << $2->name << endl;
									}
								}
								getWrite($2);
							}
						| %empty
						;

expression	:	value {$$ = $1;}
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
								$$ = tmp;
							}
						|	id {$$ = $1;}
						;

id					:	PID
							{
								Variable* tmp = new Variable($1, -1);
								tmp->isVar = true;
								$$ = tmp;
							}
						|	PID L_BRACKET PID R_BRACKET
							{
								// tmp: isArr, isVar, varIndex=var
								Variable* tmp = new Variable($1, -1);
								tmp->isArr = true;
								tmp->isVar = true;
								tmp->varIndex = $3;
								$$ = tmp;
							}
						|	PID	L_BRACKET NUM R_BRACKET
							{
								Variable* tmp = new Variable($1, -1);
								tmp->isArr = true;
								tmp->isNum = true;
								tmp->varIndex = $3;
								$$ = tmp;
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
