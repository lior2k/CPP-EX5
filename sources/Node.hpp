#include <string>
#include <iostream>
#include <vector>

namespace ariel {

    class Node {
        private:
            std::string data;
            std::vector<Node*> children;
            Node *next;
        public:
            Node(const std::string &data);
            std::vector<Node*> getChildren();
            Node *getNext();
            void setNext(Node *);
            void addChild(Node *);
            void setData(const std::string&);
            const std::string& getData() const;

            //deep copy node
            Node(Node *n);
    };

    std::ostream& operator << (std::ostream &os, Node &node);

}