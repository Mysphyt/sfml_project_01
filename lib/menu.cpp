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
    buttonText.setPosition({xpos+(width/2), ypos+(height/2)});
    // set the text style
    buttonText.setStyle(sf::Text::Bold | sf::Text::Underlined);

    // Get the local bounds of the text
    sf::FloatRect textBounds = buttonText.getLocalBounds();

    // Set origin to the center of the text
    buttonText.setOrigin(
        {textBounds.position.x + textBounds.size.x / 2.0f,
        textBounds.position.y + textBounds.size.y / 2.0f}
    );

    sf::RectangleShape buttonRect = sf::RectangleShape({width,height});
    buttonRect.setPosition({xpos,ypos});
    buttonRect.setFillColor(buttonColor);

    buttonRect.setOutlineThickness(2);
    buttonRect.setOutlineColor(sf::Color::Black);

    Button button = {
        buttonText,
        buttonRect
    };

    return button;    
};

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
        100,100, // position
        200,100, // size
        16,
        "Button 1",
        sf::Color::Black,
        sf::Color::Red
    );
    
    Button btn2 = GenerateTestButton(
        100,220, // position
        200,100, // size
        16,
        "Button 2",
        sf::Color::Black,
        sf::Color::Blue
    );

    Button btn3 = GenerateTestButton(
        100,340, // position 
        200,100, // size
        16,
        "Button 3",
        sf::Color::Black,
        sf::Color::Green
    );

    Debug("Menu");
    std::list<Button> menuBtns{btn1, btn2, btn3};

    Menu menu = {menuBackground,menuBtns};
    
    Debug("Return");
    return menu;
};

VOID CheckMouseCollisions(Menu& menu, float mouseX, float mouseY)
{
    for(Button& btn : menu.buttons) 
    {
        sf::Vector2 btnPos = btn.background.getPosition();
        sf::Vector2 btnSize = btn.background.getSize();

        bool btnContainsX = mouseX >= btnPos.x && mouseX < (btnPos.x + btnSize.x);
        bool btnContainsY = mouseY >= btnPos.y && mouseY < (btnPos.y + btnSize.y);
        if (btnContainsX && btnContainsY)
        {
            btn.text.setFillColor(sf::Color::White); 
            btn.background.setOutlineColor(sf::Color::White);
        }
        else {
            btn.text.setFillColor(sf::Color::Black); 
            btn.background.setOutlineColor(sf::Color::Black);
        }
    } 
};