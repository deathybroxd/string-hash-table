/* main.cpp
this is a test main
*/
#include "StringHashTable.h"

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
    StringHashTable<int> table;

    // test 1
    line();
    std::cout << "TEST 1 - Insert() and Get()" << std::endl;
    std::cout << "** Inserting one:1, two:2, three:3, four:4 **" << std::endl;
    table.Insert("one", 1);
    table.Insert("two", 2);
    table.Insert("three", 3);
    table.Insert("four", 4);
    check("table.Get(\"one\") should == 1", table.Get("one") == 1);
    check("table.Get(\"two\") should == 2", table.Get("two") == 2);
    check("table.Get(\"three\") should == 3", table.Get("three") == 3);
    check("table.Get(\"four\") should == 4", table.Get("four") == 4);
    check("table size should now be 4: ", table.Size() == 4);

    std::cout << "Now trying get on values that dont exist: " << std::endl;
    check("table.Get(\"five\") shouldn't work", table.Get("five").has_value() == false);
    check("table.Get(\"six\") shouldn't work", table.Get("six").has_value() == false);
    check("table.Get(\"seven\") shouldn't work", table.Get("seven").has_value() == false);
    check("table.Get(\"eight\") shouldn't work", table.Get("eight").has_value() == false);

    // test 2
    line();
    std::cout << "TEST 2 - Remove()" << std::endl;
    std::cout << "** Removing three and four **" << std::endl;
    table.Remove("three");
    table.Remove("four");
    check("After removing three and four, size should now be 2: ", table.Size() == 2);
    check("table.Get(\"three\") shouldn't work", table.Get("three").has_value() == false);
    check("table.Get(\"four\") shouldn't work", table.Get("four").has_value() == false);

    std::cout << "** Removing one and two **" << std::endl;
    table.Remove("one");
    table.Remove("two");
    check("After removing one and two, size should now be 0: ", table.Size() == 0);
    check("Table should now be empty: ", table.IsEmpty() == true);

    // test 3
    line();
    StringHashTable<int> table2;
    std::cout << "TEST 3 - Resize()" << std::endl;
    std::cout << "** Inserting 16 key-value pairs to a new table **" << std::endl;
    for(int i = 0; i < 16; ++i) {
        table2.Insert(std::to_string(i), i);
    }
    check("Size should now be 16: ", table2.Size() == 16);
    std::cout << "Checking get on all 16 keys of table2: " << std::endl;
    for(int i = 0; i < 16; ++i) {
        std::string msg = "table2.Get(\"" + std::to_string(i) + "\"): ";
        check(msg, table2.Get(std::to_string(i)) == i);
    }

    // results
    std::cout << "===== RESULTS =====" << std::endl;
    std::cout << "PASS : " << pass << std::endl;
    std::cout << "FAIL : " << fail << std::endl;
    line();

    return 0;
}