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
  if (strcmp(nowy.stan, "sprawny") != 0 && strcmp(nowy.stan, "uszkodzony") != 0 && strcmp(nowy.stan, "misja") != 0 && strcmp(nowy.stan, "naprawa") && strcmp(nowy.stan, "demontaz") != 0 && strcmp(nowy.stan, "wymaga_przegladu") != 0 && strcmp(nowy.stan, "w_naprawie") != 0) {

    return -2;
        }
  if (strcmp(nowy.klasa, "szturmowy") != 0 && strcmp(nowy.klasa, "wsparcia_ogniowego") != 0 && strcmp(nowy.klasa, "rekonesansowy") != 0 && strcmp(nowy.klasa, "obronny") !=0) {

    return -2;
  }
  Element *check = b->head;
  while(check != NULL){
    if(strcmp(check->dana.model, nowy.model) == 0){
      return -1;
    }
    check = check->next;
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
    Element *obecny = b->head;

    while (obecny->next != NULL) {
      obecny = obecny->next;
    }

    obecny->next = nowy_element;
  }
  return 1;
  }
int usun(List *b, char *model){
  if (b->head == NULL)
    return 0;

  Element *obecny = b->head;
  Element *poprzedni = NULL;

  while (obecny != NULL) {
    if (strcmp(obecny->dana.model, model) == 0) {

      if (strstr(obecny->dana.stan, "sprawny") != NULL ||
      strstr(obecny->dana.stan, "misja") != NULL ||
      strstr(obecny->dana.stan, "uszkodzony") != NULL ||
      strstr(obecny->dana.stan, "wymaga_przegladu") != NULL) {
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
int usun_do_demontazu(List *b) {
  if (b->head == NULL) return 0;
  int licznik = 0;

  Element *obecny = b->head;
  Element *poprzedni = NULL;

  while (obecny != NULL) {
    if (strcmp(obecny->dana.stan, "demontaz") == 0) {
      Element *do_usuniecia = obecny;
      if (poprzedni == NULL) {
        b->head = obecny->next;
        obecny = b->head;
      } else {
        poprzedni->next = obecny->next;
        obecny = obecny->next;
      }
      free(do_usuniecia);
      licznik++;
    } else {
      poprzedni = obecny;
      obecny = obecny->next;
    }
  }
  return licznik;
}
void sort_nazwa(List *b){
  if (b->head == NULL) return;

  int zamiana;
  Element *obecny;
  Element *koniec = NULL;

  do {
    zamiana = 0;
    obecny = b->head;

    while (obecny->next != koniec) {
      if (strcmp(obecny->dana.model, obecny->next->dana.model) > 0) {
        Mech schowek = obecny->dana;
        obecny->dana= obecny->next->dana;
        obecny->next->dana= schowek;
        zamiana = 1;
      }
      obecny = obecny->next;
    }
    koniec = obecny;
  } while (zamiana);
}

void sort_moc(List *b){
  if (b->head == NULL) return;

  int zamiana;
  Element *obecny;
  Element *koniec = NULL;

  do {
    zamiana = 0;
    obecny = b->head;

    while (obecny->next != koniec) {

      if (obecny->dana.moc < obecny->next->dana.moc) {
        Mech schowek = obecny->dana;
        obecny->dana = obecny->next->dana;
        obecny->next->dana = schowek;
        zamiana = 1;
      }
      obecny = obecny->next;
    }
    koniec = obecny;
  } while (zamiana);
}
void zapisz(List *b, char *nazwa_pliku){
  FILE *plik = fopen(nazwa_pliku, "w");
  if (plik == NULL)
    return;

  Element *obecny = b->head;
  while (obecny != NULL) {
    fprintf(plik, "%s %s %d %s %s\n",
        obecny->dana.model,
        obecny->dana.klasa,
        obecny->dana.moc,
        obecny->dana.pilot,
        obecny->dana.stan);
    obecny = obecny->next;
  }
  fclose(plik);
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
void wyszukaj_mecha(List *b) {
  if (b->head == NULL) {
    printf("Lista pusta.\n");
    return;
  }
  int opcja;
  printf("Wyszukaj po:\n1. Prefiksie modelu\n2. Mocy powyzej X\nWybor: ");
  scanf("%d", &opcja);

  Element *obecny = b->head;
  int znaleziono = 0;

  if (opcja == 1) {
    char szukane[100];
    printf("Podaj poczatek nazwy: ");
    scanf("%99s", szukane);
    printf("--- WYNIKI ---\n");
    while(obecny) {
      if (strncmp(obecny->dana.model, szukane, strlen(szukane)) == 0) {
        printf("Model: %s, Moc: %d, Stan: %s\n", obecny->dana.model, obecny->dana.moc, obecny->dana.stan);
        znaleziono++;
      }
      obecny = obecny->next;
    }
  } else if (opcja == 2) {
    int min_moc;
    printf("Podaj minimalna moc: ");
    scanf("%d", &min_moc);
    printf("--- WYNIKI ---\n");
    while(obecny) {
      if (obecny->dana.moc >= min_moc) {
        printf("Model: %s, Moc: %d, Stan: %s\n", obecny->dana.model, obecny->dana.moc, obecny->dana.stan);
        znaleziono++;
      }
      obecny = obecny->next;
    }
  }
  if (znaleziono == 0) printf("Brak wynikow.\n");
}
void edytuj_mecha(List *b) {
  char cel[100];
  printf("Podaj model mecha do edycji: ");
  scanf("%99s", cel);

  Element *obecny = b->head;
  while(obecny) {
    if (strcmp(obecny->dana.model, cel) == 0) {
      do {
        printf("Nowa klasa (szturmowy, wsparcia_ogniowego, rekonesansowy, obronny): ");
        scanf("%99s", obecny->dana.klasa);
        if (strcmp(obecny->dana.klasa, "szturmowy") == 0 ||
            strcmp(obecny->dana.klasa, "wsparcia_ogniowego") == 0 ||
            strcmp(obecny->dana.klasa, "rekonesansowy") == 0 ||
            strcmp(obecny->dana.klasa, "obronny") == 0) {
          break;
            }
        printf("BLAD: Niepoprawna klasa!\n");
      } while(1);
      do {
        printf("Nowa moc (0-100): ");
        if (scanf("%d", &obecny->dana.moc) == 1) {
          if (obecny->dana.moc >= 0 && obecny->dana.moc <= 100) break;
        } else {
          while(getchar() != '\n');
        }
        printf("BLAD: Moc musi byc 0-100!\n");
      } while(1);

      printf("Nowy pilot: ");
      scanf("%99s", obecny->dana.pilot);
      do {
        printf("Nowy stan (sprawny, wymaga_przegladu, uszkodzony, w_naprawie, misja, demontaz, naprawa): ");
        scanf("%99s", obecny->dana.stan);
        if (strcmp(obecny->dana.stan, "sprawny") == 0 || strcmp(obecny->dana.stan, "uszkodzony") == 0 ||
            strcmp(obecny->dana.stan, "misja") == 0 || strcmp(obecny->dana.stan, "naprawa") == 0 ||
            strcmp(obecny->dana.stan, "demontaz") == 0 || strcmp(obecny->dana.stan, "wymaga_przegladu") == 0 ||
            strcmp(obecny->dana.stan, "w_naprawie") == 0) {
          break;
            }
        printf("BLAD: Nieznany stan!\n");
      } while(1);

      printf("Zaktualizowano.\n");
      return;
    }
    obecny = obecny->next;
  }
  printf("Nie znaleziono takiego modelu.\n");
}