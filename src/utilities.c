#include "utilities.h"
#include "stringutils.h"
#include "time.h"

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

void copyRawBytes(void *dest, const void *src, size_t n) {
	size_t i;
	for (i = 0; i<n; i++) ((char*) dest)[i] = ((char*) src)[i];
}

char *getExecutableDirectory(const char *executablePath) {
	char *res = StringUtils_clone(executablePath);
	int i = StringUtils_strlen(res)-1;
	while (i >= 0 && res[i] != '/' && res[i] != '\\') i--;
	res[i+1] = 0;
	return res;
}

int getRandomInt(int min, int max) {
	srand(time(NULL));
	return min + (rand() % (max-min+1));
}