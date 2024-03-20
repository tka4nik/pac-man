#include "Menu.h"
#include "../../builder/SimpleGameBuilder.h"
#include "../../builder/ComplexGameBuilder.h"

#include <string>

Menu::Menu(IStateManager& state_manager) {
    float delta = 50;
    sf::Vector2f starting_position(200,30);

    auto easy_director = std::make_unique<GameBuilderDirector>(
            std::make_unique<SimpleGameBuilder>(
                    config::GAME_VIDEO_MODE.width, config::GAME_VIDEO_MODE.height,
                    config::ROOM_SIZE),
            config::EASY_GAME_TITLE,
            config::EASY_GAME_ENEMY_RATIO);

    auto medium_director = std::make_unique<GameBuilderDirector>(
            std::make_unique<SimpleGameBuilder>(
                    config::GAME_VIDEO_MODE.width, config::GAME_VIDEO_MODE.height,
                    config::ROOM_SIZE),
            config::MEDIUM_GAME_TITLE,
            config::MEDIUM_GAME_ENEMY_RATIO);

    auto hard_director = std::make_unique<GameBuilderDirector>(
            std::make_unique<ComplexGameBuilder>(
                    config::GAME_VIDEO_MODE.width, config::GAME_VIDEO_MODE.height,
                    config::ROOM_SIZE),
            config::HARD_GAME_TITLE,
            config::HARD_GAME_ENEMY_RATIO);

    auto easy_command = std::make_unique<GameCommand>(state_manager, std::move(easy_director));
    auto medium_command = std::make_unique<GameCommand>(state_manager, std::move(medium_director));
    auto hard_command = std::make_unique<GameCommand>(state_manager, std::move(hard_director));
    auto exit_command = std::make_unique<ExitCommand>(state_manager);

    m_buttons.emplace_back(std::make_unique<Button>(sf::Vector2f{starting_position.x, starting_position.y + config::BUTTON_SIZE.y}, config::BUTTON_SIZE, config::BUTTON_TEXT_EASY, config::BUTTON_FONT_SIZE , std::move(easy_command)));
    m_buttons.emplace_back(std::make_unique<Button>(sf::Vector2f{starting_position.x, starting_position.y + 2 * config::BUTTON_SIZE.y + delta}, config::BUTTON_SIZE, config::BUTTON_TEXT_MEDIUM, config::BUTTON_FONT_SIZE , std::move(medium_command)));
    m_buttons.emplace_back(std::make_unique<Button>(sf::Vector2f{starting_position.x, starting_position.y + 3 * config::BUTTON_SIZE.y + 2 * delta}, config::BUTTON_SIZE, config::BUTTON_TEXT_HARD, config::BUTTON_FONT_SIZE , std::move(hard_command)));
    m_buttons.emplace_back(std::make_unique<Button>(sf::Vector2f{starting_position.x, starting_position.y + 4 * config::BUTTON_SIZE.y + 3 * delta}, config::BUTTON_SIZE, config::BUTTON_TEXT_EXIT, config::BUTTON_FONT_SIZE, std::move(exit_command)));
}

void Menu::draw_into(sf::RenderWindow &window) {
    for (auto& ptr_button : m_buttons)
        ptr_button->draw_into(window);
}

void Menu::process_mouse(bool is_pressed, const sf::RenderWindow& window) {
    auto position_int = sf::Mouse::getPosition(window);
    auto position_float = window.mapPixelToCoords(position_int);
    for (auto& button : m_buttons) {
        if (button->is_position_in(position_float) && window.hasFocus()) {
            button->select();
            if (is_pressed)
                button->push();
        }
        else
            button->unselect();
    }
}

Button::Button(sf::Vector2f button_center_pos, sf::Vector2f button_size, const std::string& text, size_t font_size,
               std::unique_ptr<ISelectCommand> ptr_command) {

    m_rectangle.setFillColor(config::BUTTON_COLOR_FILL);
    m_rectangle.setSize(button_size);
    m_rectangle.setOrigin(button_size.x / 2, button_size.y / 2);
    m_rectangle.setPosition(button_center_pos);

    if (!m_font.loadFromFile(config::FONT_FILE))
        throw std::runtime_error("No such file in directory");
    m_text.setFont(m_font);
    m_text.setString(text);
    m_text.setCharacterSize(font_size);
    m_text.setLetterSpacing(1);
    auto textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    m_text.setPosition(button_center_pos);
    m_text.setFillColor(config::BUTTON_COLOR_TEXT);
    m_text.setOutlineColor(config::BUTTON_COLOR_FRAME);
    m_text.setOutlineThickness(config::BUTTON_FRAME_THICKNESS);
    m_ptr_command = std::move(ptr_command);
}

void Button::draw_into(sf::RenderWindow &window) {
    window.draw(m_rectangle);
    window.draw(m_text);
}

bool Button::is_position_in(sf::Vector2f pos) {
    return (m_rectangle.getGlobalBounds().contains(pos));
}
