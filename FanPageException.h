#pragma once
#include "Includes.h"

enum FAN_ERROR_CODE {FP_NOT_FOUND, FP_NAME_TAKEN};

class FanPageException : public exception {
	string str;
public:
	FanPageException(const int& error);
	char const* what() const override;
};