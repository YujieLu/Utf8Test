
#include <codecvt>
#include <iostream>

#include <visionnav/string/CharacterEncodingConvert.h>

using namespace std;

namespace visionnav
{
	namespace string
	{
		std::string cvtUcs2ToUtf8(const std::wstring & wstr)
		{
			std::string ret;
			try
			{
				std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
				ret = wcv.to_bytes(wstr);
			}
			catch (const std::exception & e) 
			{
				std::cerr << e.what() << std::endl;
			}
			return ret;
		}
		std::wstring cvtUtf8ToUcs2(const std::string & str)
		{
			std::wstring ret;
			try
			{
				std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
				ret = wcv.from_bytes(str);
			}
			catch (const std::exception & e) 
			{
				std::cerr << e.what() << std::endl;
			}
			return ret;
		}
		std::string cvtUcs2ToAnsi(const std::wstring & wstr)
		{
			setlocale(LC_ALL, "");
			std::string ret;
			std::mbstate_t state = {};
			const wchar_t *src = wstr.data();
			size_t len;
			auto err = wcsrtombs_s(&len, nullptr, 0, &src, 0, &state);
			if (static_cast<size_t>(-1) != len || !err) 
			{
				std::unique_ptr< char[] > buff(new char[len + 1]);
				err = wcsrtombs_s(&len, buff.get(), len + 1, &src, len, &state);
				if (static_cast<size_t>(-1) != len || !err)
				{
					ret = std::string(buff.get());
					//ret.assign(buff.get(), len);
				}
				else
				{
					cerr << "error converting UCS-2 to ANSI" << endl;
				}
			}
			else
			{
				cerr << "error determining the buffer size while converting UCS-2 to ANSI" << endl;
			}
			return ret;
		}
		std::wstring cvtAnsiToUcs2(const std::string & str)
		{
			std::wstring ret;
			std::mbstate_t state = {};
			size_t len;

			setlocale(LC_ALL, "");
			const char *src = str.c_str();
			auto err = mbsrtowcs_s(&len, nullptr, 0, &src, 0, &state);
			if (static_cast<size_t>(-1) != len || !err)
			{
				std::unique_ptr< wchar_t[] > buff(new wchar_t[len + 1]);
				mbsrtowcs_s(&len, buff.get(), len + 1, &src, len, &state);
				if (static_cast<size_t>(-1) != len || !err)
				{
					ret = std::wstring(buff.get());
					//ret.assign(buff.get(), len);
				}
				else
				{
					cerr << "error converting Ansi to UCS-2" << endl;
				}
			}
			else
			{
				cerr << "error determining the buffer size while converting ANSI to UCS-2" << endl;
			}
			return ret;
		}
		std::string cvtAnsiToUtf8(const std::string & str_to_cvt)
		{
			return cvtUcs2ToUtf8(cvtAnsiToUcs2(str_to_cvt));
		}

		std::string cvtUtf8ToAnsi(const std::string & str_to_cvt)
		{
			return cvtUcs2ToAnsi(cvtUtf8ToUcs2(str_to_cvt));
		}


	}
}

