#pragma once
#include "Includes.h"

class Status {
protected:
	string content;
	string timeOfUpload;
	int* refcounter;

public:
	Status() = default;
	Status(const string& c); 
	Status(const string& c, const string& time);
	virtual ~Status() = default;
	Status(const Status& other) { *this = other; }; // cpy c'tor
	Status(Status&& other) { *this = std::move(other); };  // move c'tor
	Status& operator=(const Status& other);
	Status& operator=(Status&& other);
	void increaseRef() { ++(*refcounter); }
	void decreaseRef() { if (--(*refcounter) <= 0) { delete refcounter; delete this; } }
	friend ostream& operator<<(ostream& out, const Status& s);
	bool operator==(const Status& other);
	bool operator!=(const Status& other);
	virtual void printStatus() const;
};
