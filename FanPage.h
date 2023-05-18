#pragma once
#include "Includes.h"
#include "Status.h"

class Member;

class FanPage {
protected:
	string name;
	int* refcounter;
	vector<Member*> memberArray;
	vector<Status*> statusArray;

public:
	FanPage() = default;
	FanPage(const string& _name);
	virtual ~FanPage(); 
	FanPage(const FanPage& other) { *this = other; }; // cpy c'tor
	FanPage(FanPage&& other) { *this = std::move(other); };  // move c'tor
	FanPage& operator=(const FanPage& other);
	FanPage& operator=(FanPage&& other);
	void increaseRef() { ++(*refcounter); }
	void decreaseRef() { if (--(*refcounter) <= 0) { delete refcounter; delete this; } }
	virtual const string& getName() { return name; };
	virtual void writeStatus(Status* stat);
	virtual FanPage& operator+=(Member& member);
	bool operator>(FanPage& other) const;
	bool operator<(FanPage& other) const;
	friend ostream& operator<<(ostream& out, const FanPage& f);
	int getMemberArraySize() { return (int)memberArray.size(); }
	const Member& getMember(int ind) { return *memberArray.at(ind); }
	int getStatusArraySize() { return (int)statusArray.size(); }
	Status* getStatus(int ind) { return statusArray.at(ind); }
	virtual void removeMember(Member* member);
	void printStatuses() const;
	virtual void printMembers() const;
};
