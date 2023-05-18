#pragma once
#include "Includes.h"

enum ERROR_CODE{INVALID_DATE_OF_BIRTH ,ALREADY_FRIENDS, ALREADY_FAN, NOT_FRIENDS, NOT_FAN,
	NAME_TAKEN, MEMBER_NOT_FOUND, SAME_MEMBER};

class MemberException : public exception {
	string str;
public:
	MemberException(const int& error);
	char const* what() const override;
};
