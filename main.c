#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "microgames.h"
#include <SDL2/SDL_mixer.h>

 void clean_screen(){ //Funcion para limpiar la pantalla
    printf("\033[H\033[J");
}


 void loading_bar(char custom_message[], int delay){
    char bar[] = "---------------------";
    int number = 21;
    printf("%s", custom_message);
    fflush(stdout);
    usleep(800000);
    for (int i = 0; i < number; i++){
        fflush(stdout);
        bar[i] = '#';
        if (bar[i] != 0) bar[i - 1]  = '#';
        int percentaje = i * 5;
        printf("\r%s  [%s] {%d%}",custom_message, bar, percentaje);
        usleep(delay);
        fflush(stdout);
    };
}


void print_logo(void){
    puts("=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=");
    puts("");
    puts(" ▄        ▀           █     ▄     ▄                     ");
    puts(" █      ▄▄▄    ▄ ▄▄   █   ▄ █  █  █  ▄▄▄    ▄ ▄▄   ▄▄▄  ");
    puts(" █        █    █▀  █  █ ▄▀  ▀ █▀█ █ ▀   █   █▀  ▀ █▀  █ ");
    puts(" █        █    █   █  █▀█    ██ ██▀ ▄▀▀▀█   █     █▀▀▀▀ ");
    puts(" █▄▄▄▄▄ ▄▄█▄▄  █   █  █  ▀▄  █   █  ▀▄▄▀█   █     ▀█▄▄▀ ");
    puts("");
    puts(" ▙▗▌▗                           ▗▀▖                                          ▐ ");
    puts(" ▌▘▌▄ ▞▀▖▙▀▖▞▀▖▞▀▌▝▀▖▛▚▀▖▞▀▖▞▀▘ ▐  ▞▀▖▙▀▖ ▛▀▖▙▀▖▞▀▖▞▀▌▙▀▖▝▀▖▛▚▀▖▛▚▀▖▞▀▖▙▀▖▞▀▘▐ ");
    puts(" ▌ ▌▐ ▌ ▖▌  ▌ ▌▚▄▌▞▀▌▌▐ ▌▛▀ ▝▀▖ ▜▀ ▌ ▌▌   ▙▄▘▌  ▌ ▌▚▄▌▌  ▞▀▌▌▐ ▌▌▐ ▌▛▀ ▌  ▝▀▖▝ ");
    puts(" ▘ ▘▀▘▝▀ ▘  ▝▀ ▗▄▘▝▀▘▘▝ ▘▝▀▘▀▀  ▐  ▝▀ ▘   ▌  ▘  ▝▀ ▗▄▘▘  ▝▀▘▘▝ ▘▘▝ ▘▝▀▘▘  ▀▀ ▝ ");
    puts("");
    puts("=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=_=");
    

} //Imprimimos el logo del juego

int main(void){ //La funcion principal del programa
    int run = 1;
    char buffer[67];
    char back_to_menu[67];
    clean_screen();
    while(run){ //Aqui tenemos el bucle del menu y sus opciones
        print_logo();
        puts("");
        printf("[1] Play \n[2] Credits\n[3] Exit\n\nYour choice: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        int option = atoi(buffer);
        switch(option){ //Y aqui el switch con los casos posibles y sus resultados
            
            case 1:
                puts("");
                loading_bar("[  INFO  ] Loading game, please wait...", 300000);
                puts("");
                sleep(1);
                puts("[  OK  ] Game sucessfully loaded!");
                sleep(2);
                start_game();
                clean_screen();
                break;

            case 2:
                clean_screen();
                fflush(stdout);
                puts("/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/");
                puts("");
                puts("- LinkWare | A WarioWare-style ASCII Game");
                puts("- Author: WindWakerLink");
                puts("- Game programmed entirely in C");
                puts("- Total microgames: 8");
                puts("- Current version: 1.0");
                puts("- Version 2.0 comming soon...");
                puts("");
                puts("/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/");
                puts("");
                printf("Prees ENTER to go back to the menu... ");
                fgets(back_to_menu, sizeof(back_to_menu), stdin);
                fflush(stdout);
                clean_screen();
                break;

            case 3:
                loading_bar("[  INFO  ] Closing software, please wait...", 200000);
                usleep(800000);
                clean_screen();
                run = 0;
                break;

            default:
                puts("[  ERROR  ] Invalid input, please try again");
                sleep(1);
                clean_screen();
                break;

        }
    }
    return 0;
}
