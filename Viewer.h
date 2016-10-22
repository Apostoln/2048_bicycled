#pragma once

#include "Field.h"
#include "IViewer.h"

class Viewer: public IViewer {
    private:
        Field* field;

    public:
        Viewer(Field* field);

        Field* getField();

        void printWin();
        void printLoss();
        void show();
};
