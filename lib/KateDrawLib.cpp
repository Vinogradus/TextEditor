#include "KateDrawLib.h"

namespace KateDrawLib
{

	void DrawBox(uint start_x, uint start_y, uint width, uint height,
		Colour background, Colour text, TypeOfLine line)
	{
		uint i, j;

		Gotoxy(start_x, start_y);
		SetColour(background, text);

		if (line == TypeOfLine::OneLine)
		{
			std::cout << static_cast<char>(OneLine::NW);
			for (i = 1; i < width - 1; ++i) std::cout << static_cast<char>(OneLine::H);
			std::cout << static_cast<char>(OneLine::NE);

			for (j = 1; j < height - 1; ++j)
			{
				Gotoxy(start_x, start_y + j);
				std::cout << static_cast<char>(OneLine::V);
				Gotoxy(start_x + width - 1, start_y + j);
				std::cout << static_cast<char>(OneLine::V);
			}

			Gotoxy(start_x, start_y + height - 1);
			std::cout << static_cast<char>(OneLine::SW);
			for (i = 1; i < width - 1; ++i) std::cout << static_cast<char>(OneLine::H);
			std::cout << static_cast<char>(OneLine::SE);
		}
		else if (line == TypeOfLine::TwoLine)
		{
			std::cout << static_cast<char>(TwoLine::NW);
			for (i = 1; i < width - 1; ++i) std::cout << static_cast<char>(TwoLine::H);
			std::cout << static_cast<char>(TwoLine::NE);

			for (j = 1; j < height - 1; ++j)
			{
				Gotoxy(start_x, start_y + j);
				std::cout << static_cast<char>(TwoLine::V);
				Gotoxy(start_x + width - 1, start_y + j);
				std::cout << static_cast<char>(TwoLine::V);
			}

			Gotoxy(start_x, start_y + height - 1);
			std::cout << static_cast<char>(TwoLine::SW);
			for (i = 1; i < width - 1; ++i) std::cout << static_cast<char>(TwoLine::H);
			std::cout << static_cast<char>(TwoLine::SE);
		}
	}

	void FillBox(uint start_x, uint start_y, uint width, uint height, Colour background)
	{
		Gotoxy(start_x, start_y);
		SetColour(background, background);

		uint i, j;
		for (j = 0; j < height; ++j)
		{
			Gotoxy(start_x, start_y + j);
			for (i = 0; i < width; ++i)
				std::cout << " ";
			std::cout << "\n";
		}
	}

	void FillAndDrawBox(uint start_x, uint start_y, uint width, uint height,
		Colour background, Colour text, TypeOfLine line)
	{
		FillBox(start_x, start_y, width, height, background);
		DrawBox(start_x, start_y, width, height, background, text, line);
	}

	void SetColour(Colour background, Colour text)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (WORD)(static_cast<int>(background) << 4) | static_cast<int>(text));
	}

	void Gotoxy(uint x, uint y)
	{
		HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD coord = { x,y };
		SetConsoleCursorPosition(StdOut, coord);
	}

	void DrawGrid(uint start_x, uint start_y, uint num_col, uint num_line, uint cell_width,
		uint cell_height, Colour background, Colour text, TypeOfLine line)
	{
		uint i, j, k, g;

		Gotoxy(start_x, start_y);
		SetColour(background, text);

		if (line == TypeOfLine::OneLine)
		{
			std::cout << static_cast<char>(OneLine::NW);
			for (i = 0; i < num_col; ++i)
			{
				for (j = 0; j < cell_width; ++j) std::cout << static_cast<char>(OneLine::H);
				if (i == num_col - 1) break;
				std::cout << static_cast<char>(OneLine::N);
			}
			std::cout << static_cast<char>(OneLine::NE);

			for (i = 0; i < num_line; ++i)
			{
				for (j = 1; j <= cell_height; ++j)
				{
					Gotoxy(start_x, start_y + i * (cell_height + 1) + j);
					for (k = 0; k < num_col + 1; ++k)
					{
						Gotoxy(start_x + k * (cell_width + 1), start_y + i * (cell_height + 1) + j);
						std::cout << static_cast<char>(OneLine::V);
					}
				}
				if (i == num_line - 1) break;

				Gotoxy(start_x, start_y + (i + 1) * (cell_height + 1));
				std::cout << static_cast<char>(OneLine::W);
				for (k = 0; k < num_col; ++k)
				{
					for (j = 0; j < cell_width; ++j) std::cout << static_cast<char>(OneLine::H);
					if (k == num_col - 1) break;
					std::cout << static_cast<char>(OneLine::O);
				}
				std::cout << static_cast<char>(OneLine::E);
			}

			Gotoxy(start_x, start_y + (num_line) * (cell_height + 1));
			std::cout << static_cast<char>(OneLine::SW);
			for (i = 0; i < num_col; ++i)
			{
				for (j = 0; j < cell_width; ++j) std::cout << static_cast<char>(OneLine::H);
				if (i == num_col - 1) break;
				std::cout << static_cast<char>(OneLine::S);
			}
			std::cout << static_cast<char>(OneLine::SE);
		}
		else if (line == TypeOfLine::TwoLine)
		{
			std::cout << static_cast<char>(TwoLine::NW);
			for (i = 0; i < num_col; ++i)
			{
				for (j = 0; j < cell_width; ++j) std::cout << static_cast<char>(TwoLine::H);
				if (i == num_col - 1) break;
				std::cout << static_cast<char>(TwoLine::N);
			}
			std::cout << static_cast<char>(TwoLine::NE);

			for (i = 0; i < num_line; ++i)
			{
				for (j = 1; j <= cell_height; ++j)
				{
					Gotoxy(start_x, start_y + i * (cell_height + 1) + j);
					for (k = 0; k < num_col + 1; ++k)
					{
						Gotoxy(start_x + k * (cell_width + 1), start_y + i * (cell_height + 1) + j);
						std::cout << static_cast<char>(TwoLine::V);
					}
				}
				if (i == num_line - 1) break;

				Gotoxy(start_x, start_y + (i + 1) * (cell_height + 1));
				std::cout << static_cast<char>(TwoLine::W);
				for (k = 0; k < num_col; ++k)
				{
					for (j = 0; j < cell_width; ++j) std::cout << static_cast<char>(TwoLine::H);
					if (k == num_col - 1) break;
					std::cout << static_cast<char>(TwoLine::O);
				}
				std::cout << static_cast<char>(TwoLine::E);
			}

			Gotoxy(start_x, start_y + (num_line) * (cell_height + 1));
			std::cout << static_cast<char>(TwoLine::SW);
			for (i = 0; i < num_col; ++i)
			{
				for (j = 0; j < cell_width; ++j) std::cout << static_cast<char>(TwoLine::H);
				if (i == num_col - 1) break;
				std::cout << static_cast<char>(TwoLine::S);
			}
			std::cout << static_cast<char>(TwoLine::SE);
		}

	}
}