#pragma once

#include <SFML/Graphics.hpp>
#include <iosfwd>


class IWindowKeeper {
public:
    virtual ~IWindowKeeper() = default;
protected:
    IWindowKeeper(sf::VideoMode mode, const std::string& title) : m_window(mode, title) {};
    virtual void event_handling() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
protected:
    sf::RenderWindow m_window;
};