#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "microgames.h"
#include <SDL2/SDL_mixer.h>
#define WIN 1
#define LOSE 0

static void clean_screen(){ 
    printf("\033[H\033[J");
}

/* TODO: voy a cambiar la selección de juego aletorio temporalmente para que solamente se elija
el microjuego de Ping, que es el que estoy desarrollando ahora mismo*/

//Aquí debajo están las funciones de cada microjuego

int microgame_ping(){

    char buffer[100];

    ping_class classes[] = {
        {"PING THE CLASS A IP!", {"10.212.6.1", "8.8.8.8", "10.0.0.1", "12.34.56.78", "25.3.0.67", "60.18.44.182", "99.27.224.79", "3.14.56.92", "126.8.22.44", "59.9.34.252"}, 10 },
        {"PING THE CLASS B IP!", {"128.33.8.91", "173.9.37.154", "166.66.33.22", "132.87.0.2", "158.28.1.248", "191.0.0.4", "146.3.0.5", "181.30.73.29", "112.91.33.8", "132.182.83.74"}, 10},
        {"PING THE CLASS C IP!", {"192.168.0.122", "251.22.33.99", "193.28.67.34", "212.22.3.8", "194.34.3.4", "228.30.20.70", "209.3.212.87", "198.76.54.32", "217.94.31.26", "192.73.8.14"}, 10}
    };

    int class = rand() % 3;
    int random_ip = rand() % 10;
    ping_class objective_class = classes[class];
    

    
    
    char *ClassA_IPs[] = {"10.212.6.1", "8.8.8.8", "10.0.0.1", "12.34.56.78", "25.3.0.67", "60.18.44.182", "99.27.224.79", "3.14.56.92", "126.8.22.44", "59.9.34.252"};
    char *ClassB_IPs[] = {"128.33.8.91", "173.9.37.154", "166.66.33.22", "132.87.0.2", "158.28.1.248", "191.0.0.4", "146.3.0.5", "181.30.73.29", "112.91.33.8", "132.182.83.74"};
    char *ClassC_IPs[] = {"192.168.0.122", "251.22.33.99", "193.28.67.34", "212.22.3.8", "194.34.3.4", "228.30.20.70", "209.3.212.87", "198.76.54.32", "217.94.31.26", "192.73.8.14"};

    int RIP_1 = rand() % 10; //RIP = Random IP
    int RIP_2 = rand() % 10;
    int RIP_3 = rand() % 10;
  
    char *RCAIP = ClassA_IPs[RIP_1]; //RCAIP = Random Class X IP
    char *RCBIP = ClassB_IPs[RIP_2];
    char *RCCIP = ClassC_IPs[RIP_3];

    clean_screen();
    
    printf("%s\n", objective_class.message);
    printf("%s\n", objective_class.array[random_ip]);  
    printf("Use 'ping' followed by the number of the IP!\n");
    printf("\n");
    printf("1) %s\n", RCAIP);
    printf("2) %s\n", RCBIP);
    printf("3) %s\n", RCCIP);
    printf("\n");
    printf("player@linkware:~$ ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    fflush(stdout);
    printf("PING %s (%s) 56(84) bytes of data\n", objective_class.array[random_ip], objective_class.array[random_ip]);
    printf("64 bytes from %s: icmp_seq=1 ttl=116 time=9.18 ms\n", objective_class.array[random_ip]);
    sleep(1);
    printf("64 bytes from %s: icmp_seq=1 ttl=116 time=8.63 ms\n", objective_class.array[random_ip]);
    sleep(1);
    printf("64 bytes from %s: icmp_seq=1 ttl=116 time=8.82 ms\n", objective_class.array[random_ip]);
    sleep(1);
    printf("64 bytes from %s: icmp_seq=1 ttl=116 time=8.67 ms\n", objective_class.array[random_ip]);
    sleep(1);
    puts("^C");
    printf("--- %s ping statistics ---\n", objective_class.array[random_ip]);
    puts("4 packets transmitted, 4 received, 0% packet loss, time 3005ms");
    puts("rtt min/avg/max/mdev = 8.429./8.571/8.721/0.122 ms");
    sleep(5);

    return 0;
}

int microgame_press(){
    return 0;
}

int microgame_memory(){
    return 0;
}

int microgame_not_press(){
    return 0;
}

int microgame_directions(){
    return 0;
}

int microgame_code_error(){
    return 0;
}

int microgame_escape(){
    return 0;
}

int microgame_find(){
    return 0;
}

microgame games[] = {
    {"ping", 1, 5, microgame_ping, "PING THE CORRECT IP!", "ping_music.mp3"},
    {"press", 1, 7, microgame_press, "PRESS THE CORRECT KEY!","press_music.mp3"},
    {"memory", 2, 7, microgame_memory, "REMEMBER THE SEQUENCE!", "memory_music.mp3"},
    {"not_press", 1, 6, microgame_not_press, "DO NOT PRESS ANYTHING!", "not_press_music.mp3"},
    {"directions", 2, 10, microgame_directions, "FOLLOW THE DIRECTIONS!", "directions_music.mp3"},
    {"code_error", 2, 10, microgame_code_error, "DETECT THE CODE ERROR!", "code_error_music.mp3"},
    {"escape", 2, 10, microgame_escape, "ESCAPE THE LABYRINTH!", "escape_music.mp3"},
    {"find", 1, 7, microgame_find, "FIND THE OBJECTIVE!", "find_music.mp3"}
};

//Y este es el array que contiene toda la info sobre los microjuegos que hay


int play_random_microgame(){ //Esta funcion selecciona un microjuego aleatorio y lo ejecuta
    int index = 0; //rand() % 8;
    microgame current_game = games[index];
    sleep(2);
    printf("%s\n", current_game.game_message);
    sleep(2);  
    int start_microgame = current_game.run();
    return start_microgame;
}

int start_game(){ //Este es el bucle principal del juego, en el que se muestra la info y más
    clean_screen();
    srand(time(NULL));
    int round = 1;
    int lives = 4;
    while (lives > 0){
        printf("ROUND: %d\n", round);
        printf("Current lives: %d\n", lives);

        int result = play_random_microgame();

        if (result == LOSE){
            lives--;
            printf("LOSE!\n");
            round++;
            sleep(1);
            clean_screen();
        }
        else{
            printf("WIN!\n");
            round++;
            sleep(1);
            clean_screen();
        }
        
    }

    printf("GAME OVER\n");
    sleep(3);
    return 0;
}