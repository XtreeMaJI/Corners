#include "Main.h"
#include "SFML/Graphics.hpp"

using namespace sf;

int main()
{
    LevelManager* LM;
    float WinResol = SQUARE_SIZE * FIELD_SIZE;

    RenderWindow window(VideoMode(WinResol, WinResol), "Corners");

    LM = new LevelManager(&window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            LM->HandleEvent(event);
        }
        LM->Update();
        window.clear();
        LM->RedrawWindow();
        window.display();
    }

    delete LM;
	return 0;
}