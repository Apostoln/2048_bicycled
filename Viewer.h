#pragma once

#include "Field.h"

class Viewer {
    private:
        Field* field;

    public:
        Viewer(Field* field);

        Field* getField();

        void printWin();
        void printLoss();
        void show();
};
