#include "string.h"
#include "stddef.h"
#include "stdio.h"
#include "util.h"
#include "string_token.h"

char *lpszStrLiteral = NULL;
int bufLen = 0;
int strLen = 0;
void beginString()
{
    if (lpszStrLiteral != NULL && bufLen > 0)
    {
        memset(lpszStrLiteral, 0, bufLen);
        strLen = 0;
    } 
    else
    {
        bufLen = 256;
        strLen = 0;
        lpszStrLiteral = (char*)checked_malloc(bufLen);
        memset(lpszStrLiteral, 0, bufLen);
    }
}

string endString()
{
    return lpszStrLiteral;
}

static void enlargeBuf(int strLen)
{
    char *buf = lpszStrLiteral;
    if (strLen >= bufLen)
    {
        bufLen += strLen + strLen / 2 + 2;
        buf = checked_malloc(bufLen);
        memset(buf, 0, bufLen);
        strcpy(buf, lpszStrLiteral);
        lpszStrLiteral = buf;
    }
}

void onString(const char *str)
{
    printf("FOUND STRING: %s\n", str);
    strLen += strlen(str);
    enlargeBuf(strLen);
    strcat(lpszStrLiteral, str);
}

void onChar(char c)
{
    printf("FOUND CHAR: %c\n", c);
    enlargeBuf(strLen + 1);
    lpszStrLiteral[strLen] = c;
    ++strLen;
}

void onEscape(char *escape)
{
}


