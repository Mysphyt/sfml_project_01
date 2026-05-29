#include <cmath>

#include "sprite_chopper.h"
#include "sprite_manager.h"
#include "texture_manager.h"
#include "font_manager.h"
#include "globals.h"

SpriteChopper::SpriteChopper(
    const std::string& moduleName,
    sf::RenderWindow& window,
    std::string textureName,
    std::string textureFile) : 
        Module(moduleName), 
        positionText(*FontManager::getFont("default")), 
        animNumText(*FontManager::getFont("default")),
        modeText(*FontManager::getFont("default")),
        currAnimIndex(0),
        currVertIndex(0),
        spriteSheetName(textureName),
        currMode(ChopperMode::SET_ANIM_FLOOR)
{
    positionText.setString("0, 0");
    positionText.setCharacterSize(16);
    positionText.setPosition({5,5});
    positionText.setFillColor({250,250,250});

    animNumText.setString(std::to_string(currAnimIndex));
    animNumText.setCharacterSize(16);
    animNumText.setPosition({5,20});
    animNumText.setFillColor({250,250,250});

    modeText.setString("Mode <SET_ANIM_FLOOR> Anim #"+std::to_string(currAnimIndex));
    modeText.setCharacterSize(16);
    modeText.setPosition({5,40});
    modeText.setFillColor({250,250,250});

    sf::Texture* testTexture = TextureManager::loadTexture(textureName, textureFile);
    sf::Sprite* testSprite = new sf::Sprite(*testTexture);

    testSprite->setPosition({0,0});

    sf::Vector2u testTextureSize = testTexture->getSize();

    // Scale the test texture to the curr resolution
    float scaleX = static_cast<float>(BASE_WIN_WIDTH) / testTextureSize.x;
    float scaleY = static_cast<float>(BASE_WIN_HEIGHT) / testTextureSize.y;

    testSprite->setScale({scaleX, scaleY});    
    SpriteManager::addSprite(textureName, testSprite, getId());

    // Resize the curr window to the size of the loaded texture
    // TODO: determine if this is necessary or if the sprite can be scaled & use global coordinates
    sf::Vector2u resized = testTexture->getSize();

    sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized));

    window.close();
    window.create(sf::VideoMode({static_cast<unsigned int>(visibleArea.size.x), static_cast<unsigned int>(visibleArea.size.y)}), "window");
    window.setView(sf::View(sf::FloatRect({0.f, 0.f}, {BASE_WIN_WIDTH, BASE_WIN_HEIGHT})));
}

std::vector<std::vector<sf::RectangleShape>> SpriteChopper::getAnimRects(bool saving)
{
    std::vector<std::vector<sf::RectangleShape>> newAnimRects = {};
    for (int animIt = 0; animIt < spriteSheetAnimationFloors.size(); animIt++) // For each animation
    {
        newAnimRects.push_back({});
        auto animVerts = spriteSheetAnimationVertices[animIt];

        for (int vertIt = 0; vertIt < animVerts.size(); vertIt++)
        {
            sf::Vector2i currAnimVert, nextAnimVert = {0,0};
            float rectWidth, rectHeight, rectPosX, rectPosY = 0;

            if(vertIt < animVerts.size() - 1) // Not the last index
            {
                currAnimVert = animVerts[vertIt];
                nextAnimVert = animVerts[vertIt+1];
            }
            else
            {
                if(saving || currMode == ChopperMode::SET_ANIM_FLOOR || animIt != currAnimIndex)
                {
                    // Ignore if saving, setting floor, or not the current Animation
                    continue;
                }
                // Draw the "next" rect to the current mouse position
                currAnimVert = animVerts[vertIt];
                nextAnimVert = currMousePos;
            }

            rectWidth = nextAnimVert.x - currAnimVert.x;
            rectHeight = spriteSheetAnimationFloors[animIt] - nextAnimVert.y;

            rectPosX = currAnimVert.x;
            rectPosY = nextAnimVert.y;

            int rectOutlineWidth = 2;
            sf::RectangleShape newAnimRect({rectWidth-rectOutlineWidth, rectHeight});
            newAnimRect.setPosition({rectPosX, rectPosY});
            newAnimRect.setFillColor({0,0,0,0}); // Transparent fill
            newAnimRect.setOutlineThickness(rectOutlineWidth);
            newAnimRect.setOutlineColor({0,255,100,150});
            newAnimRects[animIt].push_back(newAnimRect);
        }
    }
    return newAnimRects;
}


void SpriteChopper::update(sf::RenderWindow& window, float DeltaTime) 
{

}

void SpriteChopper::render(sf::RenderWindow& window) 
{
    for(auto& sprite : SpriteManager::getObjSpriteMap(getId()))
    {
        window.draw(*sprite.second);
    }


    sf::RectangleShape yMouseLineRect({0,BASE_WIN_HEIGHT});
    sf::RectangleShape xMouseLineRect({BASE_WIN_WIDTH,0});

    yMouseLineRect.setPosition({currMousePos.x,0});
    xMouseLineRect.setPosition({0,currMousePos.y});

    yMouseLineRect.setOutlineColor({255,0,0});
    xMouseLineRect.setOutlineColor({0,0,255});

    yMouseLineRect.setOutlineThickness(1);
    xMouseLineRect.setOutlineThickness(1);

    yMouseLineRect.setFillColor({0,0,0});
    xMouseLineRect.setFillColor({0,0,0});

    if (animRects.size() > 0)
    {
        for (int animIt=0; animIt < animRects.size(); animIt++)
        {
            for (auto animRect : animRects[animIt])
            {
                auto rectPos = animRect.getPosition();
                auto rectSize = animRect.getSize();

                sf::RectangleShape midRect({0, rectSize.y});
                midRect.setPosition({rectPos.x+(rectSize.x/2),rectPos.y});
                midRect.setFillColor({0,0,0,0});
                midRect.setOutlineColor({255,0,255,100});
                midRect.setOutlineThickness(1);

                window.draw(midRect);
                window.draw(animRect);
            }
        }
    }

    window.draw(xMouseLineRect);
    window.draw(yMouseLineRect);
    window.draw(positionText);
    window.draw(animNumText);
    window.draw(modeText);
}

void SpriteChopper::onClose (sf::RenderWindow& window, const sf::Event::Closed& closed)
{
}

void SpriteChopper::onResized (sf::RenderWindow& window, const sf::Event::Resized& resized)
{
}

void SpriteChopper::onKeyPressed (sf::RenderWindow &window, const sf::Event::KeyPressed& keyPressed)
{
    switch(keyPressed.scancode)
    {
        case sf::Keyboard::Scancode::N: // Next animation
        {
            // Update the animation index
            currAnimIndex++;
            animNumText.setString(std::to_string(currAnimIndex)); 
            currMode = ChopperMode::SET_ANIM_FLOOR;
            modeText.setString("Mode <SET_ANIM_FLOOR> Anim#"+std::to_string(currAnimIndex));

            // Add placeholder element to data vectors
            spriteSheetAnimationFloors.push_back(0);
            spriteSheetAnimationXBounds.push_back(0);
            spriteSheetAnimationVertices.push_back({});
            animRects.push_back({});
            break;
        }
        case sf::Keyboard::Scancode::F:
        {
            currMode = ChopperMode::SET_ANIM_FLOOR; 
            modeText.setString("Mode <SET_ANIM_FLOOR> Anim#"+std::to_string(currAnimIndex));
            break;
        }
        case sf::Keyboard::Scancode::V:
        {
            currMode = ChopperMode::SET_NEXT_ANIM_VERT; 
            modeText.setString("Mode <SET_ANIM_VERT> Vert#"+std::to_string(currVertIndex));
            break;
        }
        case sf::Keyboard::Scancode::S:
        {
            saveSpriteData();
            break;
        }
        default:
        {
            break;
        }
    }
}

void SpriteChopper::onKeyReleased (sf::RenderWindow &window, const sf::Event::KeyReleased& keyReleased)
{
}

void SpriteChopper::onMouseWheelScrolled (sf::RenderWindow &window, const sf::Event::MouseWheelScrolled& mouseWheelScrolled)
{
}

void SpriteChopper::onMouseButtonPressed (sf::RenderWindow &window, const sf::Event::MouseButtonPressed& mouseButtonPressed)
{
    if(currAnimIndex >= spriteSheetAnimationFloors.size())
    {
        spriteSheetAnimationFloors.push_back(0);
        spriteSheetAnimationXBounds.push_back(0);
        spriteSheetAnimationVertices.push_back({});
        animRects.push_back({});
    }
    switch(currMode)
    {
        case ChopperMode::SET_ANIM_FLOOR:
        {
            spriteSheetAnimationFloors[currAnimIndex] = currMousePos.y;
            break;
        }
        case ChopperMode::SET_NEXT_ANIM_VERT:
        {
            spriteSheetAnimationVertices[currAnimIndex].push_back(currMousePos);
            int numVerts = spriteSheetAnimationVertices[currAnimIndex].size();
            modeText.setString("Mode <SET_ANIM_VERT> Vert# "+std::to_string(numVerts));
            animRects = getAnimRects(false);
            break;
        }
        default:
        {
            break;
        }
    }
}

void SpriteChopper::onMouseMoved (sf::RenderWindow &window, const sf::Event::MouseMoved& mouseMoved)
{
    sf::Vector2f mouseWorldCoords = window.mapPixelToCoords(mouseMoved.position);
    int roundingFactor = 5;
    // Convert to double for rounding, then back to integer
    int roundedX = std::round(static_cast<double>(mouseWorldCoords.x) / roundingFactor) * roundingFactor;
    int roundedY = std::round(static_cast<double>(mouseWorldCoords.y) / roundingFactor) * roundingFactor;
    positionText.setString(std::to_string(roundedX)+","+std::to_string(roundedY));

    currMousePos = sf::Vector2i({roundedX,roundedY});

    if(animRects.size() > 0)
    {
        animRects = getAnimRects(false);
    }
}

void SpriteChopper::saveSpriteData() 
{
    std::filesystem::path metadataFilePath = "data/textures/"+spriteSheetName+"_metadata";

    std::cout<<"Writing to file " <<metadataFilePath<<std::endl;
    std::ofstream file(metadataFilePath);

    std::vector<std::string> animDataStrings;

    if (file.is_open()) {
        animRects = getAnimRects(true);
        for (int animIt = 0; animIt < animRects.size(); animIt++) 
        {
            animDataStrings.push_back(std::to_string(animIt)+":");
            for (int rectIt = 0; rectIt < animRects[animIt].size(); rectIt++)
            {
                sf::RectangleShape frameRect = animRects[animIt][rectIt];

                auto frameRectSize = frameRect.getSize();
                std::string frameRectW = std::to_string(static_cast<int>(frameRectSize.x));
                std::string frameRectH = std::to_string(static_cast<int>(frameRectSize.y));

                auto frameRectPos = frameRect.getPosition();
                std::string frameRectX = std::to_string(static_cast<int>(frameRectPos.x));
                std::string frameRectY = std::to_string(static_cast<int>(frameRectPos.y));

                std::string animString = '|' + frameRectW + ',' + frameRectH + '|' + frameRectX + ',' + frameRectY;
                animDataStrings[animIt] += animString;
                std::cout << animString << std::endl;
            }
        }
        for(auto animString : animDataStrings)
        {
            file << animString << std::endl;
        }
        file.close();
    } 
    else 
    {
        std::cerr << "Unable to open file\n";
    }
}