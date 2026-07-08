#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "microgames.h"
#include <SDL2/SDL_mixer.h>
#define WIN 1
#define LOSE 0


int microgame_win_con(int TL, int ST, char buff[] , char module[] , char *message_1, char *message_2){ // TL -> time left, ST -> start time 

        if (TL > ST){
        puts("TIME'S OUT!");
        sleep(2);
        return 0;
    }

    if (strcmp(buff, module) != 0){

        printf("%s\n", message_1);
        sleep(2);
        return 0;
    } 
    
    printf("%s\n", message_2);
    sleep(2);
    return 1;
}

static void clean_screen(){ 
    printf("\033[H\033[J");
}

/* TODO: Nada que hacer de momento*/

//debajo están las funciones de cada microjuego

int microgame_ping(){

    char buffer[64];
    int start_time = 10;
    int start = time(NULL);

    microgame_class classes[] = {
        {"PING THE CLASS A IP!", "si", "si", {"10.212.6.1", "8.8.8.8", "10.0.0.1", "12.34.56.78", "25.3.0.67", "60.18.44.182", "99.27.224.79", "3.14.56.92", "126.8.22.44", "59.9.34.252"}},
        {"PING THE CLASS B IP!", "si", "si", {"128.33.8.91", "173.9.37.154", "166.66.33.22", "132.87.0.2", "158.28.1.248", "191.0.0.4", "146.3.0.5", "181.30.73.29", "174.91.33.8", "132.182.83.74"}},
        {"PING THE CLASS C IP!", "si", "si",  {"192.168.0.122", "207.22.33.99", "193.28.67.34", "212.22.3.8", "194.34.3.4", "221.30.20.70", "209.3.212.87", "198.76.54.32", "217.94.31.26", "192.73.8.14"}}
    }; /* Aquí están las clases de IPs de la A a la C con sus IPs, junto 
    con un buffer y el tiempo que tiene el microjuego*/

    int class = rand() % 3;
    int random_ip = rand() % 10;
    int random_distraction_ip = rand() % 10;
    int random_distraction_ip2 = rand() % 10;
    microgame_class objective_class = classes[class];
    microgame_class distraction_class, distraction_class2;

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
    
    
    char *ip_list[] = {objective_class.module_4[random_ip], distraction_class.module_4[random_distraction_ip], distraction_class2.module_4[random_distraction_ip2]};

    for (int i = 0, j = 0; i <= 2; i++){
        j = rand() % 3;
        char *temp = ip_list[i];        
        ip_list[i] = ip_list[j];
        ip_list[j] = temp;
        
    }

    /* Arria está la lista con las 3 IPs del juego y el bucle lo que hace es mezclar
    las IPs de manera que salgan en un orden aleatorio*/

    clean_screen();
    
    printf("TIME: %d\n", start_time);
    puts("");
    printf("%s\n", objective_class.module_1);
    puts("Use 'ping' followed by the number of the IP!");
    puts("Example: ping 8");
    printf("\n");
    printf("1) %s\n", ip_list[0]);
    printf("2) %s\n", ip_list[1]);
    printf("3) %s\n", ip_list[2]);
    puts("");
    printf("player@re-ware:~$ ");
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

    if ((strcmp(buffer, "ping 1") == 0 && strcmp(ip_list[0], objective_class.module_4[random_ip]) == 0) ||
    (strcmp(buffer, "ping 2") == 0 && strcmp(ip_list[1], objective_class.module_4[random_ip]) == 0) ||
    (strcmp(buffer, "ping 3") == 0 && strcmp(ip_list[2], objective_class.module_4[random_ip]) == 0)){

    printf("PING %s (%s) 56(84) bytes of data.\n", objective_class.module_4[random_ip], objective_class.module_4[random_ip]);
    printf("64 bytes from %s: icmp_seq=1 ttl=116 time=9.18 ms\n", objective_class.module_4[random_ip]);
    sleep(1);
    printf("64 bytes from %s: icmp_seq=1 ttl=116 time=8.63 ms\n", objective_class.module_4[random_ip]);
    sleep(1);
    printf("64 bytes from %s: icmp_seq=1 ttl=116 time=8.82 ms\n", objective_class.module_4[random_ip]);
    sleep(1);
    printf("64 bytes from %s: icmp_seq=1 ttl=116 time=8.67 ms\n", objective_class.module_4[random_ip]);
    sleep(1);
    puts("^C");
    printf("--- %s ping statistics ---\n", objective_class.module_4[random_ip]);
    puts("4 packets transmitted, 4 received, 0% packet loss, time 3005ms");
    puts("rtt min/avg/max/mdev = 8.429./8.571/8.721/0.122 ms");
    printf("player@re-ware:~$ \n");
    sleep(2);

    return 1;
    }

    else if (strcmp(buffer, "ping 1") == 0 && strcmp(ip_list[0], objective_class.module_4[random_ip]) != 0){
        printf("PING %s (%s) 56(84) bytes of data.\n", ip_list[0], ip_list[0]);
        sleep(4);
        puts("^C");
        printf("--- %s ping statistics ---\n", ip_list[0]);
        puts("4 packets transmitted, 0 received, 100% packet loss, time 4250ms");
        puts("");
        printf("player@re-ware:~$ \n");
        sleep(2);
        return 0;
    }

    else if (strcmp(buffer, "ping 2") == 0 && strcmp(ip_list[1], objective_class.module_4[random_ip]) != 0){
        printf("PING %s (%s) 56(84) bytes of data.\n", ip_list[1], ip_list[1]);
        sleep(4);
        puts("^C");
        printf("--- %s ping statistics ---\n", ip_list[1]);
        puts("4 packets transmitted, 0 received, 100% packet loss, time 4250ms");
        puts("");
        printf("player@re-ware:~$ \n");
        sleep(2);
        return 0;
    }

    else if (strcmp(buffer, "ping 3") == 0 && strcmp(ip_list[2], objective_class.module_4[random_ip]) != 0){
        printf("PING %s (%s) 56(84) bytes of data.\n", ip_list[2], ip_list[2]);
        sleep(4);
        puts("^C");
        printf("--- %s ping statistics ---\n", ip_list[2]);
        puts("4 packets transmitted, 0 received, 100% packet loss, time 4250ms");
        puts("");
        printf("player@re-ware:~$ \n");
        sleep(2);
        return 0;
    }

    else {
        printf("bash: $%s: command not found\n", buffer);
        printf("player@re-ware-$ \n");
        sleep(2);
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

    microgame_class instructions[] = {
        {"You are in: /home/player", "Go to /home/player/Documents and list the content", "cd Documents && ls", "daf", "ho"},
        {"You are in: /etc", "Find the line contaning \"root\" in the \"passwd\" file", "grep root passwd", "saf", "ho"},
        {"You are in: /home/player/projects", "Go to /home/player/projects/https-server and execute the ELF \"main\"", "cd https-server && ./main", " sdf", "si"},
        {"You are in: /home/player", "Create a file name \"notes.txt\" containing \"Hello World!\"", "touch notes.txt && echo \"Hello World!\" < notes.txt", "si", "si"},
        {"You are in: /opt/tools", "Make \"installer.sh\" executable", "chmod +x installer.sh", "sfsdf ", "si"},
        {"You are in: /etc", "Search for \"localhost\" in all files", "grep -r localhost .", "sfsdf ", "si"},
        {"You are in: /var/log", "Count how many lines contain \"error\" in syslog", "grep -i error syslog | wc -l", "sdfsf", "si"},
        {"You are in: /", "Find running processes related to nginx", "ps aux | grep nginx", "sfsdf", "si"},
        {"You are in: /home/player/scrpts", "Make \"deploy.sh\" executable, then execute it and save output to \"log.txt\"", "chmod +x deploy.sh && ./deploy.sh > log.txt", "dsfdf", "si"},
        {"You are in: /etc", "List files containing \"conf\" and save output to \"result.txt\"", "ls | grep conf > result.txt", "sfsdfsdf", "si"}

    };

    /*Arriba, al igual que el microjuego de Ping, tenemos un buffer para input, el tiempo y el array de structs con cada una de las instrucciones y
    la respuesta correcta a esa instrucción*/

    int rand_instruction = rand() % 10;
    microgame_class target_instruction = instructions[rand_instruction];

    clean_screen();
    printf("TIME: %d\n", start_time);
    puts("");
    printf("%s\n", target_instruction.module_1);
    printf("OBJECTIVE: %s\n", target_instruction.module_2);
    puts("NOTE: All instructions must be done using ONLY ONE command line");
    puts("");
    printf("player@re-ware:~$ ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    fflush(stdout);
    int time_left = time(NULL) - start;
    int result = microgame_win_con(time_left, start_time, buffer, target_instruction.module_3, "WRONG COMMAND!", "CORRECT COMMAND!");
    return result;
}

    /*Esto de arriba ya se ha visto antes: se imprime el tiempo, el directorio en el que supuestamente estás,
    la instrucción a seguir, una nota para indicar que todos los comandos hay que hacerlos en una sola línea
    y ya se espera la respuesta del jugador y se comprueba si la respuesta es o no correcta*/    

int microgame_code_error(){

    char buffer[64];
    int start_time = 10;
    int start = time(NULL);
    

    microgame_class code_errors[] = {

        {"1 | int main(){\n2 |     int x = 5\n3 |     printf(\"%d\\n\", x);\n4 | }", "line 2", "si", "si"},
        {"5 | int main(){\n6 |     year = 2026;\n7 |     printf(\"%d\\n\", year);\n8 | }", "line 6", "si", "si"},
        {"1 | int x = 5;\n2 |\n3 | if (x = 5){\n4 |     printf(\"Five\\n\");\n5 | }", "line 3", "si", "si"},
        {" 9 | int time = 12;\n10 | char buffer[64];\n11 | fgets(buffer, sizeof(buffer), stdin);\n12 | if (buffer == \"hello\"){\n13 |     printf(\"Hi there!\\n\");", "line 12", "si", "si"},
        {"1 | int numbers[10];\n2 |\n3 | numbers[10] = 42;\n4 |", "line 3", "si", "si"},
        {"23 | int main(){\n24 |     char username[8];\n25 |\n26 |     strcpy(username, \"SuperAdmin\");\n27 |\n28 |     printf(\"%s\\n\", username);\n29 |\n30 | return 0;\n31 | }", "line 26", "si", "si"},
        {"1 | int main(){\n2 |     char *name = NULL;\n3 |\n4 |     puts(\"Loading...\");\n5 |     sleep(2);\n6 |\n7 |     printf(\"%c\\n\", name);\n8 |     return 0;\n9 | }", "line 7", "si", "si"} 

    };

    // Bueno, aquí no tengo que explicar nada porque es lo mismo qeu los otros 2 microjuegos
    int rand_code_error = rand() % 7;
    microgame_class target_code_error = code_errors[rand_code_error];

    clean_screen();
    printf("TIME: %d\n", start_time);
    puts("");
    puts("FIND THE ERROR!");
    puts("Write \"line\" followed by the line number where the error is!");
    puts("Example: line 33");
    puts("");
    printf("%s", target_code_error.module_1);
    puts("");
    puts("");
    printf("player@re-ware:~$ ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    fflush(stdout);
    int time_left = time(NULL) - start;
    int result = microgame_win_con(time_left, start_time, buffer, target_code_error.module_2, "YOU DIDN'T FIND THE ERROR!", "YOU FOUND THE ERROR!");
    return result;
}

    //Y esta parte del código es prácticamente igual a los otros microjuegos 



int microgame_find(){
    char buffer[64];
    int start_time = 10;
    int start = time(NULL);

    microgame_class find_cases[] = {
        {"Find the oldest edited file in the group!", "-rw-r--r-- 1 player player  470 May 13 19:00 README.md\n-rw-r--r-- 1 player player 1534 May 13 18:45 text.txt", "text.txt", "si", "si"},
        {"Find the shell script!", "arch-linux.iso calculator.py game.cpp hello.txt shell.sh", "shell.sh", "si", "si"},
        {"Find the private IP!", "1) 8.8.8.8\n2) 151.101.1.67\n3) 192.168.1.134\n4) 89.234.21.7", "3", "si", "si"},
        {"Find the loopback IP!", "1) 191.34.233.40\n2) 10.0.0.1\n3) 172.182.99.3\n4) 127.0.0.1", "4", "si", "si"},
        {"Find the hidden file!", "notes.txt config.cfg .bashrc picture.jpg", ".bashrc", "si", "si"},
        {"Find the suspicious file!", "ball.png debian-13.iso fantasy-book.pdf keylogger.py roblox-script.lua", "keylogger.py", "si", "si"}


        //Me he cansdo de explicar esta parte de arriba

    };

    int random_target = rand() % 6;
    microgame_class find_target = find_cases[random_target];

    clean_screen();
    printf("TIME: %d\n", start_time);
    puts("");
    printf("OBJECTIVE: %s\n", find_target.module_1);
    puts("");
    puts("NOTE: This is what you should write depending of the target:\n-File/dir: write the file/dir name\n-IP: write the number before the IP address");
    puts("");
    printf("%s\n", find_target.module_2);
    puts("");
    puts("");
    printf("player@re-ware:~$ ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    fflush(stdout);
    int time_left = time(NULL) - start;
    int result = microgame_win_con(time_left, start_time, buffer, find_target.module_3, "YOU DIDN'T FIND THE TARGET!", "YOU FOUND THE TARGET!");
    return result;
}
int microgame_memory(){

    char buffer[64];
    int start_time = 10;
    

    microgame_class sequences[] = {
        {"3) malloc\n1) pointer\n2) array\n4) struct" , "pointer array malloc struct", "si", "si"},
        {"1) linux\n2) kernel\n3) bash ", "linux kernel bash", "si", "si"},
        {"4) kotlin\n2) python\n3) java\n1) rust", "rust python java kotlin", "si", "si"},
        {"2) ls\n3) man\n5) grep\n1) mkdir\n4) sudo", "mkdir ls man sudo grep", "si", "si"},
        {"2) /usr\n1) /tmp\n3) /home\n4) /mnt", "/tmp /usr /home /mnt", "si", "si"}

    };

    int random_sequence = rand() % 5;
    microgame_class target_sequence = sequences[random_sequence];

    clean_screen();
    puts("YOU HAVE THREE SECONDS TO MEMORIZE THIS SEQUENCE!");
    puts("");
    printf("%s", target_sequence.module_1);
    fflush(stdout);
    sleep(3);
    clean_screen();

    int start = time(NULL);
    printf("TIME: %d", start_time);
    puts("");
    puts("You must write all the words in order, in lowercase and separated with a space!");
    puts("");
    printf("player@re-ware:~$ ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    fflush(stdout);
    int time_left = time(NULL) - start;
    int result = microgame_win_con(time_left, start_time, buffer, target_sequence.module_2, "WRONG ANSWER!", "CORRECT ANSWER!");
    return result;
}



int microgame_press(){
    
    char buffer[64];
    int start_time = 7;
    int start = time(NULL);

    microgame_class cases[] = {
        {"PRESS A FIVE TIMES", "aaaaa", "si", "si"},
        {"PRESS H 1 TIME AND J 3 TIMES", "hjjj", "si", "si"},
        {"PRESS / 2 TIMES, D FOR 2 TIMES AND P FOR 1 TIME", "//ddp", "si", "si"},
        {"PRESS Z 3 TIMES", "zzz", "si", "si"},
        {"PRESS ; 4 times and R 2 times", ";;;;rr", "si", "si"},
        {"PRESS G 3 TIMES, Y 2 TIMES AND V 1 TIME", "gggyyv", "si", "si"},
        {"PRESS @", "@", "si", "si"},
        {"PRESS 6 6 TIMES AND 7 7 TIMES", "6666667777777", "si", "si"},
    };

    int random_case = rand() % 8;
    microgame_class objective_press = cases[random_case];

    clean_screen();
    printf("TIME: %d", start_time);
    puts("");
    puts("");
    printf("%s\n", objective_press.module_1);
    puts("NOTE: you must press all the keys in lowercase and without spaces!");
    puts("Once you're done pressing the keys, hit ENTER");
    puts("");
    printf("player@re-ware:~$ ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    int time_left = time(NULL) - start;
    int result = microgame_win_con(time_left, start_time, buffer, objective_press.module_2, "WRONG ANSWER!", "CORRECT ANSWER!");
    return result;
     
}

void print_instructions(){
        puts("");
        puts("");
        puts("GO TO THE EXIT!");
        puts("P -> Player, E -> Exit");
        puts("CONTROLS: w -> up, a -> left, s -> down, d -> right");
        puts("You must put the direction you want to move, then hit ENTER to move");
        puts("");
        printf("player@re-ware:~$ ");
}


int microgame_escape(){

    /*
    
    #######
    #P # E#
    #  #  #  -> Así es como debería verse el laberinto
    #     #
    #######
    
    */

    int win_con = 0; // -> condición de victoria
    char buffer[64];
    char matrix[5][8] = {"#######", "#P # E#", "#  #  #",  "#     #", "#######" };
       
    int row = 1;
    int index = 1;
    int start_time = 10;
    int start = time(NULL);

    while (win_con == 0){
        clean_screen();
        printf("TIME: %d\n", start_time);
        puts("");
        for (int i = 0; i <= 4; i++){
            printf("%s", matrix[i]);
            puts("");
            
        }
        print_instructions();
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        fflush(stdout);
        int time_left = time(NULL) - start;

        if (time_left > start_time){
            puts("TIME'S OUT!");
            sleep(2);
            return 0;
        }
        
        if (strcmp(buffer, "w") == 0 ){ //Los 4 ifs de abajo son para el movimiento del jugador

            if (matrix[row - 1][index] != '#'){
                if (matrix[row -1][index] == 'E'){
                    matrix[row - 1][index] = matrix[row][index];
                    matrix[row][index] = ' ';
                    win_con = 1;
                }
                matrix[row - 1][index] = matrix[row][index];
                matrix[row][index] = ' ';
                row--;
            }


            }

        if (strcmp(buffer, "a") == 0 ){

            if (matrix[row][index - 1] != '#'){
                if (matrix[row][index - 1] == 'E'){
                    matrix[row][index - 1] = matrix[row][index];
                    matrix[row][index] = ' ';
                    win_con = 1;
                }
                matrix[row][index - 1] = matrix[row][index];
                matrix[row][index] = ' ';
                index--;
            }
            
            }

        if (strcmp(buffer, "s") == 0 ){

            if (matrix[row + 1][index] != '#'){
                if (matrix[row + 1][index] == 'E'){
                    matrix[row + 1][index] = matrix[row][index];
                    matrix[row][index] = ' ';
                    win_con = 1;
                }
                matrix[row + 1][index] = matrix[row][index];
                matrix[row][index] = ' ';
                row++;
            }
            
            }
        if (strcmp(buffer, "d") == 0 ){

            if (matrix[row][index + 1] != '#'){
                if (matrix[row][index + 1] == 'E'){
                    matrix[row][index + 1] = matrix[row][index];
                    matrix[row][index] = ' ';
                    win_con = 1;
                }
                matrix[row][index + 1] = matrix[row][index];
                matrix[row][index] = ' ';
                index++;
            }
            
            }
        }
    clean_screen();
    printf("TIME: %d\n", start_time);
    puts("");
    for (int i = 0; i <= 4; i++){
        printf("%s", matrix[i]);
        puts("");
        
    }
    print_instructions();
    puts("");
    puts("YOU FOUND THE EXIT!");
    sleep(2);
    return 1;
}
    
int microgame_ports(){
    
    char buffer[64];
    int start_time = 10;
    int start = time(NULL);

    microgame_class ports[] = {
        {"Port: ", "80", "http", "si"},
        {"Service: ", "HTTPS", "443", "si"},
        {"Port: ", "143", "imap", "si"},
        {"Service: ", "DHCP", "67", "si"},
        {"Port: ", "53", "dns", "si"},
        {"Service: ", "FTP", "21", "si"},
        {"Port: ", "22", "ssh", "si"},
    };

    int random_port = rand() % 7;
    microgame_class target_port = ports[random_port];

    clean_screen();
    printf("TIME: %d\n",  start_time);
    puts("");
    puts("Write the port or service (in lowercase)!");
    puts("");
    printf("%s%s", target_port.module_1, target_port.module_2);
    puts("");
    puts("");
    printf("player@re-ware:~$ ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    int time_left = time(NULL) - start;
    int result = microgame_win_con(time_left, start_time, buffer, target_port.module_3, "WRONG ANSWER!", "CORRECT ANSWER!");
    return result;

}

microgame games[] = {
    {microgame_ping, "PING THE CORRECT IP!"},
    {microgame_instructions, "FOLLOW THE INSTRUCTIONS!"},
    {microgame_code_error, "DETECT THE CODE ERROR!"},   
    {microgame_find, "FIND THE TARGET!"},
    {microgame_memory, "REMEMBER THE SEQUENCE!"},
    {microgame_press, "PRESS THE CORRECT KEY OR KEYS!"},
    {microgame_escape, "ESCAPE THE LABYRINTH!"},
    {microgame_ports, "WRITE THE RIGHT PORT OR SERVICE!"}
};

//Este es el array que contiene toda la info sobre los microjuegos que hay


int play_random_microgame(){ //Esta funcion selecciona un microjuego aleatorio y lo ejecuta
    int index = rand() % 8;
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
            puts("FAILURE!");
            round++;
            sleep(2);
            clean_screen();
        }
        else{
            puts("SUCCESS!");
            round++;
            sleep(2);
            clean_screen();
        }
        
    }

    puts("GAME OVER");
    sleep(3);
    return 0; 
}
