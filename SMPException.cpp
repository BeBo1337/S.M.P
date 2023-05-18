#include "SMPException.h"

SMPException::SMPException(const int& error)
{
	if (error == INVALID_TOKEN)
		str = "Invalid Input!";
}

char const* SMPException::what() const
{
	return str.c_str();
}
