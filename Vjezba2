#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person* Position;

typedef struct Person {
    char name[20];
    char surname[20];
    int BirthYear;
    Position next;
} Person;

Position CreatePerson() {
    Position newPerson = malloc(sizeof(Person));

    if (newPerson == NULL) {
        printf("Dinamička alokacija neuspjela!\n");
        return NULL;
    }

    printf("Unesite ime, prezime i godinu rođenja: ");

    if (scanf("%19s %19s %d",
        newPerson->name,
        newPerson->surname,
        &newPerson->BirthYear) != 3) {
        printf("Format unosa pogrešan.\n");
        free(newPerson);
        return NULL;
    }

    newPerson->next = NULL;
    return newPerson;
}

int insertToFront(Position head) {
    Position newPerson = CreatePerson();

    if (newPerson == NULL)
        return 1;

    newPerson->next = head->next;
    head->next = newPerson;

    return 0;
}

void printAll(Position head) {
    Position current = head->next;

    if (current == NULL) {
        printf("Lista je prazna.\n");
        return;
    }

    while (current != NULL) {
        printf("%s %s %d\n",
            current->name,
            current->surname,
            current->BirthYear);

        current = current->next;
    }
}

int insertToEnd(Position head) {
    Position current = head;

    while (current->next != NULL)
        current = current->next;

    Position newPerson = CreatePerson();

    if (newPerson == NULL)
        return 1;

    current->next = newPerson;

    return 0;
}

int findsurname(Position head) {
    Position current = head->next;
    char surname[20];

    printf("Unesite prezime koje zelite naci: ");

    if (scanf("%19s", surname) != 1)
        return 1;

    while (current != NULL) {
        if (strcmp(current->surname, surname) == 0) {
            printf("Tražena osoba je: %s %s %d\n",
                current->name,
                current->surname,
                current->BirthYear);

            return 0;
        }

        current = current->next;
    }

    printf("Prezime nije na listi.\n");
    return 1;
}

int deletePerson(Position head) {
    Position previous = head;
    Position current = head->next;
    char surname[20];

    printf("Unesite prezime osobe koju zelite izbrisati: ");

    if (scanf("%19s", surname) != 1)
        return 1;

    while (current != NULL) {
        if (strcmp(current->surname, surname) == 0) {
            previous->next = current->next;
            free(current);

            printf("Osoba je izbrisana.\n");
            return 0;
        }

        previous = current;
        current = current->next;
    }

    printf("Osoba s tim prezimenom nije pronadena.\n");
    return 1;
}

void DeleteList(Position head) {
    Position current = head->next;
    Position temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    head->next = NULL;
}

int main() {
    int choice = 1;

    Position head = malloc(sizeof(Person));

    if (head == NULL) {
        printf("Alokacija memorije nije uspjela.\n");
        return 1;
    }

    head->next = NULL;

    while (choice != 0) {
        printf("\nUnesite broj za opciju koju zelite:\n");
        printf("1: Dodaj na pocetak\n");
        printf("2: Dodaj na kraj\n");
        printf("3: Ispisi listu\n");
        printf("4: Pronadi osobu po prezimenu\n");
        printf("5: Izbrisi osobu po prezimenu\n");
        printf("6: Izbrisi cijelu listu\n");
        printf("0: Prekini program\n");
        printf("Izbor: ");

        if (scanf("%d", &choice) != 1) {
            printf("Krivi unos.\n");
            DeleteList(head);
            free(head);
            return 1;
        }

        switch (choice) {
        case 1:
            if (insertToFront(head) != 0)
                printf("Greska prilikom dodavanja.\n");
            break;

        case 2:
            if (insertToEnd(head) != 0)
                printf("Greska prilikom dodavanja.\n");
            break;

        case 3:
            printAll(head);
            break;

        case 4:
            findsurname(head);
            break;

        case 5:
            deletePerson(head);
            break;

        case 6:
            DeleteList(head);
            printf("Lista izbrisana.\n");
            break;

        case 0:
            printf("Kraj programa.\n");
            break;

        default:
            printf("Krivi unos. Ponovite!\n");
            break;
        }
    }

    DeleteList(head);
    free(head);

    return 0;
}
