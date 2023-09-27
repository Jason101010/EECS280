// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(JACK, HEARTS);
    ASSERT_EQUAL(JACK, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());

    Card d;
    ASSERT_EQUAL(TWO, d.get_rank());
    ASSERT_EQUAL(SPADES, d.get_suit());

    Card a(KING, DIAMONDS);
    ASSERT_EQUAL(KING, a.get_rank());
    ASSERT_EQUAL(DIAMONDS, a.get_suit());

    Card b(QUEEN, CLUBS);
    ASSERT_EQUAL(QUEEN, b.get_rank());
    ASSERT_EQUAL(CLUBS, b.get_suit());

    Card e(ACE, SPADES);
    Card f(JACK, DIAMONDS);

    Suit trump = DIAMONDS;
    ASSERT_EQUAL(DIAMONDS, c.get_suit(trump));
    ASSERT_EQUAL(DIAMONDS, f.get_suit(trump));

    ASSERT_TRUE(c.is_face_or_ace());
    ASSERT_FALSE(d.is_face_or_ace());
    ASSERT_TRUE(a.is_face_or_ace());
    ASSERT_TRUE(b.is_face_or_ace());
    ASSERT_TRUE(e.is_face_or_ace());

    ASSERT_TRUE(f.is_right_bower(trump));
    ASSERT_FALSE(a.is_right_bower(trump));
    ASSERT_FALSE(b.is_right_bower(trump));
    ASSERT_FALSE(c.is_right_bower(trump));
    ASSERT_FALSE(d.is_right_bower(trump));
    ASSERT_FALSE(e.is_right_bower(trump));

    ASSERT_TRUE(c.is_left_bower(trump));
    ASSERT_FALSE(a.is_left_bower(trump));
    ASSERT_FALSE(b.is_left_bower(trump));
    ASSERT_FALSE(d.is_left_bower(trump));
    ASSERT_FALSE(e.is_left_bower(trump));
    ASSERT_FALSE(f.is_left_bower(trump));

    ASSERT_TRUE(c.is_trump(trump));
    ASSERT_TRUE(f.is_trump(trump));
    ASSERT_FALSE(d.is_trump(trump));
    ASSERT_FALSE(e.is_trump(trump));
    ASSERT_TRUE(a.is_trump(trump));
    ASSERT_FALSE(b.is_trump(trump));

    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS);
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS);
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS);
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);
}

TEST(test_card_less_trump_only) {
    Card a(JACK, SPADES);
    Card b(JACK, CLUBS);
    Card c(ACE, SPADES);
    Card d(KING, SPADES);
    Card e(NINE, SPADES);
    Card f(ACE, DIAMONDS);
    Card g(ACE, HEARTS);
    Card h(KING, DIAMONDS);
    Card i(KING, CLUBS);
    Card j(JACK, DIAMONDS);
    Card k(JACK, HEARTS);
    Card l(NINE, DIAMONDS);
    Card m(NINE, HEARTS);
    Card n(TEN, CLUBS);

    Suit trump = SPADES;

    ASSERT_FALSE(Card_less(a, b, trump));
    ASSERT_FALSE(Card_less(b, c, trump));
    ASSERT_TRUE(Card_less(c, a, trump));
    ASSERT_FALSE(Card_less(c, d, trump));
    ASSERT_FALSE(Card_less(d, e, trump));
    ASSERT_FALSE(Card_less(a, f, trump));
    ASSERT_FALSE(Card_less(b, f, trump));
    ASSERT_FALSE(Card_less(c, f, trump));
    ASSERT_FALSE(Card_less(d, f, trump));
    ASSERT_FALSE(Card_less(e, f, trump));
    ASSERT_FALSE(Card_less(f, g, trump));
    ASSERT_FALSE(Card_less(f, h, trump));
    ASSERT_FALSE(Card_less(d, h, trump));
    ASSERT_FALSE(Card_less(e, i, trump));
    ASSERT_FALSE(Card_less(b, j, trump));
    ASSERT_FALSE(Card_less(b, k, trump));
    ASSERT_FALSE(Card_less(a, j, trump));
    ASSERT_FALSE(Card_less(a, k, trump));
    ASSERT_FALSE(Card_less(j, k, trump));
    ASSERT_FALSE(Card_less(k, m, trump));
    ASSERT_FALSE(Card_less(l, m, trump));
    ASSERT_FALSE(Card_less(n, l, trump));
    ASSERT_FALSE(Card_less(e, l, trump));
    ASSERT_FALSE(Card_less(e, m, trump));

}

TEST(test_card_less_trump_lead) {
    Card a(JACK, SPADES);
    Card b(JACK, CLUBS);
    Card c(ACE, SPADES);
    Card d(KING, SPADES);
    Card e(NINE, SPADES);
    Card f(ACE, DIAMONDS);
    Card g(KING, DIAMONDS);
    Card h(JACK, DIAMONDS);
    Card i(NINE, DIAMONDS);
    Card j(ACE, CLUBS);
    Card k(ACE, HEARTS);
    Card l(JACK, HEARTS);
    Card m(NINE, CLUBS);
    Card n(NINE, HEARTS);
    Card o(TEN, CLUBS);
    Card p(QUEEN, HEARTS);

    Suit trump = SPADES;
    Card lead(ACE, DIAMONDS);
    ASSERT_FALSE(Card_less(a, b, lead, trump));
    ASSERT_FALSE(Card_less(b, c, lead, trump));
    ASSERT_FALSE(Card_less(c, d, lead, trump));
    ASSERT_FALSE(Card_less(d, e, lead, trump));
    ASSERT_FALSE(Card_less(b, f, lead, trump));
    ASSERT_FALSE(Card_less(c, f, lead, trump));
    ASSERT_FALSE(Card_less(c, j, lead, trump));
    ASSERT_FALSE(Card_less(c, k, lead, trump));
    ASSERT_FALSE(Card_less(d, g, lead, trump));
    ASSERT_FALSE(Card_less(e, f, lead, trump));
    ASSERT_FALSE(Card_less(e, h, lead, trump));
    ASSERT_FALSE(Card_less(e, j, lead, trump));
    ASSERT_FALSE(Card_less(e, i, lead, trump));
    ASSERT_FALSE(Card_less(a, h, lead, trump));
    ASSERT_FALSE(Card_less(b, h, lead, trump));
    ASSERT_FALSE(Card_less(h, j, lead, trump));
    ASSERT_FALSE(Card_less(f, j, lead, trump));
    ASSERT_FALSE(Card_less(j, k, lead, trump));
    ASSERT_FALSE(Card_less(f, k, lead, trump));
    ASSERT_FALSE(Card_less(a, l, lead, trump));
    ASSERT_FALSE(Card_less(b, l, lead, trump));
    ASSERT_FALSE(Card_less(h, l, lead, trump));
    ASSERT_FALSE(Card_less(a, h, lead, trump));
    ASSERT_FALSE(Card_less(b, h, lead, trump));
    ASSERT_FALSE(Card_less(l, m, lead, trump));
    ASSERT_FALSE(Card_less(m, n, lead, trump));
    ASSERT_FALSE(Card_less(p, l, lead, trump));
    ASSERT_FALSE(Card_less(o, m, lead, trump));
    ASSERT_FALSE(Card_less(o, n, lead, trump));
    Card lead22(JACK, CLUBS);
    Card ss(QUEEN, DIAMONDS);
    Card sss(NINE, CLUBS);
    ASSERT_TRUE(Card_less(sss, ss, lead22, trump));
    //If lead suit == trump suit??
}

TEST(test_comparison) {
    Card a(ACE, SPADES);
    Card b;
    Card c(KING, DIAMONDS);
    Card d(KING, CLUBS);
    Card e(KING, SPADES);
    Card f(JACK, HEARTS);
    Card g(JACK, SPADES);
    Card h(TEN, DIAMONDS);
    Card i(TEN, DIAMONDS);
    Card j(NINE, DIAMONDS);
    Card k(NINE, SPADES);
    Card l(ACE, CLUBS);

    ASSERT_TRUE(a > b);
    ASSERT_TRUE(a < l);
    ASSERT_TRUE(c >= d);
    ASSERT_TRUE(b < c);
    ASSERT_TRUE(e >= f);
    ASSERT_TRUE(a > b);
    ASSERT_TRUE(h <= i);
    ASSERT_TRUE(h == i);
    ASSERT_TRUE(j != k);
    ASSERT_TRUE(g > j);
    ASSERT_TRUE(k <= j);

}
TEST_MAIN()
