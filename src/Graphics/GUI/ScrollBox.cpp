#include "ScrollBox.h"

void ScrollBox::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!m_is_visible) return;

    m_shared_context->m_wind->setWindowView(m_scroll_view);
    target.draw(*m_inner_content);
    m_shared_context->m_wind->setWindowView(Window::ViewType::DEFAULT);

    if (needScrollX())
        target.draw(m_scroll_x_shape);

    if (needScrollY())
        target.draw(m_scroll_y_shape);
}

void ScrollBox::setMaxWidth(float width) {
    m_max_width = width;
    update();
}

void ScrollBox::setMaxHeight(float height) {
    m_max_height = height;
    update();
}

sf::Vector2f ScrollBox::getSize() const {
    float width, height;

    width = (m_max_width != -1) ? m_max_width : m_inner_content_bounding_box.width;
    height = (m_max_height != -1) ? m_max_height : m_inner_content_bounding_box.height;

    return {width, height};
}

sf::Vector2f ScrollBox::getPosition() const {
    return {
            m_inner_content_bounding_box.left +
            std::max(m_inner_content_bounding_box.width - m_max_height, 0.f) * m_scroll_x_amount,
            m_inner_content_bounding_box.top +
            std::max(m_inner_content_bounding_box.height - m_max_height, 0.f) * m_scroll_y_amount
    };
}

void ScrollBox::update() {
    m_scroll_view.setSize(getSize());
    m_scroll_view.setCenter(getPosition() + m_scroll_view.getSize() / 2.f);

    m_scroll_view.setViewport(
            {
                    m_inner_content_bounding_box.left / (float) m_shared_context->m_wind->getWindowSize().x,
                    m_inner_content_bounding_box.top / (float) m_shared_context->m_wind->getWindowSize().y,
                    getSize().x / (float) m_shared_context->m_wind->getWindowSize().x,
                    getSize().y / (float) m_shared_context->m_wind->getWindowSize().y
            }
    );

    float scroll_y_size = std::floor(m_max_height / m_inner_content_bounding_box.height * m_max_height);
    m_scroll_y_shape.setPosition(
            m_inner_content_bounding_box.left + m_inner_content_bounding_box.width,
            m_inner_content_bounding_box.top + m_scroll_y_amount * (getSize().y - scroll_y_size)
    );
    m_scroll_y_shape.setSize({25, scroll_y_size});

    m_scroll_y_shape.setFillColor(m_scroll_state_colors[m_scroll_y_state]);
}

bool ScrollBox::needScrollX() const {
    return m_inner_content_bounding_box.width > m_max_width && m_max_width != -1.f;
}

bool ScrollBox::needScrollY() const {
    return m_inner_content_bounding_box.height > m_max_height && m_max_height != -1.f;
}

void ScrollBox::handleScrollEvent(const sf::Event &event) {
    if (!m_is_visible || !m_is_text_hovered) return;

    m_scroll_y_amount -= (float) event.mouseWheel.delta / 1000.f;

    if (m_scroll_y_amount > 1.f) {
        m_scroll_y_amount = 1.f;
        return;
    } else if (m_scroll_y_amount < 0.f) {
        m_scroll_y_amount = 0.f;
        return;
    }

    update();
}

void ScrollBox::setVisible(bool is_visible) {
    m_is_visible = is_visible;
}

void ScrollBox::handleMouseMovedEvent(const sf::Event &event) {
    auto mouse_pos{m_shared_context->m_wind->getMousePosition(Window::ViewType::DEFAULT)};

    if (m_scroll_y_state == State::ACTIVE) {
        float scroll_y_size = std::floor(m_max_height / m_inner_content_bounding_box.height * m_max_height);
        m_scroll_y_amount = std::clamp(
                (mouse_pos.y - m_scroll_y_drag_origin - m_inner_content_bounding_box.top) /
                (getSize().y - scroll_y_size),
                0.f, 1.f
        );

        update();

        return;
    }

    // scroll y hovered or regular
    if (getGlobalBounds().contains(mouse_pos)) {
        m_is_text_hovered = true;

        m_scroll_y_state = m_scroll_y_shape.getGlobalBounds().contains(mouse_pos) ? State::HOVER : State::REGULAR;
    } else {
        m_scroll_y_state = State::REGULAR;
        m_is_text_hovered = false;
    }

    update();
}

void ScrollBox::handleMousePressedEvent(const sf::Event &event) {
    auto mouse_pos{m_shared_context->m_wind->getMousePosition(Window::ViewType::DEFAULT)};

    if (m_scroll_y_state == State::HOVER) {
        m_scroll_y_state = State::ACTIVE;
        m_scroll_y_drag_origin = mouse_pos.y - m_scroll_y_shape.getGlobalBounds().top;
    }

    update();
}

void ScrollBox::handleMouseReleasedEvent(const sf::Event &event) {
    if (m_scroll_y_state == State::ACTIVE) {
        auto mouse_pos{m_shared_context->m_wind->getMousePosition(Window::ViewType::DEFAULT)};

        m_scroll_y_state = m_scroll_y_shape.getGlobalBounds().contains(mouse_pos) ?
                           State::HOVER :
                           State::REGULAR;
    }

    update();
}

sf::FloatRect ScrollBox::getGlobalBounds() const {
    return {
            m_inner_content_bounding_box.left,
            m_inner_content_bounding_box.top,
            getSize().x + m_scroll_y_shape.getGlobalBounds().width,
            getSize().y + m_scroll_x_shape.getGlobalBounds().height
    };
}
