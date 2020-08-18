#include "stdlib.h"
#include "tslib.hpp"

bool 
check_mod97(const char *acc)
{
	QString s;

	while(*acc)
	{
		if(*acc >= '0' && *acc <= '9')
			s << (*acc);

		acc++;
	}

	int check = atoi(s.sub(s.len()-2,2));

	__int64 big = 0;

	for(int i=0;i<s.len()-2;i++)
	{
		big = big * 10 + (s[i]-'0');
	}

	if((big % 97) != check)
		return false;
	else
		return true;
}

