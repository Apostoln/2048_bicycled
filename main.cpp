#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <ctime>
using Matrix = std::vector <std::vector<int>>;

enum struct Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

size_t row = 4;
size_t column = 4;


void print(Matrix field) {
    for(auto i : field) {
        for(auto j : i) {
            std::cout << j;
        }
        std::cout << std::endl;
    }
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
    for(int k = 0; k < v.size(); k++) {
        for (int i = 0; i < v.size(); i++) {
            if (v[i] != 0) {
                for (int j = i - 1; j >= 0; j--) {
                    if (v[j] == 0) {
                        v[j] = v[i];
                        v[i] = 0;
                        break;
                    }
                    if (v[j] == v[i]) {
                        v[j] *= 2;
                        v[i] = 0;
                        break;
                    }
                }
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
    size_t rotating; //amount of rotating for this dir
    switch (dir) {
        case Direction::LEFT:
            rotating = 0;
            break;
        case Direction::UP:
            rotating = 1;
            break;
        case Direction::RIGHT:
            rotating = 2;
            break;
        case Direction::DOWN:
            rotating = 3;
            break;
    }
    for(int i = 0; i < rotating; i++) {
        rotateMatrix(field);
    }
    shiftVector(field);
    for(int i = 0; i < (4-rotating); i++) {
        rotateMatrix(field);
    }
}



int main() {
    auto field = Matrix (row, std:: vector <int>(column, 0));
    newTile(field);
    newTile(field);
    print(field);
    std::cout << "Hello world!" << std::endl;
    return 0;
}
