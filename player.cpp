#include <iostream>
#include <time.h>
#include <vector>
#include <unistd.h>
#include <termios.h>


const int WWIDTH = 90;
const int WHEIGHT = 35;
const int MINX = 12;
const int MINY = 5;
const int MAXY = 7;
const int MAXX = 18;
int *playerX;
int *playerY;

void print_grid(char grid[][WWIDTH], int height, int width) {
    for (int yi = 0; yi < height; yi++) {
        for (int xi = 0; xi < width; xi++) {
            if (xi == *playerX && yi == *playerY){
                std::cout << '@';
            }
            else {
                std::cout << grid[yi][xi];
            }
        }
        std::cout << std::endl;
    }
}

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

void MoveUp(){
    *playerY = *playerY-1;
}

void MoveDown() {
    *playerY = *playerY+1;
}

void MoveLeft() {
    *playerX = *playerX-1;
}

void MoveRight() {
    *playerX = *playerX+1;
}

void MoveUR() {
    *playerX = *playerX + 1;
    *playerY = *playerY - 1;
}

void MoveUL() {
    *playerX = *playerX - 1;
    *playerY = *playerY - 1;
}

void MoveDR() {
    *playerX = *playerX + 1;
    *playerY = *playerY + 1;
}

void MoveDL() {
    *playerX = *playerX - 1;
    *playerY = *playerY + 1;
}

void doaction(char action) {
    if (action == '6') {
        MoveRight();
    }
    if (action == '4') {
        MoveLeft();
    }
    if (action == '2') {
        MoveDown();
    }
    if (action == '8') {
        MoveUp();
    }
    if (action == '1') {
        MoveDL();
    }
    if (action == '3') {
        MoveDR();
    }
    if (action == '9') {
        MoveUR();
    }
    if (action == '7') {
        MoveUL();
    }
}

int main()
{
    srand((unsigned)time(NULL));
    const int height = WHEIGHT;
    const int width = WWIDTH;
    char grid[height][width];
    // Create grid
    for (int yi = 0; yi < height; yi++) {
        for (int xi = 0; xi < width; xi++) {
            grid[yi][xi] = ' ';
        }
    }
    playerX = new int;
    playerY = new int;
    *playerX = 20;
    *playerY = 20;
    char action;
    while (true) {
        print_grid(grid, WHEIGHT, WWIDTH);
        action = getch();
        doaction(action);
    }
}
