
/******************************************************
Copyright © Vitaliy Buturlin, Evgeny Danilovich, 2017
See the license in LICENSE
******************************************************/

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#if defined(_LINUX) || defined(_MAC)
#	include <wchar.h>
#	include <stdlib.h>
#	define wcscmpi wcscasecmp
#	define stricmp strcasecmp
#endif
#if defined(_WINDOWS)
#	define wcscmpi wcsicmp
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#endif

#include "string.h"

#if defined(_WINDOWS)
#	pragma warning(disable:4996)
#endif

#if defined(_LINUX) || defined(_MAC)
#	pragma GCC diagnostic push
#	pragma GCC diagnostic ignored "-Wsign-compare"
#endif

#pragma once

#ifndef SAFE_DELETE_A
#define SAFE_DELETE_A(p) if(p)\
	{\
	delete[](p); \
	(p) = NULL; \
	}
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) if(p)\
	{\
	delete (p); \
	(p) = NULL; \
	}
#endif

//##########################################################################

const char * String::c_str() const
{
	return(m_szString);
}

String::String()
{
	m_szString = new char[1];
	m_szString[0] = 0;
}

String::String(const char * str)
{
	m_szString = new char[strlen(str) + 1];
	//sprintf(m_szString,"%s",str);
	memcpy(m_szString, str, strlen(str));
	m_szString[strlen(str)] = 0;
}

String::String(char sym)
{
	m_szString = new char[2];
	//sprintf(m_szString,"%s",&sym);
	m_szString[0] = sym;
	m_szString[1] = 0;
}

String::String(int num)
{
	char * tmp = new char[64];
	sprintf(tmp, "%d", num);
	m_szString = new char[strlen(tmp) + 1];
	memcpy(m_szString, tmp, strlen(tmp) + 1);
	SAFE_DELETE_A(tmp);
}

String::String(WORD num)
{
	char * tmp = new char[64];
	sprintf(tmp, "%u", num);
	m_szString = new char[strlen(tmp) + 1];
	memcpy(m_szString, tmp, strlen(tmp) + 1);
	SAFE_DELETE_A(tmp);
}

String::String(DWORD num)
{
	char * tmp = new char[64];
	sprintf(tmp, "%lu", num);
	m_szString = new char[strlen(tmp) + 1];
	memcpy(m_szString, tmp, strlen(tmp) + 1);
	SAFE_DELETE_A(tmp);
}

String::String(const UINT num)
{
	char * tmp = new char[64];
	sprintf(tmp, "%lu", num);
	m_szString = new char[strlen(tmp) + 1];
	memcpy(m_szString, tmp, strlen(tmp) + 1);
	SAFE_DELETE_A(tmp);
}

String::String(long num)
{
	char * tmp = new char[64];
	sprintf(tmp, "%ld", num);
	m_szString = new char[strlen(tmp) + 1];
	memcpy(m_szString, tmp, strlen(tmp) + 1);
	SAFE_DELETE_A(tmp);
}

String::String(double num)
{
	char * tmp = new char[64];
	sprintf(tmp, "%G", num);
	m_szString = new char[strlen(tmp) + 1];
	memcpy(m_szString, tmp, strlen(tmp) + 1);
	SAFE_DELETE_A(tmp);
}

String::String(bool bf)
{
	m_szString = new char[bf ? 5 : 6];
	sprintf(m_szString, "%s", bf ? "true" : "false");
}

String::String(const String & str)
{
	m_szString = new char[str.length() + 1];
	memcpy(m_szString, str.c_str(), str.length() + 1);
}

String::String(const String * str)
{
	m_szString = new char[str->length() + 1];
	memcpy(m_szString, str->c_str(), str->length() + 1);
}

String::String(String && other)
{
	//SAFE_DELETE_A(m_szString);
	m_szString = other.m_szString;
	other.m_szString = NULL;
}

String::~String()
{
	release();
}


void String::release()
{
	SAFE_DELETE_A(m_szString);
}

////////////////////////////////////////////

String String::operator+(const String &str) const
{
	char * ns = new char[length() + str.length() + 1];
	sprintf(ns, "%s%s", m_szString, str.c_str());
	String newSXStr = ns;
	SAFE_DELETE_A(ns);
	return(newSXStr);
}

String String::operator+(const String *str)
{
	char * ns = new char[length() + str->length() + 1];
	sprintf(ns, "%s%s", m_szString, str->c_str());
	String newSXStr = ns;
	SAFE_DELETE_A(ns);
	return(newSXStr);
}

String String::operator+(const char * str)
{
	char * ns = new char[length() + strlen(str) + 1];
	sprintf(ns, "%s%s", m_szString, str);
	String newSXStr = ns;
	SAFE_DELETE_A(ns);
	return(newSXStr);
}

String String::operator+(const char & sym)
{
	char * ns = new char[length() + 2];
	sprintf(ns, "%s%c", m_szString, sym);
	String newSXStr = ns;
	SAFE_DELETE_A(ns);
	return(newSXStr);
}

String String::operator+(const int & num)
{
	char * ns = new char[length() + 64];
	sprintf(ns, "%s%d", m_szString, num);
	String newSXStr = ns;
	SAFE_DELETE_A(ns);
	return(newSXStr);
}

String String::operator+(const WORD & num)
{
	char * ns = new char[length() + 64];
	sprintf(ns, "%s%hu", m_szString, num);
	String newSXStr = ns;
	SAFE_DELETE_A(ns);
	return(newSXStr);
}

String String::operator+(const DWORD & num)
{
	char * ns = new char[length() + 64];
	sprintf(ns, "%s%lu", m_szString, num);
	String newSXStr = ns;
	SAFE_DELETE_A(ns);
	return(newSXStr);
}

String String::operator+(const long & num)
{
	char * ns = new char[length() + 64];
	sprintf(ns, "%s%ld", m_szString, num);
	String newSXStr = ns;
	SAFE_DELETE_A(ns);
	return(newSXStr);
}

String String::operator+(const double & num)
{
	char * ns = new char[length() + 64];
	sprintf(ns, "%s%G", m_szString, num);
	String newSXStr = ns;
	SAFE_DELETE_A(ns);
	return(newSXStr);
}

String String::operator+(const bool & bf)
{
	char * ns = new char[length() + (bf ? 5 : 6)];
	sprintf(ns, "%s%s", m_szString, bf ? "true" : "false");
	String newSXStr = ns;
	SAFE_DELETE_A(ns);
	return(newSXStr);
}

//////////////////////////////////////////////////////


String & String::operator=(const String & str)
{
	release();
	m_szString = new char[str.length() + 1];
	memcpy(m_szString, str.c_str(), str.length() + 1);
	return(*this);
}

String & String::operator=(const String * str)
{
	release();
	m_szString = new char[str->length() + 1];
	memcpy(m_szString, str->c_str(), str->length() + 1);
	return(*this);
}

String & String::operator=(const char * str)
{
	release();
	m_szString = new char[strlen(str) + 1];
	memcpy(m_szString, str, strlen(str) + 1);
	return(*this);
}

String & String::operator=(const char & sym)
{
	release();
	m_szString = new char[2];
	m_szString[0] = sym;
	m_szString[1] = 0;
	return(*this);
}

String & String::operator=(const int & num)
{
	release();
	char * tmp = new char[64];
	sprintf(tmp, "%d", num);
	m_szString = new char[strlen(tmp) + 1];
	memcpy(m_szString, tmp, strlen(tmp) + 1);
	SAFE_DELETE_A(tmp);
	return(*this);
}

String & String::operator=(const WORD & num)
{
	release();
	char * tmp = new char[64];
	sprintf(tmp, "%hu", num);
	m_szString = new char[strlen(tmp) + 1];
	memcpy(m_szString, tmp, strlen(tmp) + 1);
	SAFE_DELETE_A(tmp);
	return(*this);
}

String & String::operator=(const DWORD & num)
{
	release();
	char * tmp = new char[64];
	sprintf(tmp, "%lu", num);
	m_szString = new char[strlen(tmp) + 1];
	memcpy(m_szString, tmp, strlen(tmp) + 1);
	SAFE_DELETE_A(tmp);
	return(*this);
}

String & String::operator=(const long & num)
{
	release();
	char * tmp = new char[64];
	sprintf(tmp, "%ld", num);
	m_szString = new char[strlen(tmp) + 1];
	memcpy(m_szString, tmp, strlen(tmp) + 1);
	SAFE_DELETE_A(tmp);
	return(*this);
}

String & String::operator=(const double & num)
{
	release();
	char * tmp = new char[64];
	sprintf(tmp, "%G", num);
	m_szString = new char[strlen(tmp) + 1];
	memcpy(m_szString, tmp, strlen(tmp) + 1);
	SAFE_DELETE_A(tmp);
	return(*this);
}

String & String::operator=(const bool & bf)
{
	release();
	m_szString = new char[bf ? 5 : 6];
	sprintf(m_szString, "%s", bf ? "true" : "false");
	return(*this);
}

String & String::operator=(String && other)
{
	if(this != &other)
	{
		SAFE_DELETE(m_szString);
		m_szString = other.m_szString;
		other.m_szString = NULL;
	}
	return(*this);
}

///////////////////////////////////////////////////


String & String::operator+=(const String & str)
{
	char * ns = new char[length() + str.length() + 1];
	sprintf(ns, "%s%s", m_szString, str.c_str());
	SAFE_DELETE_A(m_szString);
	m_szString = ns;
	return(*this);
}

String & String::operator+=(const String * str)
{
	char * ns = new char[length() + str->length() + 1];
	sprintf(ns, "%s%s", m_szString, str->c_str());
	SAFE_DELETE_A(m_szString);
	m_szString = ns;
	return(*this);
}

String & String::operator+=(const char * str)
{
	char * newstring = new char[length() + strlen(str) + 1];
	sprintf(newstring, "%s%s", m_szString, str);
	SAFE_DELETE_A(m_szString);
	m_szString = newstring;
	return(*this);
}

String & String::operator+=(const char & sym)
{
	char * newstring = new char[length() + 2];
	sprintf(newstring, "%s%c", m_szString, sym);
	SAFE_DELETE_A(m_szString);
	m_szString = newstring;
	return(*this);
}

String & String::operator+=(const int & num)
{
	char * tmp = new char[length() + 64];
	sprintf(tmp, "%s%d", m_szString, num);
	SAFE_DELETE_A(m_szString);
	m_szString = tmp;
	return(*this);
}

String & String::operator+=(const WORD & num)
{
	char * tmp = new char[length() + 64];
	sprintf(tmp, "%s%hu", m_szString, num);
	SAFE_DELETE_A(m_szString);
	m_szString = tmp;
	return(*this);
}

String & String::operator+=(const DWORD & num)
{
	char * tmp = new char[length() + 64];
	sprintf(tmp, "%s%lu", m_szString, num);
	SAFE_DELETE_A(m_szString);
	m_szString = tmp;
	return(*this);
}

String & String::operator+=(const long & num)
{
	char * tmp = new char[length() + 64];
	sprintf(tmp, "%s%ld", m_szString, num);
	SAFE_DELETE_A(m_szString);
	m_szString = tmp;
	return(*this);
}

String & String::operator+=(const double & num)
{
	char * tmp = new char[length() + 64];
	sprintf(tmp, "%s%G", m_szString, num);
	SAFE_DELETE_A(m_szString);
	m_szString = tmp;
	return(*this);
}

String & String::operator+=(const bool & bf)
{
	char * tmp = new char[length() + (bf ? 5 : 6)];
	sprintf(tmp, "%s%s", m_szString, bf ? "true" : "false");
	SAFE_DELETE_A(m_szString);
	m_szString = tmp;
	return(*this);
}

/////////////////////////////////////////////////////////

String String::operator-(const String & str)
{
	String newStr = this;
	newStr.replace(str, "", 0);
	return(newStr);
}

String String::operator-(const String * str)
{
	String newStr = this;
	newStr.replace(str, "", 0);
	return(newStr);
}

String String::operator-(const char * str)
{
	String newStr = this;
	newStr.replace(str, "", 0);
	return(newStr);
}

String String::operator-(const char & sym)
{
	String newStr = this;
	newStr.replace(sym, "", 0);
	return(newStr);
}

String String::operator-(const int & num)
{
	String newStr = this;
	newStr.replace(num, "", 0);
	return(newStr);
}

String String::operator-(const WORD & num)
{
	String newStr = this;
	newStr.replace(num, "", 0);
	return(newStr);
}

String String::operator-(const DWORD & num)
{
	String newStr = this;
	newStr.replace(num, "", 0);
	return(newStr);
}

String String::operator-(const long & num)
{
	String newStr = this;
	newStr.replace(num, "", 0);
	return(newStr);
}

String String::operator-(const double & num)
{
	String newStr = this;
	newStr.replace(num, "", 0);
	return(newStr);
}

String String::operator-(const bool & bf)
{
	String newStr = this;
	newStr.replace(bf, "", 0);
	return(newStr);
}

/////////////////////////////////////////////////////////

String & String::operator-=(const String & str)
{
	replace(str, "", 0);
	return(*this);
}

String & String::operator-=(const String * str)
{
	replace(str, "", 0);
	return(*this);
}

String & String::operator-=(const char * str)
{
	replace(str, "", 0);
	return(*this);
}

String & String::operator-=(const char & sym)
{
	replace(sym, "", 0);
	return(*this);
}

String & String::operator-=(const int & num)
{
	replace(num, "", 0);
	return(*this);
}

String & String::operator-=(const WORD & num)
{
	replace(num, "", 0);
	return(*this);
}

String & String::operator-=(const DWORD & num)
{
	replace(num, "", 0);
	return(*this);
}

String & String::operator-=(const long & num)
{
	replace(num, "", 0);
	return(*this);
}

String & String::operator-=(const double & num)
{
	replace(num, "", 0);
	return(*this);
}

String & String::operator-=(const bool & bf)
{
	replace(bf, "", 0);
	return(*this);
}

/////////////////////////////////////////////////////////

String String::operator/(const String & str)
{
	String newStr = this;
	newStr.replaceAll(str, "");
	return(newStr);
}

String String::operator/(const String * str)
{
	String newStr = this;
	newStr.replaceAll(str, "");
	return(newStr);
}

String String::operator/(const char * str)
{
	String newStr = this;
	newStr.replaceAll(str, "");
	return(newStr);
}

String String::operator/(const char & sym)
{
	String newStr = this;
	newStr.replaceAll(sym, "");
	return(newStr);
}

String String::operator/(const int & num)
{
	String newStr = this;
	newStr.replaceAll(num, "");
	return(newStr);
}

String String::operator/(const WORD & num)
{
	String newStr = this;
	newStr.replaceAll(num, "");
	return(newStr);
}

String String::operator/(const DWORD & num)
{
	String newStr = this;
	newStr.replaceAll(num, "");
	return(newStr);
}

String String::operator/(const long & num)
{
	String newStr = this;
	newStr.replaceAll(num, "");
	return(newStr);
}

String String::operator/(const double & num)
{
	String newStr = this;
	newStr.replaceAll(num, "");
	return(newStr);
}

String String::operator/(const bool & bf)
{
	String newStr = this;
	newStr.replaceAll(bf, "");
	return(newStr);
}

/////////////////////////////////////////////////////////

String & String::operator/=(const String & str)
{
	replaceAll(str, "");
	return(*this);
}

String & String::operator/=(const String * str)
{
	replaceAll(str, "");
	return(*this);
}

String & String::operator/=(const char * str)
{
	replaceAll(str, "");
	return(*this);
}

String & String::operator/=(const char & sym)
{
	replaceAll(sym, "");
	return(*this);
}

String & String::operator/=(const int & num)
{
	replaceAll(num, "");
	return(*this);
}

String & String::operator/=(const WORD & num)
{
	replaceAll(num, "");
	return(*this);
}

String & String::operator/=(const DWORD & num)
{
	replaceAll(num, "");
	return(*this);
}

String & String::operator/=(const long & num)
{
	replaceAll(num, "");
	return(*this);
}

String & String::operator/=(const double & num)
{
	replaceAll(num, "");
	return(*this);
}

String & String::operator/=(const bool & bf)
{
	replaceAll(bf, "");
	return(*this);
}

///////////////////////////////////////////////////////

bool String::operator==(const String & str) const
{
	/*if(this->length() == str.length())
	{
	DWORD len = this->length();
	for(DWORD i = 0; i<len; i++)
	{
	if(this->m_szString[i] != str.m_szString[i])
	return false;
	}
	}
	else
	return false;

	return true;*/
	return(operator==(&str));
}

bool String::operator==(const String * str) const
{
	if(length() == str->length())
	{
		DWORD len = length();
		for(DWORD i = 0; i<len; i++)
		{
			if(m_szString[i] != str->m_szString[i])
				return false;
		}
	}
	else
		return false;

	return true;
}

bool String::operator==(const char * str) const
{
	/*char *newstring = new char[strlen(str)];
	sprintf(newstring, "%s", str);
	if(*this == newstring)
	return true;
	else
	return false;
	*/
	if(length() == strlen(str))
	{
		DWORD len = length();
		for(DWORD i = 0; i<len; i++)
		{
			if(m_szString[i] != str[i])
				return false;
		}
	}
	else
		return false;

	return true;
}

bool String::operator==(const char & sym) const
{
	if(length() == 1)
	{
		if(m_szString[0] != sym)
			return false;
	}
	else
		return false;

	return true;
}

bool String::operator==(const int & num) const
{
	/*int Value = ToInt();
	if(Value == num)
	return true;
	else
	return false;*/
	return(operator==((long)num));
}

bool String::operator==(const WORD & num) const
{
	return(operator==((DWORD)num));
}

bool String::operator==(const DWORD & num) const
{
	DWORD Value = toUnsLongInt();
	return(Value == num);
}

bool String::operator==(const long & num) const
{
	long Value = toLongInt();
	return(Value == num);
}

bool String::operator==(const double & num) const
{
	double Value = toDouble();
	return(Value == num);
}

bool String::operator==(const bool & bf) const
{
	bool Value = toBool();
	return(Value == bf);
}

/////////////////////////////////////////////////////////

bool String::operator!=(const String & str) const
{
	if(*this == str)
		return false;
	else
		return true;
}

bool String::operator!=(const String * str) const
{
	if(*this == *str)
		return false;
	else
		return true;
}

bool String::operator!=(const char * str) const
{
	if(*this == str)
		return false;
	else
		return true;
}

bool String::operator!=(const char & sym) const
{
	if(*this == sym)
		return false;
	else
		return true;
}

bool String::operator!=(const int & num) const
{
	if(*this == num)
		return false;
	else
		return true;
}

bool String::operator!=(const WORD & num) const
{
	if(*this == num)
		return false;
	else
		return true;
}

bool String::operator!=(const DWORD & num) const
{
	if(*this == num)
		return false;
	else
		return true;
}

bool String::operator!=(const long & num) const
{
	if(*this == num)
		return false;
	else
		return true;
}

bool String::operator!=(const double & num) const
{
	if(*this == num)
		return false;
	else
		return true;
}

bool String::operator!=(const bool & bf) const
{
	if(*this == bf)
		return false;
	else
		return true;
}

/////////////////////////////////////////////////////////

char & String::operator[](const DWORD & num)
{
	return(m_szString[num]);
}

const char & String::operator[](const DWORD & num) const
{
	return(m_szString[num]);
}

////////////////////////////////////////////////////////

DWORD String::length() const
{
	return(strlen(m_szString));
}

DWORD String::find(const char * str, DWORD pos) const
{
	//DWORD BeginPos = pos;
	//char *newChar = new char[strlen(m_szString+BeginPos)];
	//sprintf(newChar,"%s",m_szString+BeginPos);
	char *Find = strstr(m_szString + pos, str);

	if(Find != NULL)
		// return Find - (m_szString + pos) + pos; // - pos + pos == 0 ? �����?
		return(Find - m_szString);
	else
		return -1;
}

DWORD String::find(const char & c, DWORD pos) const
{
	char str[2];
	str[0] = c;
	str[1] = 0;
	return(find(str, pos));
}

DWORD String::find(const String & str, DWORD pos) const
{
	return(find(str.c_str(), pos));
}

DWORD String::replace(const char * str, const char * replace, DWORD pos)
{
	DWORD PosBeginFmt = find(str, pos);
	DWORD StrLen = strlen(str);

	if(PosBeginFmt == ~0)
		return(~0);

	DWORD CountStrLen = strlen(replace) + length() - StrLen;
	char * CountStr = new char[CountStrLen + 1];

	//sprintf(CountStr,"%s%s%s",SubStr(0,PosBeginFmt),replace,SubStr(PosBeginFmt+StrLen,length() - (PosBeginFmt+StrLen)));
	memcpy(CountStr, m_szString, PosBeginFmt);
	memcpy(CountStr + PosBeginFmt, replace, strlen(replace));
	memcpy(CountStr + PosBeginFmt + strlen(replace), m_szString + PosBeginFmt + StrLen, length() - (PosBeginFmt + StrLen));
	SAFE_DELETE_A(m_szString);
	m_szString = CountStr;
	m_szString[CountStrLen] = 0;

	return(PosBeginFmt);
}

DWORD String::replace(const String & str, const String & sReplace, DWORD pos)
{
	return(replace(str.c_str(), sReplace.c_str(), pos));
}

DWORD String::replaceAll(const char * str, const char * replace)
{
	DWORD PosCodeBegin = 0;
	DWORD PosCodeOld = 0;
	DWORD CountCodeFMT = 0;

	while(PosCodeBegin != ~0)
	{
		PosCodeBegin = find(str, PosCodeOld);
		if(PosCodeBegin != ~0)
		{
			CountCodeFMT++;
			PosCodeOld = PosCodeBegin + strlen(str);
		}
		else
			break;
	}


	DWORD StrLen = strlen(str);
	DWORD count_str_len = length() + (CountCodeFMT * (strlen(replace) - StrLen));

	//MessageBox(0,ToPointChar(ToString(length()) + "|" + ToString(CountCodeFMT) + "|" + ToString(StrLen)),ToPointChar(count_str_len),0);
	//MessageBox(0,m_szString,ToPointChar(DWORD(strlen(m_szString))),0);

	char * count_str = new char[count_str_len + 1];
	DWORD PosBeginFmt = 0;
	DWORD OldPosEndFmt = 0;
	DWORD count_str_last_len = 0;

	if((PosBeginFmt = find(str, OldPosEndFmt)) != DWORD(-1))
	{
		//sprintf(count_str,"%s%s",SubStr(OldPosEndFmt,PosBeginFmt-OldPosEndFmt),replace);
		//MessageBox(0,count_str,"count_str1",0);
		/*memcpy(count_str,m_szString+OldPosEndFmt,count_str_last_len);
		count_str_last_len += PosBeginFmt-OldPosEndFmt;
		memcpy(count_str+count_str_last_len,replace,strlen(replace));
		count_str_last_len += strlen(replace);
		OldPosEndFmt = PosBeginFmt+StrLen;*/
		memcpy(count_str, m_szString + OldPosEndFmt, PosBeginFmt - OldPosEndFmt);
		count_str_last_len += PosBeginFmt - OldPosEndFmt;
		memcpy(count_str + count_str_last_len, replace, strlen(replace));
		count_str_last_len += strlen(replace);
		OldPosEndFmt = PosBeginFmt + StrLen;
	}
	else
		return -1;

	//MessageBox(0,count_str,"count_str1",0);

	while((PosBeginFmt = find(str, OldPosEndFmt)) != DWORD(-1))
	{
		//sprintf(count_str,"%s%s%s",count_str,SubStr(OldPosEndFmt,PosBeginFmt-OldPosEndFmt),replace);
		//MessageBox(0,ToPointChar(PosBeginFmt),"PosBeginFmt",0);
		memcpy(count_str + count_str_last_len, m_szString + OldPosEndFmt, PosBeginFmt - OldPosEndFmt);
		count_str_last_len += PosBeginFmt - OldPosEndFmt;

		memcpy(count_str + count_str_last_len, replace, strlen(replace));
		count_str_last_len += strlen(replace);

		OldPosEndFmt = PosBeginFmt + StrLen;
	}
	//MessageBox(0,SubStr(OldPosEndFmt,length()-OldPosEndFmt),"SubStr(OldPosEndFmt,length()-OldPosEndFmt)",0);
	//MessageBox(0,count_str,"count_str----",0);
	//sprintf(count_str,"%s%s",count_str,SubStr(OldPosEndFmt,length()-OldPosEndFmt));
	memcpy(count_str + count_str_last_len, m_szString + OldPosEndFmt, length() - OldPosEndFmt);
	count_str[count_str_len] = 0;
	SAFE_DELETE_A(m_szString);
	m_szString = count_str;

	//MessageBox(0,count_str,"count_str++++++",0);

	return OldPosEndFmt - StrLen;
}

DWORD String::replaceAll(const String & str, const String & replace)
{
	return(replaceAll(str.c_str(), replace.c_str()));
}

/*char* String::SubStr(DWORD pos, DWORD lenght)
{
char *str = new char[lenght];
memcpy(str, m_szString + pos, lenght);
str[lenght] = 0;
return str;
}*/

String String::substr(DWORD pos, DWORD len) const
{
	char * ns = m_szString + pos;
	if(!len || len > length() - pos)
	{
		len = length() - pos;
	}
	char * s = new char[len + 1];
	memcpy(s, ns, len);
	s[len] = 0;
	String res = s;
	SAFE_DELETE_A(s);
	return(res);
}

UINT String::remove(DWORD pos, DWORD len)
{
	/*char *str = SubStr(pos,lenght);
	char *OneSubStr = SubStr(0,pos);
	char *SecondSubStr = SubStr(pos + lenght,length() - (pos + lenght));
	char *newStr = new char[strlen(OneSubStr) + strlen(SecondSubStr)];
	sprintf(newStr,"%s%s",OneSubStr,SecondSubStr);
	m_szString = newStr;
	return str;*/

	//char *str = SubStr(pos, lenght);

	DWORD PosLenght = pos + len;
	DWORD StrLen = length() - len;
	if(length() < len)
	{
		len = length() - pos;
		PosLenght = pos + len;
		StrLen = length() - len;
	}

	if(len == 0 || pos >= length())
	{
		return(0);
	}

	char * newStr = new char[StrLen + 1];
	//sprintf(m_szString,"%s%s",SubStr(0,pos),SubStr(PosLenght,length() - PosLenght));
	memcpy(newStr, m_szString, pos);
	memcpy(newStr + pos, m_szString + PosLenght, length() - PosLenght);
	SAFE_DELETE_A(m_szString);
	m_szString = newStr;
	m_szString[StrLen] = 0;

	return(len);
}

String String::trim()
{
	UINT pos = ~0;
	UINT len = 0;
	for(UINT i = 0, l = length(); i < l; ++i)
	{
		if(!isspace(m_szString[i]))
		{
			if(i < pos)
			{
				pos = i;
			}
			len = i - pos + 1;
		}
	}
	return(substr(pos, len));
}

StringW StringW::trim()
{
	UINT pos = ~0;
	UINT len = 0;
	for(UINT i = 0, l = length(); i < l; ++i)
	{
		if(!iswspace(m_szString[i]))
		{
			if(i < pos)
			{
				pos = i;
			}
			len = i - pos + 1;
		}
	}
	return(substr(pos, len));
}

////////////////////////////////////////////

int String::toInt() const
{
	int out;
	sscanf(m_szString, "%d", &out);
	return(out);
}

long String::toLongInt() const
{
	long out;
	sscanf(m_szString, "%ld", &out);
	return(out);
}

DWORD String::toUnsLongInt() const
{
	DWORD num;
	sscanf(m_szString, "%lu", &num);
	return(num);
}

double String::toDouble() const
{
	float out;
	sscanf(m_szString, "%f", &out);
	return(out);
}

bool String::toBool() const
{
	return(toInt() == 1 || stricmp(m_szString, "true") == 0);
}

DWORD String::find_last_of(const char * str, DWORD pos) const
{

	char * Find = NULL;
	char * tmpFind = NULL;
	while((Find = strstr(m_szString + pos, str)))
	{
		pos = Find - m_szString + 1;
		tmpFind = Find;
	}

	if(tmpFind != NULL)
		// return Find - (m_szString + pos) + pos; // - pos + pos == 0 ? �����?
		return(tmpFind - m_szString);
	else
		return -1;
}

DWORD String::find_last_of(const char & c, DWORD pos) const
{
	char str[2];
	str[0] = c;
	str[1] = 0;
	return(find_last_of(str, pos));
}

DWORD String::find_last_of(const String & str, DWORD pos) const
{
	return(find_last_of(str.c_str(), pos));
}


/*bool operator<(const String & a, const String & b)
{
	return(strcmp(a.c_str(), b.c_str()) < 0);
}*/

bool String::operator<(const String & s) const
{
	return(strcmp(m_szString, s.m_szString) < 0);
}

////////////////////////////////////////////////////////
//
//
//
//
////////////////////////////////////////////////////////


const WCHAR * StringW::c_str() const
{
	return(m_szString);
}

StringW::StringW()
{
	m_szString = new WCHAR[1];
	m_szString[0] = 0;
}

StringW::StringW(const WCHAR * str)
{

	m_szString = new WCHAR[wcslen(str) + 1];
	//sprintf(m_szString,"%s",str);
	memcpy(m_szString, str, sizeof(WCHAR) * wcslen(str));
	m_szString[wcslen(str)] = 0;
}

StringW::StringW(WCHAR sym)
{
	m_szString = new WCHAR[2];
	//sprintf(m_szString,"%s",&sym);
	m_szString[0] = sym;
	m_szString[1] = 0;
}

StringW::StringW(int num)
{
	WCHAR * tmp = new WCHAR[64];
	swprintf(tmp, 64, L"%d", num);
	m_szString = new WCHAR[wcslen(tmp) + 1];
	memcpy(m_szString, tmp, sizeof(WCHAR) * (wcslen(tmp) + 1));
	SAFE_DELETE_A(tmp);
}

StringW::StringW(WORD num)
{
	WCHAR * tmp = new WCHAR[64];
	swprintf(tmp, 64, L"%hu", num);
	m_szString = new WCHAR[wcslen(tmp) + 1];
	memcpy(m_szString, tmp, sizeof(WCHAR) * (wcslen(tmp) + 1));
	SAFE_DELETE_A(tmp);
}

StringW::StringW(DWORD num)
{
	WCHAR * tmp = new WCHAR[64];
	swprintf(tmp, 64, L"%lu", num);
	m_szString = new WCHAR[wcslen(tmp) + 1];
	memcpy(m_szString, tmp, sizeof(WCHAR) * (wcslen(tmp) + 1));
	SAFE_DELETE_A(tmp);
}

StringW::StringW(long num)
{
	WCHAR * tmp = new WCHAR[64];
	swprintf(tmp, 64, L"%ld", num);
	m_szString = new WCHAR[wcslen(tmp) + 1];
	memcpy(m_szString, tmp, sizeof(WCHAR) * (wcslen(tmp) + 1));
	SAFE_DELETE_A(tmp);
}

StringW::StringW(double num)
{
	WCHAR * tmp = new WCHAR[64];
	swprintf(tmp, 64, L"%G", num);
	m_szString = new WCHAR[wcslen(tmp) + 1];
	memcpy(m_szString, tmp, sizeof(WCHAR) * (wcslen(tmp) + 1));
	SAFE_DELETE_A(tmp);
}

StringW::StringW(bool bf)
{
	m_szString = new WCHAR[bf ? 5 : 6];
	swprintf(m_szString, bf ? 5 : 6, L"%ls", bf ? L"true" : L"false");
}

StringW::StringW(const StringW & str)
{
	m_szString = new WCHAR[str.length() + 1];
	memcpy(m_szString, str.c_str(), sizeof(WCHAR) * (str.length() + 1));
}

StringW::StringW(const StringW * str)
{
	m_szString = new WCHAR[str->length() + 1];
	memcpy(m_szString, str->c_str(), sizeof(WCHAR) * (str->length() + 1));
}

StringW::StringW(StringW && other)
{
	//SAFE_DELETE_A(m_szString);
	m_szString = other.m_szString;
	other.m_szString = NULL;
}

StringW::~StringW()
{
	release();
}


void StringW::release()
{
	SAFE_DELETE_A(m_szString);
}

////////////////////////////////////////////

StringW StringW::operator+(const StringW &str) const
{
	size_t len = length() + str.length() + 1;
	WCHAR * ns = new WCHAR[len];
	swprintf(ns, len, L"%ls%ls", m_szString, str.c_str());
	StringW newSXStr = ns;
	SAFE_DELETE_A(ns);
	return(newSXStr);
}

StringW StringW::operator+(const StringW *str)
{
	WCHAR * ns = new WCHAR[length() + str->length() + 1];
	swprintf(ns, length() + str->length() + 1, L"%ls%ls", m_szString, str->c_str());
	StringW newSXStr = ns;
	SAFE_DELETE_A(ns);
	return(newSXStr);
}

StringW StringW::operator+(const WCHAR * str)
{
	WCHAR * ns = new WCHAR[length() + wcslen(str) + 1];
	swprintf(ns, length() + wcslen(str) + 1, L"%ls%ls", m_szString, str);
	StringW newSXStr = ns;
	SAFE_DELETE_A(ns);
	return(newSXStr);
}

StringW StringW::operator+(const WCHAR & sym)
{
	WCHAR * ns = new WCHAR[length() + 2];
	swprintf(ns, length() + 2, L"%ls%lc", m_szString, sym);
	StringW newSXStr = ns;
	SAFE_DELETE_A(ns);
	return(newSXStr);
}

StringW StringW::operator+(const int & num)
{
	WCHAR * ns = new WCHAR[length() + 64];
	swprintf(ns, length() + 64, L"%ls%d", m_szString, num);
	StringW newSXStr = ns;
	SAFE_DELETE_A(ns);
	return(newSXStr);
}

StringW StringW::operator+(const WORD & num)
{
	WCHAR * ns = new WCHAR[length() + 64];
	swprintf(ns, length() + 64, L"%ls%hu", m_szString, num);
	StringW newSXStr = ns;
	SAFE_DELETE_A(ns);
	return(newSXStr);
}

StringW StringW::operator+(const DWORD & num)
{
	WCHAR * ns = new WCHAR[length() + 64];
	swprintf(ns, length() + 64, L"%ls%lu", m_szString, num);
	StringW newSXStr = ns;
	SAFE_DELETE_A(ns);
	return(newSXStr);
}

StringW StringW::operator+(const long & num)
{
	WCHAR * ns = new WCHAR[length() + 64];
	swprintf(ns, length() + 64, L"%ls%ld", m_szString, num);
	StringW newSXStr = ns;
	SAFE_DELETE_A(ns);
	return(newSXStr);
}

StringW StringW::operator+(const double & num)
{
	WCHAR * ns = new WCHAR[length() + 64];
	swprintf(ns, length() + 64, L"%ls%G", m_szString, num);
	StringW newSXStr = ns;
	SAFE_DELETE_A(ns);
	return(newSXStr);
}

StringW StringW::operator+(const bool & bf)
{
	WCHAR * ns = new WCHAR[length() + (bf ? 5 : 6)];
	swprintf(ns, length() + (bf ? 5 : 6), L"%ls%ls", m_szString, bf ? L"true" : L"false");
	StringW newSXStr = ns;
	SAFE_DELETE_A(ns);
	return(newSXStr);
}

//////////////////////////////////////////////////////


StringW & StringW::operator=(const StringW & str)
{
	release();
	m_szString = new WCHAR[str.length() + 1];
	memcpy(m_szString, str.c_str(), sizeof(WCHAR) * (str.length() + 1));
	return(*this);
}

StringW & StringW::operator=(const StringW * str)
{
	release();
	m_szString = new WCHAR[str->length() + 1];
	memcpy(m_szString, str->c_str(), sizeof(WCHAR) * (str->length() + 1));
	return(*this);
}

StringW & StringW::operator=(const WCHAR * str)
{
	release();
	m_szString = new WCHAR[wcslen(str) + 1];
	memcpy(m_szString, str, sizeof(WCHAR) * (wcslen(str) + 1));
	return(*this);
}

StringW & StringW::operator=(const WCHAR & sym)
{
	release();
	m_szString = new WCHAR[2];
	m_szString[0] = sym;
	m_szString[1] = 0;
	return(*this);
}

StringW & StringW::operator=(const int & num)
{
	release();
	WCHAR * tmp = new WCHAR[64];
	swprintf(tmp, 64, L"%d", num);
	m_szString = new WCHAR[wcslen(tmp) + 1];
	memcpy(m_szString, tmp, sizeof(WCHAR) * (wcslen(tmp) + 1));
	SAFE_DELETE_A(tmp);
	return(*this);
}

StringW & StringW::operator=(const WORD & num)
{
	release();
	WCHAR * tmp = new WCHAR[64];
	swprintf(tmp, 64, L"%hu", num);
	m_szString = new WCHAR[wcslen(tmp) + 1];
	memcpy(m_szString, tmp, sizeof(WCHAR) * (wcslen(tmp) + 1));
	SAFE_DELETE_A(tmp);
	return(*this);
}

StringW & StringW::operator=(const DWORD & num)
{
	release();
	WCHAR * tmp = new WCHAR[64];
	swprintf(tmp, 64, L"%lu", num);
	m_szString = new WCHAR[wcslen(tmp) + 1];
	memcpy(m_szString, tmp, sizeof(WCHAR) * (wcslen(tmp) + 1));
	SAFE_DELETE_A(tmp);
	return(*this);
}

StringW & StringW::operator=(const long & num)
{
	release();
	WCHAR * tmp = new WCHAR[64];
	swprintf(tmp, 64, L"%ld", num);
	m_szString = new WCHAR[wcslen(tmp) + 1];
	memcpy(m_szString, tmp, sizeof(WCHAR) * (wcslen(tmp) + 1));
	SAFE_DELETE_A(tmp);
	return(*this);
}

StringW & StringW::operator=(const double & num)
{
	release();
	WCHAR * tmp = new WCHAR[64];
	swprintf(tmp, 64, L"%G", num);
	m_szString = new WCHAR[wcslen(tmp) + 1];
	memcpy(m_szString, tmp, sizeof(WCHAR) * (wcslen(tmp) + 1));
	SAFE_DELETE_A(tmp);
	return(*this);
}

StringW & StringW::operator=(const bool & bf)
{
	release();
	m_szString = new WCHAR[bf ? 5 : 6];
	swprintf(m_szString, bf ? 5 : 6, L"%ls", bf ? L"true" : L"false");
	return(*this);
}

StringW & StringW::operator=(StringW && other)
{
	if(this != &other)
	{
		SAFE_DELETE(m_szString);
		m_szString = other.m_szString;
		other.m_szString = NULL;
	}
	return(*this);
}

///////////////////////////////////////////////////


StringW & StringW::operator+=(const StringW & str)
{
	WCHAR * ns = new WCHAR[length() + str.length() + 1];
	swprintf(ns, length() + str.length() + 1, L"%ls%ls", m_szString, str.c_str());
	SAFE_DELETE_A(m_szString);
	m_szString = ns;
	return(*this);
}

StringW & StringW::operator+=(const StringW * str)
{
	WCHAR * ns = new WCHAR[length() + str->length() + 1];
	swprintf(ns, length() + str->length() + 1, L"%ls%ls", m_szString, str->c_str());
	SAFE_DELETE_A(m_szString);
	m_szString = ns;
	return(*this);
}

StringW & StringW::operator+=(const WCHAR * str)
{
	WCHAR * newstring = new WCHAR[length() + wcslen(str) + 1];
	swprintf(newstring, length() + wcslen(str) + 1, L"%ls%ls", m_szString, str);
	SAFE_DELETE_A(m_szString);
	m_szString = newstring;
	return(*this);
}

StringW & StringW::operator+=(const WCHAR & sym)
{
	WCHAR * newstring = new WCHAR[length() + 2];
	swprintf(newstring, length() + 2, L"%ls%lc", m_szString, sym);
	SAFE_DELETE_A(m_szString);
	m_szString = newstring;
	return(*this);
}

StringW & StringW::operator+=(const int & num)
{
	WCHAR * tmp = new WCHAR[length() + 64];
	swprintf(tmp, length() + 64, L"%ls%d", m_szString, num);
	SAFE_DELETE_A(m_szString);
	m_szString = tmp;
	return(*this);
}

StringW & StringW::operator+=(const WORD & num)
{
	WCHAR * tmp = new WCHAR[length() + 64];
	swprintf(tmp, length() + 64, L"%ls%hu", m_szString, num);
	SAFE_DELETE_A(m_szString);
	m_szString = tmp;
	return(*this);
}

StringW & StringW::operator+=(const DWORD & num)
{
	WCHAR * tmp = new WCHAR[length() + 64];
	swprintf(tmp, length() + 64, L"%ls%lu", m_szString, num);
	SAFE_DELETE_A(m_szString);
	m_szString = tmp;
	return(*this);
}

StringW & StringW::operator+=(const long & num)
{
	WCHAR * tmp = new WCHAR[length() + 64];
	swprintf(tmp, length() + 64, L"%ls%ld", m_szString, num);
	SAFE_DELETE_A(m_szString);
	m_szString = tmp;
	return(*this);
}

StringW & StringW::operator+=(const double & num)
{
	WCHAR * tmp = new WCHAR[length() + 64];
	swprintf(tmp, length() + 64, L"%ls%G", m_szString, num);
	SAFE_DELETE_A(m_szString);
	m_szString = tmp;
	return(*this);
}

StringW & StringW::operator+=(const bool & bf)
{
	WCHAR * tmp = new WCHAR[length() + (bf ? 5 : 6)];
	swprintf(tmp, length() + (bf ? 5 : 6), L"%ls%ls", m_szString, bf ? L"true" : L"false");
	SAFE_DELETE_A(m_szString);
	m_szString = tmp;
	return(*this);
}

/////////////////////////////////////////////////////////

StringW StringW::operator-(const StringW & str)
{
	StringW newStr = this;
	newStr.replace(str, "", 0);
	return(newStr);
}

StringW StringW::operator-(const StringW * str)
{
	StringW newStr = this;
	newStr.replace(str, "", 0);
	return(newStr);
}

StringW StringW::operator-(const WCHAR * str)
{
	StringW newStr = this;
	newStr.replace(str, "", 0);
	return(newStr);
}

StringW StringW::operator-(const WCHAR & sym)
{
	StringW newStr = this;
	newStr.replace(sym, "", 0);
	return(newStr);
}

StringW StringW::operator-(const int & num)
{
	StringW newStr = this;
	newStr.replace(num, "", 0);
	return(newStr);
}

StringW StringW::operator-(const WORD & num)
{
	StringW newStr = this;
	newStr.replace(num, "", 0);
	return(newStr);
}

StringW StringW::operator-(const DWORD & num)
{
	StringW newStr = this;
	newStr.replace(num, "", 0);
	return(newStr);
}

StringW StringW::operator-(const long & num)
{
	StringW newStr = this;
	newStr.replace(num, "", 0);
	return(newStr);
}

StringW StringW::operator-(const double & num)
{
	StringW newStr = this;
	newStr.replace(num, "", 0);
	return(newStr);
}

StringW StringW::operator-(const bool & bf)
{
	StringW newStr = this;
	newStr.replace(bf, "", 0);
	return(newStr);
}

/////////////////////////////////////////////////////////

StringW & StringW::operator-=(const StringW & str)
{
	replace(str, "", 0);
	return(*this);
}

StringW & StringW::operator-=(const StringW * str)
{
	replace(str, "", 0);
	return(*this);
}

StringW & StringW::operator-=(const WCHAR * str)
{
	replace(str, "", 0);
	return(*this);
}

StringW & StringW::operator-=(const WCHAR & sym)
{
	replace(sym, "", 0);
	return(*this);
}

StringW & StringW::operator-=(const int & num)
{
	replace(num, "", 0);
	return(*this);
}

StringW & StringW::operator-=(const WORD & num)
{
	replace(num, "", 0);
	return(*this);
}

StringW & StringW::operator-=(const DWORD & num)
{
	replace(num, "", 0);
	return(*this);
}

StringW & StringW::operator-=(const long & num)
{
	replace(num, "", 0);
	return(*this);
}

StringW & StringW::operator-=(const double & num)
{
	replace(num, "", 0);
	return(*this);
}

StringW & StringW::operator-=(const bool & bf)
{
	replace(bf, "", 0);
	return(*this);
}

/////////////////////////////////////////////////////////

StringW StringW::operator/(const StringW & str)
{
	StringW newStr = this;
	newStr.replaceAll(str, L"");
	return(newStr);
}

StringW StringW::operator/(const StringW * str)
{
	StringW newStr = this;
	newStr.replaceAll(str, L"");
	return(newStr);
}

StringW StringW::operator/(const WCHAR * str)
{
	StringW newStr = this;
	newStr.replaceAll(str, L"");
	return(newStr);
}

StringW StringW::operator/(const WCHAR & sym)
{
	StringW newStr = this;
	newStr.replaceAll(sym, L"");
	return(newStr);
}

StringW StringW::operator/(const int & num)
{
	StringW newStr = this;
	newStr.replaceAll(num, L"");
	return(newStr);
}

StringW StringW::operator/(const WORD & num)
{
	StringW newStr = this;
	newStr.replaceAll(num, L"");
	return(newStr);
}

StringW StringW::operator/(const DWORD & num)
{
	StringW newStr = this;
	newStr.replaceAll(num, L"");
	return(newStr);
}

StringW StringW::operator/(const long & num)
{
	StringW newStr = this;
	newStr.replaceAll(num, L"");
	return(newStr);
}

StringW StringW::operator/(const double & num)
{
	StringW newStr = this;
	newStr.replaceAll(num, L"");
	return(newStr);
}

StringW StringW::operator/(const bool & bf)
{
	StringW newStr = this;
	newStr.replaceAll(bf, L"");
	return(newStr);
}

/////////////////////////////////////////////////////////

StringW & StringW::operator/=(const StringW & str)
{
	replaceAll(str, L"");
	return(*this);
}

StringW & StringW::operator/=(const StringW * str)
{
	replaceAll(str, L"");
	return(*this);
}

StringW & StringW::operator/=(const WCHAR * str)
{
	replaceAll(str, L"");
	return(*this);
}

StringW & StringW::operator/=(const WCHAR & sym)
{
	replaceAll(sym, L"");
	return(*this);
}

StringW & StringW::operator/=(const int & num)
{
	replaceAll(num, L"");
	return(*this);
}

StringW & StringW::operator/=(const WORD & num)
{
	replaceAll(num, L"");
	return(*this);
}

StringW & StringW::operator/=(const DWORD & num)
{
	replaceAll(num, L"");
	return(*this);
}

StringW & StringW::operator/=(const long & num)
{
	replaceAll(num, L"");
	return(*this);
}

StringW & StringW::operator/=(const double & num)
{
	replaceAll(num, L"");
	return(*this);
}

StringW & StringW::operator/=(const bool & bf)
{
	replaceAll(bf, L"");
	return(*this);
}

///////////////////////////////////////////////////////

bool StringW::operator==(const StringW & str) const
{
	/*if(this->length() == str.length())
	{
	DWORD len = this->length();
	for(DWORD i = 0; i<len; i++)
	{
	if(this->m_szString[i] != str.m_szString[i])
	return false;
	}
	}
	else
	return false;

	return true;*/
	return(operator==(&str));
}

bool StringW::operator==(const StringW * str) const
{
	if(length() == str->length())
	{
		DWORD len = length();
		for(DWORD i = 0; i<len; i++)
		{
			if(m_szString[i] != str->m_szString[i])
				return false;
		}
	}
	else
		return false;

	return true;
}

bool StringW::operator==(const WCHAR * str) const
{
	/*WCHAR *newstring = new WCHAR[strlen(str)];
	sprintf(newstring, "%s", str);
	if(*this == newstring)
	return true;
	else
	return false;
	*/
	if(length() == wcslen(str))
	{
		DWORD len = length();
		for(DWORD i = 0; i<len; i++)
		{
			if(m_szString[i] != str[i])
				return false;
		}
	}
	else
		return false;

	return true;
}

bool StringW::operator==(const WCHAR & sym) const
{
	if(length() == 1)
	{
		if(m_szString[0] != sym)
			return false;
	}
	else
		return false;

	return true;
}

bool StringW::operator==(const int & num) const
{
	/*int Value = ToInt();
	if(Value == num)
	return true;
	else
	return false;*/
	return(operator==((long)num));
}

bool StringW::operator==(const WORD & num) const
{
	return(operator==((DWORD)num));
}

bool StringW::operator==(const DWORD & num) const
{
	DWORD Value = toUnsLongInt();
	return(Value == num);
}

bool StringW::operator==(const long & num) const
{
	long Value = toLongInt();
	return(Value == num);
}

bool StringW::operator==(const double & num) const
{
	double Value = toDouble();
	return(Value == num);
}

bool StringW::operator==(const bool & bf) const
{
	bool Value = toBool();
	return(Value == bf);
}

/////////////////////////////////////////////////////////

bool StringW::operator!=(const StringW & str) const
{
	if(*this == str)
		return false;
	else
		return true;
}

bool StringW::operator!=(const StringW * str) const
{
	if(*this == *str)
		return false;
	else
		return true;
}

bool StringW::operator!=(const WCHAR * str) const
{
	if(*this == str)
		return false;
	else
		return true;
}

bool StringW::operator!=(const WCHAR & sym) const
{
	if(*this == sym)
		return false;
	else
		return true;
}

bool StringW::operator!=(const int & num) const
{
	if(*this == num)
		return false;
	else
		return true;
}

bool StringW::operator!=(const WORD & num) const
{
	if(*this == num)
		return false;
	else
		return true;
}

bool StringW::operator!=(const DWORD & num) const
{
	if(*this == num)
		return false;
	else
		return true;
}

bool StringW::operator!=(const long & num) const
{
	if(*this == num)
		return false;
	else
		return true;
}

bool StringW::operator!=(const double & num) const
{
	if(*this == num)
		return false;
	else
		return true;
}

bool StringW::operator!=(const bool & bf) const
{
	if(*this == bf)
		return false;
	else
		return true;
}

/////////////////////////////////////////////////////////

WCHAR & StringW::operator[](const DWORD & num)
{
	return(m_szString[num]);
}

const WCHAR & StringW::operator[](const DWORD & num) const
{
	return(m_szString[num]);
}


////////////////////////////////////////////////////////

DWORD StringW::length() const
{
	return(wcslen(m_szString));
}

DWORD StringW::find(const WCHAR * str, DWORD pos) const
{
	//DWORD BeginPos = pos;
	//WCHAR *newWCHAR = new WCHAR[strlen(m_szString+BeginPos)];
	//sprintf(newWCHAR,"%s",m_szString+BeginPos);

	WCHAR *Find = wcsstr(m_szString + pos, str);

	if(Find != NULL)
		// return Find - (m_szString + pos) + pos; // - pos + pos == 0 ? �����?
		return(Find - m_szString);
	else
		return -1;
}

DWORD StringW::find(const WCHAR & c, DWORD pos) const
{
	WCHAR str[2];
	str[0] = c;
	str[1] = 0;
	return(find(str, pos));
}

DWORD StringW::find(const StringW & str, DWORD pos) const
{
	return(find(str.c_str(), pos));
}

DWORD StringW::replace(const WCHAR * str, const WCHAR * replace, DWORD pos)
{
	DWORD PosBeginFmt = find(str, pos);
	DWORD StrLen = wcslen(str);

	if(PosBeginFmt == ~0)
		return(~0);

	DWORD CountStrLen = wcslen(replace) + length() - StrLen;
	WCHAR * CountStr = new WCHAR[CountStrLen + 1];

	//sprintf(CountStr,"%s%s%s",SubStr(0,PosBeginFmt),replace,SubStr(PosBeginFmt+StrLen,length() - (PosBeginFmt+StrLen)));
	memcpy(CountStr, m_szString, PosBeginFmt);
	memcpy(CountStr + PosBeginFmt, replace, sizeof(WCHAR) * wcslen(replace));
	memcpy(CountStr + PosBeginFmt + wcslen(replace), m_szString + PosBeginFmt + StrLen, sizeof(WCHAR) * (length() - (PosBeginFmt + StrLen)));
	SAFE_DELETE_A(m_szString);
	m_szString = CountStr;
	m_szString[CountStrLen] = 0;

	return(PosBeginFmt);
}

DWORD StringW::replace(const StringW & str, const StringW & sReplace, DWORD pos)
{
	return(replace(str.c_str(), sReplace.c_str(), pos));
}

DWORD StringW::replaceAll(const WCHAR * str, const WCHAR * replace)
{
	DWORD PosCodeBegin = 0;
	DWORD PosCodeOld = 0;
	DWORD CountCodeFMT = 0;

	while(PosCodeBegin != ~0)
	{
		PosCodeBegin = find(str, PosCodeOld);
		if(PosCodeBegin != ~0)
		{
			CountCodeFMT++;
			PosCodeOld = PosCodeBegin + wcslen(str);
		}
		else
			break;
	}


	DWORD StrLen = wcslen(str);
	DWORD count_str_len = length() + (CountCodeFMT * (wcslen(replace) - StrLen));

	//MessageBox(0,ToPointWCHAR(ToString(length()) + "|" + ToString(CountCodeFMT) + "|" + ToString(StrLen)),ToPointWCHAR(count_str_len),0);
	//MessageBox(0,m_szString,ToPointWCHAR(DWORD(strlen(m_szString))),0);

	WCHAR * count_str = new WCHAR[count_str_len + 1];
	DWORD PosBeginFmt = 0;
	DWORD OldPosEndFmt = 0;
	DWORD count_str_last_len = 0;

	if((PosBeginFmt = find(str, OldPosEndFmt)) != DWORD(-1))
	{
		//sprintf(count_str,"%s%s",SubStr(OldPosEndFmt,PosBeginFmt-OldPosEndFmt),replace);
		//MessageBox(0,count_str,"count_str1",0);
		/*memcpy(count_str,m_szString+OldPosEndFmt,count_str_last_len);
		count_str_last_len += PosBeginFmt-OldPosEndFmt;
		memcpy(count_str+count_str_last_len,replace,strlen(replace));
		count_str_last_len += strlen(replace);
		OldPosEndFmt = PosBeginFmt+StrLen;*/
		memcpy(count_str, m_szString + OldPosEndFmt, sizeof(WCHAR) * (PosBeginFmt - OldPosEndFmt));
		count_str_last_len += PosBeginFmt - OldPosEndFmt;
		memcpy(count_str + count_str_last_len, replace, sizeof(WCHAR) * wcslen(replace));
		count_str_last_len += wcslen(replace);
		OldPosEndFmt = PosBeginFmt + StrLen;
	}
	else
		return -1;

	//MessageBox(0,count_str,"count_str1",0);

	while((PosBeginFmt = find(str, OldPosEndFmt)) != DWORD(-1))
	{
		//sprintf(count_str,"%s%s%s",count_str,SubStr(OldPosEndFmt,PosBeginFmt-OldPosEndFmt),replace);
		//MessageBox(0,ToPointWCHAR(PosBeginFmt),"PosBeginFmt",0);
		memcpy(count_str + count_str_last_len, m_szString + OldPosEndFmt, sizeof(WCHAR) * (PosBeginFmt - OldPosEndFmt));
		count_str_last_len += PosBeginFmt - OldPosEndFmt;

		memcpy(count_str + count_str_last_len, replace, sizeof(WCHAR) * wcslen(replace));
		count_str_last_len += wcslen(replace);

		OldPosEndFmt = PosBeginFmt + StrLen;
	}
	//MessageBox(0,SubStr(OldPosEndFmt,length()-OldPosEndFmt),"SubStr(OldPosEndFmt,length()-OldPosEndFmt)",0);
	//MessageBox(0,count_str,"count_str----",0);
	//sprintf(count_str,"%s%s",count_str,SubStr(OldPosEndFmt,length()-OldPosEndFmt));
	memcpy(count_str + count_str_last_len, m_szString + OldPosEndFmt, sizeof(WCHAR) * (length() - OldPosEndFmt));
	count_str[count_str_len] = 0;
	SAFE_DELETE_A(m_szString);
	m_szString = count_str;

	//MessageBox(0,count_str,"count_str++++++",0);

	return OldPosEndFmt - StrLen;
}

DWORD StringW::replaceAll(const StringW & str, const StringW & replace)
{
	return(replaceAll(str.c_str(), replace.c_str()));
}

/*WCHAR* StringW::SubStr(DWORD pos, DWORD lenght)
{
WCHAR *str = new WCHAR[lenght];
memcpy(str, m_szString + pos, lenght);
str[lenght] = 0;
return str;
}*/

StringW StringW::substr(DWORD pos, DWORD len) const
{
	WCHAR * ns = m_szString + pos;
	if(!len || len > length() - pos)
	{
		len = length() - pos;
	}
	WCHAR * s = new WCHAR[len + 1];
	memcpy(s, ns, sizeof(WCHAR) * len);
	s[len] = 0;
	StringW res = s;
	SAFE_DELETE_A(s);
	return(res);
}

UINT StringW::remove(DWORD pos, DWORD len)
{
	/*WCHAR *str = SubStr(pos,lenght);
	WCHAR *OneSubStr = SubStr(0,pos);
	WCHAR *SecondSubStr = SubStr(pos + lenght,length() - (pos + lenght));
	WCHAR *newStr = new WCHAR[strlen(OneSubStr) + strlen(SecondSubStr)];
	sprintf(newStr,"%s%s",OneSubStr,SecondSubStr);
	m_szString = newStr;
	return str;*/

	//WCHAR *str = SubStr(pos, lenght);

	DWORD PosLenght = pos + len;
	DWORD StrLen = length() - len;
	if(length() < len)
	{
		len = length() - pos;
		PosLenght = pos + len;
		StrLen = length() - len;
	}

	if(len == 0 || pos >= length())
	{
		return(0);
	}

	WCHAR * newStr = new WCHAR[StrLen + 1];
	//sprintf(m_szString,"%s%s",SubStr(0,pos),SubStr(PosLenght,length() - PosLenght));
	memcpy(newStr, m_szString, sizeof(WCHAR) * pos);
	memcpy(newStr + pos, m_szString + PosLenght, sizeof(WCHAR) * (length() - PosLenght));
	SAFE_DELETE_A(m_szString);
	m_szString = newStr;
	m_szString[StrLen] = 0;

	return(len);
}

////////////////////////////////////////////

int StringW::toInt() const
{
	int tmp;
	swscanf(m_szString, L"%d", &tmp);
	return(tmp);
}

long StringW::toLongInt() const
{
	long tmp;
	swscanf(m_szString, L"%ld", &tmp);
	return(tmp);
}

DWORD StringW::toUnsLongInt() const
{
	DWORD num;
	swscanf(m_szString, L"%lu", &num);
	return(num);
}

double StringW::toDouble() const
{
	//return(atof(m_szString));
	double tmp;
	swscanf(m_szString, L"%G", &tmp);
	return(tmp);
}

bool StringW::toBool() const
{
	return(toInt() == 1 || wcscmpi(m_szString, L"true") == 0);
}

DWORD StringW::find_last_of(const WCHAR * str, DWORD pos) const
{

	WCHAR * Find = NULL;
	WCHAR * tmpFind = NULL;
	while((Find = wcsstr(m_szString + pos, str)))
	{
		pos = Find - m_szString + 1;
		tmpFind = Find;
	}

	if(tmpFind != NULL)
		// return Find - (m_szString + pos) + pos; // - pos + pos == 0 ? �����?
		return(tmpFind - m_szString);
	else
		return -1;
}

DWORD StringW::find_last_of(const WCHAR & c, DWORD pos) const
{
	WCHAR str[2];
	str[0] = c;
	str[1] = 0;
	return(find_last_of(str, pos));
}

DWORD StringW::find_last_of(const StringW & str, DWORD pos) const
{
	return(find_last_of(str.c_str(), pos));
}

void StringW::insert(UINT pos, const StringW & data)
{
	insert(pos, data.c_str());
}

void StringW::insert(UINT pos, const WCHAR * data)
{
	WCHAR * tmpStr = new WCHAR[length() + wcslen(data) + 1];
	memcpy(tmpStr, m_szString, sizeof(WCHAR) * pos);
	memcpy(tmpStr + pos, data, sizeof(WCHAR) * wcslen(data));
	memcpy(tmpStr + pos + wcslen(data), m_szString + pos, sizeof(WCHAR) * (length() - pos));
	tmpStr[wcslen(data) + length()] = 0;
	SAFE_DELETE_A(m_szString);
	m_szString = tmpStr;
}


/*bool operator<(const StringW & a, const StringW & b)
{
	return(wcscmp(a.c_str(), b.c_str()) < 0);
}*/

String::operator StringW() const
{
	StringW dst;
	dst.reserve(length());
#if defined(_WINDOWS)
	MultiByteToWideChar(CP_UTF8, 0, m_szString, length() + 1, dst.m_szString, length() + 1);
#else
	mbstowcs(dst.m_szString, m_szString, length() + 1);
#endif
	return(dst);
}

StringW::operator String() const
{
	String dst;
	dst.reserve(length());
#if defined(_WINDOWS)
	WideCharToMultiByte(CP_UTF8, 0, m_szString, length() + 1, dst.m_szString, length() + 1, NULL, NULL);
#else
	wcstombs(dst.m_szString, m_szString, sizeof(WCHAR) * (length() + 1));
#endif
	return(dst);
}

void String::reserve(int length)
{
	SAFE_DELETE_A(m_szString);
	m_szString = new char[length + 1];
}

void String::appendReserve(int length)
{
	char* tmpnewstr = new char[strlen(m_szString) + length + 1];
	strcpy(tmpnewstr, m_szString);
	SAFE_DELETE_A(m_szString);

	m_szString = tmpnewstr;
}

void StringW::reserve(int length)
{
	SAFE_DELETE_A(m_szString);
	m_szString = new WCHAR[length + 1];
}

void StringW::appendReserve(int length)
{
	WCHAR* tmpnewstr = new WCHAR[wcslen(m_szString) + length + 1];
	wcscpy(tmpnewstr, m_szString);
	SAFE_DELETE_A(m_szString);

	m_szString = tmpnewstr;
}
/*
StringW operator+(const WCHAR * a, const StringW & b)
{
	return(StringW(a) + b);
}
StringW operator+(const StringW & a, const WCHAR * b)
{
	return(a + StringW(b));
}*/


bool StringW::operator<(const StringW & s) const
{
	return(wcscmp(m_szString, s.m_szString) < 0);
}

/*
#ifdef _DBG_MEM
#	define new DS_NEW
#endif*/

#if defined(_WINDOWS)
#	pragma warning(default:4996)
#endif
#if defined(_LINUX) || defined(_MAC)
#	pragma GCC diagnostic pop
#endif
