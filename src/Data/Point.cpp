#include "Point.h"

NL_NAMEUSING

NE_NAMESTART

Point::Point()
{
	x = 0.0f;
	y = 0.0f;
}

Point::Point(Float _x, Float _y)
{
	x = _x;
	y = _y;
}

bool Point::operator==(Point &addMe)
{
	return this->x == addMe.x && this->y == addMe.y;
}


Point3::Point3()
{
}

Point3::Point3(Point3 & copy)
{
	x = copy.x;
	y = copy.y;
	z = copy.z;
}

Point3::Point3(Float _x, Float _y, Float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Point3 Point3::operator=(Point3 &addMe)
{
	this->x = addMe.x;
	this->y = addMe.y;
	this->z = addMe.z;

	return *this;
}
bool Point3::operator==(Point3 &addMe)
{
	return this->x == addMe.x && this->y == addMe.y && this->z == addMe.z;
}

NE_NAMECLOSE
