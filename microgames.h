#ifndef MICROGAMES_H
#define MICROGAMES_He

typedef struct{
    int (*run)(void);
    char game_message[100];
} microgame; //Aquí tenemos el struct que define a un microjuego

typedef struct{
    char message[50];
    char *array[10];
} ping_class; //El struct para el microjuego del Ping

typedef struct{
    char current_directory[50];
    char instruction[128];
    char answer[64];

} instruction_class; //Struct para el microjuego de las instruciones

typedef struct{
    char code_lines[256];
    char line_error[8];
} code_error_class; //Struct para el microjuego del error de código y el de encontrar achivos en una lista

typedef struct{
    char message[64];
    char possible_targets[256];
    char target[16];
} find_class;

typedef struct{
    char sequence[256];
    char answer[64];
} memory_class;

typedef struct{
    char message[64];
    char answer[16];
} press_class;


/* Y estas son las funciones que vamos a usar para main.c y microgames.c
(Algunas fuciones no se van a usar porque son para la v 2.0 pero las he hecho
porque no tenía nada mejor que hacer)*/
void loading_bar(char custom_message[], int delay);
int start_game();
void play_music(const char *game_music_file);
void stop_music(void);
void go_faster(void);
void clear_screen(void);
void print_logo(void);
int play_random_microgame();

#endif