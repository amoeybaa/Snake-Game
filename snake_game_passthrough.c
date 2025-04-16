// Snake game with passthrough walls

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<ctype.h>
#include<windows.h>

#define HEIGHT 16
#define WIDTH 32

// Arrays to store coordinates of snake's tail
int snakeTailX[HEIGHT*WIDTH], snakeTailY[HEIGHT*WIDTH];


// Length of snake
int snakeTailLen;

// Flag for score and game over
int key, score, gameOver;

// Coordinates of snake's head and fruit
int snakeHeadX, snakeHeadY, fruitX, fruitY;

void setup() {
    gameOver = 0;
    snakeHeadX = WIDTH/2;
    snakeHeadY = HEIGHT/2;

    fruitX = rand()%WIDTH;
    fruitY = rand()%HEIGHT;

    while(fruitX == 0) fruitX = rand()%WIDTH;
    while(fruitY == 0) fruitY = rand()%HEIGHT;

    score = 0;
}

void draw() {
    system("cls");

    for(int i = 0; i < WIDTH+2; ++i) {printf("-");}
    printf("\n");

    for(int i = 0; i < HEIGHT; ++i) {
        for(int j = 0; j <= WIDTH; ++j) {
            if(j == 0 || j == WIDTH) printf("#");
            if(snakeHeadX == j && snakeHeadY == i) printf("O");
            else if(fruitX == j && fruitY == i) printf("*");
            else {
                int isTail = 0;
                for (int k = 0; k < snakeTailLen; k++) {
                    if (snakeTailX[k] == j
                        && snakeTailY[k] == i) {
                        printf("o");
                        isTail = 1;
                    }
                }
                if (!isTail) printf(" ");
            }
        }
        printf("\n");
    }

    for(int i = 0; i < WIDTH+2; ++i) {printf("-");}

    printf("\n\nScore = %d", score);
    printf("\n");
    printf("Press W, A, S, D for movement.\n");
    printf("Press 'X' to quit the game.");
}

void input() {
    if(kbhit()) {
        switch(tolower(getch())) {
            case 'a':           // a -> left -> '1'
                if(key != 2) key = 1;
                break;

            case 'd':           // d -> right -> '2'
                if(key != 1) key = 2;
                break;

            case 's':           // s -> down -> '3'
                if(key != 4) key = 3;
                break;

            case 'w':           // w -> up -> '4'
                if(key != 3) key = 4;
                break;

            case 'x':            // EXIT
                gameOver = 1;
                break;
        }
    }
}

void logic() {
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;
    snakeTailX[0] = snakeHeadX;
    snakeTailY[0] = snakeHeadY;

    for(int i = 1; i < snakeTailLen; ++i) {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }


    switch(key) {
        case 1:
            if(snakeHeadX == 0) snakeHeadX = WIDTH-1;
            else --snakeHeadX;
            break;

        case 2:
            if(snakeHeadX == WIDTH) snakeHeadX = 0;
            else ++snakeHeadX;
            break;

        case 3:
            if(snakeHeadY == HEIGHT) snakeHeadY = 0;
            else ++snakeHeadY;
            break;

        case 4:
            if(snakeHeadY == 0) snakeHeadY = HEIGHT-1;
            else --snakeHeadY;
            break;
        
        default:
            break;
    }

    for(int i = 0; i < snakeTailLen; ++i) {
        if(snakeTailX[i] == snakeHeadX && snakeTailY[i] == snakeHeadY) {gameOver = 1;}
    }

    if(snakeHeadX == fruitX && snakeHeadY == fruitY) {
        fruitX = rand()%WIDTH;
        fruitY = rand()%HEIGHT;

        while(fruitX == 0) fruitX = rand()%WIDTH;
        while(fruitY == 0) fruitY = rand()%HEIGHT;

        ++score;
        ++snakeTailLen;

    }
}

void main() {
    setup();
    while(!gameOver) {
        draw();
        input();
        logic();
        Sleep(65);
    }
}
