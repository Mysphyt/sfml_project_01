#ifndef DVD_LOGO_H
#define DVD_LOGO_H

#include "module.h"

class DvDLogo : public Module {
public:    
    DvDLogo(const std::string& moduleName);

    void update(sf::RenderWindow& window, float deltaTime) override;

    void render(sf::RenderWindow& window) override;
protected:
    const std::string STR_CRT_BACKGROUND = "crt_background";
    const std::string STR_DVD_LOGO = "dvd_logo";

    sf::Vector2i logoVelocity;
};

#endif