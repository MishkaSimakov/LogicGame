#ifndef LOGICGAMEENGINE_GUI_ELEMENT_H
#define LOGICGAMEENGINE_GUI_ELEMENT_H

#include "GUI_Style.h"
#include "FontManager.h"
#include <unordered_map>
#include <utility>

enum class GUI_ElementType {
    Window, Label, Button, Scrollbar,
    Textfield
};

using ElementStyles = std::unordered_map<GUI_ElementState, GUI_Style>;

class GUI_Interface;

class GUI_Element {
    friend class GUI_Interface;

public:
    GUI_Element(std::string name, const GUI_ElementType &type, GUI_Interface *owner);
    virtual ~GUI_Element();
    // Event methods.
    virtual void ReadIn(std::stringstream &stream) = 0;
    virtual void OnClick(const sf::Vector2f &mousePos) = 0;
    virtual void OnRelease() = 0;
    virtual void OnHover(const sf::Vector2f &mousePos) = 0;
    virtual void OnLeave() = 0;
    virtual void Update(float dT) = 0;
    virtual void Draw(sf::RenderTarget *target) = 0;

    virtual void UpdateStyle(const GUI_ElementState &state, const GUI_Style &style);
    virtual void ApplyStyle();

    friend std::stringstream &operator>>(std::stringstream &l_stream, GUI_Element &b) {
        b.ReadIn(l_stream);
        return l_stream;
    }

protected:
    void ApplyTextStyle();
    void ApplyBgStyle();
    void ApplyGlyphStyle();
    void RequireTexture(const std::string &name);
    void RequireFont(const std::string &name);
    void ReleaseTexture(const std::string &name);
    void ReleaseFont(const std::string &name);
    void ReleaseResources();
    std::string m_name;
    sf::Vector2f m_position;
    ElementStyles m_style; // Style of drawables.
    GUI_Visual m_visual; // Drawable bits.
    GUI_ElementType m_type;
    GUI_ElementState m_state;
    GUI_Interface *m_owner;
    bool m_needsRedraw;
    bool m_active;
    bool m_isControl;
};

#endif //LOGICGAMEENGINE_GUI_ELEMENT_H
