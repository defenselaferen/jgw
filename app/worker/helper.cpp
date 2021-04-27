#include <stdio.h>
#include <stdlib.h>

#include "../include/helper.h"

IF_S IF_T(int _SOURCE_BOOLEAN_) {
	switch(((int)((_SOURCE_BOOLEAN_ < 0) && (_SOURCE_BOOLEAN_ > 1))) + 1)
	{
		case 2:
		{
			switch(_SOURCE_BOOLEAN_ + 1)
			{
				case 2:
				{
					return IF_TRUE;
				}
				break;
				case 1:
				{
					return IF_FALSE;
				}
				break;
			}
		}
		break;
		default:
		{
			throw "Please give parameter boolean.";
		}
	}
}