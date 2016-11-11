#pragma once

#include "conio.h"

#include "Listenable.h"
#include "Direction.h"
#include "Game.h"

class Listener: public Listenable {
    protected:
        Game* game;

    public:
        Listener() = default;
        Listener(Game* game);
        virtual ~Listener() = default;

        virtual void setTarget(Game* game);
        virtual void listen() = 0;

        virtual void onPressed(Direction direction) = 0;
};
