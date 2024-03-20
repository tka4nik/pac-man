#include "SimpleGameBuilder.h"

#include <cmath>
#include <random>

void SimpleGameBuilder::create_rooms() {
    size_t room_quantity_row = (m_height / m_room_size);
    size_t room_quantity_col = (m_width / m_room_size);


    int room_size = static_cast<int>(m_room_size);
    auto starting_point = sf::Vector2f{(m_width - m_room_size*room_quantity_col)/2 + m_room_size/2, (m_height - m_room_size*room_quantity_row)/2 + + m_room_size/2};

    for (int row = 0; row < room_quantity_row * room_size; row += room_size) {
        std::vector<std::unique_ptr<Room>> vector_row;
        for (int col = 0; col < room_quantity_col * room_size; col += room_size) {
            auto room = std::make_unique<Room>(m_room_size);
            room->set_void_false();
            room->set_position(sf::Vector2f {(col + starting_point.x), (row + starting_point.y)});
            vector_row.push_back(std::move(room));
        }
        m_rooms.push_back(std::move(vector_row));
    }
}

void SimpleGameBuilder::set_rooms_sides() {
    for (size_t row = 0; row < m_rooms.size(); ++row) {
        for (size_t col = 0; col < m_rooms[0].size(); ++col) {
            if (row == 0) {
                auto wall_up = std::make_shared<Wall>(*m_rooms[row][col]);
                m_rooms[row][col]->set_side(Room::UP, std::move(wall_up));
            } else {
                auto pass = std::make_shared<Pass>(*m_rooms[row - 1][col], *m_rooms[row][col]);
                m_rooms[row][col]->set_side(Room::UP, pass);
                m_rooms[row-1][col]->set_side(Room::DOWN, pass);
            }
            if (col == 0) {
                auto wall_left = std::make_shared<Wall>(*m_rooms[row][col]);
                m_rooms[row][col]->set_side(Room::LEFT, std::move(wall_left));
            } else {
                auto pass = std::make_shared<Pass>(*m_rooms[row][col - 1], *m_rooms[row][col]);
                m_rooms[row][col]->set_side(Room::LEFT, pass);
                m_rooms[row][col-1]->set_side(Room::RIGHT, pass);
            }
            if (row == m_rooms.size() - 1) {
                auto wall_down = std::make_shared<Wall>(*m_rooms[row][col]);
                m_rooms[row][col]->set_side(Room::DOWN, std::move(wall_down));
            }
            if (col == m_rooms[0].size() - 1) {
                auto wall_right = std::make_shared<Wall>(*m_rooms[row][col]);
                m_rooms[row][col]->set_side(Room::RIGHT, std::move(wall_right));
            }
        }
    }
}

void SimpleGameBuilder::create_context(float dynamic_objects_ratio) {
    GameContext context;
    std::vector<std::vector<std::unique_ptr<Room>>::iterator> empty_rooms_buffer;

    std::vector<std::vector<std::unique_ptr<Room>>>::iterator row;
    std::vector<std::unique_ptr<Room>>::iterator col;

    for (row = m_rooms.begin(); row != m_rooms.end(); ++row)
        for (col = row->begin(); col != row->end(); ++col)
            empty_rooms_buffer.push_back(col);

    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_real_distribution<> uniform_real(0.0,1.0);

    // Pacman
    std::uniform_int_distribution<int> uniform_int(0, empty_rooms_buffer.size() - 1);
    auto random_element = (empty_rooms_buffer.begin() + uniform_int(gen));
    context.pacman.set_location(*random_element->base()->get());
    empty_rooms_buffer.erase(random_element);


    // Enemy
    for (size_t i = 0; i < empty_rooms_buffer.size(); ++i) {
        if (uniform_real(gen) < dynamic_objects_ratio) {
            auto enemy = std::make_unique<Enemy>();

            std::uniform_int_distribution<int> uniform_int(0, empty_rooms_buffer.size() - 1);
            random_element = (empty_rooms_buffer.begin() + uniform_int(gen));

            enemy->set_location(*random_element->base()->get());
            context.dynamic_objects.emplace_back(std::move(enemy));

            empty_rooms_buffer.erase(random_element);
        }
    }
    // Food
    for (auto it = empty_rooms_buffer.begin(); it != empty_rooms_buffer.end(); ++it) {
        auto food = std::make_unique<Food>();
        food->set_location(*it->base()->get());
        context.static_objects.emplace_back(std::move(food));
    }

    empty_rooms_buffer.clear();
    m_context = std::move(context);
}

void SimpleGameBuilder::create_state(IStateManager &state_manager, std::string window_title) {
    m_game_state = std::make_unique<GameState>(state_manager, window_title);
}

void SimpleGameBuilder::set_all_to_state() {
    std::vector<std::unique_ptr<Room>> rooms;
    for (auto& row: m_rooms)
        for (auto &col: row)
            rooms.push_back(std::move(col));

    Maze maze(rooms);
    m_game_state->set_maze(std::move(maze));
    m_game_state->set_context(std::move(m_context));
}

std::unique_ptr<GameState> SimpleGameBuilder::get_game() {
    return std::move(m_game_state);
}




