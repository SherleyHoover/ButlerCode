#include <stdlib.h>
#include <stdio.h>
int main() {
    printf("---------------Welcome to the Butler Code!---------------\n");
    int a;
    char c = 'y';
    while (c == 'y') {
        printf("To encode, press 1. \nTo decode, press 2.\n");
        scanf("%d", &a);
        while (a != 1 && a != 2) {
            printf("Please enter a number between 1 and 2: \n");
            main();
        }
        if ( a == 1) {
            system("encode.exe");
        }
        else {
            system("decode.exe");
        }
        printf("Continue? (y/n)");
        scanf(" %c", &c);
        while (c != 'n' && c != 'y') {
            printf("Invalid input, try again.\n");
            scanf(" %c", &c);
        }

    }
}
// Created by dong on 2026/2/13.
//