#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "resourcemanager.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    window.setFramerateLimit(144);

    tr::ResourceManager * resMan = tr::ResourceManager::GetInstance();    
    resMan->LoadFromFileXML("index.xml");
    resMan->PrintManager();

    sf::Sprite sprite;
    sprite.setTexture(*_GET_TEXTURE("wood_tileset"));

    //sf::Music * music = _GET_MUSIC("power-bots-loop");

    //music->play();

    sf::Text text;
    text.setFont(*_GET_FONT("arial"));
    text.setString(*_GET_TEXT("text1", "second-key"));


    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.draw(text);
        window.display();
    }

    return 0;
}