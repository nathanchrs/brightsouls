#ifndef UTILITIES_H
#define UTILITIES_H

	#include <stdlib.h>

	/* I.S. -
	   F.S. Layar dikosongkan */
	void clearScreen();

	/* I.S. -
	   F.S. Menunggu selama waktu yang ditetapkan (duration dalam detik, resolusi tergantung sistem) */
	void delay(const double duration);

	void copyRawBytes(void *dest, const void *src, size_t n);

#endif