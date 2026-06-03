#ifndef MICROGAMES_H
#define MICROGAMES_He

typedef struct{
    char game_name[100];
    int difficulty;
    int max_time;
    int (*run)(void);
    char game_message[100];
    char music_file[100]; 
    
} microgame; //Aquí tenemos el struct que define a un microjuego

/* Y estas son las funciones que vamos a usar para main.c y microgames.c*/

int start_game();
void play_music(const char *game_music_file);
void stop_music(void);
void go_faster(void);
void clear_screen(void);
void print_logo(void);
int play_random_microgame();

#endif