#include <stdio.h>
#include "struct.h"
#include "logic.h"
#include "interface.h"

int main(int argc, char *argv[]){
    if (argc < 3) {
        printf("BLAD: Nie podano nazw plikow!\n");
        printf("Poprawne uzycie: %s <plik_odczytu> <plik_zapisu>\n", argv[0]);
        return 1;
    }
  List Mechy_lista;
  inicjalizacja_listy(&Mechy_lista);

  wczytaj(&Mechy_lista, argv[1]);

  int wybor = 0;
    while (wybor != 7) {
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
                    printf("Dodano mecha.\n");
                else
                    if (wynik == 0)
                        printf("BLAD: Mech o takim modelu juz istnieje!\n");
                else
                    printf("BLAD!\n");
                break;
            }
            case 3: {
                int pod_wybor;
                printf("--- USUWANIE ---\n");
                printf("1. Usun pojedynczego mecha (podaj model)\n");
                printf("2. Wyczysc magazyn (usun wszystkie w stanie 'demontazu')\n");
                printf("Wybor: ");
                scanf("%d", &pod_wybor);

                if (pod_wybor == 1) {
                    char model[100];
                    printf("Podaj model mecha do usuniecia: ");
                    scanf("%99s", model);

                    int wynik = usun(&Mechy_lista, model);
                    if (wynik == 1)
                        printf("Usunieto mecha.\n");
                    else if (wynik == -2)
                            printf("BLAD: Mozna usuwac tylko mechy w stanie 'demontazu' lub 'w_naprawie'!\n");
                    else
                        printf("BLAD: Nie znaleziono takiego modelu.\n");
                }
                else if (pod_wybor == 2) {
                    int usuniete = usun_do_demontazu(&Mechy_lista);
                    if (usuniete > 0)
                        printf("Usunieto %d mechow przeznaczonych do demontazu.\n", usuniete);
                    else
                        printf("Brak mechow o statusie 'demontazu'.\n");
                }
                else {
                    printf("Nieprawidlowy wybor.\n");
                }
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
                printf("--- ZAAWANSOWANE ---\n");
                printf("1. Edytuj mecha\n");
                printf("2. Wyszukaj mecha\n");
                printf("3. Zapisz do pliku\n");
                int wyborr;
                scanf("%d", &wyborr);
                if (wyborr == 1)
                    edytuj_mecha(&Mechy_lista);
                else if (wyborr == 2)
                    wyszukaj_mecha(&Mechy_lista);
                else if (wyborr == 3) {
                    zapisz(&Mechy_lista, argv[2]);
                    printf("Zapisano dane do pliku %s.\n", argv[2]);
                }
                break;
            case 7:
                printf("Konczenie programu...\n");
            break;
            default:
                printf("Nieznana opcja. Wybierz 1-7.\n");
        }
    }
    zwolnij_pamiec(&Mechy_lista);

    return 0;
}

