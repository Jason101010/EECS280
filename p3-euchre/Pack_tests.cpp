// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"

#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());

    Card second = pack.deal_one();
    ASSERT_EQUAL(TEN, second.get_rank());
    ASSERT_EQUAL(SPADES, second.get_suit());

    for (int i = 2; i < 23; ++i) {
        pack.deal_one();
        ASSERT_FALSE(pack.empty());
    }
    Card last = pack.deal_one();
    ASSERT_EQUAL(ACE, last.get_rank());
    ASSERT_EQUAL(DIAMONDS, last.get_suit());
    ASSERT_TRUE(pack.empty());

    pack.reset();
    Card reset = pack.deal_one();
    ASSERT_EQUAL(reset, Card(NINE, SPADES));
}


TEST(test_pack_istream_ctor) {
    const string filename = "pack.in";
    ifstream ifs(filename);
    assert(ifs.is_open());

    Pack pack(ifs);
    Card first = pack.deal_one();
    ASSERT_EQUAL(first, Card(NINE, SPADES));
    Card second = pack.deal_one();
    ASSERT_EQUAL(second, Card(TEN, SPADES));

    for (int i = 2; i < 23; ++i) {
        pack.deal_one();
        ASSERT_FALSE(pack.empty());
    }

    Card last = pack.deal_one();
    ASSERT_EQUAL(ACE, last.get_rank());
    ASSERT_EQUAL(DIAMONDS, last.get_suit());
    ASSERT_TRUE(pack.empty());

    pack.reset();
    ASSERT_FALSE(pack.empty());
    Card reset = pack.deal_one();
    ASSERT_EQUAL(reset, Card(NINE, SPADES));
}


TEST(test_pack_shuffle) {
    const string filename = "pack.in";
    ifstream ifs(filename);
    assert(ifs.is_open());

    Pack pack(ifs);

    Card first = pack.deal_one();
    cout << "first shuffle: " << first << endl;
    ASSERT_EQUAL(first, Card(NINE, CLUBS));
    Card second = pack.deal_one();
    ASSERT_EQUAL(second, Card(NINE, SPADES));
    Card third = pack.deal_one();
    ASSERT_EQUAL(third, Card(TEN, CLUBS));
    Card fourth = pack.deal_one();
    ASSERT_EQUAL(fourth, Card(TEN, SPADES));

    for (int i = 4; i < 22; ++i) {
        pack.deal_one();
    }

    Card last_two = pack.deal_one();
    Card last_one = pack.deal_one();
    ASSERT_EQUAL(last_two, Card(ACE, DIAMONDS));
    ASSERT_EQUAL(last_one, Card(ACE, HEARTS));

    pack.reset();
    Card reset = pack.deal_one();
    ASSERT_EQUAL(reset, Card(NINE, CLUBS));
}


TEST(test_pack_shuffle_twice) {
    Pack pack;
    pack.shuffle();
    pack.shuffle();
    Card first = pack.deal_one();
    ASSERT_EQUAL(first, Card(NINE, DIAMONDS));
    Card second = pack.deal_one();
    ASSERT_EQUAL(second, Card(NINE, CLUBS));
    Card third = pack.deal_one();
    ASSERT_EQUAL(third, Card(NINE, HEARTS));
    Card fourth = pack.deal_one();
    ASSERT_EQUAL(fourth, Card(NINE, SPADES));

    for (int i = 4; i < 22; ++i) {
        pack.deal_one();
    }

    Card last_two = pack.deal_one();
    Card last_one = pack.deal_one();
    ASSERT_EQUAL(last_two, Card(ACE, HEARTS));
    ASSERT_EQUAL(last_one, Card(ACE, SPADES));

    pack.reset();
    Card reset = pack.deal_one();
    ASSERT_EQUAL(reset, Card(NINE, DIAMONDS));
}

TEST_MAIN()
