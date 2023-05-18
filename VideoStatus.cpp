#include "VideoStatus.h"

VideoStatus::VideoStatus(const string& c) : Status(c)
{
}

VideoStatus::VideoStatus(const string& c, const string& time) : Status(c,time)
{
}

void VideoStatus::printStatus() const
{
	cout << "On " << timeOfUpload << "a video of " << content << endl;
	cout << "This Video is in color" << endl << endl;
}

ostream& operator<<(ostream& out, const VideoStatus& s)
{
	out << VIDEO_STATUS << " " << s.timeOfUpload << s.content << endl;
	return out;
}
