#include <stdio.h>
#include <threads.h>
#include "mechanics/mechanics.h"


#define SIZE_X 128
#define SIZE_Y 64




/*
 ##################################                                   
 #|                              |#  
 #|                              |#  
 #|                              |#  
 #|                              |#  
 #|                              |#  
 #|                              |#  
 #|                              |#  
 #|                              |#   
 #|                o             |#   
 #|              ___             |# 
 ##################################                                    ##################################                                   
 ##################################                                   
*/

int gameover = 0;

struct canvas {
    
    struct Vector2 size ;
    
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
    set_canvas();
    printf("\x1b[32m"); // green color
    
    update();
}



void update() {
    
    draw();
    
    
    if (!gameover) {
        thrd_sleep(&(struct timespec){.tv_sec = 1}, NULL);
        update();
    }
}

void draw() {
    system("clear || cls");
    for (int y = 0; y < cnvs.size.y; y++) {
        printf("%.*s", cnvs.size.x, &cnvs.canvas[(y * cnvs.size.x)]);
        printf("\n");
    }
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
        cnvs.canvas[coord_to_px(16, 26)] = 'o'; 
}




int coord_to_px(int x, int y) {
    return (x + (y * cnvs.size.x));
}


