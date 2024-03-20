#pragma once

#include "IEntity.h"
#include "../maze/Maze.h"


class PacMan : public IEntity {
public:
    PacMan();
    void move(Room::Direction direction);
    void draw_into(sf::RenderWindow& window) override;
private:
    sf::CircleShape m_shape;
    inline static TextureAdapter m_texture{config::PACMAN_TEXTURE_PATH};
};