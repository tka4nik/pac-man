#pragma once

#include "../drawable.h"
#include "../../../workdir/Config.h"

#include <random>
#include <chrono>


class Room;

class IEntity : public IMyDrawable {
public:
    void set_location(Room& ptr_room) { m_location = &ptr_room; };
    Room * get_location() { return m_location; }
protected:
    Room* m_location;
};


class TextureAdapter {
public:
    explicit TextureAdapter(const std::string& file_name) {
        if (!m_texture.loadFromFile(file_name))
            throw std::runtime_error("No such file in directory.");
    }
    const sf::Texture& get_texture() const { return m_texture; }
private:
    sf::Texture m_texture;
};



class IStaticEntity : public IEntity {
public:
    [[nodiscard]] virtual std::unique_ptr<IStaticEntity> clone() const = 0;
};


class IDynamicEntity : public IEntity {
public:
    [[nodiscard]] virtual std::unique_ptr<IDynamicEntity> clone() const = 0;
    virtual void action() = 0;
};


class Food : public IStaticEntity {
public:
    Food();
    void draw_into(sf::RenderWindow& window) override;
    [[nodiscard]] std::unique_ptr<IStaticEntity> clone() const override;
private:
    sf::CircleShape m_shape;
    inline static TextureAdapter m_texture{config::FOOD_TEXTURE_PATH};
};


class Enemy : public IDynamicEntity {
public:
    Enemy();
    void draw_into(sf::RenderWindow& window) override;
    void action() override;
    [[nodiscard]] std::unique_ptr<IDynamicEntity> clone() const override;
private:
    sf::CircleShape m_shape;
    inline static TextureAdapter m_texture{config::ENEMY2_TEXTURE_PATH};

    inline static std::mt19937 generator{std::random_device{}()};
    inline static std::uniform_int_distribution<int> uniform_int{0, 3};
    inline static std::uniform_real_distribution<> uniform_real{0.0,1.0};

    sf::Clock m_clock;
    float action_delta_time = config::ENEMY_DELTA_TIME;
};