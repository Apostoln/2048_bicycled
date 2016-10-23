#pragma once

#include "Listener.h"
#include "Game.h"


Listener::Listener(Game* game):
    game(game) {}

void Listener::setTarget(Game* target) {
    game = target;
}

