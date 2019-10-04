// Utf8Example.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <direct.h>
#include <fstream>
#include <memory>
#include <stdlib.h>

#include <visionnav/string/CharacterEncodingConvert.h>

using namespace std;
using namespace visionnav::string;

int main()
{

	/*
	SetConsoleOutputCP(65001);
	CONSOLE_FONT_INFOEX info = { 0 }; // 以下设置字体来支持中文显示。
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = 16; // leave X as zero
	info.FontWeight = FW_NORMAL;
	wcscpy_s(info.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
	*/

	std::string console_str("utf8 测试");
	std::cerr << cvtUtf8ToAnsi(console_str) << endl;// wstring2string(utf8string2wstring(console_str), "zh-CN") << endl;

	//编码是utf-8,却以ANSI显示
	std::cerr << console_str << endl;

	// u8 用来将ANSI方便的转换为utf-8，这里反而转多一次;
	cerr << cvtUtf8ToAnsi(u8"utf8 测试") << endl;

	//wstring forlder(L);
	string folder_str("测试");
	auto folder_str_ansi = cvtUtf8ToAnsi(folder_str);
	cerr << folder_str_ansi << endl;
	_mkdir(folder_str_ansi.data());
	string str("测试/测试.csv");

	ofstream out(cvtUtf8ToAnsi(str));
	out << "测试,测试" << endl;
	out.close();

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
