#include "SMP.h"

SMP::SMP()
{
	members.reserve(INIT);
	fanPages.reserve(INIT);
}

SMP::~SMP()
{
	for (auto curr : members)
		delete curr;
	for (auto curr : fanPages)
		delete curr;
}

SMP& SMP::operator=(const SMP& other)
{
	for (const auto& curr : other.members)
		members.push_back(new Member(*curr));
	for (const auto& curr : other.fanPages)
		fanPages.push_back(new FanPage(*curr));
	return *this;
}

/*
	For move c'tor
*/
SMP& SMP::operator=(SMP&& other)
{
	if (this != &other)
	{
		for (int i = 0; i < other.members.size(); i++)
		{
			members.push_back(other.members.at(i));
			other.members.at(i) = nullptr;
		}
		for (int i = 0; i < other.fanPages.size(); i++)
		{
			fanPages.push_back(other.fanPages.at(i));
			other.fanPages.at(i) = nullptr;
		}
	}

	return *this;
}

void SMP::launch()
{
	getDB();
	cout << "Welcome to SMP!" << endl;
	int token = NONE;
	while (token != EXIT)
	{
		try
		{
			cout << endl;
			cout << "Please choose one of the following:" << endl;
			cout << "1 - Create a new member" << endl;
			cout << "2 - Create a new fan-page" << endl;
			cout << "3 - Add a new status" << endl;
			cout << "4 - Print all statuses of a member/fan-page" << endl;
			cout << "5 - Print the feed of a member" << endl;
			cout << "6 - Add friendship between two members" << endl;
			cout << "7 - Remove friendship between two members" << endl;
			cout << "8 - Add a member to a fan-page" << endl;
			cout << "9 - Remove a member from a fan-page" << endl;
			cout << "10 - Print all registered members and fan pages" << endl;
			cout << "11 - Print all friends of a member / all members of a fan-page" << endl;
			cout << "12 - Exit\n" << endl;
			cin >> token;
			doAction(token);
		}
		catch (const MemberException& e)
		{
			cout << e.what() << endl;
		}
		catch (const FanPageException& e)
		{
			cout << e.what() << endl;
		}
		catch (const SMPException& e)
		{
			cout << e.what() << endl;
		}
		catch (const bad_alloc& e)
		{
			cout << e.what() << endl;
		}
		catch (const exception& e)
		{
			cout << e.what() << endl;
		}
	}
	cout << "Goodbye!" << endl;
}

void SMP::doAction(int token)
{
	switch (token) {
	case NEW_MEMBER:
		addMember();
		return;
	case NEW_FAN_PAGE:
		addFanPage();
		return;
	case NEW_STATUS:
		addStatus();
		return;
	case PRINT_STATUSES:
		allStatusPrint();
		return;
	case PRINT_FEED:
		printMemberFeed();
		return;
	case NEW_FRIENDSHIP:
		addFriendship();
		return;
	case REMOVE_FRIENDSHIP:
		removeFriendship();
		return;
	case ADD_TO_FAN_PAGE:
		addFanToPage();
		return;
	case REMOVE_FROM_FAN_PAGE:
		removeFanFromPage();
		return;
	case PRINT_ALL:
		printDatabase();
		return;
	case PRINT_ALL_FRIENDS_OR_FANS:
		printFriendsOrFans();
		return;
	case EXIT:
		exitPS();
		return;
	default:
		cout << "Invalid input!\n" << endl;
		return;
	}
}

/*
* Adds a new member to the facebook database.
*/
void SMP::addMember()
{
	Date dob;
	string name;

	cout << "Please enter name of member: " << flush;
	cin.ignore();
	getline(cin, name);
	checkName(name, MEMBER);

	cout << "Please enter year of birth: " << flush;
	cin >> dob.year;

	cout << "Please enter month of birth: " << flush;
	cin >> dob.month;

	cout << "Please enter day of birth: " << flush;
	cin >> dob.day;

	members.push_back(new Member(name, dob));
	cout << "Action Completed Successfully!" << endl;
}

/*
	Adds a new fan page to the facebook database.
*/
void SMP::addFanPage()
{
	string name;
	bool check = false;

	cout << "Enter name of FanPage: " << flush;
	cin.ignore();
	getline(cin, name);
	checkName(name, FAN_PAGE);

	fanPages.push_back(new FanPage(name));
	cout << "Action Completed Successfully!" << endl;
}

/*
 Checks if a name is already in use.
 Token 1 to search for a member, Token 2 to search for a fan page.
*/
void SMP::checkName(const string& name, int token) const
{
	if (token == MEMBER) // Search for member.
	{
		for (Member* curr : members)
		{
			if(curr->getName() == name)
			{
				MemberException e(NAME_TAKEN);
				throw e;
			}
		}
	}
	else // Search for fan page.
	{
		for (FanPage* curr : fanPages)
		{
			if (curr->getName() == name)
			{
				FanPageException e(FP_NAME_TAKEN);
				throw e;
			}
		}
	}
}

/*
	Adds a new status to a member / fan page of choice.
*/
void SMP::addStatus()
{
	int token = EMPTY;
	string name;
	Status stat;

	cout << "For a Member/FanPage, please choose 1/2: " << flush;
	cin >> token;

	if (token == MEMBER) // Adds to Member.
	{
		cout << "Enter name of the member: " << flush;
		cin.ignore();
		getline(cin, name);

		for (Member* curr : members)
		{
			if (curr->getName() == name)
			{
				enterStatus(curr);
				cout << "Action Completed Successfully!" << endl;
				return;
			}
		}
		MemberException e(MEMBER_NOT_FOUND);
		throw e;
	}

	else if (token == FAN_PAGE) // Adds to Fan Page.
	{
		cout << "Enter name of fan-page: " << flush;
		cin.ignore();
		getline(cin, name);

		for (FanPage* curr : fanPages)
		{
			if (curr->getName() == name)
			{
				enterStatus(curr);
				cout << "Action Completed Successfully!" << endl;
				return;
			}
		}
		FanPageException e(FP_NOT_FOUND);
		throw e;
	}
	SMPException e(INVALID_TOKEN);
	throw e;
}

/*
	Print all statuses of a member / fan page of choice.
*/
void SMP::allStatusPrint() const
{
	int token = NONE;
	string name;
	cout << "For a Member / FanPage, please choose 1 / 2: " << flush;
	cin >> token;

	if (token == MEMBER) // For Member.
	{
		cout << "Enter name of the member: " << flush;
		cin.ignore();
		getline(cin ,name);
		for (Member* curr : members)
		{
			if (curr->getName() == name)
			{
				curr->printStatuses();
				cout << "Action Completed Successfully!" << endl;
				return;
			}
		}
		MemberException e(MEMBER_NOT_FOUND);
		throw e;
	}

	else if (token == FAN_PAGE) // For Fan Page.
	{
		cout << "Enter name of fan-page: " << flush;
		cin.ignore();
		getline(cin , name);
		for (FanPage* curr : fanPages)
		{
			if (curr->getName() == name)
			{
				curr->printStatuses();
				cout << "Action Completed Successfully!" << endl;
				return;
			}
		}
		FanPageException e(FP_NOT_FOUND);
		throw e;
	}
	SMPException e(INVALID_TOKEN);
	throw e;
}


/*
	Prints feed of a member of choice.
*/
void SMP::printMemberFeed() const
{
	string name;
	cout << "Enter name of the member: " << flush;
	cin.ignore();
	getline(cin ,name);

	for (Member* curr : members)
	{
		if (curr->getName() == name)
		{
			curr->printFeed();
			cout << "Action Completed Successfully!" << endl;
			return;
		}
	}
	MemberException e(MEMBER_NOT_FOUND);
	throw e;
}


/*
	Checks for valid input (names of Members exist in database) if so adds friendship between said members.
*/
void SMP::addFriendship()
{
	string name1;
	string name2;

	cout << "Enter name of the member #1: " << flush;
	cin.ignore();
	getline(cin, name1);
	cout << "Enter name of the member #2: " << flush;
	getline(cin, name2);

	if (name1 == name2)
	{
		MemberException e(SAME_MEMBER);
		throw e;
	}

	Member* ptr1 = nullptr, * ptr2 = nullptr;
	for (Member* curr : members)
	{
		if (curr->getName() == name1)
			ptr1 = curr;
		if (curr->getName() == name2)
			ptr2 = curr;
	}

	if (ptr1 == nullptr || ptr2 == nullptr)
	{
		MemberException e(MEMBER_NOT_FOUND);
		throw e;
	}

	*ptr1 += *ptr2;
	cout << "Action Completed Successfully!" << endl;
}


/*
	Checks for valid input (names of Members exist in database) if so removes the friendship of said members.
*/
void SMP::removeFriendship()
{
	string name1;
	string name2;

	cout << "Enter name of the member #1: " << flush;
	cin.ignore();
	getline(cin, name1);
	cout << "Enter name of the member #2: " << flush;
	getline(cin, name2);

	if (name1 == name2)
	{
		MemberException e(SAME_MEMBER);
		throw e;
	}

	Member* ptr1 = nullptr, * ptr2 = nullptr;
	for (Member* curr : members)
	{
		if (curr->getName() == name1)
			ptr1 = curr;
		if (curr->getName() == name2)
			ptr2 = curr;
	}

	if (ptr1 == nullptr || ptr2 == nullptr)
	{
		MemberException e(MEMBER_NOT_FOUND);
		throw e;
	}

	ptr1->removeMember(ptr2);
	ptr2->removeMember(ptr1);
	cout << "Action Completed Successfully!" << endl;
}


/*
	Checks it input is valid (names of Fan Page and Member exist in database) if so adds the Member to the Fan Page.
*/
void SMP::addFanToPage()
{	
	string nameFP;
	string nameM;

	Member* ptrM = nullptr;
	FanPage* ptrFP = nullptr;

	cout << "Enter name of the fan page: " << flush;
	cin.ignore();
	getline(cin ,nameFP);
	cout << "Enter name of the member: " << flush;
	getline(cin ,nameM);

	for (FanPage* curr : fanPages)
	{
		if (curr->getName() == nameFP)
		{
			ptrFP = curr;
			break;
		}
	}

	if (ptrFP == nullptr)
	{
		FanPageException e(FP_NOT_FOUND);
		throw e;
	}

	for (Member* curr : members)
	{
		if (curr->getName() == nameM)
		{
			ptrM = curr;
			break;
		}
	}

	if (ptrM == nullptr)
	{
		MemberException e(MEMBER_NOT_FOUND);
		throw e;
	}

	*ptrM += *ptrFP;
	cout << "Action Completed Successfully!" << endl;
}


/*
	Checks if input is valid (names of Fan Page and Member) if so removes the Member from the Fan Page. 
*/
void SMP::removeFanFromPage()
{
	string nameFP;
	string nameM;

	Member* ptrM = nullptr;
	FanPage* ptrFP = nullptr;

	cout << "Enter name of the fan page: " << flush;
	cin.ignore();
	getline(cin, nameFP);
	cout << "Enter name of the member: " << flush;
	getline(cin, nameM);


	for (FanPage* curr : fanPages)
	{
		if (curr->getName() == nameFP)
		{
			ptrFP = curr;
			break;
		}
	}

	if (ptrFP == nullptr)
	{
		FanPageException e(FP_NOT_FOUND);
		throw e;
	}

	for (Member* curr : members)
	{
		if (curr->getName() == nameM)
		{
			ptrM = curr;
			break;
		}
	}

	if (ptrM == nullptr)
	{
		MemberException e(MEMBER_NOT_FOUND);
		throw e;
	}

	ptrM->LeaveFanPage(ptrFP);
	cout << "Action Completed Successfully!" << endl;
}


/*
	Prints all Members and Fan Pages that exist at the momnet.
*/
void SMP::printDatabase() const
{
	int counter = 0;
	cout << "Members:\n" << endl;
	for (Member* curr : members)
	{
		cout << counter + 1 << " - " << curr->getName() << endl;
		counter++;
	}

	counter = 0;
	cout << "\nFan Pages:\n" << endl;
	for (FanPage* curr : fanPages)
	{
		cout << counter + 1 << " - " << curr->getName() << endl;
		counter++;
	}
	cout << "Action Completed Successfully!" << endl;
}

/*
	Checks if input is valid (Member/Fan Page exists) if so, print all friends/fans of member/fan page.
*/
void SMP::printFriendsOrFans() const
{
	int token = NONE;
	string name;
	Status stat;

	cout << "For a Member/FanPage, please choose 1/2: " << flush;
	cin >> token;

	if (token == MEMBER) // Member:
	{
		cout << "Enter name of the member: " << flush;
		cin.ignore();
		getline(cin, name);
		for (Member* curr : members)
		{
			if (curr->getName() == name)
			{
				curr->printMembers();
				cout << "Action Completed Successfully!" << endl;
				return;
			}
		}
		MemberException e(MEMBER_NOT_FOUND);
		throw e;
	}
	else if (token == FAN_PAGE) // Fan Page:
	{
		cout << "Enter name of fan-page: " << flush;
		cin.ignore();
		getline(cin, name);
		for (FanPage* curr : fanPages)
		{
			if (curr->getName() == name)
			{
				curr->printMembers();
				cout << "Action Completed Successfully!" << endl;
				return;
			}
		}
		FanPageException e(FP_NOT_FOUND);
		throw e;
	}
	SMPException e(INVALID_TOKEN);
	throw e;
}

int SMP::findIndMembers(const Member& member)const
{
	for (int i = 0; i < members.size(); i++)
	{
		if (members[i] == &member)
		{
			return i;
		}
	}
}

int SMP::findIndFanPages(const FanPage& fanpage)const
{
	for (int i = 0; i < fanPages.size(); i++)
	{
		if (fanPages[i] == &fanpage)
		{
			return i;
		}
	}
}

/*
	Gets and returns a status
*/
template <class T>
void SMP::enterStatus(T& curr)
{
	string content;
	int type;
	cout << "Enter 1 for Text, 2 for Image, 3 for Video: " << flush;
	cin >> type;
	cin.ignore();
	switch (type)
	{
	case TEXT:
	{
		cout << "Please enter a status: " << endl;
		getline(cin, content);
		Status* stat1 = new Status(content);
		curr->writeStatus(stat1);
		break;
	}
	case IMAGE:
	{
		cout << "Please enter the image's description: " << endl;
		getline(cin, content);
		Status* stat2 = new ImageStatus(content);
		curr->writeStatus(stat2);
		break;
	}
	case VIDEO:
	{
		cout << "Please enter the video's description:  " << endl;
		getline(cin, content);
		Status* stat3 = new VideoStatus(content);
		curr->writeStatus(stat3);
		break;
	}
	default:
	{
		SMPException e(INVALID_TOKEN);
		throw e;
	}
	}
}

/*
	Gets database from a file
*/
void SMP::getDB()
{
	ifstream inFile(DATABASE_NAME);
	if (!inFile) // if the database file doesn't exist (probably on the first run) - create a hardcoded database.
	{
		InitDB();// Adds requested hardcoded members and fanpages and the links needed.
		return;
	}

	char command;
	int ind1, ind2;
	Date dob;
	string line, curr;
	
	while (inFile.peek() != EOF)
	{
		try
		{
			inFile >> command;
			switch (command)
			{
			case ADD_MEMBER:
			{
				inFile >> line;
				curr = line;
				inFile >> dob.year;
				inFile >> dob.month;
				inFile >> dob.day;
				members.push_back(new Member(curr, dob));
				break;
			}
			case ADD_FANPAGE:
			{
				inFile >> curr;
				fanPages.push_back(new FanPage(curr));
				break;
			}
			case ADD_FRIENDSHIP:
			{
				inFile >> ind1 >> ind2;
				*members.at(ind1) += *members.at(ind2);
				break;
			}
			case ADD_MEMBER_FANPAGE:
			{
				inFile >> ind1 >> ind2;
				*members.at(ind1) += *fanPages.at(ind2);
				break;
			}
			case ADD_STATUS_MEMBER:
			{
				inFile >> ind1;
				members.at(ind1)->writeStatus(getStatus(inFile));
				break;
			}
			case ADD_STATUS_FANPAGE:
			{
				inFile >> ind1;
				fanPages.at(ind1)->writeStatus(getStatus(inFile));
				break;
			}
			}
		}
		catch (const MemberException& e) //We don't need to handle it in a unique way, we know it will try to add every friendship twice
		{}
	}
	inFile.close();
}

Status* SMP::getStatus(ifstream& inFile)
{
	char command;
	string line1, line2;
	inFile >> command;
	switch (command)
	{
		case TEXT_STATUS:
		{
			inFile >> command; //gets rid of the extra space
			getline(inFile, line1);
			getline(inFile, line2);
			return new Status(line2, line1 += "\n");
		}
		case IMAGE_STATUS:
		{
			inFile >> command; //gets rid of the extra space
			getline(inFile, line1);
			getline(inFile, line2);
			return new ImageStatus(line2, line1 += "\n");
		}
		case VIDEO_STATUS:
		{
			inFile >> command; //gets rid of the extra space
			getline(inFile, line1);
			getline(inFile, line2);
			return new VideoStatus(line2, line1 += "\n");
		}
	}

}

/*
	Saves database to a file
*/
void SMP::exitPS()
{
	ofstream outFile(DATABASE_NAME, ios::trunc);
	for (auto curr : members)
	{
		outFile << ADD_MEMBER << " " << *curr << flush;
	}
	for (auto curr : fanPages)
	{
		outFile << ADD_FANPAGE << " " << *curr << flush;
	}
	for (int i = 0; i < members.size(); i++)
	{
		for (int j = 0; j < members.at(i)->getMemberArraySize(); j++)
		{
			outFile << ADD_FRIENDSHIP << " " << i << " " << findIndMembers(members.at(i)->getMember(j)) << endl;
		}
		for (int j = 0; j < members.at(i)->getFanPageArraySize(); j++)
		{
			outFile << ADD_MEMBER_FANPAGE << " " << i << " " << findIndFanPages(members.at(i)->getFanPage(j)) << endl;
		}
		for (int j = 0; j < members.at(i)->getStatusArraySize(); j++)
		{
			Status* st = members.at(i)->getStatus(j);
			convertStatus(st, i, ADD_STATUS_MEMBER, outFile);
		}
	}
	for (int i = 0; i < fanPages.size(); i++)
	{
		for (int j = 0; j < fanPages.at(i)->getStatusArraySize(); j++)
		{
			Status* st = fanPages.at(i)->getStatus(j);
			convertStatus(st, i, ADD_STATUS_FANPAGE, outFile);
		}
	}
	outFile.close();
}

/*
	 Write status to out file, also writes if it's a status of member/fan page and the index in the members/fan pages array.
 */
void SMP::convertStatus(Status* stat, int i, char token, ofstream& outFile) const
{
	auto* tmp1 = dynamic_cast<ImageStatus*>(stat); // Check if status received is an Image Status.
	auto* tmp2 = dynamic_cast<VideoStatus*>(stat); // Check if status received is a Video Status.

	// Write to the out file the correct status format.
	if (tmp1 != nullptr)
		outFile << token << " " << i << " " << *tmp1 << flush;  
	else if (tmp2 != nullptr)
		outFile << token << " " << i << " " << *tmp2 << flush;  
	else // (the object wasn't a child of Status)
		outFile << token << " " << i << " " << *stat << flush;   
}


/*
Hard coded database addon including members, fan pages, statusesand friendships.
*/
void SMP::InitDB()
{
	Date d;
	d.day = d.month = 1;
	d.year = 2000;

	Status* s11 = new Status("hello im idan");
	Status* s12 = new Status("nice to meet you!");

	Status* s21 = new Status("hello im lebo");
	Status* s22 = new Status("whats up?!");

	Status* s31 = new Status("hello im oren");
	Status* s32 = new Status("bros yo");

	Status* s41 = new Status("fp1 fan page");
	Status* s42 = new Status("white rules");

	Status* s51 = new Status("fp2 fan page");
	Status* s52 = new Status("red is the best");

	Status* s61 = new Status("fp3 fan page");
	Status* s62 = new Status("blue supremacy");

	members.push_back(new Member("idan", d));
	members.push_back(new Member("lebo", d));
	members.push_back(new Member("oren", d));

	//makes idan and lebo friends
	*members.at(0) += *members.at(1);

	//makes idan and oren friends
	*members.at(0) += *members.at(2);

	fanPages.push_back(new FanPage("fp1"));
	fanPages.push_back(new FanPage("fp2"));
	fanPages.push_back(new FanPage("fp3"));

	//idan joins fp1
	*members.at(0) += *fanPages.at(0);
	//lebo joins fp2
	*members.at(1) += *fanPages.at(1);
	//oren join fp3
	*members.at(2) += *fanPages.at(2);

	//adds statuses to idan
	members.at(0)->writeStatus(s11);
	members.at(0)->writeStatus(s12);

	//adds statuses to lebo
	members.at(1)->writeStatus(s21);
	members.at(1)->writeStatus(s22);

	//adds statuses to oren
	members.at(2)->writeStatus(s31);
	members.at(2)->writeStatus(s32);

	//adds statuses to fp1
	fanPages.at(0)->writeStatus(s41);
	fanPages.at(0)->writeStatus(s42);

	//adds statuses to fp2
	fanPages.at(1)->writeStatus(s51);
	fanPages.at(1)->writeStatus(s52);

	//adds statuses to fp3
	fanPages.at(2)->writeStatus(s61);
	fanPages.at(2)->writeStatus(s62);

}
