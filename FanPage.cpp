
#include "Member.h"

FanPage::FanPage(const string& _name) : name(_name) , refcounter(new int(0))
{
	memberArray.reserve(INIT);
	statusArray.reserve(INIT);
}

FanPage::~FanPage()
{
	for (auto curr : statusArray)
		delete curr;
}

FanPage& FanPage::operator=(const FanPage& other)
{
	for (const auto& curr : other.memberArray)
	{
		memberArray.push_back(curr);
		curr->increaseRef();
	}
	for (const auto& curr : other.statusArray)
	{
		statusArray.push_back(curr);
		curr->increaseRef();
	}
	return *this;
}

FanPage& FanPage::operator=(FanPage&& other)
{
	if (this != &other)
	{
		for (int i = 0; i < other.memberArray.size(); i++)
		{
			memberArray.push_back(other.memberArray.at(i));
			other.memberArray.at(i) = nullptr;
		}
		for (int i = 0; i < other.statusArray.size(); i++)
		{
			statusArray.push_back(other.statusArray.at(i));
			other.statusArray.at(i) = nullptr;
		}
	}
	return *this;
}


/*
	Adds a given Status to the Status array of the Fan Page.
*/
void FanPage::writeStatus(Status* stat)
{	
	statusArray.push_back(stat);
	stat->increaseRef();
}


/*
	Adds the member on Fan Page fans array.
*/
FanPage& FanPage::operator+=(Member& member)
{
	memberArray.push_back(&member);
	member.increaseRef();
	return *this;
}


bool FanPage::operator>(FanPage& other) const
{
	if (memberArray.size() > other.memberArray.size())
		return true;
	return false;
}


bool FanPage::operator<(FanPage& other) const
{
	if (memberArray.size() < other.memberArray.size())
		return true;
	return false;
}

/*
	Removes the member from the Fan Page fans Array
*/
void FanPage::removeMember(Member* member)
{
	int counter = 0;
	for (Member* curr : memberArray)
	{
		if (curr == member)
		{
			memberArray.erase(memberArray.begin() + counter);
			memberArray.at(counter)->decreaseRef();
			break;
		}
		counter++;
	}
	return;
}

/*
	Print all statuses of this Fan Page.
*/
void FanPage::printStatuses() const
{	
	int counter = 0;
	cout << name << "'s Statuses:" << endl;
	for (Status* curr : statusArray)
	{
		cout << counter + 1 << " - " << flush;
		curr->printStatus();
		counter++;
	}
}


/*
	Print all the fans of this fan page.
*/
void FanPage::printMembers() const
{
	int counter = 0;
	cout << name << "'s Fans:" << endl;
	for (Member* curr : memberArray)
	{
		cout << counter + 1 << " - " << flush;
		cout << curr->getName() << endl;
		counter++;
	}
}

ostream& operator<<(ostream& out, const FanPage& f)
{
	out << f.name << endl;
	return out;
}
