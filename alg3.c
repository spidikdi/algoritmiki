#include <stdio.h>
#include <stdlib.h>

typedef struct Elem{
    int value;
    struct Elem* nextelem;
} Elem;

Elem* creelem (int value){
    Elem* newelem = (Elem*)malloc(sizeof(Elem));
    if (!newelem){
        printf("Не удалось \n");
        exit(1);
    }
    newelem->value = value;
    newelem->nextelem = NULL;
    return newelem;
}

void appelem (Elem** firstelem, int value) {
    Elem* newelem = creelem (value);

    if (*firstelem == NULL) {
        *firstelem = newelem;
        return;
    }

    Elem* crrelem = *firstelem;
    while (crrelem->nextelem != NULL){
        crrelem = crrelem->nextelem;
    }

    crrelem->nextelem = newelem;
}

void prielem (Elem* firstelem){
    Elem* crrelem = firstelem;
    printf("Список: ");
    while (crrelem != NULL){
        printf("%d ", crrelem->value);
        crrelem = crrelem->nextelem;
    }
    printf("\n");
}

void proverka (Elem* firstelem){
    if (firstelem == NULL || firstelem->nextelem == NULL) {
        printf("Список слишком короткий\n");
        return;
    }
    
    int ubiv = 1, vozr = 1;
    Elem* crrelem = firstelem;

    while (crrelem->nextelem != NULL){
        if (crrelem->value < crrelem->nextelem->value) ubiv = 0;
        else if (crrelem->value > crrelem->nextelem->value) vozr = 0;
        crrelem = crrelem->nextelem;
    }
    if (vozr) printf("Список упорядочен по возрастанию.\n");
    else if (ubiv) printf("Список упорядочен по убыванию.\n");
    else printf("Список неупорядочен.\n");
}
    
void deleteelems (Elem** firstelem){
    Elem* crrelem = *firstelem;
    Elem* nextelem;

    while (crrelem != NULL) {
        nextelem = crrelem->nextelem;
        free(crrelem);
        crrelem = nextelem;
    }
    *firstelem = NULL;
    printf("Cписок удален");
}

int main(){
    Elem* firstelem = NULL;
    int n, value;

    printf("Введите количество элементов списка: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++){
        printf("Введите элемент %d: ", i + 1);
        scanf("%d", &value);
        appelem(&firstelem, value);
    }

    prielem(firstelem);
    proverka(firstelem);
    deleteelems(&firstelem);

}