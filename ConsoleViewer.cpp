#pragma once

#include <iostream>
#include <iomanip>

#include "ConsoleViewer.h"

ConsoleViewer::ConsoleViewer(Field* field):
    Viewer(field) {}

void ConsoleViewer::printWin() {
    system("cls");
    std::cout << "You are won with score " << field->getScore() << std::endl;
    exit(1);
}

void ConsoleViewer::printLoss() {
    system("cls");
    std::cout << "You are lost with score " << field->getScore() << std::endl;
    exit(2);
}

void ConsoleViewer::show() {
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

