%{
	#include "parser.tab.h"
	#include <iostream>
	using namespace std;
%}

%option noyywrap

NUMBER			[0-9]+
PID					[_a-z]+

WHITESPACE	[ \t\r]+

%x COMMENT
%%

<INITIAL>{
"["						{BEGIN(COMMENT);}

\n						{++yylineno;}
{WHITESPACE}

"DECLARE"			{return DECLARE;}
"IN"					{return IN;}
"END"					{return END;}

"IF"					{return IF;}
"THEN"				{return THEN;}
"ELSE"				{return ELSE;}
"ENDIF"				{return ENDIF;}

"WHILE"				{return WHILE;}
"DO"					{return DO;}
"ENDWHILE"		{return ENDWHILE;}
"ENDDO"				{return ENDDO;}

"FOR"					{return FOR;}
"FROM"				{return FROM;}
"TO"					{return TO;}
"DOWNTO"			{return DOWNTO;}
"ENDFOR"			{return ENDFOR;}

"READ"				{return READ;}
"WRITE"				{return WRITE;}

{PID}					{
								yylval.sval = (char*) strdup(yytext);
								return PID;
							}

{NUMBER}			{
								yylval.ival = (char*) strdup(yytext);
								return NUM;
							}

":="					{return ASSIGN;}

"+"						{return ADD;}
"-"						{return SUB;}
"*"						{return MUL;}
"/"						{return DIV;}
"%"						{return MOD;}

"="						{return EQ;}
"!="					{return NEQ;}
"<"						{return LT;}
">"						{return GT;}
"<="					{return LE;}
">="					{return GE;}

")"						{return R_BRACKET;}
"("						{return L_BRACKET;}
";"						{return SEMICOLON;}
":"						{return COLON;}

}

<COMMENT>{
.*"]"					{BEGIN(INITIAL);}
.*
\n						{++yylineno;}
}

%%
