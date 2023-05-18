#pragma once
#include "Includes.h"
#include "Member.h"
#include "Status.h"
#include "ImageStatus.h"
#include "VideoStatus.h"
#include "FanPage.h"
#include "MemberException.h"
#include "FanPageException.h"
#include "SMPException.h"


enum token{ EMPTY, MEMBER , FAN_PAGE };
enum menu{ NONE , NEW_MEMBER , NEW_FAN_PAGE , NEW_STATUS, PRINT_STATUSES , PRINT_FEED , NEW_FRIENDSHIP ,
	REMOVE_FRIENDSHIP , ADD_TO_FAN_PAGE , REMOVE_FROM_FAN_PAGE, PRINT_ALL , PRINT_ALL_FRIENDS_OR_FANS, EXIT};
enum status_type{ TEXT = 1, IMAGE, VIDEO};

class SMP {
	vector<Member*> members;
	vector<FanPage*> fanPages;

	template<class T> void enterStatus(T& curr);
	void getDB();
	void InitDB();
	void exitPS();
	Status* getStatus(ifstream& inFile);
	void convertStatus(Status* stat, int i, char token, ofstream& outFile) const;
public:
	SMP();
	~SMP();
	void launch();
	SMP(const SMP& other) { *this = other; }; // cpy c'tor
	SMP(SMP&& other) { *this = std::move(other); };  // move c'tor
	SMP& operator=(const SMP& other);
	SMP& operator=(SMP&& other);
	void doAction(int token);
	void addMember();
	void addFanPage();
	void checkName(const string& name, int token) const;
	void addStatus();
	void allStatusPrint() const;
	void printMemberFeed() const;
	void addFriendship();
	void removeFriendship();
	void addFanToPage();
	void removeFanFromPage();
	void printDatabase() const;
	void printFriendsOrFans() const;
	int findIndMembers(const Member& member) const;
	int findIndFanPages(const FanPage& fanpage) const;

	
};

