/*
* =====================================================================================
*
*       Filename:  Unit.h
*
*    Description:  用于初始化工作
*
*        Version:  1.0
*        Created:  2007年07月12日 22时17分41秒 CST
*       Revision:  none
*       Compiler:  gcc
*
*         Author:  lerosua (), lerosua@gmail.com
*        Company:  Cyclone
*
* =====================================================================================
*/ 
#ifndef  UNIT_FILE_HEADER_INC
#define  UNIT_FILE_HEADER_INC
#include <gtkmm/main.h>
//#include "icalk.h"


class GUnit
{

public:
        static void init(const char* user);
        static const char* getImagePath()
        {
                return imagePath;
        }

        static const char* getSoundPath()
        {
                return soundPath;
        }

        static const char* getHomePath()
        {
                return homePath;
        }

        static const char* getUserPath()
        {
                return userPath;
        }

        static const char* getLogPath()
        {
                return logPath;
        }

        static const char* getIconPath()
        {
                return iconPath;
        }

        static const char* getTempPath()
        {
                return tempPath;
        }

private:
        static char imagePath[512];
        static char soundPath[512];
        static char homePath[512];
        static char userPath[512];
        static char logPath[512];
        static char iconPath[512];
        static char tempPath[512];
};

#endif   /* ----- #ifndef UNIT_FILE_HEADER_INC  ----- */

