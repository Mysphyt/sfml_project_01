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
std::map<std::string, std::map<std::string, std::string>> TEXTURE_DATA;

// ...

void InitProgram() {
    // create the window

    sf::RenderWindow window(sf::VideoMode({BASE_WIN_WIDTH, BASE_WIN_HEIGHT}), "window");

    sf::Font* default_font = FontManager::loadFont("default", "myfont.ttf");

    if(default_font == nullptr){
        std::cout << "FONT LOAD FAILED!!!";
    }
 
    std::filesystem::path mainMenuFilePath = "data/menus/main.csv";
    Menu mainMenu = LoadMenuFromFile(mainMenuFilePath);

    std::cout << "Loaded MainMenu... " << mainMenu.buttons.size() << std::endl;

    sf::Texture* worldTexture = TextureManager::loadTexture("world", "world.png");
    sf::Sprite* worldSprite = new sf::Sprite(*worldTexture);
    worldSprite->setScale({0.7f, 0.7f});

    worldSprite->setPosition({BASE_WIN_WIDTH/2, BASE_WIN_HEIGHT/2});
    sf::FloatRect bounds = worldSprite->getLocalBounds();
    worldSprite->setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});

    SpriteManager::addSprite("world", worldSprite, mainMenu.getId());

    MENUS.push(mainMenu);

    CURR_PROGRAM_STATE = ProgramState::MENU;

    ProgramLoop(window);
};

void RenderProgram(sf::RenderWindow& window) 
{
    // clear the window with black color
    window.clear(sf::Color::Black);

    // sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f({5000, 5000}));
    // window.setView(sf::View(visibleArea));

    // == Program Loop ==>
    if (CURR_PROGRAM_STATE == ProgramState::MENU) 
    {
        MENUS.top().Render(window);
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
        MENUS.top().Update(window, deltaTime);
    }
    else if (CURR_PROGRAM_STATE == ProgramState::MODULE)
    {
        CURR_MODULE->update(window, deltaTime);
    }
 
    // Pass event callbacks
    window.handleEvents(
        [&window](const sf::Event::Closed& closed) { 
            onClose(window, closed); 
        },
        [&window](const sf::Event::KeyPressed keyPressed) {
            onKeyPressed(window, keyPressed);
        },
        [&window](const sf::Event::KeyReleased keyReleased) {
            onKeyReleased(window, keyReleased);
        },
        [&window](const sf::Event::MouseWheelScrolled mouseWheelScrolled) {
            onMouseWheelScrolled(window, mouseWheelScrolled);
        },
        [&window](const sf::Event::MouseButtonPressed mouseButtonPressed) {
            onMouseButtonPressed(window, mouseButtonPressed);
        },
        [&window](const sf::Event::MouseMoved mouseMoved) {
            onMouseMoved(window, mouseMoved);
        },
        [&window](const sf::Event::MouseButtonReleased mouseButtonReleased) {
            onMouseButtonReleased(window, mouseButtonReleased);
        }

        //, TODO: Resize events crash my Linux system
        //[&window](const sf::Event::Resized resized) {
        //    onResized(window, resized);
        //}
    );
}

void ProgramLoop(sf::RenderWindow& window) 
{
    sf::Time t;
    sf::Clock clock;
    window.setFramerateLimit(60);

    // Target frame rate

    // run the program as long as the window is open
    while (window.isOpen())
    {
        clock.restart().asSeconds();

       // currentTime = clock();

        UpdateProgram(window, t.asMilliseconds());

        RenderProgram(window);
 
        // <== Program Loop ==

        t = clock.getElapsedTime();
    }
};
