#pragma once

//+//	Create variadic template with syntax something like (func_name, "Head{0}|Body{1}:{2}{1}-{0}", arg0, arg1, arg2)

//<3// thanks to https://codereview.stackexchange.com/questions/187183/create-a-c-string-using-printf-style-formatting printf-like variadic templates

#include <fstream>
#include <cstdarg>
#include <iomanip>
#include "_Time.h"

#define OVERWRITE_STL_SYNC // with this the class Log will call std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
//#undef OVERWRITE_STL_SYNC // uncomment this line if you don't want it

#if defined(__linux__) || defined(LINUX)
constexpr char		DIR_DELIMITER		= '/';
const string		NULL_FILE_REDIRECT	= " 2> /dev/null";
#elif				defined(_WIN32)
constexpr char		DIR_DELIMITER		= '\\';
const std::string	NULL_FILE_REDIRECT	= " 2> nul";
#else
#error				_WIN32, __linux__ and LINUX undefined - system not recognized
#endif // defined(__linux__) or defined(LINUX)

//<3// thanks to https://stackoverflow.com/a/8488201/16614732 for the line below
#define __LOG_FILENAME__ (std::strrchr(__FILE__, DIR_DELIMITER) ? std::strrchr(__FILE__, DIR_DELIMITER) + 1 : __FILE__)

#ifdef				_DEBUG
constexpr char		LOG_DEBUG_CHAR		= 'D';		// D if debug, R if release
#else				// !_DEBUG
constexpr char		LOG_DEBUG_CHAR		= 'R';		// D if debug, R if release
#endif

class Log {
public:
	Log(const Log&) = delete;
	~Log();
private:
	const enum ThreatLevels : uint8_t {		// Warning level to log
		ErrorLvl, WarningLvl, InfoLvl
	}; ThreatLevels showThreatLevel;

	const enum VerboseLevels : uint8_t {		// Head, or head and body
		NoVerbose, LowVerbose, FullVerbose
	}; VerboseLevels verboseLevel;

	char logFilePath[100];

#pragma warning(suppress : 4251) // this file will be compiled with the rest of the code so this warning is superfluous
	std::ofstream logFile;

	short bodyLen;			// specifies how many character per line (after 3 tabs)
	char line[120];			// remember to change it each time

	void startup();
	Log(uint8_t threatLevel = 2, uint8_t verboseLevel = 2);
	static Log instance;

public:
	static Log& Get();

	void setLevel(uint8_t threatLevel, uint8_t verboseLevel);

	// definitions in Log.tpp since they're templates
	template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view, typename B = std::string_view>
	void info(Fu func_name, Fi file_name, int line, H head, B body, ...);
	template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view>
	void info(Fu func_name, Fi file_name, int line, H head);


	template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view, typename B = std::string_view>
	void success(Fu func_name, Fi file_name, int line, H head, B body, ...);
	template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view>
	void success(Fu func_name, Fi file_name, int line, H head);


	template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view, typename B = std::string_view>
	void warn(Fu func_name, Fi file_name, int line, H head, B body, ...);
	template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view>
	void warn(Fu func_name, Fi file_name, int line, H head);


	template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view, typename B = std::string_view>
	void error(Fu func_name, Fi file_name, int line, H head, B body, ...);
	template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view>
	void error(Fu func_name, Fi file_name, int line, H head);

	template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view, typename B = std::string_view>
	void assert_(Fu func_name, Fi file_name, int line, bool condition, H head, B body, ...);
	template<typename Fu = std::string_view, typename Fi = std::string_view, typename H = std::string_view>
	void assert_(Fu func_name, Fi file_name, int line, bool condition, H head);
};

#include "../src/Log.tpp"