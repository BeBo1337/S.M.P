#pragma once
#include "Includes.h"
#include "Status.h"

class VideoStatus : public Status {

public:
	VideoStatus(const string& c);
	VideoStatus(const string& c, const string& time);
	~VideoStatus() = default;
	void printStatus() const override;
	friend ostream& operator<<(ostream& out, const VideoStatus& s);
};