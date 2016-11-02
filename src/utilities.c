#include "utilities.h"

#ifdef _WIN32
// Windows-specific implementation

	#include <windows.h>

	void clearScreen(){
		system("cls");
	}

	void delay(const double duration){
		Sleep(duration * 1000);
	}
	
#elif __linux__
// Linux-specific implementation
	
	#include <unistd.h>
	
	void clearScreen(){
		system("clear");
	}
	
	void delay(const double duration){
		usleep(duration * 1000000);
	}

#endif