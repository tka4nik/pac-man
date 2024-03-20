#pragma once

#include <SFML/Audio.hpp>
#include "IState.h"
#include "../drawable/maze/Maze.h"
#include "../context/Context.h"
#include "../event/IGameEvent.h"


class GameState: public IState, public IWindowKeeper {
public:
    GameState(IStateManager& state_manager, std::string title);

    bool do_step() override;

    void event_handling() override;
    void update() override;
    void handle_events();
    void render() override;

    void set_maze(Maze&& maze) { m_maze = std::move(maze); }
    void set_context(GameContext&& context);
private:
    void process_key_pressed(sf::Keyboard::Key code);
    void process_event() {}; //TODO
private:
    Maze m_maze;
    ContextManager m_context_manager;
    sf::SoundBuffer m_buffer_eat;
    sf::SoundBuffer m_buffer_win;
    sf::SoundBuffer m_buffer_lost;
    sf::Sound m_sound;
    std::vector<std::unique_ptr<IGameEvent>> m_events;
};


