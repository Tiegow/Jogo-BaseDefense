#include "game.hpp"

int main()
{
    Game game;

    //Game loop
    while (game.isRunning())
    {   
        //Update
        game.update();
        //Render
        game.render();
    }    

    return 0;
}
