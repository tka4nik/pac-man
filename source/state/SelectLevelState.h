#pragma once
#include "IState.h"
#include "../drawable/menu/Menu.h"


class SelectLevelState: public IState, public IWindowKeeper {
public:
    SelectLevelState(IStateManager& state_manager, std::string title);
    bool do_step() override;
private:
    void event_handling() override;
    void update() override;
    void render() override;
private:
    Menu m_menu;
};
