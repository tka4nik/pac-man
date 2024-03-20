#include "SelectLevelState.h"
#include "../application/Application.h"

bool SelectLevelState::do_step() {
    event_handling();
    update();
    render();
    return true;
}

void SelectLevelState::event_handling() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_state_manager.set_next_state(std::make_unique<ExitState>(m_state_manager));
            break;
        }
    }
}

void SelectLevelState::update() {
    m_menu.process_mouse(sf::Mouse::isButtonPressed(sf::Mouse::Left), m_window);
    m_menu.draw_into(m_window);
}

void SelectLevelState::render() {
    m_window.display();
    m_window.clear(config::SELECT_LEVEL_BACKGROUND_COLOR);
}

SelectLevelState::SelectLevelState(IStateManager &state_manager, std::string title)
        : IState(state_manager),
          m_menu(state_manager),
          IWindowKeeper(config::MENU_SCREEN_MODE, title) {
}

