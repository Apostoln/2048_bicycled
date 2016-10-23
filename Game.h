#pragma once

#include "Field.h"
#include "Viewer.h"
#include "Listener.h"
#include "Direction.h"

class Listener;

class Game {
    private:
        Field* field;
        Viewer* viewer;
        Listener* listener;
        int score = 0;

    public:
        Game(Viewer* viewer, Listener* listener);
        Game(Field* field, Viewer* viewer, Listener* listener);
        Field* getField();

        void run();
        void start();
        void turn(Direction direction);

        void update();
        void win();
        void loss();

        bool isWin();
        bool isLoss();
};
