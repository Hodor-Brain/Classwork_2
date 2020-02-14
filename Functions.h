#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cstdio>

using namespace std;

struct Word
{
	char eng[16] = {};
	char ukr[16] = {};
};

void flush();

int menu();

int menuchange();

int menudelete();

void newword(char* text, char* word);

void Add();

void Find();

void Change();

void Delete();