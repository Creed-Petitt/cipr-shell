//
// Created by creed on 1/5/26.
//

#ifndef CIPR_NODE_H
#define CIPR_NODE_H

#include <utility>
#include <vector>
#include <variant>
#include <string>
#include "../../Token/Token.h"

enum class NodeType {
    BINARY,
    GROUPING,
    LITERAL,
    UNARY
};

struct Node {
    NodeType type;
    Token op;
    Literal value;
    int left = -1;
    int right = -1;

    Node(const NodeType type, Token op, Literal value, const int left, const int right)
        : type(type), op(std::move(op)), value(std::move(value)),
          left(left), right(right) {}
};

class Arena {
public:
    int addNode(NodeType type, Token op, Literal value, int left = -1, int right = -1) {
        nodes.emplace_back(type, std::move(op), std::move(value), left, right);
        return static_cast<int>(nodes.size()) - 1;
    }

    Node& get(const int index) {
        return nodes[index];
    }

    size_t size() const {
        return nodes.size();
    }

    void clear() {
        nodes.clear();
    }

private:
    std::vector<Node> nodes;
};

#endif //CIPR_NODE_H