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

     Element *temp = b->head;
     int licznik = 1;
     printf("----Lista Mechow----\n");
     while(temp != NULL){
       printf("Mech %d: \n", licznik);
       printf("Model: %s \n", temp->dana.model);
       printf("Klasa: %s \n", temp->dana.klasa);
       printf("Moc: %d \n", temp->dana.moc);
       printf("Pilot: %s \n", temp->dana.pilot);
       printf("Stan: %s \n", temp->dana.stan);
       printf("-------------------------\n");
       temp=temp->next;
       licznik++;
       }
       printf("Laczna liczba mechow: %d\n", licznik);
 }