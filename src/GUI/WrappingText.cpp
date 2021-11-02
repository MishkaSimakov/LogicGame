#include "WrappingText.h"

namespace gui {
    WrappingText::WrappingText(
            sf::Vector2f position, float max_width, std::string content,
            int font_size, const std::string &font_name
    ) :
            m_font_size(font_size),
            m_content(std::move(content)),
            m_max_width(max_width) {
        m_text.setFillColor(colors::black);
        m_text.setCharacterSize(font_size);
        m_text.setFont(ResourceHolder::get().fonts.get(font_name));

        parseContent();

        m_text.setString(m_content);
        m_text.setPosition(position);
    }

    void WrappingText::handleEvent(sf::Event e, const sf::RenderWindow &window) {

    }

    void WrappingText::render(sf::RenderTarget &renderer) {
        renderer.draw(m_text);
    }

    void WrappingText::parseContent() {
        float whitespaceWidth = m_text.getFont()->getGlyph(' ', m_font_size, false).advance;
        float letterSpacing = (whitespaceWidth / 3.f) * (m_text.getLetterSpacing() - 1.f);

        float current_width = 0, current_word_length;
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
            }

            current_word_length += m_text.getFont()->getGlyph(m_content[i], m_font_size, false).advance + letterSpacing;
        }
    }
}