#pragma once

#include "Listener.h"

class Game;

class ConsoleListener: public Listener {
    private:
        Direction getDirection();

    public:
        ConsoleListener() = default;
        ConsoleListener(Game*);
        void listen();
        void onPressed(Direction);
};
