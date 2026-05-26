#ifndef MODULE_H
#define MODULE_H

#include "data.h"

class Module : public ObjData {
protected:
public:
    std::string name;

    Module(const std::string& moduleName) : ObjData() {
        name = moduleName;
    };

    virtual void update(sf::RenderWindow& window, float deltaTime);

    virtual void render(sf::RenderWindow& window);
};

extern Module* CURR_MODULE;

#endif