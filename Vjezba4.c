
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ERRORFILE -1
#define ERRORMEMORY -2

struct node;
typedef struct node* Position;

struct node {
    int koeficijent;
    int eksponent;
    Position next;
};

int readPolynom(Position);
int sumPolynom(Position, Position, Position);
int mulPolynom(Position, Position, Position);
int printList(Position);
int freePolynom(Position);

int main() {
    struct node head1;
    struct node head2;
    struct node headSuma;
    struct node headMultiple;

    int result = 0;

    head1.next = NULL;
    head2.next = NULL;
    headSuma.next = NULL;
    headMultiple.next = NULL;

    result = readPolynom(&head1);

    if (result == ERRORFILE) {
        printf("Greska! Datoteka nije otvorena!\n");
        return 0;
    }
    else if (result == ERRORMEMORY) {
        printf("Greska! Memorija nije alocirana!\n");
        freePolynom(&head1);
        return 0;
    }
    else {
        printf("Sve je u redu!\n");
    }

    result = readPolynom(&head2);

    if (result == ERRORFILE) {
        printf("Greska! Datoteka nije otvorena!\n");
        freePolynom(&head1);
        return 0;
    }
    else if (result == ERRORMEMORY) {
        printf("Greska! Memorija nije alocirana!\n");
        freePolynom(&head1);
        freePolynom(&head2);
        return 0;
    }
    else {
        printf("Sve je u redu!\n");
    }

    printf("\nPrvi polinom:\n");
    printList(head1.next);

    printf("\nDrugi polinom:\n");
    printList(head2.next);

    result = sumPolynom(head1.next, head2.next, &headSuma);

    if (result == ERRORMEMORY) {
        printf("Greska! Memorija nije alocirana!\n");
        freePolynom(&head1);
        freePolynom(&head2);
        freePolynom(&headSuma);
        return 0;
    }
    else {
        printf("\nSve je u redu!\n");
    }

    printf("\nZbroj polinoma:\n");
    printList(headSuma.next);

    result = mulPolynom(head1.next, head2.next, &headMultiple);

    if (result == ERRORMEMORY) {
        printf("Greska! Memorija nije alocirana!\n");
        freePolynom(&head1);
        freePolynom(&head2);
        freePolynom(&headSuma);
        freePolynom(&headMultiple);
        return 0;
    }
    else {
        printf("\nSve je u redu!\n");
    }

    printf("\nUmnozak polinoma:\n");
    printList(headMultiple.next);

    freePolynom(&head1);
    freePolynom(&head2);
    freePolynom(&headSuma);
    freePolynom(&headMultiple);

    return 0;
}

int readPolynom(Position P) {
    FILE* fp = NULL;
    char fileName[128] = "\0";
    Position q = NULL;
    Position start = P;
    int result;

    printf("Upisite ime datoteke:\n");
    scanf("%127s", fileName);

    fp = fopen(fileName, "r");

    if (fp == NULL) {
        printf("Datoteka nije otvorena!\n");
        return ERRORFILE;
    }

    while (1) {
        q = (Position)malloc(sizeof(struct node));

        if (q == NULL) {
            printf("Neuspjesna alokacija memorije!\n");
            fclose(fp);
            return ERRORMEMORY;
        }

        result = fscanf(fp, "%d %d",
            &q->koeficijent, &q->eksponent);

        if (result == EOF) {
            free(q);
            break;
        }

        if (result != 2) {
            free(q);
            fclose(fp);
            return ERRORFILE;
        }

        while (P->next != NULL &&
            P->next->eksponent > q->eksponent) {
            P = P->next;
        }

        q->next = P->next;
        P->next = q;

        P = start;
    }

    fclose(fp);
    return 0;
}

int sumPolynom(Position P1, Position P2, Position Suma) {
    Position q = NULL;

    while (P1 != NULL || P2 != NULL) {

        q = (Position)malloc(sizeof(struct node));

        if (q == NULL) {
            printf("Neuspjesna alokacija memorije!\n");
            return ERRORMEMORY;
        }

        if (P1 == NULL) {
            q->eksponent = P2->eksponent;
            q->koeficijent = P2->koeficijent;
            P2 = P2->next;
        }
        else if (P2 == NULL) {
            q->eksponent = P1->eksponent;
            q->koeficijent = P1->koeficijent;
            P1 = P1->next;
        }
        else {
            if (P1->eksponent > P2->eksponent) {
                q->eksponent = P1->eksponent;
                q->koeficijent = P1->koeficijent;
                P1 = P1->next;
            }
            else if (P1->eksponent < P2->eksponent) {
                q->eksponent = P2->eksponent;
                q->koeficijent = P2->koeficijent;
                P2 = P2->next;
            }
            else {
                q->eksponent = P1->eksponent;
                q->koeficijent =
                    P1->koeficijent + P2->koeficijent;

                P1 = P1->next;
                P2 = P2->next;
            }
        }

        q->next = NULL;
        Suma->next = q;
        Suma = q;
    }

    return 0;
}

int mulPolynom(Position P1, Position P2, Position multiple) {
    Position q = NULL;
    Position i = NULL;
    Position j = NULL;
    Position tmp = NULL;

    int eksp = 0;
    int koeficijent = 0;

    i = P1;

    while (i != NULL) {
        j = P2;

        while (j != NULL) {

            eksp = i->eksponent + j->eksponent;
            koeficijent = i->koeficijent * j->koeficijent;

            tmp = multiple;

            while (tmp->next != NULL &&
                tmp->next->eksponent > eksp) {
                tmp = tmp->next;
            }

            if (tmp->next != NULL &&
                tmp->next->eksponent == eksp) {

                tmp->next->koeficijent += koeficijent;
            }
            else {
                q = (Position)malloc(sizeof(struct node));

                if (q == NULL) {
                    printf("Neuspjesna alokacija memorije!\n");
                    return ERRORMEMORY;
                }

                q->eksponent = eksp;
                q->koeficijent = koeficijent;

                q->next = tmp->next;
                tmp->next = q;
            }

            j = j->next;
        }

        i = i->next;
    }

    return 0;
}

int printList(Position P) {
    Position start = P;

    if (P == NULL) {
        printf("Prazan polinom!\n");
        return 0;
    }

    printf("Polinom:\t");

    while (P != NULL) {

        if (P != start && P->koeficijent > 0) {
            printf("+");
        }

        printf("%dx^(%d)", P->koeficijent, P->eksponent);

        P = P->next;
    }

    printf("\n");

    return 0;
}

int freePolynom(Position P) {
    Position temp = NULL;

    while (P->next != NULL) {
        temp = P->next;
        P->next = temp->next;
        free(temp);
    }

    return 0;
}
