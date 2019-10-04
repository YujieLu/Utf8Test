#pragma once

#include <string>

namespace visionnav
{
	namespace string
	{
		/*
		* @brief		将UCS-2编码转换成utf-8编码
		*/
		std::string cvtUcs2ToUtf8(const std::wstring & wstr_to_cvt);

		/*
		* @brief		将utf-8编码转换为UCS-2编码
		*/
		std::wstring cvtUtf8ToUcs2(const std::string & str_to_cvt);

		/*
		* @brief		将UCS-2编码转换成系统默认的编码（gbk等）
		*/
		std::string cvtUcs2ToAnsi(const std::wstring & wstr_to_cvt);

		/*
		* @brief:		将Ansi转换成UCS-2编码
		*/
		std::wstring cvtAnsiToUcs2(const std::string & str_to_cvt);

		/*
		* @brief:		将ANSI编码转换为UTF-8
		*/
		std::string cvtAnsiToUtf8(const std::string & str_to_cvt);

		/*
		* @brief:		将UTF-8编码转换为ANSI
		*/
		std::string cvtUtf8ToAnsi(const std::string & str_to_cvt);
	}
}

