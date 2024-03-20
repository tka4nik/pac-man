#pragma once

#include "../../workdir/Config.h"
#include "../state/IState.h"
#include <SFML/Graphics.hpp>

#include <memory>


class IStateManager {
public:
    virtual void set_next_state(std::unique_ptr<IState> state) = 0;
    virtual ~IStateManager() = default;
};


class Application: public IStateManager {
public:
    Application();
    int run();

    void set_next_state(std::unique_ptr<IState> state) override;
    void apply_deffer_state_change();
private:
    std::unique_ptr<IState> m_ptr_state_current;
    std::unique_ptr<IState> m_ptr_state_next;

};