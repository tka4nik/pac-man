#include "GameState.h"
#include "SelectLevelState.h"
#include "../application/Application.h"

GameState::GameState(IStateManager &state_manager, std::string title)
        : IState(state_manager),
          IWindowKeeper(config::GAME_VIDEO_MODE, title) {
    m_window.setFramerateLimit(60);
    m_window.setKeyRepeatEnabled(false);
    m_buffer_eat.loadFromFile(config::AUDIO_CLICK_PATH);
    m_buffer_win.loadFromFile(config::AUDIO_WIN_PATH);
    m_buffer_lost.loadFromFile(config::AUDIO_LOST_PATH);
    m_sound.setBuffer(m_buffer_eat);
    m_sound.setVolume(50);
    m_sound.play();
}

void GameState::event_handling() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_state_manager.set_next_state(std::make_unique<SelectLevelState>(m_state_manager, config::SELECT_LEVEL_TITLE));

        if (event.type == sf::Event::KeyPressed && event.key.control && event.key.code == sf::Keyboard::Z) {
            m_sound.setBuffer(m_buffer_eat);
            m_context_manager.restore_previous_context();
        }

        if (event.type == sf::Event::KeyPressed  && m_context_manager.get_context()->state == GameContext::INGAME)
            process_key_pressed(event.key.code);
    }
}

void GameState::update() {
    if (m_context_manager.get_context()->state != GameContext::INGAME)
        return;

    auto context = m_context_manager.get_context();
    for (auto& entity : context->dynamic_objects)
        entity->action();

    for (auto it = context->static_objects.begin(); it != context->static_objects.end(); ++it) {
        if (context->pacman.get_location() == (*it)->get_location()) {
            m_events.emplace_back(std::move(std::make_unique<DeleteStaticEntity>(it)));
            m_sound.play();
        }
    }

    for (auto it = context->dynamic_objects.begin(); it != context->dynamic_objects.end(); ++it) {
        if (context->pacman.get_location() == (*it)->get_location()) {
            m_sound.setBuffer(m_buffer_lost);
            m_sound.play();
            m_events.emplace_back(std::move(std::make_unique<LostGame>()));
        }
    }

    if (!(context->static_objects.size())) {
        m_sound.setBuffer(m_buffer_win);
        m_sound.play();
        m_events.emplace_back(std::move(std::make_unique<WinGame>()));
    }
}

void GameState::render() {
    auto context = m_context_manager.get_context();
    switch (context->state) {
        case GameContext::INGAME:
            m_window.clear(config::GAME_COLOR_BACKGROUND_INGAME);
            break;
        case GameContext::LOST:
            m_window.clear(config::GAME_COLOR_BACKGROUND_LOST);
            break;
        default:
            m_window.clear(config::GAME_COLOR_BACKGROUND_WIN);
    }

    m_maze.draw_into(m_window);

    for (auto& el: context->static_objects)
        el->draw_into(m_window);

    context->pacman.draw_into(m_window);

    for (auto& el: context->dynamic_objects)
        el->draw_into(m_window);

    m_window.display();
}

bool GameState::do_step() {
    event_handling();
    update();
    handle_events();
    render();
    return true;
}

void GameState::set_context(GameContext&& context) {
    m_context_manager.set_context(std::move(context));
    m_context_manager.save_current_context();
}

void GameState::process_key_pressed(sf::Keyboard::Key code) {
    switch (code) {
        case sf::Keyboard::W:
            m_context_manager.save_current_context();
            m_context_manager.get_context()->pacman.move(Room::UP);
            break;

        case sf::Keyboard::S:
            m_context_manager.save_current_context();
            m_context_manager.get_context()->pacman.move(Room::DOWN);
            break;

        case sf::Keyboard::A:
            m_context_manager.save_current_context();
            m_context_manager.get_context()->pacman.move(Room::LEFT);
            break;
        case sf::Keyboard::D:
            m_context_manager.save_current_context();
            m_context_manager.get_context()->pacman.move(Room::RIGHT);
            break;
    }
}

void GameState::handle_events() {
    for (auto& event : m_events)
        event->handle(m_context_manager.get_context());
    m_events.clear();
}