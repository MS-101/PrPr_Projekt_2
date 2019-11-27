#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct zaznam {
    char kategoriaPonuky[50];
    char miestoPonuky[50];
    char ulica[100];
    int rozloha;
    int cena;
    char popis[200];
    struct zaznam *dalsi;
} ZAZNAM;

void vycistiBufferSuboru(FILE **fr) {
    while (fgetc(*fr) != '\n');
}

void vycistiBufferVstupu() {
    while (getchar() != '\n');
}


void odstranNewLine(char *buf) {
    buf[strlen(buf) - 1] = '\0';
}

void vymazZoznam(ZAZNAM ***prvyZaznam) {
    ZAZNAM *aktualnyZaznam;
    aktualnyZaznam = **prvyZaznam;
    if (**prvyZaznam != NULL) {
        while (aktualnyZaznam != NULL) {
            **prvyZaznam = aktualnyZaznam -> dalsi;
            free(aktualnyZaznam);
            aktualnyZaznam = **prvyZaznam;
        }
    }
}

void strLow(char *buf) {
    for (int i = 0; i < strlen(buf); i++) {
        buf[i] = tolower(buf[i]);
    }
}

void nacitajZaznam(ZAZNAM **prvyZaznam) {
    FILE *fr;
    ZAZNAM *aktualnyZaznam;
    aktualnyZaznam = *prvyZaznam;

    if ((fr = fopen("reality.txt", "r")) == NULL) {
        printf("Zaznamy neboli nacitane\n");
        return;
    }

    vymazZoznam(&prvyZaznam);

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
        vycistiBufferSuboru(&fr);
        fgets(kategoriaPonuky, 50, fr);
        odstranNewLine(kategoriaPonuky);
        fgets(miestoPonuky, 50, fr);
        odstranNewLine(miestoPonuky);
        fgets(ulica, 100, fr);
        odstranNewLine(ulica);
        fscanf(fr, "%d\n", &rozloha);
        fscanf(fr, "%d\n", &cena);
        fgets(popis, 200, fr);
        odstranNewLine(popis);

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

void vypisZaznam(int cisloZaznamu, ZAZNAM *aktualnyZaznam) {
    printf("%d.\n", cisloZaznamu);
    printf("kategoria ponuky: %s\n", aktualnyZaznam -> kategoriaPonuky);
    printf("miesto ponuky: %s\n", aktualnyZaznam -> miestoPonuky);
    printf("ulica: %s\n", aktualnyZaznam -> ulica);
    printf("rozloha v m2: %d\n", aktualnyZaznam -> rozloha);
    printf("cena: %d\n", aktualnyZaznam -> cena);
    printf("popis: %s\n", aktualnyZaznam -> popis);
}

void vypisZoznam(ZAZNAM *prvyZaznam) {
    ZAZNAM *aktualnyZaznam = prvyZaznam;
    int cisloZaznamu = 0;
    while (aktualnyZaznam != NULL) {
        cisloZaznamu++;
        vypisZaznam(cisloZaznamu, aktualnyZaznam);
        aktualnyZaznam = aktualnyZaznam -> dalsi;
    }
}

void pridajZaznam(ZAZNAM **prvyZaznam) {
    ZAZNAM *aktualnyZaznam, *novyZaznam;
    int pozicia, i;
    scanf("%d", &pozicia);

    char kategoriaPonuky[50];
    char miestoPonuky[50];
    char ulica[100];
    int rozloha;
    int cena;
    char popis[200];

    //nacitanie hodnot noveho zaznamu
    vycistiBufferVstupu();
    fgets(kategoriaPonuky, 50, stdin);
    odstranNewLine(kategoriaPonuky);
    fgets(miestoPonuky, 50, stdin);
    odstranNewLine(miestoPonuky);
    fgets(ulica, 100, stdin);
    odstranNewLine(ulica);
    scanf("%d", &rozloha);
    scanf("%d", &cena);
    vycistiBufferVstupu();
    fgets(popis, 200, stdin);
    odstranNewLine(popis);

    //zapis hodnot noveho zaznamu
    novyZaznam = (ZAZNAM*)malloc(sizeof(ZAZNAM));
    strcpy(novyZaznam -> kategoriaPonuky, kategoriaPonuky);
    strcpy(novyZaznam -> miestoPonuky, miestoPonuky);
    strcpy(novyZaznam -> ulica, ulica);
    novyZaznam -> rozloha = rozloha;
    novyZaznam -> cena = cena;
    strcpy(novyZaznam -> popis, popis);

    //pridanie noveho zaznamu do spajaneho zoznamu
    if (pozicia == 1 || *prvyZaznam == NULL) {
        novyZaznam -> dalsi = *prvyZaznam;
        *prvyZaznam = novyZaznam;
    } else {
        aktualnyZaznam = *prvyZaznam;
        for (i = 2; i < pozicia; i++) {
            if (aktualnyZaznam != NULL && aktualnyZaznam -> dalsi != NULL) {
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
    int pocetZmazanych = 0;

    vycistiBufferVstupu();
    fgets(hladaneMiesto, 50, stdin);
    odstranNewLine(hladaneMiesto);
    strLow(hladaneMiesto);

    aktualnyZaznam = *prvyZaznam;
    while (aktualnyZaznam != NULL) {
        strcpy(najdeneMiesto, aktualnyZaznam -> miestoPonuky);
        strLow(najdeneMiesto);

        if (strstr(najdeneMiesto, hladaneMiesto) != NULL) {
            pocetZmazanych++;
            odstranenyZaznam = aktualnyZaznam;
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

void hladajZaznamy(ZAZNAM *prvyZaznam) {
    int pocetZaznamov = 0, hladanaCena;
    ZAZNAM *aktualnyZaznam;
    scanf("%d", &hladanaCena);

    aktualnyZaznam = prvyZaznam;
    while (aktualnyZaznam != NULL) {
        if (aktualnyZaznam -> cena <= hladanaCena) {
            pocetZaznamov++;
            vypisZaznam(pocetZaznamov, aktualnyZaznam);
        }
        aktualnyZaznam = aktualnyZaznam -> dalsi;
    }

    if (pocetZaznamov == 0) {
        printf("V ponuke su len reality s vyssou cenou\n");
    }
}

void aktualizujZaznamy(ZAZNAM **prvyZaznam) {
    char hladaneMiesto[50], najdeneMiesto[50];
    ZAZNAM *aktualnyZaznam;

    vycistiBufferVstupu();
    fgets(hladaneMiesto, 50, stdin);
    odstranNewLine(hladaneMiesto);
    strLow(hladaneMiesto);

    int pocetAktualizovanych = 0;
    char kategoriaPonuky[50];
    char miestoPonuky[50];
    char ulica[100];
    int rozloha;
    int cena;
    char popis[200];

    //nacitanie hodnot aktualneho zaznamu
    fgets(kategoriaPonuky, 50, stdin);
    odstranNewLine(kategoriaPonuky);
    fgets(miestoPonuky, 50, stdin);
    odstranNewLine(miestoPonuky);
    fgets(ulica, 100, stdin);
    odstranNewLine(ulica);
    scanf("%d", &rozloha);
    scanf("%d", &cena);
    vycistiBufferVstupu();
    fgets(popis, 200, stdin);
    odstranNewLine(popis);

    aktualnyZaznam = *prvyZaznam;
    while (aktualnyZaznam != NULL) {
        strcpy(najdeneMiesto, aktualnyZaznam -> miestoPonuky);
        strLow(najdeneMiesto);

        if (strstr(najdeneMiesto, hladaneMiesto) != NULL) {
            pocetAktualizovanych++;
            strcpy(aktualnyZaznam -> kategoriaPonuky, kategoriaPonuky);
            strcpy(aktualnyZaznam -> miestoPonuky, miestoPonuky);
            strcpy(aktualnyZaznam -> ulica, ulica);
            aktualnyZaznam -> rozloha = rozloha;
            aktualnyZaznam -> cena = cena;
            strcpy(aktualnyZaznam -> popis, popis);
        }

        aktualnyZaznam = aktualnyZaznam -> dalsi;
    }

    printf("Aktualizovalo sa %d zaznamov\n", pocetAktualizovanych);
}

int koniecProgramu(ZAZNAM **prvyZaznam) {
    vymazZoznam(&prvyZaznam);
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
                vypisZoznam(prvyZaznam);
                break;
            case 'p':
                pridajZaznam(&prvyZaznam);
                break;
            case 'z':
                zmazZaznamy(&prvyZaznam); //podla miesta ponuky
                break;
            case 'h':
                hladajZaznamy(prvyZaznam); //podla ceny
                break;
            case 'a':
                aktualizujZaznamy(&prvyZaznam); //podla miesta ponuky
                break;
            case 'k':
                return koniecProgramu(&prvyZaznam);
                break;
        }
    }
}
