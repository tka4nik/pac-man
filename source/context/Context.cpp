#include "Context.h"


GameContext GameContext::clone() {
    GameContext context;
    context.pacman = pacman;
    context.state = state;
    for (auto& s_o : static_objects) {
        context.static_objects.emplace_back(s_o->clone());
    }
    for (auto& d_o : dynamic_objects) {
        context.dynamic_objects.emplace_back(d_o->clone());
    }
    return context;
}

void ContextManager::restore_previous_context() {
    if (m_history.size() == 1) {
        m_context = m_history.top().clone();
        return;
    }
    m_context = std::move(m_history.top());
    m_history.pop();
}
