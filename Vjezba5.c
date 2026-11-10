#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct cvor;
typedef struct cvor* Pozicija;

struct cvor {
    int element;
    Pozicija sljedeci;
};

/* Prototipi */
int ucitajIzDatoteke(Pozicija glava);
int ispisListe(Pozicija prvi);
int unija(Pozicija L1, Pozicija L2, Pozicija U);
int presjek(Pozicija L1, Pozicija L2, Pozicija P);
void obrisiSve(Pozicija glava);

int main() {
    struct cvor glava1 = { 0, NULL };
    struct cvor glava2 = { 0, NULL };
    struct cvor glavaUnija = { 0, NULL };
    struct cvor glavaPresjek = { 0, NULL };

    if (ucitajIzDatoteke(&glava1) != 0) {
        printf("Greska pri ucitavanju prve liste!\n");
        return 1;
    }

    if (ucitajIzDatoteke(&glava2) != 0) {
        printf("Greska pri ucitavanju druge liste!\n");
        obrisiSve(&glava1);
        return 1;
    }

    printf("\nLista 1: ");
    ispisListe(glava1.sljedeci);

    printf("Lista 2: ");
    ispisListe(glava2.sljedeci);

    unija(glava1.sljedeci, glava2.sljedeci, &glavaUnija);
    presjek(glava1.sljedeci, glava2.sljedeci, &glavaPresjek);

    printf("\nUnija: ");
    ispisListe(glavaUnija.sljedeci);

    printf("Presjek: ");
    ispisListe(glavaPresjek.sljedeci);

    obrisiSve(&glava1);
    obrisiSve(&glava2);
    obrisiSve(&glavaUnija);
    obrisiSve(&glavaPresjek);

    return 0;
}

int ucitajIzDatoteke(Pozicija glava) {
    char imeDatoteke[128];
    FILE* dat = NULL;
    int vrijednost;
    Pozicija zadnji = glava;
    Pozicija novi = NULL;

    printf("Unesite ime datoteke: ");
    scanf(" %s", imeDatoteke);

    dat = fopen(imeDatoteke, "r");
    if (!dat) {
        printf("Datoteka se ne moze otvoriti!\n");
        return 1;
    }

    while (fscanf(dat, "%d", &vrijednost) == 1) {
        novi = (Pozicija)malloc(sizeof(struct cvor));
        if (!novi) {
            fclose(dat);
            return -1;
        }

        novi->element = vrijednost;
        novi->sljedeci = NULL;
        zadnji->sljedeci = novi;
        zadnji = novi;
    }

    fclose(dat);
    return 0;
}

int ispisListe(Pozicija p) {
    if (!p) {
        printf("Prazna lista\n");
        return 0;
    }

    while (p) {
        printf("%d ", p->element);
        p = p->sljedeci;
    }
    printf("\n");
    return 0;
}


int unija(Pozicija L1, Pozicija L2, Pozicija U) {
    Pozicija zadnji = U;
    Pozicija novi = NULL;
    int zadnjaVrijednost = 0;
    int prvi = 1;

    while (L1 || L2) {
        int vrijednost;

        if (!L2 || (L1 && L1->element < L2->element)) {
            vrijednost = L1->element;
            L1 = L1->sljedeci;
        }
        else if (!L1 || L2->element < L1->element) {
            vrijednost = L2->element;
            L2 = L2->sljedeci;
        }
        else {
            vrijednost = L1->element;
            L1 = L1->sljedeci;
            L2 = L2->sljedeci;
        }

        if (prvi || vrijednost != zadnjaVrijednost) {
            novi = (Pozicija)malloc(sizeof(struct cvor));
            if (!novi) return -1;

            novi->element = vrijednost;
            novi->sljedeci = NULL;
            zadnji->sljedeci = novi;
            zadnji = novi;

            zadnjaVrijednost = vrijednost;
            prvi = 0;
        }
    }
    return 0;
}


int presjek(Pozicija L1, Pozicija L2, Pozicija P) {
    Pozicija zadnji = P;
    Pozicija novi = NULL;

    while (L1 && L2) {
        if (L1->element == L2->element) {
            novi = (Pozicija)malloc(sizeof(struct cvor));
            if (!novi) return -1;

            novi->element = L1->element;
            novi->sljedeci = NULL;
            zadnji->sljedeci = novi;
            zadnji = novi;

            L1 = L1->sljedeci;
            L2 = L2->sljedeci;
        }
        else if (L1->element < L2->element) {
            L1 = L1->sljedeci;
        }
        else {
            L2 = L2->sljedeci;
        }
    }
    return 0;
}


void obrisiSve(Pozicija glava) {
    Pozicija temp;

    while (glava->sljedeci) {
        temp = glava->sljedeci;
        glava->sljedeci = temp->sljedeci;
        free(temp);
    }
}
