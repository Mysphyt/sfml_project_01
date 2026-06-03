#include <cmath>

#include "sprite_chopper.h"

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
        currAnimIndex(0),
        currVertIndex(0),
        spriteSheetName(textureName),
        activeVertIndex(-1),
        animation(textureName)
{
    positionText.setString("0, 0");
    positionText.setCharacterSize(16);
    positionText.setPosition({5,5});
    positionText.setFillColor({250,250,250});

    animNumText.setString(std::to_string(currAnimIndex));
    animNumText.setCharacterSize(16);
    animNumText.setPosition({5,20});
    animNumText.setFillColor({250,250,250});

    sf::Texture* testTexture = TextureManager::loadTexture(textureName, textureFile);
    sf::Sprite* testSprite = new sf::Sprite(*testTexture);

    testSprite->setPosition({0,0});

    sf::Vector2u testTextureSize = testTexture->getSize();

    // Scale the test texture to the curr resolution
    scaleX = static_cast<float>(BASE_WIN_WIDTH) / testTextureSize.x;
    scaleY = static_cast<float>(BASE_WIN_HEIGHT) / testTextureSize.y;

    std::cout << "SCALE... " << scaleX << ", " << scaleY << std::endl;

    testSprite->setScale({scaleX, scaleY});    
    SpriteManager::addSprite(textureName, testSprite, getId());

    // Resize the curr window to the size of the loaded texture
    // TODO: determine if this is necessary or if the sprite can be scaled & use global coordinates
    sf::Vector2u resized = testTexture->getSize();

    sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized));

    // TODO: should call centralized event handling method of Module
    window.close();
    window.create(sf::VideoMode({static_cast<unsigned int>(visibleArea.size.x), static_cast<unsigned int>(visibleArea.size.y)}), "window"); 
    window.setView(sf::View(sf::FloatRect({0.f, 0.f}, {BASE_WIN_WIDTH, BASE_WIN_HEIGHT})));
    window.setFramerateLimit(60);

    loadSpriteData();
}

std::vector<std::vector<sf::RectangleShape>> SpriteChopper::getAnimRects(bool saving)
{
    std::vector<std::vector<sf::RectangleShape>> newAnimRects = {};
    for (int animIt = 0; animIt < spriteSheetAnimationVertices.size(); animIt++) // For each animation
    {
        newAnimRects.push_back({});
        auto animVerts = spriteSheetAnimationVertices[animIt];

        sf::Vector2i anchorVert;
        if (animVerts.size() > 0)
        {
            anchorVert = animVerts[0];
        }
        else
        {
            continue;
        }

        for (int vertIt = 0; vertIt < animVerts.size(); vertIt++)
        {
            sf::Vector2i currAnimVert, nextAnimVert = {0,0};
            float rectWidth, rectHeight, rectPosX, rectPosY = 0;

            if(vertIt < animVerts.size() - 1) // Not the last index
            {
                currAnimVert = animVerts[vertIt];
                nextAnimVert = animVerts[vertIt+1];
            }
            else if(!(saving || animIt != currAnimIndex) && activeVertIndex == -1) 
            {
                // Draw the "next" rect to the current mouse position
                currAnimVert = animVerts[vertIt];
                nextAnimVert = currMousePos;
            }
            else
            {
                continue;
            }

            rectWidth = nextAnimVert.x - currAnimVert.x;
            rectHeight = anchorVert.y - nextAnimVert.y;

            rectPosX = currAnimVert.x;
            rectPosY = nextAnimVert.y;

            int rectOutlineWidth = 2;
            sf::RectangleShape newAnimRect({rectWidth, rectHeight});
            newAnimRect.setPosition({rectPosX, rectPosY});
            newAnimRect.setFillColor({0,0,0,0}); // Transparent fill
            newAnimRect.setOutlineThickness(rectOutlineWidth);
            if (animIt == currAnimIndex)
                newAnimRect.setOutlineColor(TRANSPARENT_GREEN);
            else
                newAnimRect.setOutlineColor(TRANSPARENT_TEAL);
            newAnimRects[animIt].push_back(newAnimRect);
        }
    }
    return newAnimRects;
}


void SpriteChopper::update(sf::RenderWindow& window, float deltaTime) 
{
    animation.Update(window, deltaTime);
}

void SpriteChopper::render(sf::RenderWindow& window) 
{
    sf::RectangleShape yMouseLineRect({0,BASE_WIN_HEIGHT});
    sf::RectangleShape xMouseLineRect({BASE_WIN_WIDTH,0});

    yMouseLineRect.setPosition({currMousePos.x,0});
    xMouseLineRect.setPosition({0,currMousePos.y});

    yMouseLineRect.setOutlineColor({255,0,0,100});
    xMouseLineRect.setOutlineColor({0,0,255,100});

    yMouseLineRect.setOutlineThickness(1);
    xMouseLineRect.setOutlineThickness(1);

    yMouseLineRect.setFillColor({0,0,0});
    xMouseLineRect.setFillColor({0,0,0});

    std::vector<sf::CircleShape> vertCircles;
    activeVertIndex = -1;
    for(int animIndex = 0; animIndex < spriteSheetAnimationVertices.size(); animIndex++)
    {
        for(int vertIndex = 0; vertIndex < spriteSheetAnimationVertices[animIndex].size(); vertIndex++)
        {
            sf::Vector2i vert = spriteSheetAnimationVertices[animIndex][vertIndex];
            sf::CircleShape vertCircle(4.f);    
            float radius = vertCircle.getRadius();
            vertCircle.setPosition({vert.x, vert.y});

            bool vertContainsMouseX = (currMousePos.x - 5.f >= vert.x) && (currMousePos.x + 5.f <= vert.x);
            bool vertContainsMouseY = (currMousePos.y - 5.f >= vert.y) && (currMousePos.y + 5.f <= vert.y);

            // TODO: move circle logic to update when the mouse moves, not every frame
            if((vertContainsMouseX && vertContainsMouseY) && currAnimIndex == animIndex)
            {
                vertCircle.setFillColor({255,255,255});
                activeVertIndex=vertIndex;
            }
            else
            {
                vertCircle.setFillColor(PINK);
                animNumText.setString(std::to_string(currAnimIndex));
            }
            vertCircle.setOrigin({radius, radius});
            vertCircles.push_back(vertCircle);
        }
    }
    animNumText.setString(std::to_string(currAnimIndex) + " : " + std::to_string(activeVertIndex));

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


    for(auto& sprite : SpriteManager::getObjSpriteMap(getId()))
    {
        window.draw(*sprite.second);
    }

    for(auto& circle : vertCircles)
    {
        window.draw(circle);
    }

    window.draw(xMouseLineRect);
    window.draw(yMouseLineRect);
    window.draw(positionText);
    window.draw(animNumText);

    if(animation.spriteSheet != nullptr && animation.animFrameRects.size() > 0 && animation.animFrameRects[animation.animIt].size() > 0)
    {
        window.draw(*animation.spriteSheet);
    }
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
        case sf::Keyboard::Scancode::D: // Next animation
        {
            if(spriteSheetAnimationVertices[currAnimIndex].size() > 0)
                spriteSheetAnimationVertices[currAnimIndex].pop_back();
            animRects = getAnimRects(false);
            break;
        }
        case sf::Keyboard::Scancode::N: // Next animation
        {
            // Update the animation index
            if(currAnimIndex >= spriteSheetAnimationVertices.size() -1 && spriteSheetAnimationVertices[currAnimIndex].size() == 0)
            {
                break;
            }

            currAnimIndex++;
            animNumText.setString(std::to_string(currAnimIndex)); 

            animation.animIt = currAnimIndex;

            // Add placeholder element to data vectors
            spriteSheetAnimationVertices.push_back({});
            animRects = getAnimRects(false);

            break;
        }
        case sf::Keyboard::Scancode::P: // Next animation
        {
            // Update the animation index
            if(currAnimIndex > 0)
                currAnimIndex--;
            else
                break;
                       
            animNumText.setString(std::to_string(currAnimIndex)); 

            // Add placeholder element to data vectors
            spriteSheetAnimationVertices.push_back({});
            animRects = getAnimRects(false);

            break;
        }
        case sf::Keyboard::Scancode::F:
        {
            break;
        }
        case sf::Keyboard::Scancode::V:
        {
            break;
        }
        case sf::Keyboard::Scancode::S:
        {
            saveSpriteData();
            animation = SpriteSheetAnimation(spriteSheetName);
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

void SpriteChopper::onMouseButtonReleased (sf::RenderWindow &window, const sf::Event::MouseButtonReleased& mouseButtonReleased)
{
}

void SpriteChopper::onMouseButtonPressed (sf::RenderWindow &window, const sf::Event::MouseButtonPressed& mouseButtonPressed)
{
    if(activeVertIndex > 0)
    {
        return;
    }

    animNumText.setString(std::to_string(currAnimIndex));

    if(currAnimIndex >= spriteSheetAnimationVertices.size())
    {
        spriteSheetAnimationVertices.push_back({});
    }

    spriteSheetAnimationVertices[currAnimIndex].push_back(currMousePos);

    animRects = getAnimRects(false);
}

void SpriteChopper::onMouseMoved (sf::RenderWindow &window, const sf::Event::MouseMoved& mouseMoved)
{

    sf::Vector2f mouseWorldCoords = window.mapPixelToCoords(mouseMoved.position);
    // int roundingFactor = 5;
    // // Convert to double for rounding, then back to integer
    // int roundedX = std::round(static_cast<double>(mouseWorldCoords.x) / roundingFactor) * roundingFactor;
    // int roundedY = std::round(static_cast<double>(mouseWorldCoords.y) / roundingFactor) * roundingFactor;

    currMousePos.x = mouseWorldCoords.x; 
    currMousePos.y = mouseWorldCoords.y; // sf::Vector2i({roundedX,roundedY});

    positionText.setString(std::to_string(currMousePos.x)+","+std::to_string(currMousePos.y));

    if(activeVertIndex >= 0 && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        spriteSheetAnimationVertices[currAnimIndex][activeVertIndex] = currMousePos;
        animRects = getAnimRects(true);
    }
    else if(animRects.size() > 0)
    {
        animRects = getAnimRects(false);
    }
}

void SpriteChopper::loadSpriteData() 
{
    std::unordered_map<std::string, std::vector<std::string>> spriteDataRaw = LoadDataCSV("data/textures/"+spriteSheetName+"_metadata");
    for(const auto& animDataStr : spriteDataRaw)
    {
        int animNum = stoi(animDataStr.first);

        spriteSheetAnimationVertices.push_back({});
        std::vector<std::string> animFrames = SplitString(animDataStr.second[0], DATA_DELIM);

        int vertNum = 0;
        for(const auto& rectDataStr : animFrames) 
        {
            std::vector<std::string> rectData = SplitString(rectDataStr, ',');
            // 
            int animX = stoi(rectData[2])*scaleX;
            int animY = stoi(rectData[3])*scaleY;
            if (vertNum == 0)
            {
                // First vertex is the bottom-left corner of each animation, add height to Y for "anchor" vertex
                spriteSheetAnimationVertices[animNum].push_back({animX,animY+(stoi(rectData[1])*scaleY)});
            }

            // Vertex is the top-right corner of each frame
            animX+=stoi(rectData[0])*scaleX;

            spriteSheetAnimationVertices[animNum].push_back({animX,animY});

            vertNum++;
        }
    }
    if (spriteSheetAnimationVertices.size() > 0)
    {
        currAnimIndex = spriteSheetAnimationVertices.size() - 1;
    }
    else
    {
        currAnimIndex = 0;
    }
    animRects = getAnimRects(false);
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
                std::string frameRectW = std::to_string(static_cast<int>(frameRectSize.x/scaleX));
                std::string frameRectH = std::to_string(static_cast<int>(frameRectSize.y/scaleY));

                auto frameRectPos = frameRect.getPosition();
                std::string frameRectX = std::to_string(static_cast<int>(frameRectPos.x/scaleX));
                std::string frameRectY = std::to_string(static_cast<int>(frameRectPos.y/scaleY));

                std::string animString = '|' + frameRectW + ',' + frameRectH + ',' + frameRectX + ',' + frameRectY;
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

