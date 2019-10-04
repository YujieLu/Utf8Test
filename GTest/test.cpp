#include <gtest/gtest.h>
#include <visionnav/string/CharacterEncodingConvert.h>
#include <iostream>
using namespace std;
using namespace visionnav::string;


class EncodingTest : public testing::Test
{
public:
	std::string str = "测试";
	std::string str_utf8 = "\xE6\xB5\x8B\xE8\xAF\x95";
	std::wstring str_ucs2 = L"\u6D4B\u8BD5";
};
TEST_F(EncodingTest, UTF8EncodingTest)
{
	EXPECT_EQ(str, str_utf8);
}

TEST_F(EncodingTest, Ucs2ToUtf8Test)
{
	EXPECT_EQ(str_ucs2, cvtUtf8ToUcs2(str_utf8));
}

TEST_F(EncodingTest, Utf8ToUcs2Test)
{
	EXPECT_EQ(str_utf8, cvtUcs2ToUtf8(str_ucs2));
}

TEST_F(EncodingTest, Utf8ToAnsiAndBack)
{
	EXPECT_EQ(str_utf8, cvtAnsiToUtf8(cvtUtf8ToAnsi(str_utf8)));
}

TEST_F(EncodingTest, ucsToAnsiAndBack)
{
	EXPECT_EQ(str_ucs2, cvtAnsiToUcs2(cvtUcs2ToAnsi(str_ucs2)));
}

TEST_F(EncodingTest, AnsiFromUtf8EqAnsiFromUcs2)
{
	cerr << cvtUtf8ToAnsi(str_utf8) << endl;
	EXPECT_EQ(cvtUtf8ToAnsi(str_utf8), cvtUcs2ToAnsi(str_ucs2));
}