/* main.cpp
this is a test main
*/
#include "HashTable.h"

int pass = 0, fail = 0;

void check(const std::string& msg, const bool condition) {
    if(condition) {
        std::cout << msg << ": PASS" << std::endl;
        pass++;
    } else {
        std::cout << msg << ": FAIL" << std::endl;
        fail++;
    }
}

void line() {
    std::cout << std::string(50, '-') << std::endl;
}

int main() {
    HashTable<int, std::string> table;

    // test 1
    line();
    std::cout << "TEST 1 - Insert() and Get()" << std::endl;
    std::cout << "** Inserting 1:one, 2:two, 3:three, 4:four **" << std::endl;
    table.Insert(1, "one");
    table.Insert(2, "two");
    table.Insert(3, "three");
    table.Insert(4, "four");
    check("table.Get(1) should == one", table.Get(1) == "one");
    check("table.Get(2) should == two", table.Get(2) == "two");
    check("table.Get(3) should == three", table.Get(3) == "three");
    check("table.Get(4) should == four", table.Get(4) == "four");
    check("table size should now be 4: ", table.Size() == 4);

    std::cout << "Now trying get on values that dont exist: " << std::endl;
    check("table.Get(5) shouldn't work", table.Get(5).has_value() == false);
    check("table.Get(6) shouldn't work", table.Get(6).has_value() == false);
    check("table.Get(7) shouldn't work", table.Get(7).has_value() == false);
    check("table.Get(8) shouldn't work", table.Get(8).has_value() == false);

    // test 2
    line();
    std::cout << "TEST 2 - Remove()" << std::endl;
    std::cout << "** Removing 3:three and 4:four **" << std::endl;
    table.Remove(3);
    table.Remove(4);
    check("After removing 3 and 4, size should now be 2: ", table.Size() == 2);
    check("table.Get(3) shouldn't work", table.Get(3).has_value() == false);
    check("table.Get(4) shouldn't work", table.Get(4).has_value() == false);

    std::cout << "** Removing 1:one and 2:two **" << std::endl;
    table.Remove(1);
    table.Remove(2);
    check("After removing 1 and 2, size should now be 0: ", table.Size() == 0);
    check("Table should now be empty: ", table.IsEmpty() == true);

    // test 3
    line();
    HashTable<int, int> table2;
    std::cout << "TEST 3 - Resize()" << std::endl;
    std::cout << "** Adding inserting 16 key-value pairs to a new table **" << std::endl;
    for(int i = 0; i < 16; ++i) {
        table2.Insert(i, i);
    }
    check("Size should now be 16: ", table2.Size() == 16);
    std::cout << "Checking get on all 16 keys of table2: " << std::endl;
    for(int i = 0; i < 16; ++i) {
        std::string msg = "table2.Get(";
        std::string iStr = std::to_string(i) + "): ";
        check(msg + iStr, table2.Get(i) == i);
    }

    // results
    std::cout << "===== RESULTS =====" << std::endl;
    std::cout << "PASS : " << pass << std::endl;
    std::cout << "FAIL : " << fail << std::endl;


    return 0;
}