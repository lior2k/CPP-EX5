#include "OrgChart.hpp"
using namespace ariel;

// ------------------- Iterator --------------------
OrgChart::Iterator::Iterator(Node *ptr) {
    nodePtr = ptr;
} 

Node * OrgChart::Iterator::getNodePtr() {return this->nodePtr;}

OrgChart::Iterator& OrgChart::Iterator::operator++() {
    nodePtr = nodePtr->getNext();
    return *this;
}

OrgChart::Iterator OrgChart::Iterator::operator++(int dummy) {
    OrgChart::Iterator temp = *this;
    ++*this;
    return temp;
}

const std::string& OrgChart::Iterator::operator*() const {return this->nodePtr->getData();}

const std::string* OrgChart::Iterator::operator->() const {return &this->nodePtr->getData();}

bool OrgChart::Iterator::operator==(const Iterator &iter) const {return this->nodePtr==iter.nodePtr;}

bool OrgChart::Iterator::operator!=(const OrgChart::Iterator &it) const {return !(this->nodePtr==it.nodePtr);}

// ----------------- end Iterator --------------------

// ------------------- OrgChart -----------------------

// ------------- OrgChart Constructors ----------------
OrgChart::OrgChart() {
    root = nullptr;
}

//move contructor
OrgChart::OrgChart(OrgChart &&og) noexcept {
    root = nullptr;
    *this = og;
}

// deep copy constructor
OrgChart::OrgChart(const OrgChart &og) {
    root = nullptr;
    *this = og;
}

// destructor
OrgChart::~OrgChart() {
    for (Node *node : allNodes) {
        delete node;
    }
}
// ------------ End OrgChart Constructors ----------------

// ---------------- OrgChart Operators -------------------
// deep copy operator =
OrgChart& OrgChart::operator=(const OrgChart &og) noexcept {
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

//move operator
OrgChart& OrgChart::operator=(OrgChart &&og) noexcept {
    *this = std::move(og);
    return *this;
}
// --------------- End OrgChart Operators -------------------


// -------------- OrgChart Help Functions -------------------
std::vector<Node *> OrgChart::getNodes() const {
    return this->allNodes;
}

void OrgChart::swap(Node **first, Node **second) {
    Node* temp = *first;
    *first = *second;
    *second = temp;
}

void OrgChart::reverseList(std::vector<Node *> &list) {
    for (unsigned int i = 0; i < list.size() / 2; i++) {
        swap(&list[i], &list[list.size()-1-i]);
    }
}

/*
    add the root then add children and recursively add each child's children
*/
void OrgChart::preorder(Node *ptr, std::vector<Node *> &list) const {
    list.push_back(ptr);
    for (Node *child : ptr->getChildren()) {
        preorder(child, list);
    }
}

// print list for self debugging
void OrgChart::printList(std::vector<Node *> &list) {
    for (unsigned int i = 0; i < list.size(); i++) {
        std::cout << list[i]->getData() << " ";
    }
}

void OrgChart::setNodesNextPointers(std::vector<Node *> &list) {
    for (uint i = 0; i < list.size()-1; i++) {
        list[i]->setNext(list[i+1]);
    }
    list[list.size()-1]->setNext(nullptr);
}
// ----------- --End OrgChart Help Functions -----------------

// -------------- OrgChart Public Functions -------------------
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

OrgChart::Iterator OrgChart::begin_level_order() const {
    if (root == nullptr) {
        throw std::logic_error("Chart is empty!");
    }
    std::vector<Node *> list;
    std::vector<Node *> nodes;
    nodes.push_back(this->root);
    while (!nodes.empty()) {
        Node *current = nodes[0];
        nodes.erase(nodes.begin());
        list.push_back(current);   
        for (Node *child : current->getChildren()) {
            nodes.push_back(child);
        }
    }
    OrgChart::setNodesNextPointers(list);
    return OrgChart::Iterator(this->root);
}

OrgChart::Iterator OrgChart::end_level_order() const {
    if (root == nullptr) {
        throw std::logic_error("Chart is empty!");
    }
    return OrgChart::Iterator(nullptr);
}

/*
    similar to level order except add children from right to left instead of left to right,
    then reverse the list to get the lowest rows first and the root last
*/
OrgChart::Iterator OrgChart::begin_reverse_order() const {
    if (root == nullptr) {
        throw std::logic_error("Chart is empty!");
    }
    std::vector<Node *> list;
    std::vector<Node *> nodes;
    nodes.push_back(this->root);
    while (!nodes.empty()) {
        Node *current = nodes[0];
        nodes.erase(nodes.begin());
        list.push_back(current);   
        for (uint i = current->getChildren().size()-1; i >= 0; i--) {
            if (i == (uint) - 1) {
                break;
            }
            nodes.push_back(current->getChildren()[(uint)i]);
        }
    }
    OrgChart::reverseList(list);
    OrgChart::setNodesNextPointers(list);
    return OrgChart::Iterator(list[0]);
}

OrgChart::Iterator OrgChart::reverse_order() const {
    if (root == nullptr) {
        throw std::logic_error("Chart is empty!");
    }
    return OrgChart::Iterator(nullptr);
}

OrgChart::Iterator OrgChart::begin_preorder() const {
    if (root == nullptr) {
        throw std::logic_error("Chart is empty!");
    }
    std::vector<Node *> list;
    OrgChart::preorder(this->root, list);
    OrgChart::setNodesNextPointers(list);
    return OrgChart::Iterator(this->root);
}

OrgChart::Iterator OrgChart::end_preorder() const {
    if (root == nullptr) {
        throw std::logic_error("Chart is empty!");
    }
    return OrgChart::Iterator(nullptr);
}

OrgChart::Iterator OrgChart::begin() const {
    if (root == nullptr) {
        throw std::logic_error("Chart is empty!");
    }
    return OrgChart::begin_level_order();
}

OrgChart::Iterator OrgChart::end() const {
    if (root == nullptr) {
        throw std::logic_error("Chart is empty!");
    }
    return OrgChart::Iterator();
}
// ------------ End OrgChart Public Functions -------------------

namespace ariel {

    std::ostream& operator << (std::ostream &os, const OrgChart &oc) {
        for (Node *node : oc.getNodes()) {
            os << *node << " ";
        }
        os << std::endl;
        return os;
    }

}