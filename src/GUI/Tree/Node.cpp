#include "Node.h"

bool Node::hasChildren() {
    return !m_children.empty();
}

std::vector<Node *> *Node::getChildren() {
    return &m_children;
}

int Node::childrenCount() {
    return m_children.size();
}

void Node::addChild(Node *child) {
    m_children.push_back(child);
}

Widget *Node::getWidget() {
    return m_widget;
}

void Node::setWidget(Widget *widget) {
    m_widget = widget;
}
