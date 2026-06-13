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
el microjuego de las errores de código

   TODO: recuerda poner comentarios en todo lo que haces para no perderte

   TODO: Ahora mismo estoy con el tercer microjuego (el de los errores de código)
   TODO: Tengo que hacer que el tiempo funcione en todos los microjuegos
   TODO: ANTONIO GORDITA GUAPETONA SIX SEVEEEEEEEN


*/

//debajo están las funciones de cada microjuego

int microgame_ping(){

    char buffer[64];
    int time = 10;

    ping_class classes[] = {
        {"PING THE CLASS A IP!", {"10.212.6.1", "8.8.8.8", "10.0.0.1", "12.34.56.78", "25.3.0.67", "60.18.44.182", "99.27.224.79", "3.14.56.92", "126.8.22.44", "59.9.34.252"}},
        {"PING THE CLASS B IP!", {"128.33.8.91", "173.9.37.154", "166.66.33.22", "132.87.0.2", "158.28.1.248", "191.0.0.4", "146.3.0.5", "181.30.73.29", "174.91.33.8", "132.182.83.74"}},
        {"PING THE CLASS C IP!", {"192.168.0.122", "207.22.33.99", "193.28.67.34", "212.22.3.8", "194.34.3.4", "221.30.20.70", "209.3.212.87", "198.76.54.32", "217.94.31.26", "192.73.8.14"}}
    }; /* Aquí están las clases de IPs de la A a la C con sus IPs, junto 
    con un buffer y el tiempo que tiene el microjuego*/

    int class = rand() % 3;
    int random_ip = rand() % 10;
    int random_distraction_ip = rand() % 10;
    int random_distraction_ip2 = rand() % 10;
    ping_class objective_class = classes[class];
    ping_class distraction_class, distraction_class2;

    //Arriba elegimos una clase e IP random y las IPs de distracción y eso


    if (class == 0){
        distraction_class  = classes[1];
        distraction_class2 = classes[2];
    }
    else if (class == 1){
        distraction_class = classes[2];
        distraction_class2 = classes[0];
    }
    else if (class == 2){
        distraction_class = classes[0];
        distraction_class2 = classes[1];
    }

    /* Arriba declaramos que si la IP es de un tipo, las 2 IPs restantes tienen que ser de otro tipo*/
    
    
    char *ip_list[] = {objective_class.array[random_ip], distraction_class.array[random_distraction_ip], distraction_class2.array[random_distraction_ip2]};

    for (int i = 0, j = 0; i <= 2; i++){
        j = rand() % 3;
        char* temp = ip_list[i];        
        ip_list[i] = ip_list[j];
        ip_list[j] = temp;
        
    }

    /* Arria está la lista con las 3 IPs del juego y el bucle lo que hace es mezclar
    las IPs de manera que salgan en un orden aleatorio*/

    clean_screen();
    do {
        printf("TIME: %d\n", time);
        printf("%s\n", objective_class.message);
        printf("Use 'ping' followed by the number of the IP!\n");
        printf("Example: ping 8\n");
        printf("\n");
        printf("1) %s\n", ip_list[0]);
        printf("2) %s\n", ip_list[1]);
        printf("3) %s\n", ip_list[2]);
        printf("\n");
        printf("player@linkware:~$ ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        fflush(stdout);

        /* Este bloque de arriba es el corazón del microjuego: se imprime el mensaje correspondiente a la 
        IP que se busca, luego el consejo de como hacer el ping bien, se imprimen las IPs de la lista
        y se espera la respuesta del jugador*/

        if ((strcmp(buffer, "ping 1") == 0 && strcmp(ip_list[0], objective_class.array[random_ip]) == 0) ||
        (strcmp(buffer, "ping 2") == 0 && strcmp(ip_list[1], objective_class.array[random_ip]) == 0) ||
        (strcmp(buffer, "ping 3") == 0 && strcmp(ip_list[2], objective_class.array[random_ip]) == 0)){


        printf("PING %s (%s) 56(84) bytes of data.\n", objective_class.array[random_ip], objective_class.array[random_ip]);
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
        printf("player@linkware:~$ \n");
        sleep(3);

        return 1;
        }



        else if (strcmp(buffer, "ping 1") == 0 && strcmp(ip_list[0], objective_class.array[random_ip]) != 0){
            printf("PING %s (%s) 56(84) bytes of data.\n", ip_list[0], ip_list[0]);
            sleep(4);
            puts("^C");
            printf("--- %s ping statistics ---\n", ip_list[0]);
            puts("4 packets transmitted, 0 received, 100% packet loss, time 4250ms");
            printf("\n");
            printf("player@linkware:~$ \n");
            sleep(3);
            return 0;
        }

        else if (strcmp(buffer, "ping 2") == 0 && strcmp(ip_list[1], objective_class.array[random_ip]) != 0){
            printf("PING %s (%s) 56(84) bytes of data.\n", ip_list[1], ip_list[1]);
            sleep(4);
            puts("^C");
            printf("--- %s ping statistics ---\n", ip_list[1]);
            puts("4 packets transmitted, 0 received, 100% packet loss, time 4250ms");
            printf("\n");
            printf("player@linkware:~$ \n");
            sleep(3);
            return 0;
        }

        else if (strcmp(buffer, "ping 3") == 0 && strcmp(ip_list[2], objective_class.array[random_ip]) != 0){
            printf("PING %s (%s) 56(84) bytes of data.\n", ip_list[2], ip_list[2]);
            sleep(4);
            puts("^C");
            printf("--- %s ping statistics ---\n", ip_list[2]);
            puts("4 packets transmitted, 0 received, 100% packet loss, time 4250ms");
            printf("\n");
            printf("player@linkware:~$ \n");
            sleep(3);
            return 0;
        }

        else {
            printf("bash: $%s: command not found\n", buffer);
            printf("player@linkware-$ \n");
            sleep(3);
            return 0;
        }

        /* Voy a explicar los IFs de arriba: el primero comprueba si alguno de los pings (ping 1, ping 2...), coincide
        con la IP que se busca y si es así se hace un ping como si fuera un ping de verdad. Los 3 bucles siguientes comprueban si cada ping
        no coincide con la IP que se busca, y el último es cuando se pone otra cosa que no es "ping 1-2-3 "*/

    } while (time--);
    
    
}


int microgame_instructions(){

    char buffer[64];
    int time = 10;

    
    instruction_class instructions[] = {
        {"You are in: /home/player", "Go to /home/player/Documents and list the content", "cd Documents && ls" },
        {"You are in: /etc", "Find the line contaning \"root\" in the \"passwd\" file", "grep root passwd"},
        {"You are in: /home/player/projects", "Go to /home/player/projects/https-server and execute the ELF \"main\"", "cd https-server && ./main"},
        {"You are in: /home/player", "Create a file name \"notes.txt\" containing \"Hello World!\"", "touch notes.txt && echo \"Hello World!\" < notes.txt"},
        {"You are in: /opt/tools", "Make \"installer.sh\" executable", "chmod +x installer.sh"},
        {"You are in: /etc", "Search for \"localhost\" in all files", "grep -r \"localhost\" ."},
        {"You are in: /var/log", "Count how many lines contain \"error\" in syslog", "grep -i error syslog | wc -l"},
        {"You are in: /", "Find running processes related to nginx", "ps aux | grep nginx"},
        {"You are in: /home/player/scrpts", "Make \"deploy.sh\" executable, then execute it and save output to \"log.txt\"", "chmod +x deploy.sh && ./deploy.sh > log.txt"},
        {"You are in: /etc", "List files containing \"conf\" and save output to \"result.txt\"", "ls | grep conf > result.txt"}

    };

    int rand_instruction = rand() % 10;

    instruction_class objective_instruction = instructions[rand_instruction];

    clean_screen();
    printf("TIME: %d\n", time);
    printf("%s\n", objective_instruction.current_directory);
    printf("OBJECTIVE: %s\n", objective_instruction.instruction);
    puts("NOTE: All instructions must be done using ONLY ONE command line");
    printf("\n");
    printf("player@linkware:~$ ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    fflush(stdout);
    if (strcmp(buffer, objective_instruction.answer) == 0){

        printf("\nCORRECT COMMAND!\n");
        sleep(2);
        return 1;
    } 
    
    else{
        printf("\nWRONG COMMAND!\n");
        sleep(2);
        return 0;
    }
   


    
}

int microgame_code_error(){

    char buffer[64];
    int time = 10;
    

    code_error_class code_errors[] {

        {"1 | int main() {\n2 |   int x = 5\n3 |   printf(\"%d\n\", x);\n4 | }", "2"}  

    }

    int rand_code_error = rand() % 1;

    clean_screen();
    puts("Find the error!");





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


int microgame_escape(){
    return 0;
}

int microgame_find(){
    return 0;
}

microgame games[] = {
    {"ping", microgame_ping, "PING THE CORRECT IP!", "ping_music.mp3"},
    {"instructions", microgame_instructions, "FOLLOW THE INSTRUCTIONS!", "instructions_music.mp3"},
    {"code_error", microgame_code_error, "DETECT THE CODE ERROR!", "code_error_music.mp3"},   
    {"press", microgame_press, "PRESS THE CORRECT KEY!","press_music.mp3"},
    {"memory", microgame_memory, "REMEMBER THE SEQUENCE!", "memory_music.mp3"},
    {"not_press", microgame_not_press, "DO NOT PRESS ANYTHING!", "not_press_music.mp3"},
    {"escape", microgame_escape, "ESCAPE THE LABYRINTH!", "escape_music.mp3"},
    {"find", microgame_find, "FIND THE OBJECTIVE!", "find_music.mp3"}
};

//Este es el array que contiene toda la info sobre los microjuegos que hay


int play_random_microgame(){ //Esta funcion selecciona un microjuego aleatorio y lo ejecuta
    int index = rand() % 2; //rand() % 8; -> Este hay que descomentarlo cuando lo tenga los 8 microjuegos completados
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
            printf("FAILURE!\n");
            round++;
            sleep(2);
            clean_screen();
        }
        else{
            printf("SUCCESS!\n");
            round++;
            sleep(2);
            clean_screen();
        }
        
    }

    printf("GAME OVER\n");
    sleep(3);
    return 0; 
}