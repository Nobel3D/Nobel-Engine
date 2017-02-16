#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
NE_NAMEUSING

Camera::Camera()
{
    pPosition = vec3(0,0,0);
    pCenterObject = vec3(0, 0, 0);
    pUpObject = vec3(0, 0, 0);
    fNear = 0.f;
    fFar = 0.f;
}

Camera::Camera(vec3 position, vec3 center, vec3 up, Float _near, Float _far)
{
	setPosition(position);
	setTarget(center, up);
	setLimits(_near, _far);
}

int Camera::setPosition(vec3 position)
{
    pPosition = position;

	return 1;
}

int Camera::setTarget(vec3 center, vec3 up)
{
    pCenterObject = center;
    pUpObject = up;

	return 1;
}

int Camera::setLimits(Float _near, Float _far)
{
    fNear = _near;
    fFar = _far;
	return 1;
}

mat4 Camera::lookAt()
{
    return glm::lookAt(pPosition,			//camera position;
                       pCenterObject,		//look origins
                       pUpObject);			//head position
}

mat4 Camera::ortho(Float left, Float right, Float bottom, Float top)
{
	return glm::ortho((float)left, (float)right, (float)bottom, (float)top, 0.0f, 100.0f);
}

mat4 Camera::projection(Float fov, Resolution* res)
{
    return glm::perspective(glm::radians((float)fov), res->getRatio(), (float)fNear, (float)fFar);
}
