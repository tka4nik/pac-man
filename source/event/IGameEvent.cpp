#include "IGameEvent.h"
#include "../context/Context.h"

void LostGame::handle(GameContext* context) {
    context->state = GameContext::LOST;
}

void DeleteStaticEntity::handle(GameContext* context) {
    context->static_objects.erase(m_ptr_entity);
}

void WinGame::handle(GameContext *context) {
    context->state = GameContext::WIN;

}
