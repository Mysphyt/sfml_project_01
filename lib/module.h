#ifndef MODULE_H
#define MODULE_H

#include "data.h"

class Module {
protected:
    ObjData objData;
public:
    Module(const std::string& moduleName) {
        objData = ObjData();
    };

    virtual int getId();

    virtual void update(sf::RenderWindow& window, float deltaTime);

    virtual void render(sf::RenderWindow& window);
};

extern Module* CURR_MODULE;

#endif