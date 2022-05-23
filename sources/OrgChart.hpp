#include <string>
#include <iostream>
#include "Node.hpp"

namespace ariel {

    class OrgChart {
        public:
        enum class iterType{levelOrder, reverseOrder, preOrder};

        class Iterator {
            private:
                Node *nodePtr;
                std::vector<Node *> list;
                unsigned int currentIndex; 
            public:
                // contructors
                Iterator(Node *ptr = nullptr);
                Iterator(Node *, iterType);

                //operator overloading
                Iterator& operator++();
                Iterator operator++(int);
                const std::string& operator*() const;
                const std::string* operator->() const;
                bool operator==(const Iterator &iter) const;
                bool operator!=(const OrgChart::Iterator &it) const;

                //fill functions
                void levelOrder();
                void reverseOrder();
                void preOrder();

                //help functions
                void reverseList();
                static void swap(Node **first, Node **second);
                void dfs(Node *);
                void printList(); //print iterator's for debugging
        }; 
            private:
                Node* root;
                std::vector<Node *> allNodes;
            public:
                //default contructor
                OrgChart();
                //destructor
                ~OrgChart();
                // deep copy contructor and operator
                OrgChart(const OrgChart &og);
                OrgChart& operator=(const OrgChart &og);
                
                std::vector<Node *> getNodes() const;

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
    };

    std::ostream& operator << (std::ostream &os, const OrgChart &oc);

}