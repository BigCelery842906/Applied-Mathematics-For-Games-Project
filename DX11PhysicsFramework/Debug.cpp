#pragma once
#include <string>
#include <Windows.h>

void DebugLog(int num)
{
	OutputDebugStringA("Number: " + num);
}

void DebugIncrement() 
{
	static int x = 0;
	char sz[1024] = { 0 };
	sprintf_s(sz, "the number is %d \n", x);
	OutputDebugStringA(sz);
	x++;
}