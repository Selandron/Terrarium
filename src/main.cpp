#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "resourcemanager.hpp"
#include "gamemanager.hpp"
#include "gamestateloading.hpp"

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
    resMan->Kill();

}

int main()
{
    std::srand(std::time(nullptr));
    tr::GameManager gameManager;
    gameManager.Init();

    gameManager.ChangeState(tr::GameStateLoading::Instance());

    while (gameManager.Running())
    {
        gameManager.HandleEvents();
        gameManager.Update();
        gameManager.Draw();
    }

    gameManager.Cleanup();

    return 0;
}