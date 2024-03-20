#pragma once

#include "../entity/IEntity.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <utility>


class Room;

class IRoomSide : public IMyDrawable {
public:
    virtual void enter(IEntity& entity) = 0;
};


class Room : public IMyDrawable {
public:
    enum Direction { INVALID = -1, LEFT, RIGHT, UP, DOWN };
    explicit Room(float size);

    void draw_into(sf::RenderWindow& window) override;

    void set_side(Direction side, std::shared_ptr<IRoomSide> ptr_room_side);
    void set_position(sf::Vector2f pos);
    void set_void_true() { m_void = true; }
    void set_void_false() { m_void = false; }
    bool is_void() { return m_void; }

    float get_size() { return m_rectangle.getSize().x; };
    sf::Vector2f get_position() { return m_rectangle.getPosition(); };
    IRoomSide* get_side(Direction side) { return m_sides[side].get(); }
    Direction get_direction(IRoomSide* ptr_room_side);

private:
    sf::RectangleShape m_rectangle;
    std::array<std::shared_ptr<IRoomSide>, 4> m_sides;
    bool m_void = true;
};


class Maze : public IMyDrawable {
public:
    Maze() = default;
    Maze(std::vector<std::unique_ptr<Room>>& rooms) : m_rooms(std::move(rooms)) {};

    void draw_into(sf::RenderWindow& window) override;
private:
    std::vector<std::unique_ptr<Room>> m_rooms;
};


class Pass : public IRoomSide {
public:
    Pass(Room& room1, Room& room2) : m_room1(room1), m_room2(room2) {};
    void draw_into(sf::RenderWindow& window) override{};
    void enter(IEntity& entity) override { entity.set_location(entity.get_location() == &m_room2 ? m_room1 : m_room2);};
private:
    Room& m_room1;
    Room& m_room2;
};


class Wall : public IRoomSide {
public:
    explicit Wall(Room& room);

    void prepare_to_draw();
    void draw_into(sf::RenderWindow& window) override;
    void enter(IEntity& entity) override {};
private:
    Room& m_room;
    sf::Vertex m_line[2];
};