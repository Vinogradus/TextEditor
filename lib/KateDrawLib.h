#pragma once
#ifndef _KATEDRAWLIB_H_
#define _KATEDRAWLIB_H_

#include <iostream>
#include <Windows.h>

typedef unsigned int uint;
enum class Colour;
enum class OneLine;
enum class TwoLine;
enum class TypeOfLine;

namespace KateDrawLib
{
	void DrawBox(uint start_x, uint start_y, uint width, uint height,
		Colour background, Colour text, TypeOfLine line);
	void FillBox(uint start_x, uint start_y, uint width, uint height, Colour background);
	void FillAndDrawBox(uint start_x, uint start_y, uint width, uint height,
		Colour background, Colour text, TypeOfLine line);
	void SetColour(Colour background, Colour text);
	void Gotoxy(uint x, uint y);
	void DrawGrid(uint start_x, uint start_y, uint num_col, uint num_line, uint cell_width,
		uint cell_height, Colour background, Colour text, TypeOfLine line);
};

enum class Colour
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

enum class OneLine
{
	NW = 218, N = 194, NE = 191,
	W = 195, O = 197, E = 180,
	SW = 192, S = 193, SE = 217,

	V = 179, H = 196
};

enum class TwoLine
{
	NW = 201, N = 203, NE = 187,
	W = 204, O = 206, E = 185,
	SW = 200, S = 202, SE = 188,

	V = 186, H = 205
};

enum class TypeOfLine
{
	OneLine = 1,
	TwoLine = 2
};

#endif //_KATEDRAWLIB_H_
