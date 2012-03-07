// Precompiled Header - Includes that every file needs

#ifndef STDAFX_H__
#define STDAFX_H__


// Lean and Mean - Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
// Windows.h - Has a lot of stuff we need for Windows applications
#include <Windows.h>

//	Common includes
//		Vector - dynamic array
#include <vector>
using std::vector;
//		String - dynamic string
#include <string>
using std::string;
//		FStream - for file I/O
#include <fstream>
using std::fstream;
using std::ofstream;
using std::ifstream;
//		List and Map - for event system
#include <list>
#include <map>
using std::multimap;
using std::pair;
using std::list;
//		Queue - for message system
#include <queue>
using std::queue;

//		CTime - seeding random numbers
#include <ctime>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// For timeGetTime
#pragma comment(lib, "Winmm.lib")

// Wrappers
#include "Wrappers/CSGD_TextureManager.h"
#include "Wrappers/CSGD_Direct3D.h"
#include "Wrappers/CSGD_DirectInput.h"
#include "Wrappers/CSGD_XAudio2.h"
#include "Wrappers/SGD_Math.h"
#include "Wrappers/SGD_Util.h"
#include "Util/UtilStructs.h"
#include "Util/ByteUtil.h"

// Our files
#include "CGame.h"

// Singleton Macros
#define TEX_MNG		CSGD_TextureManager::GetInstance()
#define D3D			CSGD_Direct3D::GetInstance()
#define INPUT		CSGD_DirectInput::GetInstance()
#define AUDIO		CSGD_XAudio2::GetInstance()
#define GAME		CGame::GetInstance()

#endif