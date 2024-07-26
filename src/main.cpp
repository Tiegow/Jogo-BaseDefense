#include "game.hpp"
// #include <SFML/System.hpp>
#include <iostream>

int main()
{
    Game game;

    //Game loop
    while (game.isRunning())
    {         
        // //Update
        game.update();
        // //Render
        game.render();
    }    

    return 0;
}
