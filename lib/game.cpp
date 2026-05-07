#include "game.h"
#include "menu.h"

// Globals
std::stack<Menu> MENUS;
GameState CURR_GAME_STATE;
// ...

void InitGame() {
    // create the window
    sf::RenderWindow window(sf::VideoMode({WIN_WIDTH, WIN_HEIGHT}), "My window");
    std::filesystem::path mainMenuFilePath = "data/menus/main.csv";
    Menu mainMenu = LoadMenu(mainMenuFilePath);

    // Init event globals
    MENUS.push(mainMenu);// Menu { 0, {}, testMenuBackground };

    CURR_GAME_STATE = GameState::MENU;

    GameLoop(window);
};

void GameLoop(sf::RenderWindow& window) 
{
    // Target frame rate
    auto time_between_frames = std::chrono::microseconds(std::chrono::seconds(1)) / TARGET_FRAME_RATE;
    auto target_frame_time = std::chrono::steady_clock::now();

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // 
        DWORD current_time, delta_time;
        current_time = clock();
         
        // == Game Loop ==>

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

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);
        RenderMenu(window, MENUS.top());
        
        // end the current frame
        window.display();

        // <== Game Loop ==

        // Target frame time calculation
        delta_time = current_time - clock() / (double) CLOCKS_PER_SEC;

        // Use sleep_until to reach target frame time (does nothing if frame time is already reached)
        target_frame_time += time_between_frames;     // calculate target point in time
        std::this_thread::sleep_until(target_frame_time);  // sleep until that time point
    }
};