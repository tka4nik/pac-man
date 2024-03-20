#include "IState.h"
#include "../application/Application.h"


IState::IState(IStateManager &state_manager) : m_state_manager(state_manager) {}