#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct zaznam {
    char[50] kategoriaPonuky;
    char[50] miestoPonuky;
    char[100] ulica;
    int rozloha;
    int cena;
    char[200] popis;
} ZAZNAM

void nacitajZaznam() {

}

void vypisZaznam() {

}

void pridajZaznam() {

}

void zmazZaznamy() {

}

void aktualizujZaznamy() {

}

int ukoncProgram {
    return 0;
}

int main() {
    FILE *fr = NULL;
    ZAZNAM *prvyZaznam = NULL;
    while (1)  {
        switch (getchar()) {
            case 'n':
                nacitajZaznam(&fr, &prvyZaznam);
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
