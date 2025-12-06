#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1000

void vstavka(int arr[], int n){
    for (int i = 1; i < n; i++){
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bistro(int arr[], int left, int right) {
    if (left < right) {
        int pivot = arr[right];
        int i = left - 1;
        for (int j = left; j < right; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp;

        int pi = i + 1;
        bistro(arr, left, pi - 1);
        bistro(arr, pi + 1, right);
    }
}
void printarr(int arr[], int n){
    for (int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void vvodarr(int arr[], int n){
    for (int i = 0; i < n; i++){
        printf("Введите %d элемент: ", i);
        scanf("%d", &arr[i]);
    }
}

void randarr(int arr[], int n){
    for (int i = 0; i < n; i++){
        arr[i] = rand() % 1000;
    }
}

int filearr(int arr[], int n, const char *name){
    FILE *file = fopen(name, "r");
    if (!file){
        printf("Ошибка открытия файла\n");
        return 0;
    }

    for (int i = 0; i < n; i++){
        if (fscanf(file, "%d", &arr[i]) != 1){
            printf("Ошибка чтения файла\n");
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}

int main(){
    srand(time(NULL));
    int arr[MAX_SIZE];
    int n, method, arrmethod;
    char filename[100];

    printf("Введите размер массива\n");
    scanf("%d", &n);
    if (n > MAX_SIZE){
        printf("Слишком большой размер массива\n");
        return 1;
    }

    printf("Выберите как задать массив:\n1. Ввод с клавиатуры\n2. Генерация случайных чисел\n3. Чтение из файлы\n");
    scanf("%d", &arrmethod);

    switch (arrmethod){
    case 1:
        vvodarr(arr, n);
        break;
    case 2:
        randarr(arr, n);
        break;
    case 3:
        printf("Введите имя файлы: ");
        scanf("%s", filename);
        if (!filearr(arr, n, filename)) return 1;
        break;
    default:
        printf("Выбран неверный способ задания массивая\n");
        return 1;
    }

    printf("Выберите метод сортировки\n1. Сортировка вставками\n2. Быстрая сортировка\n");
    scanf("%d", &method);

    printf("Массив до сортировки:");
    printarr(arr, n);

    if (method == 1){
        vstavka(arr, n);
    } else if (method == 2){
        bistro(arr, 0, n-1);
    } else{
        printf("Выбран неверый метод сортировки");
    }

    printf("Массив после сортировки\n");
    printarr(arr, n);
}