#include "program.h"
#include "menu.h"
#include "font_manager.h"
#include "texture_manager.h"
#include "sprite_manager.h"
#include "module.h"

// Globals
std::stack<Menu> MENUS;
Module* CURR_MODULE;
ProgramState CURR_PROGRAM_STATE;
// ...

void InitProgram() {
    // create the window

    sf::RenderWindow window(sf::VideoMode({WIN_WIDTH, WIN_HEIGHT}), "My window");

    sf::Font* default_font = FontManager::loadFont("default", "myfont.ttf");

    if(default_font == nullptr){
        std::cout << "FONT LOAD FAILED!!!";
    }
 
    std::filesystem::path mainMenuFilePath = "data/menus/main.csv";
    Menu mainMenu = LoadMenu(mainMenuFilePath);

    sf::Texture* worldTexture = TextureManager::loadTexture("world", "world.png");
    sf::Sprite* worldSprite = new sf::Sprite(*worldTexture);

    worldSprite->setPosition({WIN_WIDTH/2, WIN_HEIGHT/2});
    sf::FloatRect bounds = worldSprite->getLocalBounds();
    worldSprite->setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});

    SpriteManager::addSprite("world", worldSprite, mainMenu.data.getId());

    MENUS.push(mainMenu);

    CURR_PROGRAM_STATE = ProgramState::MENU;

    ProgramLoop(window);
};

void RenderProgram(sf::RenderWindow& window) 
{
    // clear the window with black color
    window.clear(sf::Color::Black);

    // == Program Loop ==>
    if (CURR_PROGRAM_STATE == ProgramState::MENU) 
    {
        RenderMenu(window, MENUS.top());
    }
    else if (CURR_PROGRAM_STATE == ProgramState::MODULE)
    {
        CURR_MODULE->render(window);
    }

    // end the current frame
    window.display();
}

void UpdateProgram(sf::RenderWindow& window, float deltaTime)
{
       
    // == Program Loop ==>
    if (CURR_PROGRAM_STATE == ProgramState::MENU) 
    {
        UpdateMenu(window, MENUS.top(), deltaTime);
    }
    else if (CURR_PROGRAM_STATE == ProgramState::MODULE)
    {
        CURR_MODULE->update(window, deltaTime);
    }
 
    // Pass event callbacks
    window.handleEvents(
        [&](const sf::Event::Closed& closed) { 
            onClose(window, closed); 
        },
        [&](const sf::Event::KeyPressed keyPressed) {
            onKeyPressed(window, keyPressed);
        },
        [&](const sf::Event::KeyReleased keyReleased) {
            onKeyReleased(window, keyReleased);
        },
        [&](const sf::Event::MouseWheelScrolled mouseWheelScrolled) {
            onMouseWheelScrolled(window, mouseWheelScrolled);
        },
        [&](const sf::Event::MouseButtonPressed mouseButtonPressed) {
            onMouseButtonPressed(window, mouseButtonPressed);
        },
        [&](const sf::Event::MouseMoved mouseMoved) {
            onMouseMoved(window, mouseMoved);
        },
        [&](const sf::Event::Resized resized) {
            onResized(window, resized);
        } 
    );
}

void ProgramLoop(sf::RenderWindow& window) 
{
    // Target frame rate
    auto timeBetweenFrames = std::chrono::microseconds(std::chrono::seconds(1)) / TARGET_FRAME_RATE;
    auto targetFrameTime = std::chrono::steady_clock::now();

    float currentTime, deltaTime, frameDiff, dtime, cdtime;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        currentTime = clock();

        UpdateProgram(window, deltaTime/1000.f);

        RenderProgram(window);
 
        // <== Program Loop ==

        // Use sleep_until to reach target frame time (does nothing if frame time is already reached)
        targetFrameTime += timeBetweenFrames;     // calculate target point in time
        std::this_thread::sleep_until(targetFrameTime);  // sleep until that time point

        // Target frame time calculation
        deltaTime = clock() - currentTime;

        std::cout<<"CTIME: " <<currentTime<<std::endl<<"DTIME: "<<deltaTime<<std::endl;
        // std::cout<<"dtime: " <<dtime<<std::endl<<"cdtime: "<<cdtime<<std::endl;
    }
};