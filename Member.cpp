#include "Member.h"
#include "MemberException.h"

Member::Member(const string& _name, const Date& _dateOfBirth) : FanPage(_name), dateOfBirth(_dateOfBirth)
{
	if (dateOfBirth.year < 1900 || dateOfBirth.year > 2022 || dateOfBirth.month < 1 || dateOfBirth.month > 12 ||
		dateOfBirth.day < 1 || dateOfBirth.day > 31)
	{
		MemberException e(INVALID_DATE_OF_BIRTH);
		throw e;
	}

	fpArray.reserve(INIT);
	feedArray.reserve(FEED_NUM);
	username_of_status.reserve(FEED_NUM);
}

Member::~Member()
{
	FanPage::~FanPage();
}

Member& Member::operator=(const Member& other)
{
	FanPage::operator=(other);
	dateOfBirth = other.dateOfBirth;
	for (const auto& curr : other.fpArray)
	{
		fpArray.push_back(curr);
		curr->increaseRef();
	}
	for (const auto& curr : other.feedArray)
	{
		feedArray.push_back(curr);
		curr->increaseRef();
	}
	for (const auto& curr : other.username_of_status)
		username_of_status.push_back(curr);
	return *this;
}

Member& Member::operator=(Member&& other)
{
	if (this != &other)
	{
		FanPage::operator=(other);
		dateOfBirth = other.dateOfBirth;

		for (int i = 0; i < other.fpArray.size(); i++)
		{
			fpArray.push_back(other.fpArray.at(i));
			other.fpArray.at(i) = nullptr;
		}
		for (int i = 0; i < other.feedArray.size(); i++)
		{
			feedArray.push_back(other.feedArray.at(i));
			other.feedArray.at(i) = nullptr;
		}
		for (int i = 0; i < other.username_of_status.size(); i++)
		{
			username_of_status.push_back(other.username_of_status.at(i));
			other.username_of_status.at(i) = nullptr;
		}
	}
	return *this;
}

/*
	Adds friendship between members (in-case they aren't already friends)
*/
Member& Member::operator+=(Member& other)
{
	for (Member* curr : memberArray)
	{
		if (curr == &other)
		{
			MemberException e(ALREADY_FRIENDS);
			throw e;
		}
	}

	memberArray.push_back(&other);
	other.memberArray.push_back(this);
	increaseRef();
	other.increaseRef();

	return *this;
}

/*
	Adds member to a fan page of choice (in-case he isn't a fan already)
*/
Member& Member::operator+=(FanPage& fp)
{	
	for (FanPage* curr : fpArray)
	{
		if (curr == &fp)
		{
			MemberException e(ALREADY_FAN);
			throw e;
		}
	}

	fpArray.push_back(&fp);
	fp.increaseRef();
	fp += *this;
	return *this;
}

/*
	Removes friendship between two members (in-case they are friends)
*/
void Member::removeMember(Member* member)
{
	int counter = 0;
	for (Member* curr : memberArray)
	{
		if (curr == member)
		{
			removeFriendFromFeed(member->getName());
			memberArray.erase(memberArray.begin() + counter);
			memberArray.at(counter)->decreaseRef();
			return;
		}
		counter++;
	}
	MemberException e(NOT_FRIENDS);
	throw e;
}

/*
	Updates the member's feed and removes the statuses of the member in which is not a friend anymore
*/
void Member::removeFriendFromFeed(const string& _name)
{
	for (int i = 0; i < username_of_status.size(); i++)
	{
		if (username_of_status.at(i) == _name)
		{
			username_of_status.erase(username_of_status.begin() + i);
			feedArray.erase(feedArray.begin() + i);
			feedArray.at(i)->decreaseRef();
			i--;
		}
	}
}

/*
	Removes a member as a fan from a fan page of choice (in-case he is a fan)
*/
void Member::LeaveFanPage(FanPage* fp)
{
	int counter = 0;
	for (FanPage* curr : fpArray)
	{
		if (curr == fp)
		{
			fpArray.erase(fpArray.begin() + counter);
			fpArray.at(counter)->decreaseRef();
			fp->removeMember(this);
			return;
		}
		counter++;
	}
	MemberException e(NOT_FAN);
	throw e;
}


/*
	Adds the new status to the statuses array.
*/
void Member::writeStatus(Status* stat)
{
	statusArray.push_back(stat);
	stat->increaseRef();
	addToFeed(stat, name);
}


/*
	Adds a new status to the feeds of all friends.
*/
void Member::addToFeed(Status* stat, string& username)
{
	bool isEmpty;
	int size;
	for (Member* currFriend : memberArray)
	{
		size = (int) currFriend->feedArray.size();
		isEmpty = currFriend->feedArray.empty();
		if (!isEmpty && size < FEED_NUM)
		{
			currFriend->feedArray.push_back(currFriend->feedArray.at(size - 1));
			currFriend->username_of_status.push_back(currFriend->username_of_status.at(size - 1));
		}

		for (int i = size - 1; i > 0; i--)
		{
			currFriend->feedArray.at(i) = currFriend->feedArray.at(i - 1);
			currFriend->username_of_status.at(i) = currFriend->username_of_status.at(i - 1);
		}

		if (isEmpty)
		{
			currFriend->feedArray.push_back(stat);
			currFriend->username_of_status.push_back(username);
		}
		else
		{
			currFriend->feedArray.at(0) = stat;
			currFriend->username_of_status.at(0) = username;
		}
		stat->increaseRef();
	}
}

/*
	Prints the feed of this member.
*/
void Member::printFeed() const
{
	cout << name << "'s Feed:" << endl;
	for (int i = 0; i < (int) feedArray.size(); i++)
	{
		cout << i+1 << " - By " << username_of_status.at(i) << " " << flush;
		feedArray.at(i)->printStatus();
	}
}


/*
	Prints the friends list of this member.
*/
void Member::printMembers() const
{
	int counter = 0;
	cout << name << "'s Friends:" << endl;
	for (Member* curr : memberArray)
	{
		cout << counter + 1 << " - " << flush;
		cout << curr->getName() << endl;
		counter++;
	}
}


/*
	Print all the fan pages the member is a fan of
*/
void Member::printFanPages() const
{
	int counter = 0;
    cout << "Member " << name << "'s Fan Pages Are: " << flush;
    for(FanPage* curr : fpArray)
    {
		cout << counter + 1 << " - " << flush;
        cout << curr->getName() << endl;
		counter++;
    }
}

ostream& operator<<(ostream& out, const Member& m)
{
	out << m.name << " " << m.dateOfBirth.year << " " << m.dateOfBirth.month << " " << m.dateOfBirth.day << endl;
	return out;
}
