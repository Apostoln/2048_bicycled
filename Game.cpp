#pragma once

#include "Game.h"
#include "Field.h"
#include "Viewer.h"
#include "Listener.h"
#include "Direction.h"

Game::Game(Field* field, Viewer* viewer, Listener* listener):
    field(field), viewer(viewer), listener(listener) {}

Game::Game(Viewer* viewer, Listener* listener):
    viewer(viewer), listener(listener), field(viewer->getField()) {}


Field* Game::getField() {
    return field;
}


void Game::start() {
    for(int i = 0; i < 2; i++) {
        field->newTile();
    }
    update();

    listener->setTarget(this);
    listener->listen();
}

void Game::turn(Direction direction) {
    if(direction != Direction::NONE) {
        auto result = field->shiftTiles(direction);
        if (std::get<0>(result)) {
            *field += std::get<1>(result);
            field->newTile();

            update();

            if(isWin()) {
                win();
                return ;
            }
            if(isLoss()) {
                loss();
                return ;
            }
        }
    }
}


void Game::update() {
    viewer->show();
}

void Game::win() {
    viewer->printWin();
}

void Game::loss() {
    viewer->printLoss();
}


bool Game::isWin() {
    for(auto i: field->getBoard()) {
        for(auto j: i) {
            if (2048 == j) {
                return true;
            }
        }
    }
    return false;
}

bool Game::isLoss() {
    std::vector <Direction> dirs = {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT};
    for(auto dir: dirs) {
        auto temp = *field;
        if (std::get<0>(temp.shiftTiles(dir))) {
            return false;
        }
    }
    return true;
}
