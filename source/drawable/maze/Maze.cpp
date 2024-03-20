
#include "Maze.h"

#include <utility>

void Room::draw_into(sf::RenderWindow &window) {
    if (!m_void)
        window.draw(m_rectangle);
    for (const auto& side : m_sides) {
        side->draw_into(window);
    }
}

void Room::set_position(sf::Vector2f pos) {
    m_rectangle.setPosition(pos);
}

void Room::set_side(Room::Direction side, std::shared_ptr<IRoomSide> ptr_room_side) {
    if (side != INVALID)
        m_sides[side] = std::move(ptr_room_side);
}

Room::Direction Room::get_direction(IRoomSide* ptr_room_side) {
    if (m_sides[LEFT].get() == ptr_room_side)
        return LEFT;
    if (m_sides[RIGHT].get() == ptr_room_side)
        return RIGHT;
    if (m_sides[UP].get() == ptr_room_side)
        return UP;
    if (m_sides[DOWN].get() == ptr_room_side)
        return DOWN;
    else {
        return INVALID;
    }
}

Room::Room(float size) :m_rectangle({size, size}) {
    m_rectangle.setOrigin(m_rectangle.getSize().x / 2, m_rectangle.getSize().y / 2);
    m_rectangle.setFillColor(config::GAME_COLOR_ROOM);
}

void Maze::draw_into(sf::RenderWindow &window) {
    for (auto& room : m_rooms)
        room->draw_into(window);
}

Wall::Wall(Room& room) : m_room(room) {

}

void Wall::draw_into(sf::RenderWindow &window) {
    prepare_to_draw();
    window.draw(m_line,2,sf::Lines);
}

void Wall::prepare_to_draw() {
    auto direction = m_room.get_direction(this);
    auto position = m_room.get_position();
    auto size = m_room.get_size();
    sf::Vector2f points[4] = {sf::Vector2f {position.x - size/2,position.y + size/2},
                              sf::Vector2f {position.x + size/2,position.y + size/2},
                              sf::Vector2f {position.x + size/2,position.y - size/2},
                              sf::Vector2f {position.x - size/2,position.y - size/2}};

    switch (direction) {
        case Room::LEFT:                                                                   // 3-----*
            m_line[0] = sf::Vertex{points[0], config::GAME_COLOR_WALL};  // ||    |
            m_line[1] = sf::Vertex{points[3], config::GAME_COLOR_WALL};  // ||    |
            break;                                                                         // 0-----*
        case Room::RIGHT:                                                                  // *-----2
            m_line[0] = sf::Vertex{points[1], config::GAME_COLOR_WALL};  // |    ||
            m_line[1] = sf::Vertex{points[2], config::GAME_COLOR_WALL};  // |    ||
            break;                                                                         // *-----1
        case Room::UP:                                                                     // 3=====2
            m_line[0] = sf::Vertex{points[2], config::GAME_COLOR_WALL};  // |     |
            m_line[1] = sf::Vertex{points[3], config::GAME_COLOR_WALL};  // |     |
            break;                                                                         // *-----*
        case Room::DOWN:                                                                   // *-----*
            m_line[0] = sf::Vertex{points[0], config::GAME_COLOR_WALL};  // |     |
            m_line[1] = sf::Vertex{points[1], config::GAME_COLOR_WALL};  // |     |
            break;                                                                         // 0=====1
        case Room::INVALID:
            throw std::runtime_error("Bad side");
    }
}
