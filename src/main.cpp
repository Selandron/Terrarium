#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "resourcemanager.hpp"

void benchmarck()
{
    tr::ResourceManager * resMan = tr::ResourceManager::GetInstance(); 

    //std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    //STEP 1 -- LOAD BENCHMARK1 -- SHOULD WORK (result : scope benchmark1 loaded)
    std::cout << "STEP 1 -- LOAD BENCHMARK1 -- SHOULD WORK (result : scope benchmark1 loaded)" << std::endl;
    resMan->LoadFromFileXML("benchmark1.xml");
    resMan->PrintManager();
    std::cout << std::endl;

    //std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    //STEP 2 -- UNLOAD BENCHMARK1 -- SHOULD WORK (result : no resources)
    std::cout << "STEP 2 -- UNLOAD BENCHMARK1 -- SHOULD WORK (result : no resources)" << std::endl;
    resMan->Clear();
    resMan->PrintManager();
    std::cout << std::endl;

    //std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    //STEP 3 -- LOAD BENCHMARK2 -- SHOULD WORK (result : scope benchmark2 loaded)
    std::cout << "STEP 3 -- LOAD BENCHMARK2 -- SHOULD WORK (result : scope benchmark2 loaded)" << std::endl;
    resMan->LoadFromFileXML("benchmark1.xml", "benchmark2");
    resMan->PrintManager();
    std::cout << std::endl;

    //STEP 4 -- LOAD TWO SCOPE -- SHOULD WORK (result : scope benchmark1 & benchmark2 loaded)
    std::cout << "STEP 4 -- LOAD TWO SCOPE -- SHOULD WORK (result : scope benchmark1 & benchmark2 loaded)" << std::endl;
    resMan->LoadFromFileXML("benchmark1.xml", "benchmark1");
    resMan->PrintManager();
    std::cout << std::endl;

    //STEP 5 -- UNLOAD BENCHMARK2 -- SHOULD WORK (result : scope benchmark1 loaded)
    std::cout << "STEP 5 -- UNLOAD BENCHMARK2 -- SHOULD WORK (result : scope benchmark1 loaded)" << std::endl;
    resMan->ClearScope("benchmark2");
    resMan->PrintManager();
    std::cout << std::endl;

    //STEP 6 -- LOAD BENCHMARK3 -- SHOULD WORK BUT WITH FAILURES (result : scope benchmark1 & 3 loaded whithout the errored files)
    std::cout << "STEP 6 -- LOAD BENCHMARK3 -- SHOULD WORK BUT WITH FAILURES (result : scope benchmark1 & 3 loaded whithout the errored files)" << std::endl;
    resMan->LoadFromFileXML("benchmark1.xml", "benchmark3");
    resMan->PrintManager();
    std::cout << std::endl;

    //STEP 7 -- LOAD BENCHMARK4 -- SHOULD WORK BUT WITH FAILURES (result : scope benchmark1 & 3 loaded but not 4)
    std::cout << "STEP 7 -- LOAD BENCHMARK4 -- SHOULD WORK BUT WITH FAILURES (result : scope benchmark1 & 3 loaded but not 4)" << std::endl;
    resMan->LoadFromFileXML("benchmark1.xml", "benchmark4");
    resMan->PrintManager();
    std::cout << std::endl;

    //STEP 8 -- LOAD BENCHMARK5 -- SHOULD WORK BUT WITH FAILURES (result : scope benchmark1 & 3 loaded but not 5)
    std::cout << "STEP 8 -- LOAD BENCHMARK5 -- SHOULD WORK BUT WITH FAILURES (result : scope benchmark1 & 3 loaded but not 5)" << std::endl;
    resMan->LoadFromFileXML("benchmark1.xml", "benchmark5");
    resMan->PrintManager();
    std::cout << std::endl;

    //STEP 9 -- UNLOAD ALL -- SHOULD WORK (result : no resources)
    std::cout << "STEP 9 -- UNLOAD ALL -- SHOULD WORK (result : no resources)" << std::endl;
    resMan->Clear();
    resMan->PrintManager();
    std::cout << std::endl;

}

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
    window.setFramerateLimit(144);

    //benchmarck();

    tr::ResourceManager * resMan = tr::ResourceManager::GetInstance();
    resMan->LoadFromFileXML("benchmark1.xml");

    sf::Texture * texture;
    sf::SoundBuffer * buffer;
    sf::Sound sound;
    sf::Music * music;
    sf::Text text;
    sf::Font * font;
    sf::Sprite sprite;
    try
    {
        texture = _GET_TEXTURE("mud_block_tileset");
        buffer = _GET_SOUNDBUFFER("patakas-world");
        music = _GET_MUSIC("power-bots-loop");
        font = _GET_FONT("arial");
        text.setFont(*font);
        text.setString(*_GET_TEXT("text1", "first-key"));
        sprite.setTexture(*texture);
        sound.setBuffer(*buffer);
        sound.play();
        music->play();
    }
    catch (tr::ResourceNotFoundException & e)
    {
        std::cout << e.what() << std::endl;
    }



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