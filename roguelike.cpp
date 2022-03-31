#include <iostream>
#include <random>
#include <time.h>
#include <stdio.h>

constexpr int WIDTH = 90;
constexpr int HEIGHT = 35;
constexpr int MINX = 12;
constexpr int MAXX = 18;
constexpr int MINY = 5;
constexpr int MAXY = 7;



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
    int rooms = 10 + (rand() % static_cast<int>(20 - 10 + 1));
    for (int i = 0; i <= rooms; i++) {
        int roomaddx = 0 + (rand() % static_cast<int>(width - 0 + 1)); // Not actually random
        int roomaddy = 0 + (rand() % static_cast<int>(height - 0 + 1));
        int roomsizex = MINX + (rand() % static_cast<int>(MAXY - MINX + 1)); // 5 is min, 10 is max
        int roomsizey = MINY + (rand() % static_cast<int>(MAXY - MINY + 1));
        int roomendx = roomaddx+roomsizex;
        int roomendy = roomaddy+roomsizey;
        roomaddx += 2;
        roomaddy += 2;
        while (true) {
            if (roomendx <= width-1) {
                break;
            }
            roomaddx -= 1;
            roomsizex -= 1;
            roomendx -= 1;
        }
        while (true) {
            if (roomendy <= height-1) {
                break;
            }
            roomaddy -= 1;
            roomsizey -= 1;
            roomendy -= 1;
        }
        for (int yi = roomaddy; yi < roomendy && yi < height; yi++) {
            for (int xi = roomaddx; xi < roomendx && xi < width; xi++) {
                grid[yi][xi] = '#';
                if (xi == roomaddx && (grid[yi][xi-1] != '#') && (grid[yi][xi-2] != '#')) {
                    grid[yi][xi-1] = '|';
                }
                if (xi == roomendx-1 && (grid[yi][xi+1] != '#') && (grid[yi][xi+2] != '#')) {
                    grid[yi][xi+1] = '|';
                }
                if (yi == roomaddy && (grid[yi-1][xi] != '#') && (grid[yi-2][xi] != '#')) {
                    grid[yi-1][xi] = '=';
                }
                if (yi == roomendy-1 && (grid[yi+1][xi] != '#') && (grid[yi+2][xi] != '#')) {
                    grid[yi+1][xi] = '=';
                }
            }
        }
        for (int yi = 0; yi < height; yi++) {
            for (int xi = 0; xi < width; xi++) {
                if (grid[yi][xi] == '|' && (grid[yi][xi-1] == '#') && (grid[yi][xi+1] == '#')) {
                    grid [yi][xi] = '#';
                }
                if (grid[yi][xi] == '=' && (grid[yi-1][xi] == '#') && (grid[yi+1][xi] == '#')) {
                    grid [yi][xi] = '#';
                }
            }
        }
    }
    // Generate grid
    print_grid(grid, height, width);

}
