#pragma once
#include <Data/Float.h>
#include <Data/Point.h>
#include <Data/VideoMode.h>
#include <glm/glm.hpp>

using namespace glm;

NE_NAMESTART

    class Camera
    {
    private:
        vec3 pPosition;
        vec3 pCenterObject;
        vec3 pUpObject;
        Float fNear, fFar;
    public:
        Camera();
        Camera(vec3 position, vec3 center, vec3 up, Float _near, Float _far);

        int setPosition(vec3 position);
        int setTarget(vec3 center, vec3 up);
        int setLimits(Float _near, Float _far);
        mat4 lookAt();
        mat4 ortho(Float left, Float right, Float bottom, Float top);
        mat4 projection(Float FoV_Angle, Resolution* res);

    };

NE_NAMECLOSE
