#include "Console.h"

Console::Console(uint32_t width, uint32_t height, uint32_t fontSize) {
	this->width = width;
	this->height = height;
	buffer = new wchar_t[width * height];
	handle = CreateConsoleScreenBuffer(GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(handle);

	CONSOLE_FONT_INFOEX font;
	wcscpy_s(font.FaceName, L"Lucida Console");
	font.cbSize = sizeof(font);
	font.dwFontSize.X = fontSize;
	font.dwFontSize.Y = fontSize;
	font.FontFamily = FF_DONTCARE;
	font.FontWeight = FW_NORMAL;
	font.nFont = 0;

	SetCurrentConsoleFontEx(handle, false, &font);
}

Console::~Console() {
	delete buffer;
}

void Console::setChar(uint32_t x, uint32_t y, wchar_t chr, bool updateNow) {
	if (x < 0 || x >= width || y < 0 || y >= height) return;
	buffer[y * width + x] = chr;
	if (updateNow) {
		DWORD bytesWritten = 0;
		WriteConsoleOutputCharacter(handle, buffer + width * y + x, 1, { (SHORT)x, (SHORT)y }, &bytesWritten);
	}
}

void Console::flush() {
	DWORD bytesWritten = 0;
	for (uint32_t y = 0; y < height; ++y)
		WriteConsoleOutputCharacter(handle, buffer + width * y, width, { 0, (SHORT)y }, &bytesWritten);
}