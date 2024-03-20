#include "IEntity.h"
#include "../maze/Maze.h"

#include <SFML/Graphics.hpp>


Food::Food() {
    m_shape = sf::CircleShape(config::GAME_FOOD_SIZE, 30);
    m_shape.setOrigin(config::GAME_FOOD_SIZE, config::GAME_FOOD_SIZE);
    m_shape.setTexture(&m_texture.get_texture());
}

std::unique_ptr<IStaticEntity> Food::clone() const {
    return std::make_unique<Food>(*this);
}

void Food::draw_into(sf::RenderWindow &window) {
    m_shape.setPosition(m_location->get_position());
    window.draw(m_shape);
}

std::unique_ptr<IDynamicEntity> Enemy::clone() const {
    return std::make_unique<Enemy>(*this);
}

void Enemy::draw_into(sf::RenderWindow &window) {
    m_shape.setPosition(m_location->get_position());
    window.draw(m_shape);
}

void Enemy::action() {
    if (uniform_real(generator) <= 0.7 && m_clock.getElapsedTime().asSeconds() > action_delta_time) {
        m_location->get_side(static_cast<Room::Direction>(uniform_int(generator)))->enter(*this);
        action_delta_time = uniform_real(generator);
        m_clock.restart();
    }
}

Enemy::Enemy() {
    m_shape = sf::CircleShape(config::GAME_ENEMY_SIZE, 30);
    m_shape.setOrigin(config::GAME_ENEMY_SIZE, config::GAME_ENEMY_SIZE);
    m_shape.setTexture(&m_texture.get_texture());
}
