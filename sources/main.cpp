// #include "OrgChart.hpp"
// using namespace ariel;

// int main(int argc, char const *argv[])
// {
//     OrgChart org;
//     org.add_root("CEO")
//       .add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
//       .add_sub("CEO", "CFO")         // Now the CFO is subordinate to the CEO
//       .add_sub("CEO", "COO")         // Now the COO is subordinate to the CEO
//       .add_sub("CTO", "VP_SW") // Now the VP Software is subordinate to the CTO
//       .add_sub("COO", "VP_BI");      // Now the VP_BI is subordinate to the COO

//     OrgChart org2(org);
//     org2.add_sub("CEO", "Lior");
//     std::cout << org2 << std::endl;
// std::cout << org << std::endl;
//     return 0;
// }
