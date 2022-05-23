
// #include <iostream>
// #include <vector>
// #include "OrgChart.hpp"
// using namespace ariel;

// int main(int argc, char const *argv[]) {
//     OrgChart org;
// //     try {
// //         org.add_sub("ceo", "ooe");
// //     } catch(std::exception e) {

// //     }
    
//     org.add_root("CEO")
//     .add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
//     .add_sub("CEO", "CFO")         // Now the CFO is subordinate to the CEO
//     .add_sub("CEO", "COO")         // Now the COO is subordinate to the CEO
//     .add_sub("CTO", "VP_SW") // Now the VP Software is subordinate to the CTO
//     .add_sub("COO", "VP_BI");      // Now the VP_BI is subordinate to the COO
//     for (auto it = org.begin_reverse_order(); it != org.reverse_order(); ++it) {
//         std::cout << *it << std::endl;
//     }

//     return 0;
// }
