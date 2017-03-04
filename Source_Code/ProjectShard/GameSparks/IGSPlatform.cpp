#if defined(WINAPI_FAMILY)
#define __STDC_WANT_SECURE_LIB__ 0
#define sprintf_s(buf, size, fmt, ...) sprintf(buf, fmt, __VA_ARGS__)
#define swprintf_s(buf, size, fmt, ...) swprintf(buf, size, fmt, __VA_ARGS__)
#endif

#include <GameSparks/IGSPlatform.h>

#if GS_TARGET_PLATFORM == GS_PLATFORM_ANDROID
#	include <sys/types.h>
#	include <unistd.h>
#	include <fstream>
#elif GS_TARGET_PLATFORM == GS_PLATFORM_WIN32
#if WINAPI_FAMILY_DESKTOP_APP == WINAPI_FAMILY
#	include <locale>
#	include <shlwapi.h>
#	include <shlobj.h>
#	pragma comment(lib,"shlwapi.lib")
#	define GS_WINDOWS_DESKTOP
#else
#	include <Objbase.h>
//#	include <wrl.h>
#	undef nullptr
#	include <wrl.h>
#	include <windows.storage.h>
#	include <codecvt>
#	define GS_WINDOWS_APP
extern "C" int _getch(void) { return 0; }

#endif
#	pragma comment(lib, "Rpcrt4.lib")
#	include <Rpc.h>
#elif GS_TARGET_PLATFORM == GS_PLATFORM_MAC
#   include "TargetConditionals.h"
#   include <sys/stat.h> // for mkdir

	/* works like mkdir(1) used as "mkdir -p" */
	static void mkdirp(const char *dir) {
	    char tmp[PATH_MAX];
	    char *p = NULL;
	    size_t len;
	    
	    snprintf(tmp, sizeof(tmp),"%s",dir);
	    len = strlen(tmp);
	    if(tmp[len - 1] == '/')
	        tmp[len - 1] = 0;
	    for(p = tmp + 1; *p; p++)
	        if(*p == '/') {
	            *p = 0;
	            mkdir(tmp, S_IRWXU | S_IRWXG);
	            *p = '/';
	        }
	    mkdir(tmp, S_IRWXU | S_IRWXG);
	}

	gsstl::string get_osx_device_id();
#elif GS_TARGET_PLATFORM == GS_PLATFORM_IOS
    gsstl::string gs_ios_get_writeable_base_path();
    gsstl::string get_ios_device_id();
#elif defined(__ORBIS__)
#	include <save_data.h>
#	include <cassert>
#	include <stdlib.h>
#else
//#	include <uuid/uuid.h>
#endif

#if GS_TARGET_PLATFORM == GS_PLATFORM_MARMALADE
#	include <s3e.h>
#endif

namespace GameSparks { namespace Core {


// trim from start
static inline gsstl::string &ltrim(gsstl::string &s) {
        s.erase(s.begin(), gsstl::find_if(s.begin(), s.end(), gsstl::not1(gsstl::ptr_fun<int, int>(isspace))));
        return s;
}

// trim from end
static inline gsstl::string &rtrim(gsstl::string &s) {
        s.erase(gsstl::find_if(s.rbegin(), s.rend(), gsstl::not1(gsstl::ptr_fun<int, int>(isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline gsstl::string &trim(gsstl::string &s) {
        return ltrim(rtrim(s));
}

#if GS_TARGET_PLATFORM != GS_PLATFORM_MAC && GS_TARGET_PLATFORM != GS_PLATFORM_IOS
static gsstl::string generate_guid()
{
	gsstl::string ret = "NO-UUID-SUPPORT-FOR-THIS-PLATFORM";

	#ifdef WIN32
		#if defined(GS_WINDOWS_DESKTOP)
			UUID uuid;
			UuidCreate(&uuid);

			unsigned char * str;
			UuidToStringA(&uuid, &str);

			ret = gsstl::string((char*)str);

			RpcStringFreeA(&str);
		#else
			GUID guid;
			if (S_OK != CoCreateGuid(&guid))
				return "GUID-CREATION-FAILED";

			OLECHAR* bstrGuid;
			StringFromCLSID(guid, &bstrGuid);

			typedef std::codecvt_utf8<wchar_t> convert_type;
			std::wstring_convert<convert_type, wchar_t> converter;

			ret = converter.to_bytes(bstrGuid);

			// ensure memory is freed
			::CoTaskMemFree(bstrGuid);
		#endif
	#elif defined(ANDROID)
		gsstl::ifstream ifs("/proc/sys/kernel/random/uuid");
		ifs >> ret;
	#elif defined(__ORBIS__)
	SceKernelUuid uuid;
	int result = sceKernelUuidCreate(&uuid);
	assert(result == 0);

	char hex[sizeof(uuid)*2+1];
	snprintf(hex, sizeof(hex), "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x"
		, (int)uuid.timeLow
		, (int)uuid.timeMid
		, (int)uuid.timeHiAndVersion
		, (int)uuid.clockSeqHiAndReserved
		, (int)uuid.clockSeqLow
		, (int)uuid.node[0]
		, (int)uuid.node[1]
		, (int)uuid.node[2]
		, (int)uuid.node[3]
		, (int)uuid.node[4]
		, (int)uuid.node[5]

	);
	ret = hex;

	#endif
	/*#else
		uuid_t uuid;
		uuid_generate_random(uuid);
		char s[37];
		uuid_unparse(uuid, s);
		ret = s;
	#endif
		return ret;
	*/
	//assert(false);
	return trim(ret);
}
#endif


gsstl::string IGSPlatform::GetDeviceId() const
{
	static gsstl::string device_id;

	if (device_id.empty())
	{
		#if GS_TARGET_PLATFORM == GS_PLATFORM_MAC
			device_id = get_osx_device_id();
		#elif GS_TARGET_PLATFORM == GS_PLATFORM_IOS
			device_id = get_ios_device_id();
		#elif GS_TARGET_PLATFORM == GS_PLATFORM_MARMALADE
			device_id = s3eDeviceGetString(S3E_DEVICE_UNIQUE_ID);
		#else
			device_id = LoadValue("device_id");
			if (device_id.empty())
			{
				device_id = generate_guid();
				StoreValue("device_id", device_id);
			}
		#endif

		device_id = trim(device_id);
	}

	return device_id;
}



gsstl::string IGSPlatform::GetDeviceOS() const
{
	#if GS_TARGET_PLATFORM == GS_PLATFORM_MAC
		return "OSX";
	#elif GS_TARGET_PLATFORM == GS_PLATFORM_IOS
		return "IOS";
	#elif GS_TARGET_PLATFORM == GS_PLATFORM_ANDROID
		return "Android";
	#elif GS_TARGET_PLATFORM == GS_PLATFORM_WIN32
		return "W8";
	#elif GS_TARGET_PLATFORM == GS_PLATFORM_LINUX
		return "Linux";
	#elif GS_TARGET_PLATFORM == GS_PLATFORM_MARMALADE
		return "Marmelade";
	#elif GS_TARGET_PLATFORM == GS_PLATFORM_BADA
		return "Bada";
	#elif GS_TARGET_PLATFORM == GS_PLATFORM_BLACKBERRY
		return "Blackberry";
	#elif GS_TARGET_PLATFORM == GS_PLATFORM_NACL
		return "NaCl";
	#elif GS_TARGET_PLATFORM == GS_PLATFORM_EMSCRIPTEN
		return "emscripten";
	#elif GS_TARGET_PLATFORM == GS_PLATFORM_TIZEN
		return "Tizen";
	#elif GS_TARGET_PLATFORM == GS_PLATFORM_QT5
		return "QTS";
	#elif GS_TARGET_PLATFORM == GS_PLATFORM_WINRT
		return "W8";
	#elif GS_TARGET_PLATFORM == GS_PLATFORM_WP8
		return "WP8";
	#else
	#   error "Unsupported platform"
		return "Unknown";
	#endif
}


gsstl::string IGSPlatform::GetPlatform() const
{
	return GetDeviceOS();
}

#if defined(WIN32)
// convert UTF-8 string to wstring
static std::wstring utf8_to_wstring(const std::string& str)
{
	int output_size = MultiByteToWideChar(CP_UTF8, NULL, str.c_str(), static_cast<int>(str.size()), NULL, 0);
	assert(output_size > 0);
	gsstl::vector<wchar_t> buffer(output_size);
	int result = MultiByteToWideChar(CP_UTF8, NULL, str.c_str(), static_cast<int>(str.size()), buffer.data(), static_cast<int>(buffer.size()));
	(void)result; // unused in release builds
	assert( result == output_size );
	std::wstring ret(buffer.begin(), buffer.end());
	return ret;
	//std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	//return myconv.from_bytes(str);
}

// convert wstring to UTF-8 string
static std::string wstring_to_utf8(const std::wstring& str)
{
	int output_size = WideCharToMultiByte(CP_UTF8, NULL, str.c_str(), static_cast<int>(str.size()), NULL, 0, NULL, NULL);
	assert(output_size > 0);
	gsstl::vector<char> buffer(output_size);
	int result = WideCharToMultiByte(CP_UTF8, NULL, str.c_str(), static_cast<int>(str.size()), buffer.data(), static_cast<int>(buffer.size()), NULL, NULL);
	(void)result; // unused in release builds
	assert(result == output_size);
	std::string ret(buffer.begin(), buffer.end());
	return ret;

	//std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	//return myconv.to_bytes(str);
}
#endif

// variant of fopen that takes care of the fact, that we cannot use utf-8 for paths on windows
static FILE* gs_fopen(const gsstl::string& path, const char* mode)
{
#if defined(WIN32)
	return _wfopen(utf8_to_wstring(path).c_str(), utf8_to_wstring(mode).c_str());
#else
	return fopen(path.c_str(), mode);
#endif /* WIN32 */
}


void IGSPlatform::StoreValue(const gsstl::string& key, const gsstl::string& value) const
{
	// TODO: port to all the platforms
	FILE* f = gs_fopen(ToWritableLocation(key), "wb");
	assert(f);
	if (!f)
	{
    	DebugMsg("**** Failed to store value to '" + key + "'");
    	return;
	}
	size_t written = fwrite(value.c_str(), 1, value.size(), f);
    (void)(written);
    assert(written == value.size());
	fclose(f);
}


gsstl::string IGSPlatform::LoadValue(const gsstl::string& key) const
{
	// TODO: port to all the platforms
	FILE *f = gs_fopen(ToWritableLocation(key), "rb");
	
    if(!f)
    {
    	//DebugMsg("**** Failed to load value from '" + ToWritableLocation(key) + "'");
        return "";
    }
    
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	if (fsize <= 0)
	{
		fclose(f);
		return "";
	}
	fseek(f, 0, SEEK_SET);
    gsstl::vector<char> bytes(static_cast<gsstl::vector<char>::size_type>(fsize));
	size_t read_bytes = fread(&bytes.front(), 1, fsize, f);
    (void)(read_bytes);
	assert(read_bytes == static_cast<size_t>(fsize));
	fclose(f);
	return gsstl::string( bytes.begin(), bytes.end() );
}



gsstl::string IGSPlatform::ToWritableLocation(gsstl::string desired_name) const
{
	desired_name = "gamesparks_" + desired_name;

	#if GS_TARGET_PLATFORM == GS_PLATFORM_MARMALADE || defined(GS_OVERRIDE_TOWRITABLELOCATION) // marmalade || windows; Note, that windows is for testing only. You should not put the files into the working directoy
    // http://docs.madewithmarmalade.com/display/MD/S3E+File+overview
	// This should work on marmalade
	return desired_name;

	#elif GS_TARGET_PLATFORM == GS_PLATFORM_WIN32
		#if defined(GS_WINDOWS_DESKTOP)
			static gsstl::string base_path;

			if (base_path.empty())
			{
				wchar_t szPath[MAX_PATH];
				if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, 0, szPath)))
				{
					base_path = wstring_to_utf8(szPath);
				}
				else
				{
					DebugMsg("Failed to get CSIDL_APPDATA path.");
					base_path = "./";
					assert(false);
				}

				base_path = base_path + "\\GameSparks\\" + m_apiKey + "\\";

				std::replace(base_path.begin(), base_path.end(), '/', '\\');

				int result = SHCreateDirectoryExW(NULL, utf8_to_wstring(base_path).c_str(), NULL);

				if (
					result != ERROR_SUCCESS &&
					result != ERROR_FILE_EXISTS &&
					result != ERROR_ALREADY_EXISTS
					)
				{
					DebugMsg("Failed to create directory.");
					// if you end up here, you probably forgot to set-up your credentials.
					// The default credentials in the sample contain characters that are not valid in windows paths ('<' and '>')
					assert(false);
				}
			}

			assert(!base_path.empty());

			return base_path + desired_name;
		#else
			static std::wstring wbase_path = Windows::Storage::ApplicationData::Current->LocalFolder->Path->Data();
			static auto base_path = wstring_to_utf8(wbase_path);
			return base_path + "\\" + desired_name;
		#endif /* defined(GS_WINDOWS_DESKTOP) */


	#elif GS_TARGET_PLATFORM == GS_PLATFORM_MAC

    ////////////////// OS X
    static gsstl::string base_path;
    if (base_path.empty())
    {
		// the environment might not be correctly setup, then we store data in /tmp
        gsstl::string writable_path("/tmp/GameSparks");

		if(char* homedir = getenv("HOME"))
			writable_path = homedir;

		writable_path += "/Library/Application Support/GameSparks/" + m_apiKey + "/";
        
        struct stat s;// = {0};
        
        if (0 != stat(writable_path.c_str(), &s) ) // Check if directory exists
        {
            mkdirp(writable_path.c_str());
        }
    
        base_path = writable_path;
    }
    
    return base_path + desired_name;

	#elif GS_TARGET_PLATFORM == GS_PLATFORM_ANDROID

	//////////////////////////////// Android
	// http://stackoverflow.com/questions/6276933/getfilesdir-from-ndk
	static gsstl::string base_path = "";
	if (base_path.empty())
	{
		char buf[200]; // 64bit int can be 20 digits at most
		sprintf(buf, "/proc/%i/cmdline", (int)getpid());

		FILE* f = fopen(buf, "rb");
		if (!f)
		{
			DebugMsg("Failed to get writable path");
			return "./" + desired_name;
		}

		fread(buf, 1, sizeof(buf), f);
		fclose(f);

		if(buf[0] == '.') // if executed via adb shell
			return "./" + desired_name;

		// bytes not contains the list of null separated command line arguments, the string constructor below will copy until the first null byte
		base_path = "/data/data/" + gsstl::string(buf) + "/";
	}
	return base_path + desired_name;

    #elif GS_TARGET_PLATFORM == GS_PLATFORM_IOS
    static gsstl::string base_path = gs_ios_get_writeable_base_path();
    return base_path + "/" + desired_name;

	#elif defined(__ORBIS__)
	return "/data/" + desired_name;
	#else
    #   error "ToWritableLocation not implemented for this platform. If you're planing on overriding it yourself, please define GS_OVERRIDE_TOWRITABLELOCATION"
	#endif
}

}} // namespace GameSparks { namespace Core {
