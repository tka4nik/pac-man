#pragma once

#include "../builder/GameBuilderDirector.h"

#include <iostream>
#include <memory>


class IStateManager;

class ISelectCommand {
public:
    virtual void execute() = 0;
    virtual ~ISelectCommand() = default;
};


class IChangeStateCommand : public ISelectCommand {
public:
    IChangeStateCommand(IStateManager& state_manager) : m_state_manager(state_manager) {};
protected:
    IStateManager& m_state_manager;
};


class ExitCommand : public IChangeStateCommand {
public:
    using IChangeStateCommand::IChangeStateCommand;
    void execute() override;
};


class GameCommand : public IChangeStateCommand {
public:
    GameCommand(IStateManager& state_manager, std::unique_ptr<GameBuilderDirector>&& ptr_director)
        : IChangeStateCommand(state_manager), m_ptr_director(std::move(ptr_director)) {}
    void execute() override;
private:
    std::unique_ptr<GameBuilderDirector> m_ptr_director;
};
