#pragma once
#include "IWindowKeeper.h"

#include <iostream>


class ContextManager;
class GameContext;
class IStateManager;

class IState {
public:
    explicit IState(IStateManager& state_manager);
    virtual bool do_step() = 0;

    virtual ~IState() = default;
protected:
    IStateManager& m_state_manager;
};


class ExitState: public IState {
public:
    explicit ExitState(IStateManager& state_manager) : IState(state_manager){};
    bool do_step() override { return false; }
};