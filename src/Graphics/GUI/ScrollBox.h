#ifndef LOGICGAMEENGINE_SCROLLBOX_H
#define LOGICGAMEENGINE_SCROLLBOX_H

#include "SharedContext.h"
#include "RoundedRectangle.h"
#include "Window.h"

#include <SFML/Graphics.hpp>

class ScrollBox : public sf::Drawable {
public:
    enum class State {
        REGULAR,
        HOVER,
        ACTIVE
    };

    template<class T>
    ScrollBox(SharedContext *sharedContext, StateType stateType, T *inner_content) :
            m_shared_context(sharedContext),
            m_scroll_x_shape({10, 10}),
            m_scroll_y_shape({10, 10}),
            m_inner_content(inner_content),
            m_inner_content_bounding_box(inner_content->getGlobalBounds()) {
        m_shared_context->m_eventManager->addEventCallback(
                stateType, sf::Event::MouseWheelMoved, &ScrollBox::handleScrollEvent, this
        );
        m_shared_context->m_eventManager->addEventCallback(
                stateType, sf::Event::MouseMoved, &ScrollBox::handleMouseMovedEvent, this
        );
        m_shared_context->m_eventManager->addMousePressedCallback(
                stateType, sf::Mouse::Left, &ScrollBox::handleMousePressedEvent, this
        );
        m_shared_context->m_eventManager->addMouseReleasedCallback(
                stateType, sf::Mouse::Left, &ScrollBox::handleMouseReleasedEvent, this
        );

        m_scroll_state_colors[State::REGULAR] = {150, 150, 150, 75};
        m_scroll_state_colors[State::HOVER] = {150, 150, 150, 125};
        m_scroll_state_colors[State::ACTIVE] = {150, 150, 150, 150};

        update();
    }

    template<class T>
    void setInnerContent(T *inner_content) {
        m_inner_content = inner_content;
        m_inner_content_bounding_box = inner_content->getGlobalBounds();

        update();
    }

    void setVisible(bool is_visible);

    void setMaxWidth(float width);

    void setMaxHeight(float height);

    void update();

    sf::FloatRect getGlobalBounds() const;

protected:
    void handleMouseMovedEvent(const sf::Event &event);

    void handleScrollEvent(const sf::Event &event);

    void handleMousePressedEvent(const sf::Event &event);

    void handleMouseReleasedEvent(const sf::Event &event);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    bool needScrollX() const;

    bool needScrollY() const;

    sf::Vector2f getSize() const;

    sf::Vector2f getPosition() const;

    SharedContext *m_shared_context;

    float m_max_width{-1.f};
    float m_max_height{-1.f};

    float m_scroll_x_amount{0.f};
    float m_scroll_y_amount{0.f};

    RoundedRectangle m_scroll_x_shape;
    RoundedRectangle m_scroll_y_shape;

    bool m_is_text_hovered{true};
    State m_scroll_y_state{State::REGULAR};
    float m_scroll_y_drag_origin{0.f};

    sf::View m_scroll_view;

    sf::Drawable *m_inner_content;
    sf::FloatRect m_inner_content_bounding_box;

    bool m_is_visible{true};

    std::unordered_map<State, sf::Color> m_scroll_state_colors;
};


#endif //LOGICGAMEENGINE_SCROLLBOX_H
