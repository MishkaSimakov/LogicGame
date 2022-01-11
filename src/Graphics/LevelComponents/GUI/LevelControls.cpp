#include "LevelControls.h"
#include "StateManager.h"

LevelControls::LevelControls(SharedContext *sharedContext, void (LevelState::*run_tests_cb)(), LevelState *object):
        m_shared_context(sharedContext),
        m_run_tests_btn(
                sharedContext, StateType::Level, m_run_tests_btn_size,
                {
                        (float) sharedContext->m_wind->getWindowSize().x - m_run_tests_btn_size.x - 25.f,
                        25.f
                }
        ) {
    m_run_tests_btn.setTexture(&ResourceHolder::get().textures.get("play")); // TODO: add texture
    m_run_tests_btn.setOnClickCallback(run_tests_cb, object);
}

void LevelControls::draw() {
    m_shared_context->m_wind->draw(m_run_tests_btn);
}