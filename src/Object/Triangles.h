#pragma once

#include <nedef.h>
#include <Graphics/NObject.h>
#include <Data/Point.h>

NE_NAMESTART
    class Triangles : public NObject
    {
    private:
        Point3* geo_pTriangle1;
        Point3* geo_pTriangle2;
        Point3* geo_pTriangle3;

    public:
        Triangles(Point3* _1, Point3* _2, Point3* _3);
        ~Triangles();

        void Draw();
        void Load();
        void Destroy();
        void Rotate(Float _rotation, Axis _ax);
};

NE_NAMECLOSE
