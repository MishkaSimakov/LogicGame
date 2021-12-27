#ifndef LOGICGAMEENGINE_NODE_H
#define LOGICGAMEENGINE_NODE_H

#include <vector>
#include "Widget.h"

class Node {
public:
    Node() = default;
    virtual ~Node();

    bool hasChildren();
    std::vector<Node *> *getChildren();
    int childrenCount();

    void addChild(Node *child);

    Widget *getWidget();
    void setWidget(Widget *widget);

private:
    std::vector<Node *> m_children;
    Widget *m_widget{nullptr};
};

#endif //LOGICGAMEENGINE_NODE_H
