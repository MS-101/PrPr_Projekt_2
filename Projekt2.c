#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct zaznam {
    char kategoriaPonuky[50];
    char miestoPonuky[50];
    char ulica[100];
    int rozloha;
    int cena;
    char popis[200];
    struct zaznam *dalsi;
} ZAZNAM;

void vycistiBuffer(FILE **fr) {
    while (fgetc(*fr) != '\n');
}

void odstranEnter(char *buf) {
    buf[strlen(buf) - 1] = '\0';
}

void nacitajZaznam(ZAZNAM **prvyZaznam) {
    FILE *fr;
    ZAZNAM *aktualnyZaznam, *novyZaznam;
    aktualnyZaznam = *prvyZaznam;

    if ((fr = fopen("reality.txt", "r")) == NULL) {
        printf("Zaznamy neboli nacitane\n");
        return;
    }

    if (*prvyZaznam != NULL) {
        while (aktualnyZaznam != NULL) {
            *prvyZaznam = aktualnyZaznam -> dalsi;
            free(aktualnyZaznam);
            aktualnyZaznam = *prvyZaznam;
        }
    }

    int pocetZaznamov = 0;
    char kategoriaPonuky[50];
    char miestoPonuky[50];
    char ulica[100];
    int rozloha;
    int cena;
    char popis[200];

    while (fgetc(fr) == '&') {
        pocetZaznamov++;

        //nacitanie udajov zo suboru
        vycistiBuffer(&fr);
        fgets(kategoriaPonuky, 50, fr);
        odstranEnter(kategoriaPonuky);
        fgets(miestoPonuky, 50, fr);
        odstranEnter(miestoPonuky);
        fgets(ulica, 100, fr);
        odstranEnter(ulica);
        fscanf(fr, "%d\n", &rozloha);
        fscanf(fr, "%d\n", &cena);
        fgets(popis, 200, fr);
        odstranEnter(popis);

        //zapis udajov do spajaneho zoznamu
        if (pocetZaznamov == 1) {
            *prvyZaznam = (ZAZNAM *)malloc(sizeof(ZAZNAM));
            strcpy((*prvyZaznam) -> kategoriaPonuky, kategoriaPonuky);
            strcpy((*prvyZaznam) -> miestoPonuky, miestoPonuky);
            strcpy((*prvyZaznam) -> ulica, ulica);
            (*prvyZaznam) -> rozloha = rozloha;
            (*prvyZaznam) -> cena = cena;
            strcpy((*prvyZaznam) -> popis, popis);
            aktualnyZaznam = *prvyZaznam;
        } else {
            aktualnyZaznam -> dalsi = (ZAZNAM *)malloc(sizeof(ZAZNAM));
            aktualnyZaznam = aktualnyZaznam -> dalsi;
            strcpy(aktualnyZaznam -> kategoriaPonuky, kategoriaPonuky);
            strcpy(aktualnyZaznam -> miestoPonuky, miestoPonuky);
            strcpy(aktualnyZaznam -> ulica, ulica);
            aktualnyZaznam -> rozloha = rozloha;
            aktualnyZaznam -> cena = cena;
            strcpy(aktualnyZaznam -> popis, popis);
        }
    }

    if (pocetZaznamov > 0) {
        aktualnyZaznam -> dalsi = NULL;
    }

    printf("Nacitalo sa %d zaznamov\n", pocetZaznamov);
    fclose(fr);
}

void vypisZaznam(ZAZNAM *prvyZaznam) {
    ZAZNAM *aktualnyZaznam = prvyZaznam;
    int cisloZaznamu = 1;
    while (aktualnyZaznam != NULL) {
        printf("%d.\n", cisloZaznamu);
        printf("kategoria ponuky: %s\n", aktualnyZaznam -> kategoriaPonuky);
        printf("miesto ponuky: %s\n", aktualnyZaznam -> miestoPonuky);
        printf("ulica: %s\n", aktualnyZaznam -> ulica);
        printf("rozloha v m2: %d\n", aktualnyZaznam -> rozloha);
        printf("cena: %d\n", aktualnyZaznam -> cena);
        printf("popis: %s\n", aktualnyZaznam -> popis);
        aktualnyZaznam = aktualnyZaznam -> dalsi;
        cisloZaznamu++;
    }
}

void pridajZaznam(ZAZNAM **prvyZaznam) {
    ZAZNAM *aktualnyZaznam, *novyZaznam;
    int pozicia, i;
    scanf("%d", &pozicia);

    int pocetZaznamov = 0;
    char kategoriaPonuky[50];
    char miestoPonuky[50];
    char ulica[100];
    int rozloha;
    int cena;
    char popis[200];

    //nacitanie hodnot noveho zaznamu
    while (getchar() != '\n');
    fgets(kategoriaPonuky, 50, stdin);
    odstranEnter(kategoriaPonuky);
    fgets(miestoPonuky, 50, stdin);
    odstranEnter(miestoPonuky);
    fgets(ulica, 100, stdin);
    odstranEnter(ulica);
    scanf("%d", &rozloha);
    scanf("%d", &cena);
    while (getchar() != '\n');
    fgets(popis, 200, stdin);
    odstranEnter(popis);

    //zapis hodnot noveho zaznamu
    novyZaznam = (ZAZNAM*)malloc(sizeof(ZAZNAM));
    strcpy(novyZaznam -> kategoriaPonuky, kategoriaPonuky);
    strcpy(novyZaznam -> miestoPonuky, miestoPonuky);
    strcpy(novyZaznam -> ulica, ulica);
    novyZaznam -> rozloha = rozloha;
    novyZaznam -> cena = cena;
    strcpy(novyZaznam -> popis, popis);

    //pridanie noveho zaznamu do spajaneho zoznamu
    if (pozicia == 1) {
        novyZaznam -> dalsi = *prvyZaznam;
        *prvyZaznam = novyZaznam;
    } else {
        aktualnyZaznam = *prvyZaznam;
        for (i = 2; i < pozicia; i++) {
            if (aktualnyZaznam -> dalsi != NULL) {
                aktualnyZaznam = aktualnyZaznam -> dalsi;
            } else {
                break;
            }
        }
        novyZaznam -> dalsi = aktualnyZaznam -> dalsi;
        aktualnyZaznam -> dalsi = novyZaznam;
    }
}

void zmazZaznamy(ZAZNAM **prvyZaznam) {
    ZAZNAM *aktualnyZaznam, *predoslyZaznam, *odstranenyZaznam;
    char hladaneMiesto[50];
    char najdeneMiesto[50];
    int i;
    int pocetZmazanych = 0;

    scanf("%s", hladaneMiesto);
    for (i = 0; i < strlen(hladaneMiesto); i++) {
        hladaneMiesto[i] = tolower(hladaneMiesto[i]);
    }

    aktualnyZaznam = *prvyZaznam;
    while (aktualnyZaznam != NULL) {
        strcpy(najdeneMiesto, aktualnyZaznam -> miestoPonuky);
        for (i = 0; i < strlen(najdeneMiesto); i++) {
            najdeneMiesto[i] = tolower(najdeneMiesto[i]);
        }

        if (strstr(najdeneMiesto, hladaneMiesto) != NULL) {
            pocetZmazanych++;
            odstranenyZaznam = aktualnyZaznam;
            printf("Bol odstraneny zaznam s miestom: %s\n", odstranenyZaznam -> miestoPonuky);
            if (aktualnyZaznam == *prvyZaznam) {
                *prvyZaznam = (*prvyZaznam) -> dalsi;
            } else {
                predoslyZaznam -> dalsi = aktualnyZaznam -> dalsi;
            }
            aktualnyZaznam = aktualnyZaznam -> dalsi;
            free(odstranenyZaznam);
        } else {
            predoslyZaznam = aktualnyZaznam;
            aktualnyZaznam = aktualnyZaznam -> dalsi;
        }
    }

    printf("Vymazalo sa %d zaznamov\n", pocetZmazanych);
}

void vyhladajZaznamy(ZAZNAM *prvyZaznam) {

}

void aktualizujZaznamy(ZAZNAM **prvyZaznam) {

}

int ukoncProgram(ZAZNAM **prvyZaznam) {
    ZAZNAM *aktualnyZaznam;
    if (*prvyZaznam != NULL) {
        while (aktualnyZaznam != NULL) {
            *prvyZaznam = aktualnyZaznam -> dalsi;
            free(aktualnyZaznam);
            aktualnyZaznam = *prvyZaznam;
        }
    }
    return 0;
}

int main() {
    ZAZNAM *prvyZaznam = NULL;
    while (1)  {
        switch (getchar()) {
            case 'n':
                nacitajZaznam(&prvyZaznam);
                break;
            case 'v':
                vypisZaznam(prvyZaznam);
                break;
            case 'p':
                pridajZaznam(&prvyZaznam);
                break;
            case 'z':
                zmazZaznamy(&prvyZaznam); //podla miesta ponuky
                break;
            case 'h':
                vyhladajZaznamy(prvyZaznam); //podla ceny
                break;
            case 'a':
                aktualizujZaznamy(&prvyZaznam); //podla miesta ponuky
                break;
            case 'k':
                return ukoncProgram(&prvyZaznam);
                break;
        }
    }
}
