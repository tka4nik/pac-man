#pragma once
#include <SFML/Graphics.hpp>

namespace config {
    const unsigned int FRAME_RATE_LIMIT = 60;
    const sf::VideoMode MENU_SCREEN_MODE = {400,600};
    const sf::Vector2f BUTTON_SIZE = {200,80};

    const size_t BUTTON_FONT_SIZE = static_cast<size_t>(BUTTON_SIZE.y / 1.5f);
    const float BUTTON_FRAME_THICKNESS = 2;
    const char FONT_FILE[] = "fonts/Carlito-Regular.ttf";
    const char SELECT_LEVEL_TITLE[] = "Select Level";
    const sf::VideoMode SELECT_LEVEL_VIDEO_MODE{ 400, 600 };
    const std::string BUTTON_TEXT_EASY = "Easy";
    const std::string BUTTON_TEXT_MEDIUM = "Medium";
    const std::string BUTTON_TEXT_HARD = "Hard";
    const std::string BUTTON_TEXT_EXIT = "Exit";
// Игра:
    const sf::VideoMode GAME_VIDEO_MODE{ 430, 330  };
    const char EASY_GAME_TITLE[] = "Level: Easy";
    const char MEDIUM_GAME_TITLE[] = "Level: Medium";
    const char HARD_GAME_TITLE[] = "Level: Hard";
    const float ENEMY_DELTA_TIME = 0.5f;
    const float EASY_GAME_ENEMY_RATIO = 0.0f;
    const float MEDIUM_GAME_ENEMY_RATIO = 0.03f;
    const float HARD_GAME_ENEMY_RATIO = 0.07f;
    const float ROOM_SIZE = 50;
    const float GAME_ENEMY_SIZE = ROOM_SIZE/2 * 0.7;
    const float GAME_FOOD_SIZE = ROOM_SIZE * 0.2;
    const std::string FOOD_TEXTURE_PATH = "images/food1.png";
    const std::string ENEMY1_TEXTURE_PATH = "images/enemy1.png";
    const std::string ENEMY2_TEXTURE_PATH = "images/enemy2.png";
    const std::string PACMAN_TEXTURE_PATH = "images/pacman1.png";
    const std::string AUDIO_CLICK_PATH = "sounds/click.wav";
    const std::string AUDIO_WIN_PATH = "sounds/pickupCoin.wav";
    const std::string AUDIO_LOST_PATH = "sounds/hitHurt.wav";
// Пакмэн:
    const float GAME_PACMAN_SIZE = ROOM_SIZE * 0.8;
    const sf::Keyboard::Key KEY_LEFT = sf::Keyboard::A;
    const sf::Keyboard::Key KEY_RIGHT = sf::Keyboard::D;
    const sf::Keyboard::Key KEY_UP = sf::Keyboard::W;
    const sf::Keyboard::Key KEY_DOWN = sf::Keyboard::S;
// Цвета:
    const sf::Color BUTTON_COLOR_TEXT = sf::Color::Black;
    const sf::Color BUTTON_COLOR_FILL = {196, 125, 26};
    const sf::Color BUTTON_COLOR_SELECTION = { 242, 189, 114 };
    const sf::Color BUTTON_COLOR_FRAME = {47, 173, 134};
    const sf::Color SELECT_LEVEL_BACKGROUND_COLOR{ 25, 25, 25 };
    const sf::Color GAME_COLOR_BACKGROUND_INGAME{ 50,50,50 };
    const sf::Color GAME_COLOR_BACKGROUND_WIN{ 0, 100, 0 };
    const sf::Color GAME_COLOR_BACKGROUND_LOST{ 100, 0, 0 };
    const sf::Color GAME_COLOR_PACMAN{ 250, 250, 0 };
    const sf::Color GAME_COLOR_ROOM {149, 158, 131};
    const sf::Color GAME_COLOR_WALL = sf::Color::Black;
    const sf::Color GAME_FOOD_COLOR{ 0, 200, 100 };
    const sf::Color GAME_ENEMY_COLOR{ 255, 50, 0 };
}