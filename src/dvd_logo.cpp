#include "dvd_logo.h"
#include "sprite_manager.h"
#include "texture_manager.h"
#include "globals.h"

DvDLogo::DvDLogo(const std::string& moduleName) : Module(moduleName) 
{
    logoVelocity = {1,1};

    sf::Texture* dvdTexture = TextureManager::loadTexture(STR_DVD_LOGO, "dvd.png");
    sf::Sprite* dvdSprite = new sf::Sprite(*dvdTexture);

    dvdSprite->setPosition({0,0});
    dvdSprite->setScale({0.25f, 0.25f});

    sf::Texture* crtTexture = TextureManager::loadTexture(STR_CRT_BACKGROUND, "crt.jpg");
    sf::Sprite* crtSprite = new sf::Sprite(*crtTexture);

    crtSprite->setPosition({0,0});

    sf::Vector2u crtTextureSize = crtTexture->getSize();

    // Scale the crt texture to the current resolution
    float scaleX = static_cast<float>(BASE_WIN_WIDTH) / crtTextureSize.x;
    float scaleY = static_cast<float>(BASE_WIN_HEIGHT) / crtTextureSize.y;

    crtSprite->setScale({scaleX, scaleY});    

    // Add sprites in DRAW ORDER
    SpriteManager::addSprite(STR_CRT_BACKGROUND, crtSprite, getId());
    SpriteManager::addSprite(STR_DVD_LOGO, dvdSprite, getId());
}

void DvDLogo::update(sf::RenderWindow& window, float DeltaTime) 
{
    sf::Sprite* dvdLogoSprite = SpriteManager::getObjSpriteMap(getId())[STR_DVD_LOGO];
    sf::FloatRect spriteBounds = dvdLogoSprite->getGlobalBounds();
    sf::Vector2f spritePosition = dvdLogoSprite->getPosition();
    sf::Vector2f newSpritePosition = {spritePosition.x + logoVelocity.x, spritePosition.y + logoVelocity.y};
    
    if (newSpritePosition.x < 0 || (newSpritePosition.x + spriteBounds.size.x) >= BASE_WIN_WIDTH) { 
        logoVelocity.x *= -1;
    }
    if (newSpritePosition.y < 0 || (newSpritePosition.y + spriteBounds.size.y) >= BASE_WIN_HEIGHT) { 
        logoVelocity.y *= -1;
    }

    dvdLogoSprite->setPosition({spritePosition.x+logoVelocity.x, spritePosition.y+logoVelocity.y});
}

void DvDLogo::render(sf::RenderWindow& window) 
{
    for(auto& sprite : SpriteManager::getObjSpriteMap(getId()))
    {
        window.draw(*sprite.second);
    }
}