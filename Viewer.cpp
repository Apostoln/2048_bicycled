#pragma once

#include <iostream>
#include <iomanip>

#include "Viewer.h"

Viewer::Viewer(Field* field):
    field(field) {}


Field* Viewer::getField() {
    return field;
}


void Viewer::printWin() {
    system("cls");
    std::cout << "You are won with score " << field->getScore() << std::endl;
    exit(1);
}

void Viewer::printLoss() {
    system("cls");
    std::cout << "You are lost with score " << field->getScore() << std::endl;
    exit(2);
}

void Viewer::show() {
    system("cls");
    for(auto i : field->getBoard()) {
        for(auto j : i) {
            std::cout << std::setw(4) << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Score: " << field->getScore() << std::endl;
}

