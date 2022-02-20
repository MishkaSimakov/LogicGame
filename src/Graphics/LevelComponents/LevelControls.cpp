#include "LevelControls.h"
#include "StateManager.h"

LevelControls::LevelControls(
        SharedContext *sharedContext,
        void (LevelState::*run_tests_cb)(),
        void (LevelState::*quit_level_cb)(),
        LevelState *object
) :
        m_shared_context(sharedContext),
        m_run_tests_btn(
                sharedContext, StateType::Level, m_run_tests_btn_size,
                {
                        (float) sharedContext->m_wind->getWindowSize().x - m_run_tests_btn_size.x - 25.f,
                        25.f
                }
        ),
        m_quit_level_btn(
                sharedContext, StateType::Level, m_quit_level_btn_size, {25.f, 25.f}
        ) {
    m_quit_level_btn.setTexture(&ResourceHolder::get().textures.get("icons/home_2_1"));
    m_quit_level_btn.setOnClickCallback(quit_level_cb, object);

    m_run_tests_btn.setTexture(&ResourceHolder::get().textures.get("icons/play_cr"));
    m_run_tests_btn.setOnClickCallback(run_tests_cb, object);
}

void LevelControls::draw() {
    m_shared_context->m_wind->draw(m_run_tests_btn);
    m_shared_context->m_wind->draw(m_quit_level_btn);
}