#include "Node.hpp"
using namespace ariel;

Node::Node(const std::string &data) {
    this->data = data;
}

Node::Node(Node *n) {
    this->data = n->data;
    for (Node *child : n->getChildren()) {
        Node tmp = new Node(child);
        this->children.push_back(&tmp);
    }
}

std::vector<Node*> Node::getChildren() {
    return this->children;
}

void Node::addChild(Node *child) {
    this->children.push_back(child);
}

void Node::setData(const std::string &data) {
    this->data = data;
}

const std::string& Node::getData() const{
    return this->data;
}

namespace ariel {

    std::ostream& operator << (std::ostream &os, Node &node) {
        os << node.getData();
        return os;
    }

}


