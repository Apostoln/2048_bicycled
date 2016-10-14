#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <chrono>
#include <tuple>

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

int SCORE = 0;

void print(Matrix field) {
    system("cls");
    for(auto i : field) {
        for(auto j : i) {
            std::cout << std::setw(4) << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Score: " << SCORE << std::endl;
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

    for(int i = 0; i < field.size() * field[0].size(); i++) {
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

int shiftVector(std::vector <int>& v) {
    int score = 0;
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
                score += v[j-1];
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
                score += v[j];
            }
        }
    }
    return score;
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

std::tuple <bool, int> shiftTiles(Matrix& field, Direction dir) {
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
        case Direction::NONE:
            return std::make_tuple(false, 0);
    }

    int score = 0;

    Matrix temp = field;
    for(int i = 0; i < rotating; i++) {
        rotateMatrix(temp);
    }
    for(auto &i : temp) {
        score += shiftVector(i);
    }
    for(int i = 0; i < (4-rotating); i++) {
        rotateMatrix(temp);
    }

    if(temp != field) {
        field = temp;
        return std::make_tuple(true, score);
    }
    else {
        return std::make_tuple(false, score);
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
            default:
                direction = Direction::NONE;
                break;
        }
    }
    return direction;
}

bool isWin(Matrix field) {
    for(auto i: field) {
        for(auto j: i) {
            if (2048 == j) {
                return true;
            }
        }
    }
    return false;
}

bool isLoss(Matrix field) {
    std::vector <Direction> dirs = {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT};
    for(auto dir: dirs) {
        auto temp = field;
        if (std::get<0>(shiftTiles(temp, dir))){
            return false;
        }
    }
    return true;
}

void printWin() {
    system("cls");
    std::cout << "You are won with score " << SCORE << std::endl;
}

void printLoss() {
    system("cls");
    std::cout << "You are lost with score " << SCORE << std::endl;
}

int main() {
    auto field = Matrix (row, std:: vector <int>(column, 0));
    newTile(field);
    newTile(field);
    print(field);
    while(true) {

        Direction direction = control();
        if(direction != Direction::NONE) {
            auto result = shiftTiles(field, direction);
            if (!std::get<0>(result)) {
                continue;
            }
            SCORE += std::get<1>(result);
            newTile(field);
            print(field);
            if(isWin(field)) {
                printWin();
                return 0;
            }
            if(isLoss(field)) {
                printLoss();
                return 0;
            }
        }
    }
}
