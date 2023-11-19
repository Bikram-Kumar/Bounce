#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#ifdef _WIN32
    #include <windows.h>
#else
    #include <ncurses.h>
#endif



#include "main.h"









#define SIZE_X 96
#define SIZE_Y 32
#define REFRESH_TIME_ms 20




/*
 ##################################                                   
 #|                              |#  
 #|           ___           ___  |#  
 #|     ___                      |#  
 #|             ___        ___   |#  
 #|                              |#  
 #|     ___                      |#  
 #|                  ___         |#  
 #|         ___                  |#   
 #|                o             |#   
 #|     ___         ___          |# 
 ##################################                                    ##################################                                   
 ##################################                                   
*/

int gameover = 0;
int input;
int player_move = 0;
int player_x = 10;

S_GAME_DATA GAME_DATA = {
    .gameover = false,
    .player_start_position = (Vector2) {SIZE_X/2, 2/3 * SIZE_Y }
};









struct canvas {
    
    Vector2Int size ;
    
    char canvas[SIZE_X*SIZE_Y];
    
} cnvs = {
    {SIZE_X,SIZE_Y}, ""
} ;




void start(), set_canvas(), update(), draw();
int coord_to_px(int x, int y);

int main () {
    start();
    
}

void start() {
    
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    
    
    init_mechanics();
    
    set_canvas();
    
    update();
}




#ifdef linux
    struct timespec ts = {.tv_sec = 0, .tv_nsec = REFRESH_TIME_ms * 1000 * 1000 };
#endif



void update() {
    
    clear();
    draw();
    
    timeout(REFRESH_TIME_ms);
    input = getch();
    
    if (input == 'g') {
        player_move += 1;
    } else if (input == 'l') {
        player_move = 0;
    }
    
    if (player_move) {
        player_x += 1;
        cnvs.canvas[coord_to_px(player_x, 26)] = 'o';
    }
    
    
    if (!gameover) {
        
       /* #ifdef _WIN32         
            Sleep(REFRESH_TIME);
        #else 
            nanosleep(&ts, &ts);
        #endif
        */
        
        update();
    }
}





void draw() {
    
    attron(COLOR_PAIR(1));
    for (int y = 0; y < cnvs.size.y; y++) {
        printw("%.*s", cnvs.size.x, &cnvs.canvas[(y * cnvs.size.x)]);
        printw("\n");
    }
    attroff(COLOR_PAIR(1));
    
    refresh();
}


void set_canvas() {
    
    memset(cnvs.canvas, ' ', (cnvs.size.x * cnvs.size.y * sizeof(char)) );
    
    // Top and bottom border
    for (int x = 0; x < cnvs.size.x; x++) {
        for (int y = 0; y < 2; y++) {
            cnvs.canvas[coord_to_px(x,y)] = '#';
            cnvs.canvas[coord_to_px(x, cnvs.size.y - 1 - y)] = '#'; // last two lines
        }
    }
    
    
    // left and right border
    for (int y = 2; y < (cnvs.size.y - 2); y++) {
        
        cnvs.canvas[coord_to_px(0,y)] = '#';
        cnvs.canvas[coord_to_px(1,y)] = '|';
        cnvs.canvas[coord_to_px(cnvs.size.x - 1, y)] = '#'; 
        cnvs.canvas[coord_to_px(cnvs.size.x - 2, y)] = '|'; 
        
    }
    
        cnvs.canvas[coord_to_px(15, 28)] = '_'; 
        cnvs.canvas[coord_to_px(16, 28)] = '_'; 
        cnvs.canvas[coord_to_px(13, 26)] = 'o'; 
}




int coord_to_px(int x, int y) {
    return (x + (y * cnvs.size.x));
}




