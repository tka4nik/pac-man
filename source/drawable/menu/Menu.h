#pragma once

#include "../../command/ISelectCommand.h"
#include "../drawable.h"
#include "../../../workdir/Config.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class IStateManager;

class Button : public IMyDrawable {
public:
    Button(sf::Vector2f button_center_pos,
           sf::Vector2f button_size,
           const std::string& text,
           size_t font_size,
           std::unique_ptr<ISelectCommand> ptr_command);
    void draw_into(sf::RenderWindow& window) override;

    void select() { m_rectangle.setFillColor(config::BUTTON_COLOR_SELECTION);}
    void unselect() { m_rectangle.setFillColor(config::BUTTON_COLOR_FILL); }
    bool is_selected() { return m_is_selected; }
    bool is_position_in(sf::Vector2f pos);
    void push() { m_ptr_command->execute(); }
private:
    std::unique_ptr<ISelectCommand> m_ptr_command;
private:
    bool m_is_selected = false;
    sf::Font m_font;
    sf::Text m_text;
    sf::RectangleShape m_rectangle;
};


class Menu : public IMyDrawable {
public:
    explicit Menu(IStateManager& state_manager);
    void draw_into(sf::RenderWindow& window) override;
    void process_mouse(bool is_pressed, const sf::RenderWindow& window);
private:
    sf::RectangleShape m_shape;
    std::vector<std::unique_ptr<Button>> m_buttons;
};

