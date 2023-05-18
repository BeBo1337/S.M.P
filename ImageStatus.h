#pragma once
#include "Includes.h"
#include "Status.h"

class ImageStatus : public Status {

public:
	ImageStatus(const string& c);
	ImageStatus(const string& c , const string& time);
	~ImageStatus() = default;
	void printStatus() const override;
	friend ostream& operator<<(ostream& out, const ImageStatus& s);
};