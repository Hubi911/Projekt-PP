cmake_minimum_required(VERSION 3.0)
project(Projekt_PP C)

set(CMAKE_C_STANDARD 11)

add_executable(Main Main.c logic.c interface.c)

set(SCIEZKA_WEJSCIE "C:/Users/polow/OneDrive/Pulpit/Studia/semestr 3/Język c/Projekt-PP/cmake-build-debug/projekt_mechy.txt")
set(SCIEZKA_WYJSCIE "C:/Users/polow/OneDrive/Pulpit/Studia/semestr 3/Język c/Projekt-PP/cmake-build-debug/wynik.txt")

add_custom_target(uruchom

        COMMAND Main "${SCIEZKA_WEJSCIE}" "${SCIEZKA_WYJSCIE}"

        DEPENDS Main

        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}

        COMMENT "Uruchamianie programu Main ze sciezkami...")

