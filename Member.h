#pragma once
#include "Includes.h"
#include "FanPage.h"

class Member : public FanPage {
	Date dateOfBirth;
	vector<FanPage*> fpArray;

	vector<Status*> feedArray;
	vector<string> username_of_status;

private:
	void addToFeed(Status* stat, string& username);
	void removeFriendFromFeed(const string& _name);

public:
	Member() = default;
	Member(const string& _name, const Date& _dateOfBirth);
	~Member() override;
	Member(const Member& other){ *this = other; }; // cpy c'tor
	Member(Member&& other){ *this = std::move(other); };  // move c'tor
	Member& operator=(const Member& other);
	Member& operator=(Member&& other);
	Member& operator+=(Member& other) override;
	Member& operator+=(FanPage& fp);
	friend ostream& operator<<(ostream& out, const Member& m);
	void removeMember(Member* member) override;
	void LeaveFanPage(FanPage* fp);
	void writeStatus(Status* stat) override;
	int getFanPageArraySize() { return (int)fpArray.size(); };
	const FanPage& getFanPage(int ind) { return *fpArray.at(ind); }
	void printFeed() const;
	void printMembers() const override;
    void printFanPages() const;

};