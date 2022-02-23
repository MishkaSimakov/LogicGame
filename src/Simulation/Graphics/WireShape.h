#ifndef LOGICGAMEENGINE_WIRESHAPE_H
#define LOGICGAMEENGINE_WIRESHAPE_H

#include "Window.h"
#include "ConnectorShape.h"
#include <iostream>

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class WireShape {
public:
    WireShape(const sf::Vector2f &start, const sf::Vector2f &end) :
            m_start(start), m_end(end),
            m_segments(sf::TriangleStrip), m_outline_segments(sf::TriangleStrip) {};

    void setStartConnector(ConnectorShape *start_connector) {
        m_start_connector = start_connector;
    }

    void setEndConnector(ConnectorShape *end_connector) {
        m_end_connector = end_connector;
    }

    [[nodiscard]] ConnectorShape *getStartConnector() const {
        return m_start_connector;
    }

    [[nodiscard]] ConnectorShape *getEndConnector() const;

    // Эта функция в случае, когда кабель перемещают, возвращает коннектор из которого его тянут
    ConnectorShape *getDragOriginConnector();

    void addMissingConnector(ConnectorShape *connector);

    void draw(Window *window);

    void update();

    void dragTo(const sf::Vector2f &position);

    bool checkClick(const sf::Vector2f &position);

    void select() {
        m_is_selected = true;
    }

    void deselect() {
        m_is_selected = false;
    }

    [[nodiscard]] bool isUnconnected() const {
        return !m_start_connector || !m_end_connector;
    }

    [[nodiscard]] long getWaypointByPosition(const sf::Vector2f &position) const;

    [[nodiscard]] size_t getSegmentIdByPosition(const sf::Vector2f &position);

    [[nodiscard]] size_t addWaypoint(const sf::Vector2f &position, size_t segment_id);

    void dragWaypoint(size_t waypoint_id, const sf::Vector2f &position);

    bool needToRemoveWaypoint(size_t waypoint_id);

    void removeWaypoint(size_t waypoint_id);

protected:
    static void appendSegment(
            sf::Vector2f start, sf::Vector2f end, float width,
            sf::VertexArray *vertex_array, sf::Color color
    );

    static float sign(
            const sf::Vector2f &a, const sf::Vector2f &b, const sf::Vector2f &c
    );

    static bool isPointInTriangle(
            const sf::Vector2f &point,
            const sf::Vector2f &a, const sf::Vector2f &b, const sf::Vector2f &c
    );

    sf::Vector2f m_start;
    sf::Vector2f m_end;

    ConnectorShape *m_start_connector{nullptr};
    ConnectorShape *m_end_connector{nullptr};

    bool m_is_selected{false};

    std::vector<sf::Vector2f> m_waypoints;

    const float m_width{3.f};
    const float m_outline_width{20.f};

    sf::VertexArray m_segments;
    sf::VertexArray m_outline_segments;
    std::vector<sf::CircleShape> m_waypoint_circles;
};


#endif //LOGICGAMEENGINE_WIRESHAPE_H
