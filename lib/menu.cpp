#include "menu.h"

sf::Font DEFAULT_BUTTON_FONT;

sf::Color ParseColorString(const std::string& colorStr)
{
    std::vector<std::string> menuColorValues = SplitString(colorStr, ',');
    int menuR = stoi(menuColorValues[0]);
    int menuG = stoi(menuColorValues[1]);
    int menuB = stoi(menuColorValues[2]);
    sf::Color menuColor = sf::Color({menuR, menuG, menuB});   
    return menuColor;
};

VOID RenderButton(sf::RenderWindow& window, const Button& button)
{
    window.draw(button.background); 
    window.draw(button.text);
};

VOID RenderMenu(sf::RenderWindow& window, const Menu& menu) 
{
    // Draw the menu background
    window.draw(menu.background);

    // Render each button
    for (Button menuButton : menu.buttons)
    {
        RenderButton(window, menuButton); 
    }
};

Button CreateButton(
    float xpos, float ypos, 
    float width, float height, 
    int textSize,
    const std::string& textString, 
    sf::Color textColor,
    sf::Color buttonColor)
{
    // Button1
    sf::Text buttonText(DEFAULT_BUTTON_FONT); // a font is required to make a text object
    // set the string to display
    buttonText.setString(textString);
    // set the character size
    buttonText.setCharacterSize(16); // in pixels, not points!
    // set the color
    buttonText.setFillColor(textColor);
    // set the position
    buttonText.setPosition({xpos+(width/2), ypos+(height/2)});
    // set the text style
    buttonText.setStyle(sf::Text::Bold | sf::Text::Underlined);

    // Get the local bounds of the text
    sf::FloatRect textBounds = buttonText.getLocalBounds();

    // Set origin to the center of the text
    // buttonText.setOrigin(
    //     {textBounds.position.x + textBounds.size.x / 2.0f,
    //     textBounds.position.y + textBounds.size.y / 2.0f}
    // );

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

    Button btn1 = CreateButton(
        100,100, // position
        200,100, // size
        16,
        "Button 1",
        sf::Color::Black,
        sf::Color::Red
    );
    
    Button btn2 = CreateButton(
        100,220, // position
        200,100, // size
        16,
        "Button 2",
        sf::Color::Black,
        sf::Color::Blue
    );

    Button btn3 = CreateButton(
        100,340, // position 
        200,100, // size
        16,
        "Button 3",
        sf::Color::Black,
        sf::Color::Green
    );

    Debug("Menu");
    std::vector<Button> menuBtns{btn1, btn2, btn3};

    Menu menu = {-1,menuBackground,menuBtns};
    
    Debug("Return");
    return menu;
}

VOID CheckMouseCollisions(Menu& menu, float mouseX, float mouseY)
{
    int buttonIndex = 0;
    menu.activeButtonIndex = -1;
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
            menu.activeButtonIndex = buttonIndex;
            break;
        }
        else {
            btn.text.setFillColor(sf::Color::Black); 
            btn.background.setOutlineColor(sf::Color::Black);
        }

        buttonIndex += 1;
    }
};


Menu LoadMenu(const std::filesystem::path& filePath)
{
    std::unordered_map<std::string, std::vector<std::string>> csvData = LoadDataCSV(filePath);

    std::vector<std::string> menuData = csvData["MENU"];
    std::string menuStr = menuData[0];
    std::vector<std::string> menuDataValues = SplitString(menuStr, DATA_DELIM);

    std::string menuName = menuDataValues[0];
    Debug("Parsing Menu: " + menuName);

    std::string menuColorStr = menuDataValues[1];
    sf::Color menuColor = ParseColorString(menuColorStr);

    std::vector<std::string> buttonData = csvData["BUTTON"]; 
    std::vector<Button> buttons;
    for (std::string buttonStr : buttonData)
    {
        std::vector<std::string> dataValues = SplitString(buttonStr, DATA_DELIM);
        std::string buttonName = dataValues[0];
        Debug("Parsing Button: " + buttonName);
        std::vector<std::string> button_pos = SplitString(dataValues[1], ',');
        std::vector<std::string> button_size = SplitString(dataValues[2], ',');

        int textSize = stoi(dataValues[3]);
        bool centerText = stoi(dataValues[4]);
        bool boldText = stoi(dataValues[5]);
        bool underlineText = stoi(dataValues[6]);

        std::string buttonColorStr = dataValues[7];
        std::string textColorStr = dataValues[8];

        sf::Color buttonColor = ParseColorString(buttonColorStr);
        sf::Color textColor = ParseColorString(textColorStr);

        Button button = CreateButton(
            stoi(button_pos[0]),stoi(button_pos[1]), // position
            stoi(button_size[0]),stoi(button_size[1]), // size
            textSize,
            buttonName,
            textColor,
            buttonColor
        );

        buttons.push_back(button);
    }

    sf::RectangleShape menuBackground({0,0});

    menuBackground.setSize({WIN_WIDTH, WIN_HEIGHT});

    menuBackground.setFillColor(menuColor);

    return Menu({-1, menuBackground, buttons});
}
