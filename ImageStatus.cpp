#include "ImageStatus.h"

ImageStatus::ImageStatus(const string& c) : Status(c)
{
}

ImageStatus::ImageStatus(const string& c, const string& time) : Status(c,time)
{
}

void ImageStatus::printStatus() const
{
	cout << "On " << timeOfUpload << "a picture of " << content << endl;
	cout << "This Image is in color" << endl << endl;
}

ostream& operator<<(ostream& out, const ImageStatus& s)
{
	out << IMAGE_STATUS <<" " << s.timeOfUpload << s.content << endl;
	return out;
}
