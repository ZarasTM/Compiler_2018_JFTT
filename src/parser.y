/*
 * TODO: ADD FUCKING IF'S AND CHECK CONDITIONAL STATEMENTS
 * Registers G, H (used for loading arrays and variables)
 * Register A (used for index input)
 * Register F (used to hold result of arythmetic operations)
 * All above registers are sacred and no important data should be held there
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
							  addLine("HALT");
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
						|	IF condition THEN commands
							{
								addLine("JUMP 0");
								labeler->addJump();
								labeler->addLabel();
							}
							ELSE commands ENDIF
							{
								labeler->addLabel();
								labeler->fixIf();
							}
						|	IF condition THEN commands ENDIF
							{
								labeler->addLabel();
								labeler->fixIf();
							}
						|	WHILE
							{
									labeler->addLabel();
							}
							condition DO commands ENDWHILE
							{
								addLine("JUMP 0");
								labeler->addJump();
								labeler->addLabel();
								labeler->fixWhile();
							}
						|	DO
							{
								labeler->addLabel();
							}
							commands WHILE condition ENDDO
							{
								addLine("JUMP 0");
								labeler->addJump();
								labeler->addLabel();
								labeler->fixWhile();
							}
						|	FOR PID FROM value TO value	DO commands ENDFOR
						|	FOR PID FROM value DOWNTO value	DO commands ENDFOR
						|	READ id SEMICOLON
							{
								if(DEBUG) {
									cout << "Reading ";
									if($2->isArr){
										cout << $2->name << "(" << $2->varIndex << ") " << endl;
									}else{
										cout << $2->name << endl;
									}
								}
								getRead($2);
							}
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
							{
								if(DEBUG){
									cout << "Adding ";
									if($1->isArr){
										cout << $1->name << "(" << $1->varIndex << ") ";
									}else{
										cout << $1->name;
									}
									cout << " + ";
									if($3->isArr){
										cout << $3->name << "(" << $3->varIndex << ") " << endl;
									}else{
										cout << $3->name << endl;
									}
								}
								operationGen->getADD($1, $3);
								Variable* tmp = new Variable("ADD_RES", -1);
								tmp->isRes = true;
								$$ = tmp;
							}
						|	value SUB value
							{
								if(DEBUG){
									cout << "Subtracting ";
									if($1->isArr){
										cout << $1->name << "(" << $1->varIndex << ") ";
									}else{
										cout << $1->name;
									}
									cout << " - ";
									if($3->isArr){
										cout << $3->name << "(" << $3->varIndex << ") " << endl;
									}else{
										cout << $3->name << endl;
									}
								}
								operationGen->getSUB($1, $3);
								Variable* tmp = new Variable("SUB_RES", -1);
								tmp->isRes = true;
								$$ = tmp;
							}
						|	value MUL value
							{
								if(DEBUG){
									cout << "Multiplying ";
									if($1->isArr){
										cout << $1->name << "(" << $1->varIndex << ") ";
									}else{
										cout << $1->name;
									}
									cout << " * ";
									if($3->isArr){
										cout << $3->name << "(" << $3->varIndex << ") " << endl;
									}else{
										cout << $3->name << endl;
									}
								}
								operationGen->getMUL($1, $3);
								Variable* tmp = new Variable("MUL_RES", -1);
								tmp->isRes = true;
								$$ = tmp;
							}
						|	value DIV value
							{
								if(DEBUG){
									cout << "Dividing ";
									if($1->isArr){
										cout << $1->name << "(" << $1->varIndex << ") ";
									}else{
										cout << $1->name;
									}
									cout << " / ";
									if($3->isArr){
										cout << $3->name << "(" << $3->varIndex << ") " << endl;
									}else{
										cout << $3->name << endl;
									}
								}
								operationGen->getDIV($1, $3);
								Variable* tmp = new Variable("DIV_RES", -1);
								tmp->isRes = true;
								$$ = tmp;
							}
						|	value MOD value
							{
								if(DEBUG){
									cout << "Preforming modulo ";
									if($1->isArr){
										cout << $1->name << "(" << $1->varIndex << ") ";
									}else{
										cout << $1->name;
									}
									cout << " mod(";
									if($3->isArr){
										cout << $3->name << "(" << $3->varIndex << "))" << endl;
									}else{
										cout << $3->name << ")" << endl;
									}
								}
								operationGen->getMOD($1, $3);
								Variable* tmp = new Variable("MOD_RES", -1);
								tmp->isRes = true;
								$$ = tmp;
							}
						;

condition		:	value EQ value
							{
								if(DEBUG){
									cout << "Checking if ";
									if($1->isArr){
										cout << $1->name << "(" << $1->varIndex << ") ";
									}else{
										cout << $1->name;
									}
									cout << " = ";
									if($3->isArr){
										cout << $3->name << "(" << $3->varIndex << ")" << endl;
									}else{
										cout << $3->name << ")" << endl;
									}
								}
								operationGen->getEQ($1, $3);
								labeler->addJump();
							}
						|	value NEQ value
							{
								if(DEBUG){
									cout << "Checking if ";
									if($1->isArr){
										cout << $1->name << "(" << $1->varIndex << ") ";
									}else{
										cout << $1->name;
									}
									cout << " != ";
									if($3->isArr){
										cout << $3->name << "(" << $3->varIndex << ")" << endl;
									}else{
										cout << $3->name << ")" << endl;
									}
								}
								operationGen->getNEQ($1, $3);
								labeler->addJump();
							}
						|	value LT value
							{
								if(DEBUG){
									cout << "Checking if ";
									if($1->isArr){
										cout << $1->name << "(" << $1->varIndex << ") ";
									}else{
										cout << $1->name;
									}
									cout << " < ";
									if($3->isArr){
										cout << $3->name << "(" << $3->varIndex << ")" << endl;
									}else{
										cout << $3->name << ")" << endl;
									}
								}
								operationGen->getLT($1, $3);
								labeler->addJump();
							}
						|	value GT value
							{
								if(DEBUG){
									cout << "Checking if ";
									if($1->isArr){
										cout << $1->name << "(" << $1->varIndex << ") ";
									}else{
										cout << $1->name;
									}
									cout << " > ";
									if($3->isArr){
										cout << $3->name << "(" << $3->varIndex << ")" << endl;
									}else{
										cout << $3->name << ")" << endl;
									}
								}
								operationGen->getGT($1, $3);
								labeler->addJump();
							}
						|	value LE value
							{
								if(DEBUG){
									cout << "Checking if ";
									if($1->isArr){
										cout << $1->name << "(" << $1->varIndex << ") ";
									}else{
										cout << $1->name;
									}
									cout << " <= ";
									if($3->isArr){
										cout << $3->name << "(" << $3->varIndex << ")" << endl;
									}else{
										cout << $3->name << ")" << endl;
									}
								}
								operationGen->getLE($1, $3);
								labeler->addJump();
							}
						|	value GE value
							{
								if(DEBUG){
									cout << "Checking if ";
									if($1->isArr){
										cout << $1->name << "(" << $1->varIndex << ") ";
									}else{
										cout << $1->name;
									}
									cout << " >= ";
									if($3->isArr){
										cout << $3->name << "(" << $3->varIndex << ")" << endl;
									}else{
										cout << $3->name << ")" << endl;
									}
								}
								operationGen->getGE($1, $3);
								labeler->addJump();
							}
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
