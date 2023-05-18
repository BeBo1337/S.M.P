#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <stdlib.h>

#define DATABASE_NAME "database.txt"

#define ADD_MEMBER 'm'
#define ADD_FANPAGE 'f'
#define ADD_FRIENDSHIP 'a'
#define ADD_MEMBER_FANPAGE 'b'
#define ADD_STATUS_MEMBER 'c'
#define ADD_STATUS_FANPAGE 'd'
#define TEXT_STATUS 't'
#define IMAGE_STATUS 'i'
#define VIDEO_STATUS 'v'

#define INIT 100
#define FEED_NUM 10
#define NOT_FOUND -1
#define EMPTY_STRING ""

struct Date {
	int day;
	int month;
	int year;
};

using namespace std;