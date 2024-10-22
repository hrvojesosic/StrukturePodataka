#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _person* position;
typedef struct _person {
    //data
    char fname[32];
    char lname[32];
    int birth_year;
    //link
    position next;
}person;

position create_person(position head, char* fname, char* lname, int birth_year);
int prepend_list(position head, char* fname, char* lname, int brith_year);
int append_list(position head, char* fname, char* lname, int birth_year);
int insert_after(position previous, position to_insert);
int print_list(position first);
position find_by_lname(position first, char* lname);
position find_last(position head);
position findPrevious(position first, position target);
position delete_person(position head, position target);

int main() {
    char fname1[32], fname2[32];
    char lname1[32], lname2[32];
    char lname3[32];
    int bday1, bday2;

    person head = { .fname = "",.lname = "",.next = NULL };

    printf("Dodajte element na pocetak liste: \n");
    scanf("%s %s %d", fname1, lname1, &bday1);

    prepend_list(&head, fname1, lname1, bday1);

    printf("Lista sad izgleda ovako: \n");
    print_list(head.next);


    printf("Dodajte element na kraj liste: \n");
    scanf("%s %s %d", fname2, lname2, &bday2);
    append_list(&head, fname2, lname2, bday2);


    printf("Lista nakon dodavanja na kraj izgleda ovako: \n");
    print_list(head.next);

    printf("Potrazite neko prezime iz liste: \n");
    scanf("%s", lname3);
    position target = find_by_lname(head.next, lname3);
    if (target != NULL) {
        printf("Pronaden je element iz liste %s %s %d", target->fname, target->lname, target->birth_year);
    }






    return 0;
}
position create_person(position head, char* fname, char* lname, int birth_year) {
    position new_person = NULL;

    new_person = (person*)malloc(sizeof(person));
    if (new_person == NULL) {
        printf("ERror allocating memory.");
        return NULL;
    }
    strcpy(new_person->fname, fname);
    strcpy(new_person->lname, lname);
    new_person->birth_year = birth_year;
    new_person->next = NULL;
    return new_person;

}
int prepend_list(position head, char* fname, char* lname, int birth_year) {
    position new_person = NULL, last = NULL;
    new_person = create_person(head, fname, lname, birth_year);
    if (new_person == NULL) {
        return -1;

    }

    head->next = new_person;

    return EXIT_SUCCESS;
}
int append_list(position head, char* fname, char* lname, int birth_year) {
    position new_person = NULL;
    position last_person = NULL;

    new_person = create_person(head, fname, lname, birth_year);
    if (new_person == NULL) {
        return -1;
    }
    if (head->next == NULL) {
        //prazna lista
        head->next = new_person;
    }
    else { //ako nije prazna trazimo zadnjeg i fixamo pointere
        last_person = find_last(head);
        last_person->next = new_person;
    }
    new_person->next = NULL;







    return 0;
}
int print_list(position first) {
    position temp = NULL;
    temp = first;
    while (temp) {
        printf("First name: %s\nLast name: %s\nBirth Year: %d\n", temp->fname, temp->lname, temp->birth_year);
        temp = temp->next;

    }

    return EXIT_SUCCESS;
}
position find_last(position head) {
    if (head == NULL) {
        return NULL; //prazna lista
    }
    position temp = NULL;
    temp = head;

    while (temp->next) {
        temp = temp->next;
    }

    return temp;
}
position find_by_lname(position first, char* lname) {
    position temp = NULL;
    temp = first;
    while (temp) {
        if (strcmp(temp->lname, lname) == 0) {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}
int insert_after(position previous, position to_insert) {
    //nema unosa ako je prijasnji clan NULL ili je clan koji zelimo unit NULL
    if (previous == NULL || to_insert == NULL) {
        return -1;
    }

    to_insert->next = previous->next;
    previous->next = to_insert;
    return 0;
}
position findPrevious(position first, position target) {

    position temp = NULL;
    temp = first;
    if (first == target) {
        printf("Poslali ste prvi element liste.");
        return NULL;
    }
    if (first == NULL) {
        return NULL;
    }
    while (temp->next != NULL && temp->next != target) {

        temp = temp->next;
    }

    return temp;

}
position delete_person(position head, position toDelete) {
    position temp = NULL;
    temp = toDelete;
    position previous = NULL;
    if (head == NULL || toDelete == NULL) {
        return head;
    }
    if (head == toDelete) {
        position new_head = head->next;
        free(head);
        return new_head;
    }

    previous = findPrevious(head, toDelete);
    if (previous == NULL) {
        //toDel not in list?
        return head;
    }
    previous->next = toDelete->next;
    free(toDelete);
    return head;

}