// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here

TEST(test_List_default_constructor) {
    List<int> a;
    ASSERT_TRUE(a.size() == 0);
    ASSERT_TRUE(a.empty());
    List<bool> b;
    ASSERT_TRUE(b.size() == 0);
    ASSERT_TRUE(b.empty());
    List<string> c;
    ASSERT_TRUE(c.size() == 0);
    ASSERT_TRUE(c.empty());
}

TEST(test_List) {
    //adding elements
    List<int> a;
    int input1 = 7;
    a.push_back(input1);
    List<int>::Iterator begin1 = a.begin();
    ASSERT_TRUE(a.front() == 7);
    ASSERT_TRUE(a.back() == 7);
    ASSERT_TRUE(*begin1 == a.front());
    ASSERT_TRUE(*begin1 == a.back());
    int input2 = 11;
    a.push_front(input2);
    ASSERT_TRUE(a.front() == 11);
    ASSERT_TRUE(a.back() == 7);
    List<int>::Iterator begin2 = a.begin();
    ASSERT_TRUE(*begin2 == a.front());
    ASSERT_TRUE(*begin1 == a.back());
    int input3 = 1;
    a.push_back(input3);
    ASSERT_TRUE(a.front() == 11);
    ASSERT_TRUE(a.back() == 1);
    ASSERT_TRUE(*begin2 == a.front());
    ++begin1; //begin 1 now points to the third and final element in the list
    ASSERT_TRUE(*begin1 == a.back());
    ASSERT_TRUE(a.size() == 3);
    --begin1;
    a.push_front(input1);
    --begin1;
    ASSERT_TRUE(begin1 == begin2);

    //7 11 7 1

    //removing elements
    a.pop_front();
    ASSERT_TRUE(a.front() == 11);
    ASSERT_TRUE(a.back() == 1);
    a.pop_back();
    ASSERT_TRUE(a.front() == 11);
    ASSERT_TRUE(a.back() == 7);
    a.clear();
    ASSERT_TRUE(a.size() == 0);
    ASSERT_TRUE(a.empty());

    //When an element of a list is deleted, the iterator
    //that pointed to it still points to it; how to deal with this problem?
}

TEST(test_list_basic) {
    List<int> a;
    int datum1 = 0;
    a.push_front(datum1);
    ASSERT_EQUAL(a.front(), 0);
    a.pop_back();
    ASSERT_TRUE(a.empty());

    List<int> b;
    int datum2 = -5;
    b.push_back(datum2);
    ASSERT_EQUAL(b.back(), -5);
    b.pop_front();
    ASSERT_TRUE(b.empty());
}

TEST(test_list_copy_contructor) {
    List<int> a;
    int datum1 = -3;
    a.push_front(datum1);
    int datum2 = -2;
    a.push_back(datum2);
    int datum3 = -1;
    a.push_back(datum3);
    int datum4 = 0;
    a.push_back(datum4);
    int datum5 = 1;
    a.push_back(datum5);

    List<int> b(a);
    ASSERT_EQUAL(b.front(), -3);
    ASSERT_EQUAL(b.back(), 1);
    ASSERT_EQUAL(b.size(), 5);
    b.pop_front();
    ASSERT_EQUAL(b.front(), -2);
    b.pop_back();
    ASSERT_EQUAL(b.back(), 0);
    ASSERT_EQUAL(b.size(), 3);
    ASSERT_EQUAL(a.front(), -3);
    ASSERT_EQUAL(a.back(), 1);
    ASSERT_EQUAL(a.size(), 5);
}

TEST(test_list_assignment1) {
    List<int> a;
    int datum1 = -3;
    a.push_front(datum1);
    int datum2 = -2;
    a.push_back(datum2);
    int datum3 = -1;
    a.push_back(datum3);
    int datum4 = 0;
    a.push_back(datum4);
    int datum5 = 1;
    a.push_back(datum5);

    List<int> c;
    c = a;
    ASSERT_EQUAL(c.front(), -3);
    ASSERT_EQUAL(c.back(), 1);
    ASSERT_EQUAL(c.size(), 5);
    c.pop_front();
    ASSERT_EQUAL(c.front(), -2);
    c.pop_back();
    ASSERT_EQUAL(c.back(), 0);
    ASSERT_EQUAL(c.size(), 3);
    ASSERT_EQUAL(a.front(), -3);
    ASSERT_EQUAL(a.back(), 1);
    ASSERT_EQUAL(a.size(), 5);
}

TEST(test_list_assignment2) {
    List<int> a;
    int datum1 = -3;
    a.push_front(datum1);
    int datum2 = -2;
    a.push_back(datum2);
    int datum3 = -1;
    a.push_back(datum3);
    int datum4 = 0;
    a.push_back(datum4);
    int datum5 = 1;
    a.push_back(datum5);

    List<int> c;
    c.push_front(datum1);
    c.push_front(datum2);
    c.push_front(datum3);
    c.push_front(datum4);
    c.push_front(datum5);

    c = a;
    ASSERT_EQUAL(c.front(), -3);
    ASSERT_EQUAL(c.back(), 1);
    ASSERT_EQUAL(c.size(), 5);
    c.clear();
    ASSERT_TRUE(c.empty());
}


TEST(test_iterator) {
    List<string> a;
    string input1 = "AA";
    a.push_back(input1);
    ASSERT_TRUE(a.front() == "AA");
    ASSERT_TRUE(a.back() == "AA");
    List<string>::Iterator begin1 = a.begin();
    ASSERT_TRUE(*begin1 == a.front());
    ASSERT_TRUE(*begin1 == a.back());
    a.erase(begin1);
    ASSERT_TRUE(a.empty());
    a.push_front(input1);
    List<string>::Iterator begin2 = a.begin();
    ASSERT_TRUE(*begin2 == "AA");
    string input2 = "BB";
    a.insert(begin2, input2);
    ASSERT_TRUE(a.front() == "BB");
    ASSERT_TRUE(a.back() == "AA");
    ASSERT_TRUE(a.size() == 2);
    ASSERT_TRUE(a.back() == *begin2);
    //BB AA
    string input3 = "CC";
    string input4 = "DD";
    string input5 = "EE";
    a.push_back(input3);
    a.push_back(input4);
    a.push_back(input5);
    //BB AA CC DD EE
    string temp = "";
    for (List<string>::Iterator i = a.begin(); i != a.end(); ++i) {
        temp += *i;
    }
    ASSERT_TRUE(temp == "BBAACCDDEE");
    List<string>::Iterator tempit;
    for (List<string>::Iterator i = a.begin(); i != a.end(); i = i) {
        tempit = i;
        ++tempit;
        a.erase(i);
        i = tempit;
    }
    ASSERT_TRUE(a.empty());

    List<string> b;
    string i1 = "A";
    b.push_back(i1);
    List<string>::Iterator it1 = b.begin();
    string i2 = "B";
    b.push_back(i2);
    string i3 = "C";
    b.insert(it1, i3);
    string i4 = "D";
    List<string>::Iterator it2 = b.begin();
    ++it2;
    ++it2;
    //C A B
    b.insert(it2, i4);
    //C A D B
    string temp2 = "";
    for (List<string>::Iterator i = b.begin(); i != b.end(); ++i) {
        temp2 += *i;
    }
    ASSERT_TRUE(temp2 == "CADB");
    List<string>::Iterator iter1 = b.begin(); //C
    List<string>::Iterator iter2 = b.begin();
    ++iter2; //A
    List<string>::Iterator iter3 = iter2;
    ++iter3; //D
    List<string>::Iterator iter4 = iter3;
    ++iter4; //B
    b.erase(iter3); // CAB
    ASSERT_TRUE(b.front() == "C");
    ASSERT_TRUE(b.back() == "B");
    List<string>::Iterator iter5 = b.begin();
    ++iter5;
    ASSERT_TRUE(*iter5 == "A");
    b.erase(iter1);
    ASSERT_TRUE(b.front() == "A");
    ASSERT_TRUE(b.back() == "B");
    b.erase(iter4);
    ASSERT_TRUE(b.front() == "A");
    ASSERT_TRUE(b.back() == "A");
}

TEST(test_iterator_additional) {
    List<int> a;
    List<int>::Iterator iter1; //default constructor
    a.insert(iter1, 5);
    ASSERT_EQUAL(a.back(), 5);
    a.insert(iter1, -2);
    ASSERT_EQUAL(a.front(), 5);
    ASSERT_EQUAL(a.back(), -2);
    ASSERT_EQUAL(a.size(), 2);
}

TEST(test_list_big_three) {
    List<string> a;
    string input1 = "A";
    string input2 = "B";
    string input3 = "C";
    string input4 = "D";
    string input5 = "E";
    a.push_back(input1);
    a.push_back(input2);
    a.push_back(input3);
    a.push_back(input4);
    a.push_back(input5);
    //ABCDE
    List<string>::Iterator it1 = a.begin();
    List<string>::Iterator it2 = a.begin();
    ASSERT_TRUE(it1 == it2);
    ++it1;
    ASSERT_TRUE(it1 != it2);
    ++it2;
    ASSERT_TRUE(it1 == it2);
    List<string> a_copy;
    a_copy = a;
    string temp = "";
    for (List<string>::Iterator i = a_copy.begin(); i != a_copy.end(); ++i) {
        temp += *i;
    }
    ASSERT_TRUE(temp == "ABCDE");
    List<string> a_copy2(a_copy);
    string temp2 = "";
    for (List<string>::Iterator i = a_copy2.begin(); i != a_copy2.end(); ++i) {
        temp2 += *i;
    }
    ASSERT_TRUE(temp2 == "ABCDE");
    a_copy2.clear();
    ASSERT_TRUE(a_copy2.empty());

    List<string>::Iterator it3;
    List<string>::Iterator it4;
    ASSERT_TRUE(it3 == it4);

    List<int> b;
    List<int> c;
    c = b;
    ASSERT_TRUE(c.empty());
    int intput1 = 3;
    int intput2 = 5;
    b.push_back(intput1);
    b.push_back(intput2);
    c.push_back(intput1);
    c.push_back(intput2);
    b = c;
    ASSERT_TRUE(b.front() == 3);
    ASSERT_TRUE(b.back() == 5);
}

TEST(test_additional) {
    List<int> a;
    int input1 = 9;
    List<int>::Iterator it1 = a.begin();
    a.insert(it1, input1);
    ASSERT_TRUE(a.front() == 9);
    ASSERT_TRUE(a.back() == 9);
    ASSERT_TRUE(a.size() == 1);
    int input2 = 1;
    a.insert(it1, input2);
    ASSERT_TRUE(a.front() == 9);
    ASSERT_TRUE(a.back() == 1);
    ASSERT_TRUE(a.size() == 2);
    a.clear();
    ASSERT_TRUE(a.empty());
}

TEST_MAIN()