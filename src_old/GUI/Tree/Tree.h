#ifndef LOGICGAMEENGINE_TREE_H
#define LOGICGAMEENGINE_TREE_H

#include "Node.h"
#include <vector>

class Tree {
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Node;
        using difference_type = std::ptrdiff_t;
        using pointer = Node*;
        using reference = Node&;

        iterator() = default;

        iterator(Node* root);

        Node& operator*() const;

        Node* operator->() const;

        iterator& operator++();

        iterator const operator++(int);

        bool operator==(iterator const& other) const;

        bool operator!=(iterator const& other) const;

        Node* current_node;
        int child_num {0};
    private:

    };

    Tree();

    iterator begin() {
        return {m_root};
    };

    iterator end() {
        iterator it {m_root};
        it.child_num = m_root->childrenCount();

        return it;
    };

    /*
     * TODO: он же список дел:
     * Необходимо доделать алгоритм, который будет осуществлять обход по дереву с вызовами необходимых функций
     */

private:
    Node *m_root;
};

#endif //LOGICGAMEENGINE_TREE_H
