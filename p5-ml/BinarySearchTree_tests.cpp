// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <sstream>

using namespace std;

TEST(test_stub) {
    // Add your tests here
    ASSERT_TRUE(true);
}

TEST(test_bst_basics) {
    BinarySearchTree<int> tree;

    //Empty tree
    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(tree.size(), 0);
    ASSERT_EQUAL(tree.height(), 0);
    ASSERT_TRUE(tree.check_sorting_invariant());
    stringstream ss1;
    tree.traverse_inorder(ss1);
    string s1 = "";
    ASSERT_EQUAL(s1, ss1.str());
    
    stringstream ss2;
    tree.traverse_preorder(ss2);
    cout << "Print empty tree" << endl << endl;
    ASSERT_EQUAL(s1, ss2.str());

    //Add basic integers
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(tree.size(), 3);
    ASSERT_EQUAL(tree.height(), 2);
    ASSERT_TRUE(tree.check_sorting_invariant());

    stringstream ss3;
    stringstream ss4;
    tree.traverse_inorder(ss3);
    tree.traverse_preorder(ss4);
    cout << "Print tree";
    string s2 = "1 2 3 ";
    string s3 = "2 1 3 ";
    ASSERT_EQUAL(s2, ss3.str());
    ASSERT_EQUAL(s3, ss4.str());

    //Copy constructor
    BinarySearchTree<int> tree_copy(tree);
    ASSERT_FALSE(tree_copy.empty());
    ASSERT_EQUAL(tree_copy.size(), 3);
    ASSERT_EQUAL(tree_copy.height(), 2);
    ASSERT_TRUE(tree_copy.check_sorting_invariant());

    //Copying empty tree
    BinarySearchTree<int> tree_empty;
    BinarySearchTree<int> tree_copy_empty(tree_empty);
    ASSERT_TRUE(tree_empty.empty());
    ASSERT_TRUE(tree_copy_empty.empty());


    //Assignment operator
    BinarySearchTree<int> tree_copy2;
    tree_copy2.insert(3);
    tree_copy2.insert(5);
    tree_copy2.insert(4);
    ASSERT_TRUE(tree.check_sorting_invariant());
    cout << "Print tree2";
    std::cout << tree_copy2.to_string() << endl << endl;

    //self-assignment
    tree_copy2 = tree_copy2;
    ASSERT_FALSE(tree_copy2.empty());
    ASSERT_TRUE(tree_copy2.size() == 3);
    ASSERT_EQUAL(tree_copy2.height(), 3);
    ASSERT_TRUE(tree.check_sorting_invariant());

    tree_copy2 = tree;
    ASSERT_FALSE(tree_copy2.empty());
    ASSERT_EQUAL(tree_copy2.size(), 3);
    ASSERT_EQUAL(tree_copy2.height(), 2);
    ASSERT_TRUE(tree_copy2.check_sorting_invariant());
    cout << "Print tree2";
    std::cout << tree_copy2.to_string() << endl << endl;

    BinarySearchTree<int> b;
    b.insert(1);
    b.insert(0);
    *b.begin() = 2;
    ASSERT_FALSE(b.check_sorting_invariant());

    BinarySearchTree<int> c;
    c.insert(1);
    c.insert(4);
    c.insert(5);
    c.insert(6);
    c.insert(8);
    ASSERT_TRUE(c.check_sorting_invariant());
    BinarySearchTree<int>::Iterator it = c.begin();
    ++it;
    ++it;
    *it = 7;
    ASSERT_FALSE(c.check_sorting_invariant());
    *it = 5;
    ++it;
    c.insert(7);
    ++it;
    *it = 1;
    ASSERT_FALSE(c.check_sorting_invariant());
}

TEST(test_bst_basics_string) {
    BinarySearchTree<string> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(tree.size(), 0);
    ASSERT_EQUAL(tree.height(), 0);
    ASSERT_TRUE(tree.check_sorting_invariant());

    tree.insert("grape");
    tree.insert("apple");
    tree.insert("orange");
    ASSERT_TRUE(tree.check_sorting_invariant());
    cout << "Print string tree";
    cout << tree.to_string() << endl << endl;
    tree.insert("banana");
    ASSERT_EQUAL(tree.size(), 4);
    ASSERT_EQUAL(tree.height(), 3);
    cout << "Print string tree";
    cout << tree.to_string() << endl << endl;
}

TEST(test_bst_iterator_empty) {
    //Empty tree with nullptr
    BinarySearchTree<int> tree;
    BinarySearchTree<int>::Iterator it1;
    ASSERT_EQUAL(it1, tree.begin());
    ASSERT_EQUAL(it1, tree.end());

    //Min element
    BinarySearchTree<int>::Iterator min = tree.min_element();
    ASSERT_EQUAL(min, tree.end());

    //Max element
    BinarySearchTree<int>::Iterator max = tree.max_element();
    ASSERT_EQUAL(max, tree.end());

    //Min greater than
    BinarySearchTree<int>::Iterator min_greater = tree.min_greater_than(0);
    ASSERT_EQUAL(min_greater, tree.end());

    //Find
    BinarySearchTree<int>::Iterator find = tree.find(5);
    ASSERT_EQUAL(find, tree.end());

    //Can iterator operators be used on null iterator??
    //How to test interator->
    //Does ierator have copy constructor and assignment operator??

    //Operator
    ASSERT_TRUE(tree.begin() == tree.end());
}

TEST(test_bst_iterator_integer) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    ASSERT_TRUE(tree.check_sorting_invariant());
    BinarySearchTree<int>::Iterator it1 = tree.begin();
    BinarySearchTree<int>::Iterator it2 = tree.end();
    ASSERT_EQUAL(*it1, 3);

    //Min element
    BinarySearchTree<int>::Iterator min = tree.min_element();
    ASSERT_EQUAL(*min, 3);

    //Max element
    BinarySearchTree<int>::Iterator max = tree.max_element();
    ASSERT_EQUAL(*max, 3);

    //Min greater than
    BinarySearchTree<int>::Iterator min_greater = tree.min_greater_than(3);
    ASSERT_EQUAL(min_greater, tree.end());
    min_greater = tree.min_greater_than(2);
    ASSERT_EQUAL(*min_greater, 3);

    //Find
    BinarySearchTree<int>::Iterator find = tree.find(5);
    ASSERT_EQUAL(find, tree.end());
    find = tree.find(3);
    ASSERT_EQUAL(*find, 3);

    //++
    BinarySearchTree<int>::Iterator move1 = tree.begin();
    move1++;
    ASSERT_EQUAL(move1, it2);

    //Insert 5
    tree.insert(5);
    ASSERT_TRUE(tree.check_sorting_invariant());
    min = tree.min_element();
    ASSERT_EQUAL(*min, 3);
    max = tree.max_element();
    ASSERT_EQUAL(*max, 5);
    min_greater = tree.min_greater_than(3);
    ASSERT_EQUAL(*min_greater, 5);
    find = tree.find(5);
    ASSERT_EQUAL(*find, 5);
    BinarySearchTree<int>::Iterator move2 = tree.begin();
    ++move2;
    ASSERT_EQUAL(*move2, 5);
    ++move2;
    ASSERT_EQUAL(move2, it2);

    //Insert -2
    tree.insert(-2);
    ASSERT_TRUE(tree.check_sorting_invariant());
    min = tree.min_element();
    ASSERT_EQUAL(*min, -2);

    //Prefix and postfix ++
    BinarySearchTree<int>::Iterator move3 = tree.begin();
    ASSERT_EQUAL(*move3, -2);
    ++++move3;
    cout << *move3 << endl;
    ASSERT_EQUAL(*move3, 5);

    move3 = tree.begin();
    cout << *move3 << endl; //not allowed to have chain postfix++
    move3++;
    cout << *move3 << endl;
    move3++;
    cout << *move3 << endl;
    move3++;
    ASSERT_EQUAL(move3, it2);

    cout << "Print tree";
    std::cout << tree.to_string() << endl << endl;

    //Modify
    BinarySearchTree<int>::Iterator modify = tree.begin();
    *modify = -8;
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_EQUAL(*tree.begin(), -8);
    modify++;
    *modify = 4;
    ASSERT_EQUAL(*modify, 4);
    ASSERT_TRUE(tree.check_sorting_invariant());
    cout << "Print tree";
    std::cout << tree.to_string() << endl << endl;
}

TEST(test_bst_bigtree) {
    BinarySearchTree<int> tree;
    tree.insert(6);
    tree.insert(5);
    tree.insert(9);
    tree.insert(1);
    tree.insert(2);
    tree.insert(7);
    tree.insert(10);
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_EQUAL(tree.size(), 7);
    ASSERT_EQUAL(tree.height(), 4)
        cout << "Print big tree";
    cout << tree.to_string() << endl << endl;

    BinarySearchTree<int>::Iterator it1 = tree.begin();
    BinarySearchTree<int>::Iterator it2 = tree.end();
    ASSERT_EQUAL(*it1, 1);

    //Min
    BinarySearchTree<int>::Iterator min = tree.min_element();
    ASSERT_EQUAL(*min, 1)
        ASSERT_TRUE(it1 == min);

    //Max
    BinarySearchTree<int>::Iterator max = tree.max_element();
    ASSERT_EQUAL(*max, 10)

        //Min greater than
        BinarySearchTree<int>::Iterator min_greater = tree.min_greater_than(0);
    ASSERT_EQUAL(*it1, *min_greater);
    ASSERT_TRUE(it1 == min_greater);
    min_greater = tree.min_greater_than(1);
    ASSERT_EQUAL(*min_greater, 2);
    ASSERT_FALSE(it1 == min_greater);
    ASSERT_TRUE(it1 != min_greater);
    min_greater = tree.min_greater_than(5);
    ASSERT_EQUAL(*min_greater, 6);
    min_greater = tree.min_greater_than(6);
    ASSERT_EQUAL(*min_greater, 7);
    min_greater = tree.min_greater_than(10);
    ASSERT_EQUAL(min_greater, it2);

    //Find
    BinarySearchTree<int>::Iterator find = tree.find(4);
    ASSERT_EQUAL(find, it2);
    find = tree.find(5);
    ASSERT_EQUAL(*find, 5);

    BinarySearchTree<int>::Iterator insert = tree.insert(4);
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_TRUE(tree.find(4) == insert);

}

TEST(test_duck_comparator) {
    class Duck {
    public:
        Duck() : wealth(0) {} // tree requires default-constructible
        Duck(int wealth_in) : wealth(wealth_in) {}
        int getWealth() const { return wealth; }


    private:
        int wealth;

    };

    class DuckWealthLess {
    public:
        bool operator() (const Duck& d1, const Duck& d2) const {
            return d1.getWealth() < d2.getWealth();
        }

    };

    //Passing in custom comparator
    BinarySearchTree<Duck, DuckWealthLess> duck_tree;
    const BinarySearchTree<Duck, DuckWealthLess>& const_duck_tree(duck_tree);
    BinarySearchTree<Duck, DuckWealthLess> duck_tree_copy;
    duck_tree_copy = duck_tree;

    ASSERT_TRUE(duck_tree.empty());
    ASSERT_TRUE(const_duck_tree.empty());
    ASSERT_TRUE(duck_tree_copy.empty());

    ASSERT_TRUE(duck_tree.size() == 0);
    ASSERT_TRUE(const_duck_tree.size() == 0);
    ASSERT_TRUE(duck_tree_copy.size() == 0);

    ASSERT_TRUE(duck_tree.height() == 0);
    ASSERT_TRUE(const_duck_tree.height() == 0);
    ASSERT_TRUE(duck_tree_copy.height() == 0);

    //Insert ducks
    duck_tree.insert(Duck(30));
    duck_tree.insert(Duck(20));
    duck_tree.insert(Duck(50));
    ASSERT_TRUE(duck_tree.check_sorting_invariant());

    //Assignment operators
    duck_tree_copy = duck_tree;
    ASSERT_EQUAL(duck_tree_copy.size(), 3);
    ASSERT_EQUAL(duck_tree_copy.height(), 2);
    ASSERT_FALSE(duck_tree_copy.empty());
    ASSERT_TRUE(duck_tree_copy.check_sorting_invariant());

    //Print out duck_tree
    //duck_tree.traverse_inorder(std::cout);
    //duck_tree.traverse_preorder(std::cout);
    //cout << "Print duck tree";
    //cout << duck_tree.to_string() << endl << endl;

    //Duck iterator
    BinarySearchTree<Duck, DuckWealthLess>::Iterator duck_begin = duck_tree.begin();
    ASSERT_EQUAL((*duck_begin).getWealth(), 20)
        BinarySearchTree<Duck, DuckWealthLess>::Iterator duck_end = duck_tree.end();
    ASSERT_EQUAL(duck_end, duck_tree.end());

    //Insert
    BinarySearchTree<Duck, DuckWealthLess>::Iterator duck_insert = 
        duck_tree.insert(Duck(40));
    ASSERT_TRUE(duck_tree.check_sorting_invariant());
    ASSERT_EQUAL((*duck_insert).getWealth(), 40);

    //Find
    BinarySearchTree<Duck, DuckWealthLess>::Iterator duck_find = duck_tree.find(10);
    ASSERT_EQUAL(duck_find, duck_end);
    duck_find = duck_tree.find(30);
    ASSERT_TRUE((*duck_find).getWealth() == 30);

    //Min
    BinarySearchTree<Duck, DuckWealthLess>::Iterator duck_min = duck_tree.min_element();
    ASSERT_EQUAL((*duck_min).getWealth(), 20);
    ASSERT_TRUE(duck_begin == duck_min);

    //Max
    BinarySearchTree<Duck, DuckWealthLess>::Iterator duck_max = duck_tree.max_element();
    ASSERT_EQUAL((*duck_max).getWealth(), 50);

    //Min greater than
    BinarySearchTree<Duck, DuckWealthLess>::Iterator duck_min_greater
        = duck_tree.min_greater_than(0);
    ASSERT_TRUE(duck_min_greater == duck_min);
    duck_min_greater = duck_tree.min_greater_than(20);
    ASSERT_EQUAL((*duck_min_greater).getWealth(), 30);
    duck_min_greater = duck_tree.min_greater_than(50);
    ASSERT_TRUE(duck_min_greater == duck_end);

    //to string
    //string s1 = const_duck_tree.to_string();
    //string s2 = duck_tree.to_string();

    //operator
    BinarySearchTree<Duck, DuckWealthLess>::Iterator duck_move = duck_begin;
    duck_move++;
    ASSERT_EQUAL((*duck_move).getWealth(), 30);
    ++duck_move;
    ASSERT_EQUAL((*duck_move).getWealth(), 40);
    ++++duck_move;
    ASSERT_EQUAL(duck_move, duck_end);
}

TEST(test_std_pair) {
    BinarySearchTree<std::pair<string, int>> tree;
    tree.insert({ "grape", 8 });
    tree.insert({ "apple", 20 });
    tree.insert({ "orange", 5 });
    ASSERT_FALSE(tree.empty());
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_EQUAL(tree.size(), 3);
    ASSERT_TRUE(tree.height() == 2);

    //tree.traverse_inorder(std::cout);
    //tree.traverse_preorder(std::cout);
    //cout << "Print empty tree";
    //cout << tree.to_string() << endl << endl;

    //Big three
    BinarySearchTree<std::pair<string, int>> tree_copy1(tree);
    ASSERT_TRUE(tree_copy1.check_sorting_invariant());
    BinarySearchTree<std::pair<string, int>> tree_copy2;
    ASSERT_TRUE(tree_copy2.check_sorting_invariant());

    //Iterator
    BinarySearchTree<std::pair<string, int>>::Iterator tree_begin = tree.begin();
    ASSERT_EQUAL(tree.begin()->first, "apple");
    ASSERT_EQUAL(tree.begin()->second, 20);
    ASSERT_EQUAL(tree_begin->first, "apple");
    ASSERT_EQUAL(tree_begin->second, 20);

    //Insert
    BinarySearchTree<std::pair<string, int>>::Iterator tree_insert
        = tree.insert({ "banana", 100 });
    ASSERT_EQUAL(tree_insert->first, "banana");
    ASSERT_EQUAL(tree_insert->second, 100);
    ASSERT_TRUE(tree_begin != tree_insert);

    //Min
    BinarySearchTree<std::pair<string, int>>::Iterator tree_min = tree.min_element();
    ASSERT_EQUAL(tree_min->first, "apple");
    ASSERT_EQUAL(tree_min->second, 20);

    //Max
    BinarySearchTree<std::pair<string, int>>::Iterator tree_max = tree.max_element();
    ASSERT_EQUAL(tree_max->first, "orange");
    ASSERT_EQUAL(tree_max->second, 5);

    //Min greater than
    BinarySearchTree<std::pair<string, int>>::Iterator tree_greater
        = tree.min_greater_than({ "gradonfruit", 4 });
    ASSERT_EQUAL(tree_greater->first, "grape");
    ASSERT_EQUAL(tree_greater->second, 8);

    //Find
    BinarySearchTree<std::pair<string, int>>::Iterator tree_find
        = tree.find({ "banana", 100 });
    ASSERT_EQUAL(tree_find->first, "banana");
    ASSERT_EQUAL(tree_find->second, 100);
    ASSERT_TRUE(tree_find == tree_insert);

    //operator
    BinarySearchTree<std::pair<string, int>>::Iterator tree_traverse;
    tree_traverse = tree_begin;
    ++++tree_traverse;
    ASSERT_EQUAL(tree_traverse->first, "grape");
    ASSERT_EQUAL(tree_traverse->second, 8);
    tree_traverse++;
    ASSERT_EQUAL(tree_traverse->first, "orange");
    ASSERT_EQUAL(tree_traverse->second, 5);
    tree_traverse++;
    ASSERT_TRUE(tree_traverse == tree.end());
}

TEST_MAIN()
