#pragma once

#include "Field.h"
#include "IViewer.h"

class Viewer: public IViewer {
    protected:
        Field* field;

    public:
        Viewer(Field* field);

        Field* getField();

        void printWin() = 0;
        void printLoss() = 0;
        void show() = 0;
};
