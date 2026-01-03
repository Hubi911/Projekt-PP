#ifndef LOGIC_H
#define LOGIC_H
#include "struct.h"

void inicjalizacja_listy(List *b);
void zwolnij_pamiec(List *b);
int dodaj(List *b, Mech nowy);
int usun(List *b, char *model);
void sort_nazwa(List *b);
void sort_moc(List *b);
void zapisz(List *b, char *nazwa_pliku);
void wczytaj(List *b, char *nazwa_pliku);

#endif
