#include "doctest.h"
#include "OrgChart.hpp"
using namespace ariel;
using namespace std;

TEST_CASE("CASE 1") {

    OrgChart chart;
    chart.add_root("Lior")
    .add_sub("Lior", "Liel")
    .add_sub("Lior", "Moriya Rahel")
    .add_sub("Lior", "Chai")
    .add_sub("Liel", "Abra")
    .add_sub("Liel", "Yotam")
    .add_sub("Moriya Rahel", "Ben Shlomo")
    .add_sub("Ben Shlomo", "Shani")
    .add_sub("Moriya Rahel", "Efrat")
    .add_sub("Chai", "Nawaf");

    // CHECK(*chart.begin() == "Lior");

    vector<string> checkLevelOrder = {"Lior", "Liel", "Moriya Rahel", "Chai", "Abra", "Yotam", "Ben Shlomo", "Efrat", "Nawaf", "Shani"};
    string st = "Lior Liel Moriya Rahel Chai Abra Yotam Ben Shlomo Efrat Nawaf Shani ";
    string ans;
    OrgChart::Iterator iter = chart.begin_level_order();
    
    for (unsigned int i = 0; i < checkLevelOrder.size(); i++) {
        ++iter;
        ans += *iter + " ";
        CHECK(checkLevelOrder[i] == *iter);
    }
    CHECK(ans == st);

    vector<string> checkReversedOrder = {"Shani", "Nawaf", "Efrat", "Ben Shlomo", "Yotam", "Abra", "Chai", "Moriya Rahel", "Liel", "Lior"};
    st = "Shani Nawaf Efrat Ben Shlomo Yotam Abra Chai Moriya Rahel Liel Lior ";
    ans = "";
    iter = chart.begin_reverse_order();
    for (unsigned int i = 0; i < checkReversedOrder.size(); i++) {
        ++iter;
        ans += *iter + " ";
        CHECK(checkReversedOrder[i] == *iter);
    }
    CHECK(ans == st);

    vector<string> preOrderCheck = {"Lior", "Liel", "Abra", "Yotam", "Moriya Rahel", "Ben Shlomo", "Shani","Efrat", "Chai", "Nawaf"};
    st = "Lior Liel Abra Yotam Moriya Rahel Ben Shlomo Shani Efrat Chai Nawaf";
    ans = "";
    iter = chart.begin_preorder();
    for (unsigned int i = 0; i < preOrderCheck.size(); i++) {
        ++iter;
        ans += *iter + " ";
        CHECK(preOrderCheck[i] == *iter);
    }

    CHECK_THROWS(chart.add_sub("Doesn'tExist", "Employee"));
    
}