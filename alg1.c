#include <stdio.h>
#include <stdlib.h>

#define COLOR_RESET  "\033[0m"
#define COLOR_STRING "\033[91m"  
#define MAXLINE 1024 

int in_comment(const char *line) {  //Проверочка на комментарий с начала строки
    int k = 0; 
    while (line[k] == ' ' || line[k] == '\t'){
        k++;
    }
    if (line[k] == '/' && line[k+1] == '/') {
        return 1;   
    }   
    return 0;
}


void podsvetka(const char *line, int *mnogostroch) {
    if (in_comment(line)) {
        printf("%s", line);
        return;
    }

    int in_string = 0; 
    int i = 0;
    
    while (line[i] != '\0'){
        if (*mnogostroch) { //Проверка на конец многострочки, если мы уже в нем
            if (line[i] == '*'  && line[i+1] == '/') {
                putchar(line[i]);       
                putchar(line[i+1]); 
                *mnogostroch = 0;
                i += 2;
                continue;
            } else {
                putchar(line[i]);
                i++;
                continue;
            }
        }
        
        if (line[i] == '/' && line[i+1] == '*') { //Проверка на начало многострочки, если еще не в нем
            putchar(line[i]);       
            putchar(line[i+1]); 
            *mnogostroch = 1;
            i += 2;
            continue;
        }

        if (line[i] == '/' && line [i+1] == '/') { //Проверка на комментарий внутри строки
            printf("%s", line + i);
            i += 2;
            break;
        }

        if (line[i] == '"' && (i == 0 || line[i - 1] != '\\')) {
            if (!in_string){
                printf(COLOR_STRING);
                in_string = 1;
                putchar(line[i]);
                i++;
                continue;
            } else {
                putchar(line[i]);
                printf(COLOR_RESET);
                in_string = 0;
                i++;
                continue;   
            }
        }
        
        putchar(line[i]);
        i++;

    }
    
    printf(COLOR_RESET);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s kglab1.c\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Не удалось открыть файл");
        return 1;
    }

    char popo[MAXLINE];
    int mnogostroch = 0;
    while (fgets(popo, sizeof(popo), file)) {
        podsvetka(popo, &mnogostroch);
    }

    fclose(file);
    return 0;
}
