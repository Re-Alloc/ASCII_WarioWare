#ifndef MICROGAMES_H
#define MICROGAMES_H

typedef struct{
    int (*run)(void);
    char game_message[100];
} microgame; //Aquí tenemos el struct que define a un microjuego

typedef struct{
    char module_1[256];
    char module_2[256];
    char module_3[256];
    char *module_4[10];
} microgame_class;

/*He decidido crear la 'microgame class' para agrupar todas las clases que 
 * tenía antes en una sola, con diferentes módulos para sustituir a las 
 * diferentes cosas que había antes*/


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
