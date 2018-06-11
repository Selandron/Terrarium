#include <SFML/Graphics.hpp>
#include "resourcemanager.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    window.setFramerateLimit(144);

    tr::ResourceManager * resMan = tr::ResourceManager::GetInstance();
    resMan->LoadFromFileXML("index.xml");
    resMan->PrintManager();
    resMan->ClearScope("main_scope");
    resMan->LoadFromFileXML("index.xml", "second_scope");
    resMan->PrintManager();

    sf::CircleShape shape(100.f);
    shape.setTexture(_GET_TEXTURE("chaud"));

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}