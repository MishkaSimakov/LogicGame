#include "GUI_Element.h"
#include "GUI_Interface.h"

GUI_Element::GUI_Element(std::string name, const GUI_ElementType &type, GUI_Interface *owner)
        : m_name(std::move(name)), m_type(type), m_owner(owner),
          m_state(GUI_ElementState::Neutral), m_needsRedraw(false),
          m_active(true), m_isControl(false) {}

GUI_Element::~GUI_Element() { ReleaseResources(); }

void GUI_Element::ReleaseResources() {
    for (auto &style: m_style) {
        ReleaseTexture(style.second.m_backgroundImage);
        ReleaseTexture(style.second.m_glyph);
        ReleaseFont(style.second.m_textFont);
    }
}

void GUI_Element::ReleaseTexture(const std::string &name) {
    if (name.empty()) {
        return;
    }

    m_owner->GetManager()->GetContext()->
            m_textureManager->ReleaseResource(name);
}

void GUI_Element::UpdateStyle(const GUI_ElementState &state, const GUI_Style &style) {
    // Resource management.
    if (style.m_backgroundImage !=
        m_style[state].m_backgroundImage) {
        ReleaseTexture(m_style[state].m_backgroundImage);
        RequireTexture(style.m_backgroundImage);
    }
    if (style.m_glyph != m_style[state].m_glyph) {
        ReleaseTexture(m_style[state].m_glyph);
        RequireTexture(style.m_glyph);
    }
    if (style.m_textFont != m_style[state].m_textFont) {
        ReleaseFont(m_style[state].m_textFont);
        RequireFont(style.m_textFont);
    }
    // Style application.
    m_style[state] = style;
    if (state == m_state) {
        SetRedraw(true);
        ApplyStyle();
    }
}

void GUI_Element::RequireTexture(const std::string &name) {
    if (name.empty()) { return; }
    m_owner->GetManager()->GetContext()->m_textureManager->RequireResource(name);
}

void GUI_Element::ApplyStyle() {
    ApplyTextStyle();
    ApplyBgStyle();
    ApplyGlyphStyle();

    if (m_owner != this && !IsControl()) {
        m_owner->AdjustContentSize(this);
    }
}

void GUI_Element::ApplyTextStyle() {
    FontManager *fonts = m_owner->GetManager()->
            GetContext()->m_fontManager;
    const GUI_Style &CurrentStyle = m_style[m_state];
    if (CurrentStyle.m_textFont != "") {
        m_visual.m_text.setFont(
                *fonts->GetResource(CurrentStyle.m_textFont));
        m_visual.m_text.setColor(CurrentStyle.m_textColor);
        m_visual.m_text.setCharacterSize(CurrentStyle.m_textSize);
        if (CurrentStyle.m_textCenterOrigin) {
            sf::FloatRect rect = m_visual.m_text.getLocalBounds();
            m_visual.m_text.setOrigin(rect.left + rect.width / 2.0f,
                                      rect.top + rect.height / 2.0f);
        } else {
            m_visual.m_text.setOrigin(0.f, 0.f);
        }
    }
    m_visual.m_text.setPosition(m_position +
                                CurrentStyle.m_textPadding);
}

void GUI_Element::ApplyBgStyle() {
    TextureManager *textures = m_owner->GetManager()->
            GetContext()->m_textureManager;
    const GUI_Style &CurrentStyle = m_style[m_state];
    if (CurrentStyle.m_backgroundImage != "") {
        m_visual.m_backgroundImage.setTexture(*textures->GetResource(CurrentStyle.m_backgroundImage));
        m_visual.m_backgroundImage.setColor(CurrentStyle.m_backgroundImageColor);
    }
    m_visual.m_backgroundImage.setPosition(m_position);
    m_visual.m_backgroundSolid.setSize(
            sf::Vector2f(CurrentStyle.m_size));
    m_visual.m_backgroundSolid.setFillColor(
            CurrentStyle.m_backgroundColor);
    m_visual.m_backgroundSolid.setPosition(m_position);
}

void GUI_Element::ApplyGlyphStyle(){
    const GUI_Style& CurrentStyle = m_style[m_state];
    TextureManager* textures = m_owner->GetManager()->
            GetContext()->m_textureManager;
    if (CurrentStyle.m_glyph != ""){
        m_visual.m_glyph.setTexture(
                *textures->GetResource(CurrentStyle.m_glyph));
    }
    m_visual.m_glyph.setPosition(m_position +
                                 CurrentStyle.m_glyphPadding);
}

void GUI_Element::SetState(const GUI_ElementState& l_state){
    if (m_state == l_state){ return; }
    m_state = l_state;
    SetRedraw(true);
}

void GUI_Element::SetPosition(const sf::Vector2f& l_pos){
    m_position = l_pos;
    if (m_owner == nullptr || m_owner == this){ return; }
    const auto& padding = m_owner->GetPadding();
    if (m_position.x < padding.x){ m_position.x = padding.x; }
    if (m_position.y < padding.y){ m_position.y = padding.y; }
}

bool GUI_Element::IsInside(const sf::Vector2f& l_point) const{
    sf::Vector2f position = GetGlobalPosition();
    return(l_point.x >= position.x &&
           l_point.y >= position.y &&
           l_point.x <= position.x + m_style.at(m_state).m_size.x &&
           l_point.y <= position.y + m_style.at(m_state).m_size.y);
}

sf::Vector2f GUI_Element::GetGlobalPosition() const{
    sf::Vector2f position = GetPosition();
    if (m_owner == nullptr || m_owner == this){ return position; }
    position += m_owner->GetGlobalPosition();
    if (IsControl()){ return position; }
    position.x -= m_owner->m_scrollHorizontal;
    position.y -= m_owner->m_scrollVertical;
    return position;
}