#include "Game.h"
#include "Controller.h"
#include "View.h"

#include "Direction.h"

int main() {
    Game game(4);
    View view(&game);
    Controller controller(&game, &view);
    controller.run();
}
