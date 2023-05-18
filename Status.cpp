#include "Status.h"

Status::Status(const string& c) : content(c), refcounter(new int(0))
{
	// current date and time on the current system
	time_t now = time(0);
	// convert now to string form
	string date_time = ctime(&now);
	timeOfUpload = date_time;
}

Status::Status(const string& c, const string& time) : content(c), timeOfUpload(time), refcounter(new int(0))
{
}

/*
	For cpy c'tor
*/
Status& Status::operator=(const Status& other)
{
	content = other.content;
	timeOfUpload = other.timeOfUpload;
	increaseRef();
	return *this;
}

/*
	For move c'tor
*/
Status& Status::operator=(Status&& other)
{
	if (this != &other)
	{
		content = other.content;
		timeOfUpload = other.timeOfUpload;
		other.content = EMPTY_STRING;
		other.timeOfUpload = EMPTY_STRING;
	}

	return *this;
}

/*
	Compares between two Statuse's contents
*/
bool Status::operator==(const Status& other)
{
	if (content == other.content)
		return true;
	return false;
}

bool Status::operator!=(const Status& other)
{
	if (content != other.content)
		return true;
	return false;
}

/*
	Print status.
*/
void Status::printStatus() const
{
	cout << "On " << timeOfUpload << content << endl << "This status is in Black & White"  << endl << endl;
}

ostream& operator<<(ostream& out, const Status& s)
{
	out << TEXT_STATUS << " " << s.timeOfUpload << s.content << endl;
	return out;
}
