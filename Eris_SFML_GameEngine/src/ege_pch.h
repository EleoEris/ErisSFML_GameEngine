#pragma once
// I'm not using this for compilation time but for the ease of access
#ifdef EGE_RELEASE
#	define USING_PROFILER
#endif

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <string_view>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <unordered_set>
#include <functional>


#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#ifdef EGE_PLATFORM_WINDOWS
#	include <Windows.h>
#endif // EGE_PLATFORM_WINDOWS

#include <Eris_Utility/Log.h>
#include <Eris_Utility/functions.h>

#include <ChernoInstrumentor/Instrumentor.h>

#include "States/GameState.h"
#include "States/MainMenuState.h"
#include "States/EditorState.h"
#include "core/WindowComponent.h"
#include "components/PhysicsComponent.h"
#include "components/AnimationComponent.h"
#include "components/HitboxComponent.h"
#include "Entities/Entity.h"
#include "Entities/Character.h"


///////////////
// constants //
///////////////

//C++++//			add the line below if upgrade to cpp20 and delete the define on the line after
//constexpr char* LOREM_LONG	= "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Scelerisque eleifend donec pretium vulputate sapien nec sagittis aliquam malesuada. Ornare massa eget egestas purus viverra accumsan in. Habitant morbi tristique senectus et netus et. Tincidunt vitae semper quis lectus. Mi ipsum faucibus vitae aliquet nec. Ac turpis egestas integer eget aliquet nibh. Ac auctor augue mauris augue neque gravida in. Quis commodo odio aenean sed. Turpis egestas pretium aenean pharetra magna ac. Vitae sapien pellentesque habitant morbi tristique senectus et. Vitae elementum curabitur vitae nunc. Ac felis donec et odio. At elementum eu facilisis sed odio. Eu mi bibendum neque egestas congue quisque. Elit ullamcorper dignissim cras tincidunt lobortis. Purus in massa tempor nec feugiat nisl pretium fusce. In metus vulputate eu scelerisque. Nunc lobortis mattis aliquam faucibus purus. Magna eget est lorem ipsum dolor sit amet consectetur." // Char array of 999 char + \0
#define			LOREM_LONG			"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Scelerisque eleifend donec pretium vulputate sapien nec sagittis aliquam malesuada. Ornare massa eget egestas purus viverra accumsan in. Habitant morbi tristique senectus et netus et. Tincidunt vitae semper quis lectus. Mi ipsum faucibus vitae aliquet nec. Ac turpis egestas integer eget aliquet nibh. Ac auctor augue mauris augue neque gravida in. Quis commodo odio aenean sed. Turpis egestas pretium aenean pharetra magna ac. Vitae sapien pellentesque habitant morbi tristique senectus et. Vitae elementum curabitur vitae nunc. Ac felis donec et odio. At elementum eu facilisis sed odio. Eu mi bibendum neque egestas congue quisque. Elit ullamcorper dignissim cras tincidunt lobortis. Purus in massa tempor nec feugiat nisl pretium fusce. In metus vulputate eu scelerisque. Nunc lobortis mattis aliquam faucibus purus. Magna eget est lorem ipsum dolor sit amet consectetur." // Char array of 999 char + \0
#define			LOREM				"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce ultrices lacus eget nisi congue, et posuere nunc mattis aliquam." // Char array of 127 char + \0

namespace MATH {
template <typename T> constexpr int sgn(T& val) {
	return (T(0) < val) - (val < T(0));
}

constexpr float	ROOT2		= 1.4142135623f;				// sqrt(2)
constexpr float	ROOT3		= 1.7320508075f;				// sqrt(3)

constexpr float	PI			= 3.1415926535f;
constexpr float	TAU			= 6.2831853071f;				// 2 * PI
constexpr float	EU			= 2.7182818284f;				// e
constexpr float	PHI			= 1.6180339887f;				// golden ratio

// doubles of constants
constexpr double dROOT2		= 1.4142135623730950488016;		// sqrt(2)
constexpr double dROOT3		= 1.7320508075688772935274;		// sqrt(3)

constexpr double dPI		= 3.1415926535897932384626;
constexpr double dTAU		= 6.2831853071795864769252;		// 2 * dPI
constexpr double dEU		= 2.7182818284590452353602;		// e
constexpr double dPHI		= 1.6180339887498948482045;		// golden ratio
}


////////////
// MACROS //
////////////


// ErisUtility _Time
#define			T_PROGRAM_START_TIME			_Time::s_programStartTime.getStr()		// returns string&, safe for file naming
#define			T_FILE_STR						_Time::s_file.getNowStr()				// returns string&, safe for file naming
#define			T_DATE_STR						_Time::s_date.getNowStr()				// returns string& with current date
#define			T_DATE_CHG_FORMAT(f)			_Time::s_date.changeFormat(f)			// changes date format
#define			T_TIME_STR						_Time::s_time.getNowStr()				// returns string& with current time
#define			T_TIME_CHG_FORMAT(f)			_Time::s_time.changeFormat(f)			// changes format of time
#define			T_DATETIME_STR					_Time::s_datetime.getNowStr()			// returns string& with current datetime
#define			T_DATETIMET_CHG_FORMAT(f)		_Time::s_datetime.changeFormat(f)		// changes format of datetime

// ErisUtility Log
// macros with _R suffix will work in release
#define			LOG_INFO_R(...)				Log::Get().info(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)		// head, body and args to format body in c-style
#define			LOG_WARN_R(...)				Log::Get().warn(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)		// head, body and args to format body in c-style
#define			LOG_SUCC_R(...)				Log::Get().success(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)	// head, body and args to format body in c-style
#define			LOG_ERR_R(...)				Log::Get().error(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)		// head, body and args to format body in c-style
#define			LOG_ASSERT(cond, ...)		Log::Get().assert_(__FUNCTION__, __LOG_FILENAME__, __LINE__, cond, __VA_ARGS__); if (cond) __debugbreak()

#ifdef			_DEBUG
#define			LOG_INFO(...)		Log::Get().info(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)		// head, body and args to format body in c-style
#define			LOG_WARN(...)		Log::Get().warn(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)		// head, body and args to format body in c-style
#define			LOG_SUCC(...)		Log::Get().success(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)	// head, body and args to format body in c-style
#define			LOG_ERR(...)		Log::Get().error(__FUNCTION__, __LOG_FILENAME__, __LINE__, __VA_ARGS__)		// head, body and args to format body in c-style
// #define				LOG_ASSERT(asser, head, ...)	Log::Get().assert_(__FUNCTION__, __LOG_FILENAME__, __LINE__, asser, head, __VA_ARGS__); if (asser) __debugbreak()

#else			// !_DEBUG
#define			LOG_LEVEL(...)
#define			LOG_INFO(...)
#define			LOG_WARN(...)
#define			LOG_SUCC(...)
#define			LOG_ERR(...)
//#define				LOG_ASSERT(...)
#endif				// _DEBUG

// Cherno Profiler
#ifdef			USING_PROFILER
#	define		PROFILER_BEGIN()	Cherno::Instrumentor::Get().BeginSession(T_PROGRAM_START_TIME + "_" + LOG_DEBUG_CHAR)
#	define		PROFILE_HERE		Cherno::InstrumentationTimer timer_##__FUNCTION__(__FUNCSIG__)
#	define		PROFILER_END()		Cherno::Instrumentor::Get().EndSession();
#else
#	define		PROFILER_BEGIN()
#	define		PROFILE_HERE
#	define		PROFILER_END()
#endif