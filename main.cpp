#include "Game.h"
#include "Direction.h"
#include "ConsoleListener.h"
#include "ConsoleViewer.h"

const int FIELD_SIZE = 4;

int main() {
    ConsoleListener listener;
    Field field(FIELD_SIZE);
    ConsoleViewer viewer(&field);

    Game game(&viewer, &listener);
    game.run();

}
