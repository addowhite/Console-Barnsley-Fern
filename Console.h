#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <stdint.h>
#include <Windows.h>

class Console {

public:
	enum Colors : uint32_t {
		WHITE      = 0x2588,
		LIGHT_GRAY = 0x2593,
		GRAY       = 0x2592,
		DARK_GRAY  = 0x2591,
		BLACK      = ' '
	};

	Console(uint32_t width, uint32_t height, uint32_t fontSize = 16);
	~Console();
	void setChar(uint32_t x, uint32_t y, wchar_t chr, bool updateNow);
	inline void clear() { fill(BLACK); };
	inline void fill(wchar_t chr) {
		for (wchar_t *it = buffer; it != buffer + width * height; *(it++) = chr);
	};
	void flush();
	inline uint32_t getWidth() { return width; };
	inline uint32_t getHeight() { return height; };

private:
	uint32_t width, height;
	HANDLE handle;
	wchar_t *buffer;

};

#endif /* _CONSOLE_H_ */