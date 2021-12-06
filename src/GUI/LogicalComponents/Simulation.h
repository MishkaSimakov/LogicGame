#ifndef LOGICGAMEENGINE_SIMULATION_H
#define LOGICGAMEENGINE_SIMULATION_H

#include "Widget.h"

#include <memory>
#include <vector>

namespace gui {
    class ActingLogicalComponent;
    class Connector;

    class Simulation : public Widget {
    public:
        static Simulation *get();

        void reset();

        template<typename T, typename... Args>
        void addLogicalComponent(Args &&... args);

        void addLogicalComponent(std::unique_ptr<ActingLogicalComponent> component);

        bool handleEvent(sf::Event e, const sf::RenderWindow &window) override;

        void render(sf::RenderTarget &renderer) override;

        Connector *tryToConnectWire(Connector *connector, const sf::Vector2f &position);

        std::vector<std::unique_ptr<ActingLogicalComponent>> m_components;

        bool need_to_reset{false};
    protected:
        Simulation() = default;
    };

    template<typename T, typename... Args>
    void Simulation::addLogicalComponent(Args &&... args) {
        addLogicalComponent(std::make_unique<T>(std::forward<Args>(args)...));
    }
}


#endif //LOGICGAMEENGINE_SIMULATION_H
