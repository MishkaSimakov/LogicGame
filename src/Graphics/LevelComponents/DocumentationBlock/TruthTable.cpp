#include "TruthTable.h"

TruthTable::TruthTable(const sf::Vector2f &position, const Level &level) :
        m_position(position),
        m_title(L"Таблица истинности:", ResourceHolder::get().fonts.get("arial"), 30),
        m_borders(sf::Lines) {
    m_title.setPosition(m_position);
    m_title.setFillColor(sf::Color::Black);
    setLevel(level);
}

void TruthTable::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!m_is_visible) return;

    target.draw(m_borders);

    target.draw(m_title);
    for (auto &cell: m_cells) {
        target.draw(cell);
    }
}

void TruthTable::setPosition(const sf::Vector2f &position) {
    sf::Vector2f shift = position - m_position;

    m_title.move(shift);

    for (auto &cell: m_cells) {
        cell.move(shift);
    }
    for (int vertex = 0; vertex < m_borders.getVertexCount(); ++vertex) {
        m_borders[vertex].position += shift;
    }

    m_position = position;
}

void TruthTable::setLevel(const Level &level) {
    m_borders.clear();
    m_cells.clear();

    m_is_visible = level.getVisibleTestsCount() > 0;

    if (!m_is_visible) return;

    sf::Vector2f current_position{
            m_position.x,
            m_title.getGlobalBounds().top + m_title.getGlobalBounds().height + 25
    };

    float margin_x = 25;
    float margin_y = 15;

    size_t col_count = level.getInputsCount() + level.getOutputsCount();
    size_t row_count = std::min(level.getVisibleTestsCount(), level.getTests().size());

    std::vector<float> column_width(col_count);

    for (int col = 0; col < col_count; ++col) {
        current_position.x += margin_x;

        auto &label = m_cells.emplace_back(
                col < level.getInputsCount()
                ? level.getInputs()[col]
                : level.getOutputs()[col - level.getInputsCount()],
                ResourceHolder::get().fonts.get("arial"), 30
        );

        label.setStyle(sf::Text::Bold);
        label.setPosition(current_position);
        label.setFillColor(sf::Color::Black);

        column_width[col] = label.getGlobalBounds().left + label.getGlobalBounds().width - current_position.x;
        current_position.x += column_width[col] + margin_x;
    }

    current_position.y = m_cells.back().getGlobalBounds().top + m_cells.back().getGlobalBounds().height + margin_y;

    for (int row = 0; row < row_count; ++row) {
        m_borders.append(sf::Vertex({m_position.x, current_position.y}, sf::Color::Black));
        m_borders.append(sf::Vertex(current_position, sf::Color::Black));

        current_position.x = m_position.x;
        current_position.y += margin_y;

        for (int col = 0; col < col_count; ++col) {
            current_position.x += margin_x;

            auto &label = m_cells.emplace_back(
                    (col < level.getInputsCount()
                     ? level.getTests()[row].first[col]
                     : level.getTests()[row].second[col - level.getInputsCount()]) ? L"1" : L"0",
                    ResourceHolder::get().fonts.get("arial"), 30
            );

            label.setPosition(current_position);
            label.setFillColor(sf::Color::Black);

            current_position.x += column_width[col] + margin_x;
        }

        current_position.y = m_cells.back().getGlobalBounds().top + m_cells.back().getGlobalBounds().height + margin_y;
    }
}
