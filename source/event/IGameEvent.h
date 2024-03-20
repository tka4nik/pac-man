#pragma once

#include <list>
#include <memory>


class GameContext;
class IStaticEntity;

class IGameEvent {
public:
    virtual void handle(GameContext* context) = 0;
    virtual ~IGameEvent() = default;
};

class WinGame : public IGameEvent {
public:
    void handle(GameContext* context) override;
};

class LostGame : public IGameEvent {
public:
    void handle(GameContext* context) override;
};

class DeleteStaticEntity : public IGameEvent {
    using list_iterator = std::list<std::unique_ptr<IStaticEntity>>::iterator;
public:
    DeleteStaticEntity(list_iterator ptr_entity) : m_ptr_entity(ptr_entity) {};
    void handle(GameContext* context) override;
private:
    list_iterator m_ptr_entity;
};



