#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "logic.h"
#include "interface.h"

int main(int argc, char *argv[]){
  List Mechy_lista;
  inicjalizacja_listy(&Mechy_lista);

  wczytaj(&Mechy_lista, "projekt_mechy.txt");
  wypisz(&Mechy_lista);
  return 0;
  }
