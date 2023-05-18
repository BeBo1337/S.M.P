#include "FanPageException.h"

FanPageException::FanPageException(const int& error)
{
	switch (error)
	{
	case FP_NOT_FOUND:
		str = "Fan Page not found!";
		break;
	case FP_NAME_TAKEN:
		str = "Name of Fan Page already in use!";
		break;
	}
}

char const* FanPageException::what() const
{
	return str.c_str();
}
