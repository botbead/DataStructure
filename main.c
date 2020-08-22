#pragma hdrstop
#pragma argsused

#include <stdio.h>
#include "common.h"

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#define ARYLEN 200

int _tmain(int argc, _TCHAR* argv[]) 
{
	char c;
    unsigned *p;
	SAMPLE(&p, ARYLEN);
    TRAVERSING(p, ARYLEN);
    _SAMPLE(p);
    scanf("%c", &c);
	return 0;
}
