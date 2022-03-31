#include <iostream>
#include <random>
#include <time.h>
#include <stdio.h>
#include <vector>

const int WIDTH = 90;
const int HEIGHT = 35;
const int MINX = 12;
const int MINY = 5;
const int MAXY = 7;
const int MAXX = 18;


void print_grid(char grid[][WIDTH], int height, int width) {
    for (int yi = 0; yi < height; yi++) {
        for (int xi = 0; xi < width; xi++) {
            std::cout << grid[yi][xi];
        }
        std::cout << std::endl;
    }
}

int main()
{
    srand((unsigned)time(NULL));
    const int height = HEIGHT;
    const int width = WIDTH;
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
        *roomaddx = 0 + (rand() % static_cast<int>(width - 0 + 1)); // Not actually random
        *roomaddy = 0 + (rand() % static_cast<int>(height - 0 + 1));
        *roomsizex = MINX + (rand() % static_cast<int>(MAXY - MINX + 1)); // 5 is min, 10 is max
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
            if (*roomendx <= width-1) {
                break;
            }
            *roomaddx -= 1;
            *roomsizex -= 1;
            *roomendx -= 1;
        }
        while (true) {
            if (*roomendy <= height-1) {
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
                    if ((rand() % 5) == 1 && not *found) {
                        *found = true;
                        grid[yi][xi-1] = '+';
                    }
                }
                if (xi == *roomendx-1 && (grid[yi][xi+1] != '#') && (grid[yi][xi+2] != '#')) {
                    grid[yi][xi+1] = '|';
                    if ((rand() % 5) == 1 && not *found) {
                        *found = true;
                        grid[yi][xi+1] = '+';
                    }
                }
                if (yi == *roomaddy && (grid[yi-1][xi] != '#') && (grid[yi-2][xi] != '#')) {
                    grid[yi-1][xi] = '=';
                    if ((rand() % 5) == 1 && not *found) {
                        *found = true;
                        grid[yi-1][xi] = '+';
                    }
                }
                if (yi == *roomendy-1 && (grid[yi+1][xi] != '#') && (grid[yi+2][xi] != '#')) {
                    grid[yi+1][xi] = '=';
                    if ((rand() % 5) == 1 && not *found) {
                        *found = true;
                        grid[yi+1][xi] = '+';
                    }
                }
            }
        }
    }
    int* startpoint;
    startpoint = new int[2];
    int* endpoint;
    endpoint = new int[2];
    for (int yi = *roomaddy; yi < *roomendy && yi < height; yi++) {
        for (int xi = *roomaddx; xi < *roomendx && xi < width; xi++) {
            if (grid[yi][xi] == '+') {
                startpoint[0] = yi;
                startpoint[1] = xi;
                for (int yyi = *roomaddy; yyi < *roomendy && yyi < height; yyi++) {
                    for (int xxi = *roomaddx; xxi < *roomendx && xxi < width; xxi++) {
                    }
                }
            }
        }
    }
    std::cout << startpoint[0] << std::endl;
    delete[] endpoint;
    delete[] startpoint;
    delete roomaddx;
    delete roomaddy;
    delete roomendx;
    delete roomendy;
    delete roomsizex;
    delete roomsizey;

    // Generate grid
    print_grid(grid, height, width);

}
