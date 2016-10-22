#pragma once

class Field;

class IViewer {
    public:
        virtual Field* getField() = 0;
        virtual void printWin() = 0;
        virtual void printLoss() = 0;
        virtual void show() = 0;
};
