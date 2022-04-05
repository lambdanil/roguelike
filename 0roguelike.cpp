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

void MoveUp(char grid[WHEIGHT][WWIDTH]){
    if (grid[*playerY-1][*playerX] != '-' && grid[*playerY-1][*playerX] != '|' && grid[*playerY-1][*playerX] != ' ' && grid[*playerY-1][*playerX] != '+') {
        *playerY = *playerY-1;
    }
    else if (grid[*playerY-1][*playerX] == '+') {
        grid[*playerY-1][*playerX] = '_';
    }
}

void MoveDown(char grid[WHEIGHT][WWIDTH]) {
    if (grid[*playerY+1][*playerX] != '-' && grid[*playerY+1][*playerX] != '|' && grid[*playerY+1][*playerX] != ' ' && grid[*playerY+1][*playerX] != '+') {
        *playerY = *playerY+1;
    }
    else if (grid[*playerY+1][*playerX] == '+') {
        grid[*playerY+1][*playerX] = '_';
    }
}

void MoveLeft(char grid[WHEIGHT][WWIDTH]) {
    if (grid[*playerY][*playerX-1] != '-' && grid[*playerY][*playerX-1] != '|' && grid[*playerY][*playerX-1] != ' ' && grid[*playerY][*playerX-1] != '+') {
        *playerX = *playerX-1;
    }
    else if (grid[*playerY][*playerX-1] == '+') {
        grid[*playerY][*playerX-1] = '_';
    }
}

void MoveRight(char grid[WHEIGHT][WWIDTH]) {
    if (grid[*playerY][*playerX+1] != '-' && grid[*playerY][*playerX+1] != '|' && grid[*playerY][*playerX+1] != ' ' && grid[*playerY][*playerX+1] != '+') {
        *playerX = *playerX+1;
    }
    else if (grid[*playerY][*playerX+1] == '+') {
        grid[*playerY][*playerX+1] = '_';
    }
}

void MoveUR(char grid[WHEIGHT][WWIDTH]) {
    if (grid[*playerY-1][*playerX+1] != '-' && grid[*playerY-1][*playerX+1] != '|' && grid[*playerY-1][*playerX+1] != ' ' && grid[*playerY-1][*playerX+1] != '+') {
        *playerX = *playerX + 1;
        *playerY = *playerY - 1;
    }
    else if (grid[*playerY-1][*playerX+1] == '+') {
        grid[*playerY-1][*playerX+1] = '_';
    }
}

void MoveUL(char grid[WHEIGHT][WWIDTH]) {
    if (grid[*playerY-1][*playerX-1] != '-' && grid[*playerY-1][*playerX-1] != '|' && grid[*playerY-1][*playerX-1] != ' ' && grid[*playerY-1][*playerX-1] != '+') {
        *playerX = *playerX - 1;
        *playerY = *playerY - 1;
    }
    else if (grid[*playerY-1][*playerX-1] == '+') {
        grid[*playerY-1][*playerX-1] = '_';
    }
}

void MoveDR(char grid[WHEIGHT][WWIDTH]) {
    if (grid[*playerY+1][*playerX+1] != '-' && grid[*playerY+1][*playerX+1] != '|' && grid[*playerY+1][*playerX+1] != ' ' && grid[*playerY+1][*playerX+1] != '+') {
        *playerX = *playerX + 1;
        *playerY = *playerY + 1;
    }
    else if (grid[*playerY+1][*playerX+1] == '+') {
        grid[*playerY+1][*playerX+1] = '_';
    }
}

void MoveDL(char grid[WHEIGHT][WWIDTH]) {
    if (grid[*playerY+1][*playerX-1] != '-' && grid[*playerY+1][*playerX-1] != '|' && grid[*playerY+1][*playerX-1] != ' ' && grid[*playerY+1][*playerX-1] != '+') {
        *playerX = *playerX - 1;
        *playerY = *playerY + 1;
    }
    else if (grid[*playerY+1][*playerX-1] == '+') {
        grid[*playerY+1][*playerX-1] = '_';
    }
}

void doaction(char action, char grid[WHEIGHT][WWIDTH]) {
    if (action == '6') {
        MoveRight(grid);
    }
    if (action == '4') {
        MoveLeft(grid);
    }
    if (action == '2') {
        MoveDown(grid);
    }
    if (action == '8') {
        MoveUp(grid);
    }
    if (action == '1') {
        MoveDL(grid);
    }
    if (action == '3') {
        MoveDR(grid);
    }
    if (action == '9') {
        MoveUR(grid);
    }
    if (action == '7') {
        MoveUL(grid);
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
    // Rooms
    int rooms = 15 + (rand() % static_cast<int>(20 - 15 + 1));
    std::vector<int> vector_rooms;
    bool* found;
    found = new bool;
    int* roomaddx;
    roomaddx = new int;
    int* roomaddy;
    roomaddy = new int;
    int* roomendx;
    roomendx = new int;
    int* roomendy;
    roomendy = new int;
    int* roomsizex;
    roomsizex = new int;
    int* roomsizey;
    roomsizey = new int;
    for (int i = 0; i <= rooms; i++) {
        *roomaddx = 0 + (rand() % static_cast<int>(width - 0 + 1)); 
        *roomaddy = 0 + (rand() % static_cast<int>(height - 0 + 1));
        *roomsizex = MINX + (rand() % static_cast<int>(MAXY - MINX + 1)); 
        *roomsizey = MINY + (rand() % static_cast<int>(MAXY - MINY + 1));
        *roomendx = *roomaddx+*roomsizex;
        *roomendy = *roomaddy+*roomsizey;

        vector_rooms.push_back(*roomaddy);
        vector_rooms.push_back(*roomaddx);
        vector_rooms.push_back(*roomendy);
        vector_rooms.push_back(*roomendx);

        *roomaddx += 2;
        *roomaddy += 2;
        while (true) {
            if (*roomendx <= width-2) {
                break;
            }
            *roomaddx -= 1;
            *roomsizex -= 1;
            *roomendx -= 1;
        }
        while (true) {
            if (*roomendy <= height-2) {
                break;
            }
            *roomaddy -= 1;
            *roomsizey -= 1;
            *roomendy -= 1;
        }
        *found = false;
        for (int yi = *roomaddy; yi < *roomendy && yi < height; yi++) {
            for (int xi = *roomaddx; xi < *roomendx && xi < width; xi++) {
                grid[yi][xi] = '#';
                if (xi == *roomaddx && (grid[yi][xi-1] != '#') && (grid[yi][xi-2] != '#')) {
                    grid[yi][xi-1] = '|';
                    if ((rand() % 2) == 1 &&not *found) {
                        *found = true;
                        grid[yi][xi-1] = '+';
                    }
                }
                if (xi == *roomendx-1 && (grid[yi][xi+1] != '#') && (grid[yi][xi+2] != '#')) {
                    grid[yi][xi+1] = '|';
                    if  ((rand() % 2) == 1 &&not *found) {
                        *found = true;
                        grid[yi][xi+1] = '+';
                    }
                }
                if (yi == *roomaddy && (grid[yi-1][xi] != '#') && (grid[yi-2][xi] != '#')) {
                    grid[yi-1][xi] = '-';
                    //(rand() % 5) == 1 &&
                    if ((rand() % 2) == 1 &&not *found) {
                        *found = true;
                        grid[yi-1][xi] = '+';
                    }
                }
                if (yi == *roomendy-1 && (grid[yi+1][xi] != '#') && (grid[yi+2][xi] != '#')) {
                    grid[yi+1][xi] = '-';
                    if ((rand() % 2) == 1 &&not *found) {
                        *found = true;
                        grid[yi+1][xi] = '+';
                    }
                }
            }
        }
    }
    *roomaddx = 0 + (rand() % static_cast<int>(width - 0 + 1));
    *roomaddy = 0 + (rand() % static_cast<int>(height - 0 + 1));
    *roomsizex = MINX + (rand() % static_cast<int>(MAXY - MINX + 1));
    *roomsizey = MINY + (rand() % static_cast<int>(MAXY - MINY + 1));
    *roomendx = *roomaddx + *roomsizex;
    *roomendy = *roomaddy + *roomsizey;
    int* tracer;
    tracer = new int[2];
    tracer[0] = 0;
    tracer[1] = 0;
    int* newpos;
    newpos = new int[2];
    newpos[0] = 0;
    newpos[1] = 0;
    int* lastpos;
    lastpos = new int[2];
    std::vector<int> donepos;
    for (int yi = 0; yi < height; yi++) {
        for (int xi = 0; xi < width; xi++) {
            if (grid[yi][xi] == '+'  && yi > 0 && xi > 0) {
                if (grid[yi + 1][xi] != '-' && grid[yi + 1][xi] != '|') {
                    donepos.push_back(yi+1);
                    donepos.push_back(xi);
                }
                else if (grid[yi - 1][xi] != '-' && grid[yi - 1][xi] != '|') {
                    donepos.push_back(yi - 1);
                    donepos.push_back(xi);
                }
                else if (grid[yi][xi+1] != '-' && grid[yi][xi + 1] != '|') {
                    donepos.push_back(yi);
                    donepos.push_back(xi+1);
                }
                else if (grid[yi][xi-1] != '-' && grid[yi][xi - 1] != '|') {
                    donepos.push_back(yi);
                    donepos.push_back(xi-1);
                }
            }
        }
    }
    for (unsigned int i = 0; i < ((donepos.size() / 2)) - 2; i++) {
        lastpos[0] = donepos.at(0 + (i * 2));
        lastpos[1] = donepos.at(1 + (i * 2));
        newpos[0] = donepos.at(2 + (i * 2));
        newpos[1] = donepos.at(3 + (i * 2));
        while (lastpos[0] != newpos[0] && lastpos[1] != newpos[1]) {
            bool* reverse;
            reverse = new bool;
            *reverse = false;
            if (lastpos[1] != newpos[1]) {
                if (lastpos[1] < newpos[1]) {
                    for (int i = lastpos[1]; i != newpos[1]+1; i++) {
                        if (grid[lastpos[0]][lastpos[1]] != '+' && grid[lastpos[0]][lastpos[1]] != '|' && grid[lastpos[0]][lastpos[1]] != '-') {
                            grid[lastpos[0]][lastpos[1]] = '#';
                            lastpos[1] = i+1; }
                        int index = 0;
                        while ((grid[lastpos[0]][lastpos[1]] == '+' || grid[lastpos[0]][lastpos[1]] == '|' || grid[lastpos[0]][lastpos[1]] == '-')) {
                            if (lastpos[0] < 2) {
                                *reverse = true;
                            }
                            else {
                                *reverse = false;
                                lastpos[0] = lastpos[0]+1;
                            }
                            if (lastpos[1] > WHEIGHT){
                                    break;
                            }
                            index++;
                            if (index > WHEIGHT*2){
                                break;
                            }
                        }
                        grid[lastpos[0]][lastpos[1]] = '#';
                        if (lastpos[1] == newpos[1]) {
                            break;
                        }
                    }
                }
                else {
                    int index;
                    for (int i = lastpos[1]; i != newpos[1]-1; i--) {
                        if (grid[lastpos[0]][lastpos[1]] != '+' && grid[lastpos[0]][lastpos[1]] != '|' && grid[lastpos[0]][lastpos[1]] != '-') {
                            grid[lastpos[0]][lastpos[1]] = '#';
                            lastpos[1] = i-1; }
                        index = WHEIGHT*2;
                        while ((grid[lastpos[0]][lastpos[1]] == '+' || grid[lastpos[0]][lastpos[1]] == '|' || grid[lastpos[0]][lastpos[1]] == '-')) {
                            if (lastpos[0] > WHEIGHT-2) {
                                *reverse = true;
                            }
                            else {
                                *reverse = false;
                                lastpos[0] = lastpos[0]-1;
                            }
                        }
                        grid[lastpos[0]][lastpos[1]] = '#';
                        if (lastpos[1] == newpos[1]) {
                            break;
                        }
                        index--;
                        if (index < 1){
                            break;
                        }
                    }
                }
            }
            if (lastpos[0] != newpos[0]) {
                int index;
                if (lastpos[0] < newpos[0]) {
                    for (int i = lastpos[0]; i != newpos[0]+1; i++) {
                        if (grid[lastpos[0]][lastpos[1]] != '+' && grid[lastpos[0]][lastpos[1]] != '|' && grid[lastpos[0]][lastpos[1]] != '-') {
                            grid[lastpos[0]][lastpos[1]] = '#';
                            lastpos[0] = i+1; }
                        index = 0;
                        while ((grid[lastpos[0]][lastpos[1]] == '+' || grid[lastpos[0]][lastpos[1]] == '|' || grid[lastpos[0]][lastpos[1]] == '-')) {
                            if (lastpos[1] < 2) {
                                *reverse = true;
                            }
                            else {
                                *reverse = false;
                                lastpos[1] = lastpos[1]+1;
                            }
                        }
                        grid[lastpos[0]][lastpos[1]] = '#';
                        if (lastpos[0] == newpos[0]) {
                            break;
                        }
                        index++;
                        if (index > WWIDTH*2){
                            break;
                        }
                    }
                }
                else {
                    for (int i = lastpos[0]; i != newpos[0]-1; i--) {
                        if (grid[lastpos[0]][lastpos[1]] != '+' && grid[lastpos[0]][lastpos[1]] != '|' && grid[lastpos[0]][lastpos[1]] != '-') {
                            grid[lastpos[0]][lastpos[1]] = '#';
                            lastpos[0] = i-1; }
                        index = WWIDTH*2;
                        while ((grid[lastpos[0]][lastpos[1]] == '+' || grid[lastpos[0]][lastpos[1]] == '|' || grid[lastpos[0]][lastpos[1]] == '-')) {
                            if (lastpos[1] > WWIDTH - 2) {
                                *reverse = true;
                            }
                            else {
                                *reverse = false;
                                lastpos[1] = lastpos[1]-1;
                            }
                        }
                        grid[lastpos[0]][lastpos[1]] = '#';
                        if (lastpos[0] == newpos[0]) {
                            break;
                        }
                        index--;
                        if (index < 1){
                                break;
                        }
                    }
                }
            delete reverse;
            }
        }
    }
    for (int yi = 0; yi < height; yi++) {
        for (int xi = 0; xi < width; xi++) {
            if (grid[yi][xi] == '+') {
                if (grid[yi+1][xi] || grid[yi-1][xi]) {
                    grid[yi][xi] = '|';
                }
                if (grid[yi][xi+1] || grid[yi][xi-1]) {
                    grid[yi][xi] = '-';
                }
            }
        }
    }
    delete[] lastpos;
    bool* founddoor;
    founddoor = new bool;
    lastpos = new int;
    for (int yi = 1; yi < WHEIGHT; yi++) {
        for (int xi = 1; xi < WWIDTH; xi++) {
            if (grid[yi+1][xi] == '|' && grid[yi-1][xi] == '|' || (grid[yi][xi+1] == '-' && grid[yi][xi-1]) == '-') {
                *lastpos = 1;
                *founddoor = false;
                while (true) {
                    if (yi+(*lastpos) > WHEIGHT) {
                        break;
                    }
                    if (grid[yi+(*lastpos)][xi] != '|') {
                        if ((grid[yi+(*lastpos)][xi]) == '+') {
                            *founddoor = true;
                        }
                        break;
                    }
                    *lastpos += 1;
                }
                *lastpos = 1;
                while (true) {
                    if (yi-(*lastpos) < 2) {
                        break;
                    }
                    if (grid[yi-(*lastpos)][xi] != '|') {
                        if ((grid[yi-(*lastpos)][xi]) == '+') {
                            *founddoor = true;
                        }
                        break;
                    }
                    *lastpos += 1;
                }
                if (*founddoor == false && yi > 0 && xi > 0) {
                    if ((grid[yi+1][xi] == '#' && grid[yi-1][xi] == '#') || (grid[yi][xi+1] == '#' && grid[yi][xi-1] == '#')) {
                            grid[yi][xi] = '+';
                    }
                }
            }

            if (grid[yi][xi+1] == '-' && grid[yi][xi-1] == '-' || (grid[yi+1][xi] == '|' && grid[yi-1][xi]) == '|') {
                *lastpos = 1;
                *founddoor = false;
                while (true) {
                    if (xi+(*lastpos) > WWIDTH) {
                        break;
                    }
                    if (grid[yi][xi+(*lastpos)] != '-') {
                        if ((grid[yi][xi+(*lastpos)]) == '+') {
                            *founddoor = true;
                        }
                        break;
                    }
                    *lastpos += 1;
                }
                *lastpos = 1;
                while (true) {
                    if (yi-(*lastpos) < 2) {
                        break;
                    }
                    if (grid[yi][xi-(*lastpos)] != '-') {
                        if ((grid[yi][xi-(*lastpos)]) == '+') {
                            *founddoor = true;
                        }
                        break;
                    }
                    *lastpos += 1;
                }
                if (*founddoor == false && yi > 0 && xi > 0) {
                    if ((grid[yi+1][xi] == '#' && grid[yi-1][xi] == '#') || (grid[yi][xi+1] == '#' && grid[yi][xi-1] == '#')) {
                        grid[yi][xi] = '+';
                    }
                }
            }

        }
    }
    for (int yi = 0; yi < WHEIGHT; yi++) {
        for (int xi = 0; xi < WWIDTH; xi++) {
            if (xi == 0 || yi == 0) {
                grid[yi][0] == ' ';
                grid[0][xi] == ' ';
            }
        }
    }
    delete[] lastpos;

    delete roomaddx;
    delete roomaddy;
    delete roomendx;
    delete roomendy;
    delete roomsizex;
    delete tracer;
    delete roomsizey;
    delete[] newpos;
    playerX = new int;
    playerY = new int;
    *playerX = 20;
    *playerY = 20;
    char action;
    while (true) {
        print_grid(grid, WHEIGHT, WWIDTH);
        action = getch();
        doaction(action, grid);
    }

    // Generate grid
    //print_grid(grid, height, width);

}
