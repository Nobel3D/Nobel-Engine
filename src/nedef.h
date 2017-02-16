#pragma once

#include <NBL.h>
#include <stdio.h>

#define NE_NAMESTART namespace NobelEngine {
#define NE_NAMECLOSE }
#define NE_NAMEUSING using namespace NobelEngine;
#define NE_LOGPATH "engine.log"

typedef unsigned int GLuint;
typedef float GLfloat;
typedef unsigned short GLushort;
typedef int COOR;

#define NE_LOG(sector, message) { LOG(sector, message, NE_LOGPATH) }

#define LOGFORM(message) {      Log::Add("FORM", message, NE_LOGPATH); \
                                if(NL_DEBUG) STRERR(message); }

#define ERRORFORM(message) {    Log::Add("FORM", message, NE_LOGPATH); \
                                STRERR(message); }

#define LOGOBJ(message) {      Log::Add("Drawable", message, NE_LOGPATH); \
                                if(NL_DEBUG) STRERR(message); }

#define ERROROBJ(message) {    Log::Add("Drawable", message, NE_LOGPATH); \
                                STRERR(message); }

#define LOGSHADER(message) {    Log::Add("COMPILESHADER", message, NE_LOGPATH); \
                                if(NL_DEBUG) STRERR(message); }
#define ERRORSHADER(message) {  Log::Add("ERRORSHADER", message, NE_LOGPATH); \
                                STRERR(message); }

