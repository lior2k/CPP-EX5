#include "OrgChart.hpp"
using namespace ariel;

// ------------------- Iterator --------------------
OrgChart::Iterator::Iterator(Node *ptr) {
    this->currentIndex = 0;
    nodePtr = ptr;
} 

OrgChart::Iterator::Iterator(Node *ptr, iterType type) {
    this->currentIndex = 0;
    this->nodePtr = ptr;
    if (ptr == nullptr) {
        return;
    }
    if (type == iterType::levelOrder) {
        levelOrder();
    }
    if (type == iterType::reverseOrder) {
        reverseOrder();
    }
    if (type == iterType::preOrder) {
        preOrder();
    }
}

OrgChart::Iterator& OrgChart::Iterator::operator++() {
    nodePtr = list[++currentIndex];
    if (currentIndex >= list.size()) {
        nodePtr = NULL;
    }
    return *this;
}

OrgChart::Iterator OrgChart::Iterator::operator++(int dummy) {
    OrgChart::Iterator temp = *this;
    ++*this;
    return temp;
}

const std::string& OrgChart::Iterator::operator*() const {return this->list[currentIndex]->getData();}

const std::string* OrgChart::Iterator::operator->() const {return &this->list[currentIndex]->getData();}

bool OrgChart::Iterator::operator==(const Iterator &iter) const {return this->nodePtr==iter.nodePtr;}

bool OrgChart::Iterator::operator!=(const OrgChart::Iterator &it) const {return !(this->nodePtr==it.nodePtr);}

/*
    pretty similar to bfs on graphs, add root -> add his children -> for each added child add his children aswell
*/
void OrgChart::Iterator::levelOrder() {
    std::vector<Node *> nodes;
    nodes.push_back(nodePtr);
    while (!nodes.empty()) {
        Node *current = nodes[0];
        nodes.erase(nodes.begin());
        this->list.push_back(current);   
        for (Node *child : current->getChildren()) {
            nodes.push_back(child);
        }
    }
}

/*
    similar to level order except add children from right to left instead of left to right,
    then reverse the list to get the lowest rows first and the root last
*/
void OrgChart::Iterator::reverseOrder() {
    std::vector<Node *> nodes;
    std::vector<Node *>::reverse_iterator it;
    nodes.push_back(nodePtr);
    while (!nodes.empty()) {
        Node *current = nodes[0];
        nodes.erase(nodes.begin());
        this->list.push_back(current);
        // traverse the children from end to begin
        for (uint i = current->getChildren().size()-1; i >= 0; i--) {
            if (i == (uint) - 1) {
                break;
            }
            nodes.push_back(current->getChildren()[(uint)i]);
        }
    }
    reverseList();
}

void OrgChart::Iterator::reverseList() {
    for (unsigned int i = 0; i < list.size() / 2; i++) {
        swap(&list[i], &list[list.size()-1-i]);
    }
}

void OrgChart::Iterator::swap(Node **first, Node **second) {
    Node* temp = *first;
    *first = *second;
    *second = temp;
}

void OrgChart::Iterator::dfs(Node *ptr) {
    list.push_back(ptr);
    for (Node *child : ptr->getChildren()) {
        dfs(child);
    }
}

/*
    add the root then add children and recursively add each child's children
*/
void OrgChart::Iterator::preOrder() {
    dfs(nodePtr);
}

// print list for self debugging
void OrgChart::Iterator::printList() {
    for (unsigned int i = 0; i < list.size(); i++) {
        std::cout << list[i]->getData() << " ";
    }
}

// ----------------- end Iterator --------------------

// ------------------- OrgChart -----------------------

OrgChart::OrgChart() {
    root = nullptr;
}

// deep copy constructor
OrgChart::OrgChart(const OrgChart &og) {
    root = new Node(og.root);
    for (Node *node : og.allNodes) {
        this->allNodes.push_back(new Node(node));
    }
}

// destructor
OrgChart::~OrgChart() {
    for (Node *node : allNodes) {
        delete node;
    }
}

// deep copy operator =
OrgChart& OrgChart::operator=(const OrgChart &og) {
    if (this != &og) {
        if (og.root == nullptr) {
            this->root = nullptr;
        } else {
            root = new Node(og.root);
            for (Node *node : og.allNodes) {
                this->allNodes.push_back(new Node(node));
            }
        }
    }
    return *this;
}

std::vector<Node *> OrgChart::getNodes() const {
    return this->allNodes;
}

OrgChart& OrgChart::add_root(const std::string &root) {
    if (this->root != nullptr) {
        this->root->setData(root);
        return *this;
    }
    Node *n = new Node(root);
    this->root = n;
    this->allNodes.push_back(n);
    return *this;
}

OrgChart& OrgChart::add_sub(const std::string &parent, const std::string &child) {
    if (root == nullptr) {
        throw std::logic_error("Cant add sub before adding root");
    }
    bool flag = true;
    for (unsigned int i = 0; i < this->allNodes.size(); i++) {
        if (allNodes[i]->getData() == parent) {
            flag = false;
            Node *n = new Node(child);
            allNodes[i]->addChild(n);
            this->allNodes.push_back(n);
            break;
        }
    }
    if (flag) {
        throw std::logic_error("Superior not found");
    }
    return *this;
}

OrgChart::Iterator OrgChart::begin_level_order() const {if (root == nullptr) {throw std::logic_error("Chart is empty!");} return OrgChart::Iterator(this->root, iterType::levelOrder);}

OrgChart::Iterator OrgChart::end_level_order() const {if (root == nullptr) {throw std::logic_error("Chart is empty!");} return OrgChart::Iterator(nullptr, iterType::levelOrder);}

OrgChart::Iterator OrgChart::begin_reverse_order() const {if (root == nullptr) {throw std::logic_error("Chart is empty!");} return OrgChart::Iterator(this->root, iterType::reverseOrder);}

OrgChart::Iterator OrgChart::reverse_order() const {if (root == nullptr) {throw std::logic_error("Chart is empty!");} return OrgChart::Iterator(nullptr, iterType::reverseOrder);}

OrgChart::Iterator OrgChart::begin_preorder() const {if (root == nullptr) {throw std::logic_error("Chart is empty!");} return OrgChart::Iterator(this->root, iterType::preOrder);}

OrgChart::Iterator OrgChart::end_preorder() const {if (root == nullptr) {throw std::logic_error("Chart is empty!");} return OrgChart::Iterator(nullptr, iterType::preOrder);}

OrgChart::Iterator OrgChart::begin() const {if (root == nullptr) {throw std::logic_error("Chart is empty!");} return OrgChart::Iterator(this->root, iterType::levelOrder);}

OrgChart::Iterator OrgChart::end() const {if (root == nullptr) {throw std::logic_error("Chart is empty!");} return OrgChart::Iterator();}  

namespace ariel {

    std::ostream& operator << (std::ostream &os, const OrgChart &oc) {
        for (Node *node : oc.getNodes()) {
            os << *node << " ";
        }
        os << std::endl;
        return os;
    }

}