#include <stdio.h>
#include "alg1.h"
#include "alg2.h"
#include "alg3.h"
#include "alg4.h"
#include "alg5.h"

int main() {
    int choice;

    do {
        printf("\n=== Меню лабораторных работ ===\n");
        printf("1. Лабораторная 1\n");
        printf("2. Лабораторная 2\n");
        printf("3. Лабораторная 3\n");
        printf("4. Лабораторная 4\n");
        printf("5. Лабораторная 5\n");
        printf("0. Выход\n");
        printf("Выберите лабораторную: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: alg1_run(); break;
            case 2: alg2_run(); break;
            case 3: alg3_run(); break;
            case 4: alg4_run(); break;
            case 5: alg5_run(); break;
            case 0: printf("Выход из программы.\n"); break;
            default: printf("Некорректный выбор! Попробуйте снова.\n");
        }
    } while(choice != 0);

    return 0;
}
