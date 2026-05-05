#include "menu.h"

sf::Font DEFAULT_BUTTON_FONT;

VOID RenderButton(sf::RenderWindow& window, Button button)
{
    window.draw(button.background); 
    window.draw(button.text);
};

VOID RenderMenu(sf::RenderWindow& window, Menu menu) 
{
    // Draw the menu background
    window.draw(menu.background);

    // Render each button
    for (Button menuButton : menu.buttons)
    {
        RenderButton(window, menuButton); 
    }
};

Button GenerateTestButton(
    float xpos, float ypos, 
    float width, float height, 
    int textSize,
    std::string textString, 
    sf::Color textColor,
    sf::Color buttonColor)
{
    // Button1
    sf::Text buttonText(DEFAULT_BUTTON_FONT); // a font is required to make a text object
    // set the string to display
    buttonText.setString(textString);
    // set the character size
    buttonText.setCharacterSize(textSize); // in pixels, not points!
    // set the color
    buttonText.setFillColor(textColor);
    // set the position
    buttonText.setPosition({xpos, ypos});
    // set the text style
    buttonText.setStyle(sf::Text::Bold | sf::Text::Underlined);

    sf::RectangleShape buttonRect = sf::RectangleShape({width,height});
    buttonRect.setPosition({xpos,ypos});
    buttonRect.setFillColor(buttonColor);

    Button button = {
        buttonText,
        buttonRect
    };

    return button;    
}

Menu GenerateTestMenu(float width, float height)
{
    Debug("Generating Test Menu...");

    bool font_loaded = DEFAULT_BUTTON_FONT.openFromFile("myfont.ttf");

    if(!font_loaded){
        std::cout << "FONT LOAD FAILED!!!";
    }

    sf::RectangleShape menuBackground({0,0});
    menuBackground.setSize({width, height});
    menuBackground.setFillColor(sf::Color(50,50,50));

    Button btn1 = GenerateTestButton(
        100,100,
        200,100,
        16,
        "Btn1",
        sf::Color::Black,
        sf::Color::Red
    );
    
    Button btn2 = GenerateTestButton(
        100,200,
        200,100,
        16,
        "Btn2",
        sf::Color::Black,
        sf::Color::Blue
    );

    Button btn3 = GenerateTestButton(
        100,300,
        200,100,
        16,
        "Btn3",
        sf::Color::Black,
        sf::Color::Green
    );

    Debug("Menu");
    std::list<Button> menuBtns{btn1, btn2, btn3};

    Menu menu = {menuBackground,menuBtns};
    
    Debug("Return");
    return menu;
};