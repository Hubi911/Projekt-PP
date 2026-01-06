#include <stdio.h>
#include <string.h>
#include "interface.h"

void pokaz_menu(){
  printf("\n----ZARZADZAJ FLOTA----\n");
  printf("1. Lista mechow\n");
  printf("2. Dodaj nowego mecha\n");
  printf("3. Usun mecha\n");
  printf("4. Sortuj po nazwie\n");
  printf("5. Sortuj po mocy\n");
  printf("6. Zapisz\n");
  printf("7. Wyjdz\n");
  printf("Twoj wybor: ");
 }
 void wypisz(List *b){
   if(b->head==NULL){
     printf("Nasza lista jest pusta.\n");
     return;
     }

     Element *obecny = b->head;
     int licznik = 0;
     printf("----Lista Mechow----\n");
     while(obecny != NULL){
       printf("Mech %d: \n", licznik + 1);
       printf("Model: %s \n", obecny->dana.model);
       printf("Klasa: %s \n", obecny->dana.klasa);
       printf("Moc: %d \n", obecny->dana.moc);
       if (strcmp(obecny->dana.pilot, "-") == 0) {
         printf("Pilot: (brak) \n");
       } else {
         printf("Pilot: %s \n", obecny->dana.pilot);
       }
       printf("Stan: %s \n", obecny->dana.stan);
       printf("-------------------------\n");
       obecny=obecny->next;
       licznik++;
       }
       printf("Laczna liczba mechow: %d\n", licznik);
 }
Mech pobierz_od_uzytkownika() {
  Mech m;

  printf("Podaj model: ");
  scanf("%99s", m.model);

  printf("Podaj klase (szturmowy, wsparcia_ogniowego, rekonesansowy, obronny): ");
  scanf("%99s", m.klasa);

  do {
    printf("Podaj moc reaktora (0-100): ");
    if (scanf("%d", &m.moc) == 1) {
      if (m.moc >= 0 && m.moc <= 100)
        break;
    } else {
      while(getchar() != '\n');
    }
    printf("BLAD: Moc musi byc liczba z zakresu 0-100!\n");
  } while(1);

  printf("Podaj nick pilota: ");
  scanf("%99s", m.pilot);

  printf("Podaj stan (sprawny, wymaga_przegladu, uszkodzony, w_naprawie, misja): ");
  scanf("%99s", m.stan);

  return m;
}