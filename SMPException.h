#pragma once
#include "Includes.h"

#define INVALID_TOKEN 0

class SMPException : public exception{
	string str;
public:
	SMPException(const int& error);
	char const* what() const override;
};