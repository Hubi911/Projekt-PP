#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logic.h"

void inicjalizacja_listy(List *b){
  b->head = NULL;
  }
void zwolnij_pamiec(List *b){
  }
int dodaj(List *b, Mech nowy){
  Element *nowy_element = (Element*)malloc(sizeof(Element));
  if (nowy_element == NULL) {
    return 0;
  }
  nowy_element->dana = nowy;
  nowy_element->next = b->head;
  b->head = nowy_element;
  return 1;
  }
int usun(List *b, char *model){
  }
void sort_nazwa(List *b){
  }
void sort_moc(List *b){
  }
void zapisz(List *b, char *nazwa_pliku){
  }
void wczytaj(List *b, char *nazwa_pliku){
  FILE *plik = fopen(nazwa_pliku,"r");
  if (plik == NULL){
    return;
  }
  Mech robo;
  while(fscanf(plik," %100s %100s %d %100s %100s",robo.model, robo.klasa, &robo.moc, robo.pilot, robo.stan) == 5){
    dodaj(b, robo);
  }
  fclose(plik);
}