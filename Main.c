#include <stdio.h>
#include "struct.h"
#include "logic.h"
#include "interface.h"

int main(int argc, char *argv[]){
  List Mechy_lista;
  inicjalizacja_listy(&Mechy_lista);

  wczytaj(&Mechy_lista, "projekt_mechy.txt");

  int wybor = 0;
    while (wybor != 6) {
        pokaz_menu();


        if (scanf("%d", &wybor) != 1) {
            while(getchar() != '\n');
            wybor = 0;
            continue;
        }

        switch (wybor) {
            case 1:
                wypisz(&Mechy_lista);
                break;
            case 2: {
                Mech m = pobierz_od_uzytkownika();
                int wynik = dodaj(&Mechy_lista, m);
                if (wynik == 1)
                    printf("SUKCES: Dodano mecha.\n");
                else
                    if (wynik == 0)
                        printf("BLAD: Mech o takim modelu juz istnieje!\n");
                else
                    printf("BLAD!\n");
                break;
            }
            case 3: {
                char model[100];
                printf("Podaj model mecha do usuniecia: ");
                scanf("%99s", model);

                int wynik = usun(&Mechy_lista, model);
                if (wynik == 1)
                    printf("SUKCES: Usunieto mecha.\n");
                else
                    if (wynik == -2)
                        printf("BLAD: Nie mozna usunac (mech jest sprawny/w misji)!\n");
                else
                    printf("BLAD: Nie znaleziono takiego modelu.\n");
                break;
            }
            case 4:
                sort_nazwa(&Mechy_lista);
                printf("Posortowano liste alfabetycznie.\n");
                wypisz(&Mechy_lista);
                break;
            case 5:
                sort_moc(&Mechy_lista);
                printf("Posortowano liste wedlug mocy (malejaco).\n");
                wypisz(&Mechy_lista);
                break;
            case 6:
                zapisz(&Mechy_lista, "Mechy_zapis.txt");
                printf("Zapisano dane do pliku %s. Koniec programu.\n", "Mechy_zapis.txt");
                break;
            default:
                printf("Nieznana opcja. Wybierz 1-6.\n");
        }
    }
    zwolnij_pamiec(&Mechy_lista);

    return 0;
}

