#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "microgames.h"
#include <SDL2/SDL_mixer.h>

//Archivo principal del juego

 void clean_screen(){ //Funcion para limpiar la pantalla
    printf("\033[H\033[J");
}

void print_logo(void){
    printf("========================================\n");
    printf("   __   _      __  _      __            \n");
    printf("  / /  (_)__  / /_| | /| / /__ ________ \n");
    printf(" / /__/ / _ \\/  '_/ |/ |/ / _ `/ __/ -_)\n");
    printf("/____/_/_//_/_/\\_\\|__/|__/\\_,_/_/  \\__/\n");
    printf("                                         \n");
    printf("========================================\n");
    
} //Imprimimos el logo del juego

int main(void){ //La funcion principal del programa
    int run = 1;
    char buffer[67];
    char back_to_menu[67];
    clean_screen();
    while(run){ //Aqui tenemos el bucle del menu y sus opciones
        print_logo();
        printf("\n");
        printf("[1] Play \n[2] Credits\n[3] Exit\nYour choice: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        int option = atoi(buffer);
        switch(option){ //Y aqui el switch con los casos posibles y sus resultados
            
            case 1:
                printf("[ INFO ] Loading game, please wait...\n");
                sleep(3);
                start_game();
                clean_screen();
                break;

            case 2:
                clean_screen();
                printf("/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/\n");
                printf("\n");
                printf("LinkWare | A WarioWare-style ASCII Game\n");
                printf("Autor: WindWakerLink\n");
                printf("Programmed entierly in C\n");
                printf("This game currently has 8 microgames in total\n");
                printf("\n");
                printf("/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/\n");
                printf("\n");
                printf("Prees ENTER to go back to the menu...");
                fgets(back_to_menu, sizeof(back_to_menu), stdin);
                clean_screen();
                break;

            case 3:
                printf("[ INFO ] Closing software, please wait...\n");
                sleep(5);
                clean_screen();
                run = 0;
                break;

            default:
                printf("[ ERROR ] Invalid input, please try again\n");
                sleep(1);
                clean_screen();
                break;

        }
    }
    return 0;
}