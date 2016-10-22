#pragma once

#include "conio.h"

#include "IListener.h"
#include "Direction.h"

class Listener: public IListener {
    private:
        Game* game;

        Direction getDirection();

    public:
        Listener() = default;
        Listener(Game* game);

        void setTarget(Game* game);
        void listen();

        void onPressed(Direction direction);
};
