#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logic.h"

void inicjalizacja_listy(List *b){
  b->head = NULL;
  }
void zwolnij_pamiec(List *b){
  Element *obecny = b->head;
  while (obecny != NULL) {
    Element *do_usuniecia = obecny;
    obecny = obecny->next;
    free(do_usuniecia);
  }
  b->head = NULL;
}
int dodaj(List *b, Mech nowy){
  if (strcmp(nowy.stan, "sprawny") != 0 && strcmp(nowy.stan, "uszkodzony") != 0 && strcmp(nowy.stan, "misja") != 0 && strcmp(nowy.stan, "naprawa") && strcmp(nowy.stan, "wymaga_przegladu") != 0 && strcmp(nowy.stan, "w_naprawie") != 0) {

    return -2;
        }
  if (strcmp(nowy.klasa, "szturmowy") != 0 && strcmp(nowy.klasa, "wsparcia_ogniowego") != 0 && strcmp(nowy.klasa, "rekonesansowy") != 0 && strcmp(nowy.klasa, "obronny") !=0) {

    return -2;
  }
  Element *nowy_element = (Element*)malloc(sizeof(Element));
  if (nowy_element == NULL) {
    return 0;
  }
  nowy_element->dana = nowy;
  nowy_element->next = NULL;
  if (b->head == NULL) {
    b->head = nowy_element;
  } else {
    Element *temp = b->head;

    while (temp->next != NULL) {
      temp = temp->next;
    }

    temp->next = nowy_element;
  }
  return 1;
  }
int usun(List *b, char *model){
  if (b->head == NULL) return 0; // Pusta lista

  Element *obecny = b->head;
  Element *poprzedni = NULL;

  while (obecny != NULL) {
    if (strcmp(obecny->dana.model, model) == 0) {

      if (strstr(obecny->dana.stan, "sprawny") != NULL ||
          strstr(obecny->dana.stan, "misja") != NULL) {
        return -2;
          }

      if (poprzedni == NULL) {
        b->head = obecny->next;
      } else {
        poprzedni->next = obecny->next;
      }

      free(obecny);
      return 1;
    }
    poprzedni = obecny;
    obecny = obecny->next;
  }
  return 0;
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
    printf("BLAD: Nie udalo sie otworzyc pliku!\n");
    return;
  }
  Mech robo;
  while(fscanf(plik," %100s %100s %d %100s %100s",robo.model, robo.klasa, &robo.moc, robo.pilot, robo.stan) == 5){
    dodaj(b, robo);
  }
  fclose(plik);
}