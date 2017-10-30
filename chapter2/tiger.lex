%{
#include <string.h>
#include "util.h"
#include "tokens.h"
#include "errormsg.h"
#include "string_token.h"

int charPos=1;

int yywrap(void)
{
 charPos=1;
 return 1;
}


void adjust(void)
{
 EM_tokPos=charPos;
 charPos+=yyleng;
}

%}

%s COMMENT STRING_LITERAL STRING_IGNORE
%%
<INITIAL>"/*"           {adjust(); BEGIN COMMENT; printf("begin comments : %d\n", EM_tokPos); }
<COMMENT>"*/"           {adjust(); BEGIN INITIAL; printf("end comments : %d\n", EM_tokPos); }
<COMMENT>.              {adjust(); continue; } 

<INITIAL>\"                             {adjust(); BEGIN STRING_LITERAL; printf("begin string literal: %d\n", EM_tokPos); beginString(); continue; }
<STRING_LITERAL>\\n                     {adjust(); onChar('\n'); continue; }
<STRING_LITERAL>\\t                     {adjust(); onChar('\t'); continue; }
<STRING_LITERAL>\\\^[a-zA-Z@\?\[]       {adjust(); continue; }
<STRING_LITERAL>\\([01][0-9][0-9]|2[0-4][0-9]|25[0-5])      {adjust(); onChar(atoi(yytext + 1)); continue; }
<STRING_LITERAL>\\\"                    {adjust(); onChar('\"'); continue; } 
<STRING_LITERAL>\\\\                    {adjust(); onChar('\\'); continue; }
<STRING_LITERAL>\\                      {adjust(); BEGIN STRING_IGNORE; printf("begin ignored string: %d\n", EM_tokPos); continue; }
<STRING_IGNORE>[ \t\n\r\f]              {adjust(); continue; }
<STRING_IGNORE>\\                       {adjust(); BEGIN STRING_LITERAL; printf("end ignored string: %d\n", EM_tokPos); continue; }
<STRING_LITERAL>\"                      {adjust(); BEGIN INITIAL; printf("end string literal:%d \n", EM_tokPos); yylval.sval = endString(); return STRING; } 
<STRING_LITERAL>.                       {adjust(); onString(yytext); continue; }


<INITIAL>" "            {adjust(); continue; }
<INITIAL>\t             {adjust(); continue; }
<INITIAL>\r             {adjust(); continue; }
<INITIAL>\n             {adjust(); EM_newline(); continue;}
<INITIAL>","            {adjust(); return COMMA;}
<INITIAL>":"            {adjust(); return COLON; }
<INITIAL>";"            {adjust(); return SEMICOLON; }
<INITIAL>"("            {adjust(); return LPAREN; }
<INITIAL>")"            {adjust(); return RPAREN; }
<INITIAL>"["            {adjust(); return LBRACK; }
<INITIAL>"]"            {adjust(); return RBRACK; }
<INITIAL>"{"            {adjust(); return LBRACE; }
<INITIAL>"}"            {adjust(); return RBRACE; }
<INITIAL>"."            {adjust(); return DOT; }
<INITIAL>"+"            {adjust(); return PLUS; }
<INITIAL>"-"            {adjust(); return MINUS; }
<INITIAL>"*"            {adjust(); return TIMES; }
<INITIAL>"/"            {adjust(); return DIVIDE; }
<INITIAL>"="            {adjust(); return EQ; }
<INITIAL>"<>"           {adjust(); return NEQ; }
<INITIAL>"<"            {adjust(); return LT; }
<INITIAL>"<="           {adjust(); return LE; }
<INITIAL>">"            {adjust(); return GT; }
<INITIAL>">="           {adjust(); return GE; }
<INITIAL>"&"            {adjust(); return AND; }
<INITIAL>"|"            {adjust(); return OR; }
<INITIAL>":="           {adjust(); return ASSIGN; }

<INITIAL>"for"          {adjust(); return FOR; }
<INITIAL>"while"        {adjust(); return WHILE; }
<INITIAL>"to"           {adjust(); return TO; }
<INITIAL>"break"        {adjust(); return BREAK; } 
<INITIAL>"let"          {adjust(); return LET; }
<INITIAL>"in"           {adjust(); return IN; }
<INITIAL>"end"          {adjust(); return END; }
<INITIAL>"function"     {adjust(); return FUNCTION; }
<INITIAL>"var"          {adjust(); return VAR; }
<INITIAL>"type"         {adjust(); return TYPE; }
<INITIAL>"array"        {adjust(); return ARRAY; }
<INITIAL>"if"           {adjust(); return IF; }
<INITIAL>"then"         {adjust(); return THEN; }
<INITIAL>"else"         {adjust(); return ELSE; }
<INITIAL>"do"           {adjust(); return DO; }
<INITIAL>"of"           {adjust(); return OF; }
<INITIAL>"nil"          {adjust(); return NIL; }

<INITIAL>[a-zA-Z]+[a-zA-Z0-9_]*         {adjust(); yylval.sval = String(yytext); return ID; }
<INITIAL>[0-9]+         {adjust(); yylval.ival=atoi(yytext); return INT; }

<INITIAL>.              {adjust(); EM_error(EM_tokPos,"illegal token"); }


%%

