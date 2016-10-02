#include <iostream>
#include <vector>
#include <random>
#include <chrono>

#include "conio.h"

using Matrix = std::vector <std::vector<int>>;

enum class Direction{
    NONE = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

size_t size = 4;
size_t row = size;
size_t column = size;

void print(Matrix field) {
    system("cls");
    for(auto i : field) {
        for(auto j : i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void newTile(Matrix& field) {
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> rowDis(0, row-1 );
    std::uniform_int_distribution<> columnDis(0, column-1);
    std::bernoulli_distribution valueDis(0.5);
    int value = valueDis(gen)? 2 : 4;
    int y = rowDis(gen);
    int x = columnDis(gen);

    while(true) {
        if (field[y][x] == 0) {
            field[y][x] = value;
            break;
        }
        x++;
        if (x >= field[y].size()) {
            y++;
            x = 0;
        }
        if (y >= field.size()) {
            x++;
            y = 0;
        }
    }
}

void shiftVector(std::vector <int>& v) {
    auto mask = std::vector<bool> (false);
    for(int i = 0; i < v.size(); i++) {
        if(v[i] != 0 && i != 0) {
            int j = i-1;
            while(j > 0 && v[j-1] == 0) {
                j--;
            }
            if(v[j] == 0 && v[j-1] == v[i] && mask[j-1] == false) {
                v[j-1] *= 2;
                v[i] = 0;
                mask[j-1] = true;
                mask[i] = false;
            }
            else if(v[j] == 0) {
                v[j] = v[i];
                v[i] = 0;
                mask[j] = mask[i];
                mask[i] = false;
            }
            else if (v[j] == v[i] && j!= i) {
                v[j] *= 2;
                v[i] = 0;
            }
        }
    }
}

void rotateMatrix(Matrix& m) {
    auto result = m;
    for(int i = 0; i < m.size(); i++) {
        for(int j = 0; j < m[0].size(); j++) {
            result[i][j] = m[m.size()-j-1][i];
        }
    }
    m = result;
}

void shiftTiles(Matrix& field, Direction dir) {
    //Rotate matrix, shift tiles for every row and rerotate back
    size_t rotating; //amount of rotating for this direction
    switch (dir) {
        case Direction::LEFT:
            rotating = 0;
            break;
        case Direction::DOWN:
            rotating = 1;
            break;
        case Direction::RIGHT:
            rotating = 2;
            break;
        case Direction::UP:
            rotating = 3;
            break;
    }
    for(int i = 0; i < rotating; i++) {
        rotateMatrix(field);
    }
    for(auto &i : field) {
        shiftVector(i);
    }
    for(int i = 0; i < (4-rotating); i++) {
        rotateMatrix(field);
    }
}

Direction control() {
    Direction direction = Direction::NONE;
    if(kbhit()) {
        int key = getch();
        key = getch();
        switch(key) {
            case 72:
                direction = Direction::UP;
                break;
            case 80:
                direction = Direction::DOWN;
                break;
            case 75:
                direction = Direction::LEFT;
                break;
            case 77:
                direction = Direction::RIGHT;
                break;
        }
    }
    return direction;
}

int main() {
    auto field = Matrix (row, std:: vector <int>(column, 0));
    newTile(field);
    newTile(field);
    print(field);
    while(true) {
        Direction direction = control();
        if(direction != Direction::NONE) {
            shiftTiles(field, direction);
            newTile(field);
            print(field);
        }
    }
    return 0;
}
