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

   NOTA: ya he terminado de hacer 4 de los 8 microjuegos (VENGA, ME QUEDA POCO :) ) 
   
   


*/

//debajo están las funciones de cada microjuego

int microgame_ping(){

    char buffer[64];
    int start_time = 10;
    int start = time(NULL);

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
    
    printf("TIME: %d\n", start_time);
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
    int time_left = time(NULL) - start;

    /* Este bloque de arriba es la base del microjuego: se imprime el mensaje correspondiente a la 
    IP que se busca, luego el consejo de como hacer el ping bien, se imprimen las IPs de la lista
    y se espera la respuesta del jugador*/

    if (time_left > start_time){
        puts("TIME'S OUT!");
        sleep(2);
        return 0;
    }

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

    
    
}

int microgame_instructions(){

    char buffer[64];
    int start_time = 15;
    int start = time(NULL);

    instruction_class instructions[] = {
        {"You are in: /home/player", "Go to /home/player/Documents and list the content", "cd Documents && ls" },
        {"You are in: /etc", "Find the line contaning \"root\" in the \"passwd\" file", "grep root passwd"},
        {"You are in: /home/player/projects", "Go to /home/player/projects/https-server and execute the ELF \"main\"", "cd https-server && ./main"},
        {"You are in: /home/player", "Create a file name \"notes.txt\" containing \"Hello World!\"", "touch notes.txt && echo \"Hello World!\" < notes.txt"},
        {"You are in: /opt/tools", "Make \"installer.sh\" executable", "chmod +x installer.sh"},
        {"You are in: /etc", "Search for \"localhost\" in all files", "grep -r localhost ."},
        {"You are in: /var/log", "Count how many lines contain \"error\" in syslog", "grep -i error syslog | wc -l"},
        {"You are in: /", "Find running processes related to nginx", "ps aux | grep nginx"},
        {"You are in: /home/player/scrpts", "Make \"deploy.sh\" executable, then execute it and save output to \"log.txt\"", "chmod +x deploy.sh && ./deploy.sh > log.txt"},
        {"You are in: /etc", "List files containing \"conf\" and save output to \"result.txt\"", "ls | grep conf > result.txt"}

    };

    /*Arriba, al igual que el microjuego de Ping, tenemos un buffer para input, el tiempo y el array de structs con cada una de las instrucciones y
    la respuesta correcta a esa instrucción*/

    int rand_instruction = rand() % 10;

    instruction_class target_instruction = instructions[rand_instruction];

    clean_screen();
    printf("TIME: %d\n", start_time);
    printf("%s\n", target_instruction.current_directory);
    printf("OBJECTIVE: %s\n", target_instruction.instruction);
    puts("NOTE: All instructions must be done using ONLY ONE command line");
    printf("\n");
    printf("player@linkware:~$ ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    fflush(stdout);
    int time_left = time(NULL) - start;

    if (time_left > start_time){
        puts("TIME'S OUT!");
        sleep(2);
        return 0;
    }

    if (strcmp(buffer, target_instruction.answer) == 0){

        puts("CORRECT COMMAND!");
        sleep(2);
        return 1;
    } 
    
    puts("WRONG COMMAND!");
    sleep(2);
    return 0;
    
    /*Esto de arriba ya se ha visto antes: se imprime el tiempo, el directorio en el que supuestamente estás,
    la instrucción a seguir, una nota para indicar que todos los comandos hay que hacerlos en una sola línea
    y ya se espera la respuesta del jugador y se comprueba si la respuesta es o no correcta*/    
}

int microgame_code_error(){

    char buffer[64];
    int start_time = 10;
    int start = time(NULL);
    

    code_error_class code_errors[] = {

        {"1 | int main(){\n2 |     int x = 5\n3 |     printf(\"%d\\n\", x);\n4 | }", "line 2"},
        {"5 | int main(){\n6 |     year = 2026;\n7 |     printf(\"%d\\n\", year);\n8 | }", "line 6"},
        {"1 | int x = 5;\n2 |\n3 | if (x = 5){\n4 |     printf(\"Five\\n\");\n5 | }", "line 3"},
        {" 9 | int time = 12;\n10 | char buffer[64];\n11 | fgets(buffer, sizeof(buffer), stdin);\n12 | if (buffer == \"hello\"){\n13 |     printf(\"Hi there!\\n\");", "line 12"},
        {"1 | int numbers[10];\n2 |\n3 | numbers[10] = 42;\n4 |", "line 3"},
        {"23 | int main(){\n24 |     char username[8];\n25 |\n26 |     strcpy(username, \"SuperAdmin\");\n27 |\n28 |     printf(\"%s\\n\", username);\n29 |\n30 | return 0;\n31 | }", "line 26"},
        {"1 | int main(){\n2 |     char *name = NULL;\n3 |\n4 |     puts(\"Loading...\");\n5 |     sleep(2);\n6 |\n7 |     printf(\"%c\\n\", name);\n8 |     return 0;\n9 | }", "line 7"} 

    };

    // Bueno, aquí no tengo que explicar nada porque es lo mismo qeu los otros 2 microjuegos
    int rand_code_error = rand() % 7;

    code_error_class target_code_error = code_errors[rand_code_error];

    clean_screen();
    printf("TIME: %d\n", start_time);
    puts("FIND THE ERROR!");
    puts("Write \"line\" followed by the line number where the error is!");
    puts("Example: line 33");
    printf("\n");
    printf("%s", target_code_error.code_lines);
    printf("\n");
    printf("\n");
    printf("player@linkware:~$ ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    fflush(stdout);
    int time_left = time(NULL) - start;
    

    if (time_left > start_time){
        puts("TIME'S OUT!");
        sleep(2);
        return 0;
    }

    if (strcmp(buffer, target_code_error.line_error) == 0){
        
        printf("YOU FOUND THE ERROR!\n");
        sleep(2);
        return 1;
    }

    puts("YOU DIDN'T FOUND THE ERROR");
    sleep(2);
    return 0;

    //Y esta parte del código es prácticamente igual a los otros microjuegos 

}

int microgame_find(){
    char buffer[64];
    int start_time = 10;
    int start = time(NULL);

    find_class find_cases[] = {
        {"Find the oldest edited file in the group!", "-rw-r--r-- 1 player player  470 May 13 19:00 README.md\n-rw-r--r-- 1 player player 1534 May 13 18:45 text.txt", "text.txt"},
        {"Find the shell script!", "arch-linux.iso calculator.py game.cpp hello.txt shell.sh", "shell.sh"},
        {"Find the private IP!", "1) 8.8.8.8\n2) 151.101.1.67\n3) 192.168.1.134\n4) 89.234.21.7", "3"},
        {"Find the loopback IP!", "1) 191.34.233.40\n2) 10.0.0.1\n3) 172.182.99.3\n4) 127.0.0.1", "4"},
        {"Find the hidden file!", "notes.txt config.cfg .bashrc picture.jpg", ".bashrc"},
        {"Find the suspicious file!", "ball.png debian-13.iso fantasy-book.pdf keylogger.py roblox-script.lua", "keylogger.py"}


    };

    int random_target = rand() % 6;
    find_class find_target = find_cases[random_target];

    clean_screen();
    printf("TIME: %d\n", start_time);
    printf("OBJECTIVE: %s\n", find_target.message);
    printf("\n");
    printf("NOTE: This is what you should write depending of the target:\n-File/dir: write the file/dir name\n-IP: write the number before the IP address\n");
    printf("\n");
    printf("%s\n", find_target.possible_targets);
    printf("\n");
    printf("\n");
    printf("player@linkware:~$ ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    fflush(stdout);
    int time_left = time(NULL) - start;

    if (time_left > start_time){
        puts("TIME'S OUT!");
        sleep(2);
        return 0;
    }

    if (strcmp(buffer, find_target.target) == 0){
        puts("YOU FOUND THE TARGET!");
        sleep(1);
        return 1;
    }

    puts("YOU DIDN'T FOUND THE TARGET!");
    sleep(1);
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



microgame games[] = {
    {"ping", microgame_ping, "PING THE CORRECT IP!"},
    {"instructions", microgame_instructions, "FOLLOW THE INSTRUCTIONS!"},
    {"code_error", microgame_code_error, "DETECT THE CODE ERROR!"},   
    {"find", microgame_find, "FIND THE OBJECTIVE!"},
    {"press", microgame_press, "PRESS THE CORRECT KEY!"},
    {"memory", microgame_memory, "REMEMBER THE SEQUENCE!"},
    {"not_press", microgame_not_press, "DO NOT PRESS ANYTHING!"},
    {"escape", microgame_escape, "ESCAPE THE LABYRINTH!"},
  
};

//Este es el array que contiene toda la info sobre los microjuegos que hay


int play_random_microgame(){ //Esta funcion selecciona un microjuego aleatorio y lo ejecuta
    int index = rand() % 4; //rand() % 8; -> Este hay que descomentarlo cuando lo tenga los 8 microjuegos completados
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