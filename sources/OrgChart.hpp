#include <string>
#include <iostream>
#include "Node.hpp"

namespace ariel {

    class OrgChart {
        public:

        class Iterator {
            private:
                Node *nodePtr;
                
            public:
                // contructors
                Iterator(Node *ptr = nullptr);
                Node *getNodePtr();
                //operator overloading
                Iterator& operator++();
                Iterator operator++(int);
                const std::string& operator*() const;
                const std::string* operator->() const;
                bool operator==(const Iterator &iter) const;
                bool operator!=(const OrgChart::Iterator &it) const;

        }; 
            private:
                Node* root;
                std::vector<Node *> allNodes;
                //help functions
                static void swap(Node **, Node **);
                static void reverseList(std::vector<Node *> &);
                std::vector<Node *> getNodes() const;
                void preorder(Node *, std::vector<Node *> &) const;
                static void setNodesNextPointers(std::vector<Node *> &);
                static void printList(std::vector<Node *> &);
            public:
                //default contructor
                OrgChart();
                //move contructor
                OrgChart(OrgChart &&og) noexcept;
                //destructor
                ~OrgChart();
                // deep copy contructor and operator
                OrgChart(const OrgChart &og);

                OrgChart& operator=(OrgChart &&og) noexcept;
                OrgChart& operator=(const OrgChart &og) noexcept;
                
                OrgChart &add_root(const std::string &root);
                OrgChart &add_sub(const std::string &parent, const std::string &child);

                Iterator begin_level_order() const;
                Iterator end_level_order() const;
                Iterator begin_reverse_order() const;
                Iterator reverse_order() const;
                Iterator begin_preorder() const;
                Iterator end_preorder() const;
                Iterator begin() const;
                Iterator end() const;
                friend std::ostream& operator << (std::ostream &os, const OrgChart &oc);
    };

}