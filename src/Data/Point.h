#pragma once

#include <nedef.h>

NL_NAMEUSING

NE_NAMESTART

    class Point
    {
    public:
        Float x;
        Float y;

        Point();
        Point(Float _x, Float _y);

        bool operator==(Point &addMe);
    };
    class Point3
    {
    public:
        Float x;
        Float y;
        Float z;

        Point3();
        Point3(Point3 &copy);
        Point3(Float _x, Float _y, Float _z);

        Point3 operator=(Point3 &addMe);
        bool operator==(Point3 &addMe);
        bool operator!=(Point3 &addMe);
    };

NE_NAMECLOSE
