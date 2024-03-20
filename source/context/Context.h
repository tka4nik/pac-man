#pragma once
#include "../drawable/entity/IEntity.h"
#include "../drawable/entity/PacMan.h"

#include <SFML/Graphics.hpp>
#include <stack>
#include <list>


class GameContext {
public:
    enum State { INGAME, WIN, LOST } state = INGAME;
    std::list<std::unique_ptr<IDynamicEntity>> dynamic_objects;
    std::list<std::unique_ptr<IStaticEntity>> static_objects;
    PacMan pacman;
public:
    GameContext clone();
};


class ContextManager {
public:
    void save_current_context() { m_history.push(m_context.clone()); };
    void restore_previous_context();
    void set_context(GameContext&& context) {m_context = std::move(context); };
    GameContext* get_context() { return &m_context; };
private:
    GameContext m_context;
    std::stack<GameContext> m_history;
};
