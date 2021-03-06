#include "WrappingText.h"

WrappingText::WrappingText(
        sf::Vector2f position, float max_width, std::wstring content,
        int font_size, const std::string &font_name, sf::Uint32 style
) :
        m_position(position),
        m_content(std::move(content)),
        m_font_size(font_size),
        m_max_width(max_width) {
    m_text.setStyle(style);
    m_text.setFillColor(sf::Color::Black);
    m_text.setCharacterSize(font_size);
    m_text.setFont(ResourceHolder::get().fonts.get(font_name));

    parseContent();

    m_text.setString(m_content);
    m_text.setPosition(m_position);
}

void WrappingText::parseContent() {
    float whitespaceWidth = m_text.getFont()->getGlyph(' ', m_font_size, false).advance;
    float letterSpacing = (whitespaceWidth / 3.f) * (m_text.getLetterSpacing() - 1.f);

    float current_width = 0, current_word_length = 0;
    int last_whitespace_position = 0;

    if (m_content.back() != ' ')
        m_content += ' ';

    for (int i = 0; i < m_content.size(); ++i) {
        if (m_content[i] == ' ') {
            if (current_width + current_word_length > m_max_width && current_width > 0) {
                m_content[last_whitespace_position] = '\n';
                current_width = 0;
            }

            current_width += current_word_length;
            current_word_length = 0;
            last_whitespace_position = i;
        } else if (m_content[i] == '\n') {
            current_word_length = 0;
            current_width = 0;
        }

        current_word_length += m_text.getFont()->getGlyph(m_content[i], m_font_size, false).advance + letterSpacing;
    }
}

void WrappingText::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_text);
}

void WrappingText::setPosition(const sf::Vector2f &position) {
    m_position = position;

    m_text.setPosition(position);
}

sf::FloatRect WrappingText::getGlobalBounds() const {
    auto bounds = m_text.getGlobalBounds();

    bounds.width = m_max_width;

    return bounds;
}

void WrappingText::setString(const std::wstring &string) {
    m_content = string;
    parseContent();

    m_text.setString(m_content);
}
