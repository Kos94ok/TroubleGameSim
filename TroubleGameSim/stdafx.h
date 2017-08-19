#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include <random>
#include <string>

#ifdef _WIN32
	#include <tchar.h>
	#include <conio.h>
	#include <Windows.h>
#elif __linux__
	#include <unistd.h>
	#include <termios.h>
#endif
