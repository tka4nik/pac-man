#include "PacMan.h"


PacMan::PacMan() {
    m_shape = sf::CircleShape{config::GAME_PACMAN_SIZE / 2, 20};
    m_shape.setOrigin(config::GAME_PACMAN_SIZE / 2, config::GAME_PACMAN_SIZE / 2);
    m_shape.setTexture(&m_texture.get_texture());
}

void PacMan::move(Room::Direction direction) {
    m_location->get_side(direction)->enter(*this);
}

void PacMan::draw_into(sf::RenderWindow &window) {
    m_shape.setPosition(m_location->get_position());
    window.draw(m_shape);

}


