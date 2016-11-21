/* File : queuelist.h */
/* Representasi queue dengan list berkait dengan first (HEAD) dan last (TAIL) */

#include "queuelist.h"

/* Prototype manajemen memori */
void Queue_Alokasi (queue_address *P, queue_infotype X)
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka queue_Info(P)=X dan 
        queue_Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
{
	*P = (queue_address) malloc (sizeof (ElmtQueue));
	if (*P != Nil)
	{
		queue_Info(*P) = X;
		queue_Next(*P) = Nil;
	}
}
void Queue_Dealokasi (queue_address P)
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
{
	free(P);
}
bool Queue_IsEmpty (Queue Q)
/* Mengirim true jika Q kosong: HEAD(Q)=Nil and TAIL(Q)=Nil */
{
	return ((Head(Q) == Nil) && (Tail(Q) == Nil));
}
int Queue_NbElmt(Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong */
{
	queue_address P;
	P = Head(Q);
	int c;
	c = 0;
	while ((P != Nil))
	{
		c++;
		P = queue_Next(P);
	}
	return c;
}
/*** Kreator ***/
void Queue_CreateEmpty(Queue * Q)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
{
	Head(*Q) = Nil;
	Tail(*Q) = Nil;
}
/*** Primitif Add/Delete ***/
void Queue_Add (Queue * Q, queue_infotype X)
/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q
   jika alokasi berhasil; jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
{
	queue_address P;

	Queue_Alokasi(&P, X);
	if (P != Nil)
	{
		if (Queue_IsEmpty(*Q))
			Head(*Q) = P;
		else
			queue_Next(Tail(*Q)) = P;
	}
	Tail(*Q) = P;
}
void Queue_Del(Queue * Q, queue_infotype * X)
/* Proses: Menghapus X pada bagian HEAD dari Q dan mendealokasi
   elemen HEAD */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */
{
	queue_address P;

	*X = InfoHead(*Q);
	P = Head(*Q);
	Head(*Q) = queue_Next(Head(*Q));
	if (Head(*Q) == Nil)
		Tail(*Q) = Nil;
	Queue_Dealokasi(P);
}