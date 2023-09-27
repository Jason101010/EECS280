// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player* alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}



TEST(test_simple_make_trump1) {
    //Round 1: 0 trump suit; is dealer
    Player* alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(NINE, SPADES));
    alice->add_card(Card(TEN, SPADES));
    alice->add_card(Card(QUEEN, SPADES));
    alice->add_card(Card(KING, SPADES));
    alice->add_card(Card(ACE, SPADES));

    Card upcard1 = Card(ACE, HEARTS);
    Suit order_up1 = DIAMONDS;
    bool make_trump_or_not1 = alice->make_trump(upcard1, true, 1, order_up1);
    ASSERT_FALSE(make_trump_or_not1); //--> No make trump
    ASSERT_EQUAL(order_up1, DIAMONDS); //-->order_up_suit unchanged

    delete alice;

    //Round 1: 1 trump suit (left bower); is not dealer
    Player* bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(NINE, CLUBS));
    bob->add_card(Card(TEN, CLUBS));
    bob->add_card(Card(JACK, SPADES));//trump

    Card upcard2 = Card(ACE, CLUBS);
    Suit order_up2 = DIAMONDS;
    bool make_trump_or_not2 = bob->make_trump(upcard2, false, 1, order_up2);
    ASSERT_FALSE(make_trump_or_not2); //No make trump
    ASSERT_EQUAL(order_up2, DIAMONDS); //-->order_up_suit unchanged

    delete bob;

    //Round1: 1 trump suit (normal trump); is dealer
    Player* biscuit = Player_factory("Biscuit", "Simple");
    biscuit->add_card(Card(NINE, SPADES));
    biscuit->add_card(Card(TEN, SPADES));
    biscuit->add_card(Card(NINE, CLUBS));
    biscuit->add_card(Card(TEN, CLUBS));
    biscuit->add_card(Card(QUEEN, CLUBS));//normal trump

    Card upcard2_1 = Card(ACE, CLUBS);
    Suit order_up2_1 = DIAMONDS;
    bool make_trump_or_not2_1 = biscuit->make_trump(upcard2_1, true, 1, order_up2_1);
    ASSERT_FALSE(make_trump_or_not2_1); //No make trump
    ASSERT_EQUAL(order_up2_1, DIAMONDS); //-->order_up_suit unchanged

    delete biscuit;

    //Round1: 2 trump suits (left bower + 1 normal trump)
    Player* cat = Player_factory("Cat", "Simple");
    cat->add_card(Card(JACK, SPADES)); //trump
    cat->add_card(Card(TEN, SPADES));
    cat->add_card(Card(NINE, HEARTS));
    cat->add_card(Card(TEN, CLUBS));
    cat->add_card(Card(JACK, CLUBS)); //trump

    Card upcard3 = Card(ACE, CLUBS);
    Suit order_up3 = DIAMONDS;
    bool make_trump_or_not3 = cat->make_trump(upcard3, false, 1, order_up3);
    ASSERT_TRUE(make_trump_or_not3);
    ASSERT_EQUAL(order_up3, CLUBS);

    delete cat;

    //Round1: 2 normal turmp suits
    Player* curry = Player_factory("Curry", "Simple");
    curry->add_card(Card(KING, CLUBS)); //trump
    curry->add_card(Card(TEN, SPADES));
    curry->add_card(Card(NINE, HEARTS));
    curry->add_card(Card(TEN, CLUBS));
    curry->add_card(Card(JACK, CLUBS)); //trump

    Card upcard3_1 = Card(ACE, CLUBS);
    Suit order_up3_1 = DIAMONDS;
    bool make_trump_or_not3_1 = curry->make_trump(upcard3_1, false, 1, order_up3_1);
    ASSERT_TRUE(make_trump_or_not3_1);
    ASSERT_EQUAL(order_up3_1, CLUBS);

    delete curry;

    //Round1: three normal face order up
    Player* dog = Player_factory("Dog", "Simple");
    dog->add_card(Card(JACK, SPADES)); //trump
    dog->add_card(Card(KING, SPADES)); //trump
    dog->add_card(Card(QUEEN, SPADES)); //trump
    dog->add_card(Card(KING, CLUBS));
    dog->add_card(Card(QUEEN, CLUBS));

    Card upcard4 = Card(ACE, SPADES);
    Suit order_up4 = DIAMONDS;
    bool make_trump_or_not4 = dog->make_trump(upcard4, true, 1, order_up4);
    ASSERT_TRUE(make_trump_or_not4);
    ASSERT_EQUAL(order_up4, SPADES);

    delete dog;

}



TEST(test_simple_make_trump2) {
    //Round2: 1 trump suit (left bower); not dealer
    Player* alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(NINE, CLUBS));
    alice->add_card(Card(JACK, SPADES)); //trump
    alice->add_card(Card(JACK, HEARTS));
    alice->add_card(Card(KING, DIAMONDS));
    alice->add_card(Card(ACE, DIAMONDS));

    Card upcard1 = Card(NINE, SPADES); //trump: CLUBS
    Suit order_up1 = DIAMONDS;
    bool make_trump_or_not1 = alice->make_trump(upcard1, false, 2, order_up1);
    ASSERT_TRUE(make_trump_or_not1);
    ASSERT_EQUAL(order_up1, CLUBS);

    delete alice;

    //Round2: 1 trump suit (normal); not dealer
    Player* apple = Player_factory("Apple", "Simple");
    apple->add_card(Card(NINE, CLUBS));
    apple->add_card(Card(ACE, CLUBS)); //trump
    apple->add_card(Card(JACK, HEARTS));
    apple->add_card(Card(KING, DIAMONDS));
    apple->add_card(Card(ACE, DIAMONDS));

    Card upcard1_1 = Card(NINE, SPADES); //trump: CLUBS
    Suit order_up1_1 = DIAMONDS;
    bool make_trump_or_not1_1 = apple->make_trump(upcard1_1, false, 2, order_up1_1);
    ASSERT_TRUE(make_trump_or_not1_1);
    ASSERT_EQUAL(order_up1_1, CLUBS);

    delete apple;

    //Round2: 0 trump suit; not dealer
    Player* bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(ACE, CLUBS));
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(KING, HEARTS));
    bob->add_card(Card(JACK, DIAMONDS));

    Card upcard2 = Card(TEN, CLUBS); //-->trump: SPADES
    Suit order_up2 = DIAMONDS;
    bool make_trump_or_not2 = bob->make_trump(upcard2, false, 2, order_up2);
    ASSERT_FALSE(make_trump_or_not2);
    ASSERT_EQUAL(order_up2, DIAMONDS);

    delete bob;

    //Round2: 2 trump suit (Face + Ace); not dealer
    Player* cat = Player_factory("Cat", "Simple");
    cat->add_card(Card(JACK, SPADES)); //trump
    cat->add_card(Card(ACE, CLUBS)); //trump
    cat->add_card(Card(NINE, HEARTS));
    cat->add_card(Card(JACK, DIAMONDS));
    cat->add_card(Card(TEN, CLUBS));

    Card upcard3 = Card(NINE, SPADES); //-->CLUBS
    Suit order_up3 = DIAMONDS;
    bool make_trump_or_not3 = cat->make_trump(upcard3, false, 2, order_up3);
    ASSERT_TRUE(make_trump_or_not3);
    ASSERT_EQUAL(order_up3, CLUBS);

    delete cat;

    //Round2: 0 trump; Screw the dealer
    Player* dog = Player_factory("Dog", "Simple");
    dog->add_card(Card(NINE, SPADES));
    dog->add_card(Card(TEN, SPADES));
    dog->add_card(Card(NINE, HEARTS));
    dog->add_card(Card(TEN, CLUBS));
    dog->add_card(Card(NINE, DIAMONDS));

    Card upcard4 = Card(JACK, SPADES); //trump: CLUBS
    Suit order_up4 = DIAMONDS;
    bool make_trump_or_not4 = dog->make_trump(upcard4, true, 2, order_up4);
    ASSERT_TRUE(make_trump_or_not4);
    ASSERT_EQUAL(order_up4, CLUBS);

    delete dog;
}


TEST(test_simple_lead_not_full) {
    //One left: left bower trump
    Player* alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(JACK, CLUBS));

    Card lead1 = alice->lead_card(SPADES);
    Card assertion_card1 = Card(JACK, CLUBS);
    ASSERT_EQUAL(lead1, assertion_card1);

    delete alice;

    //One left: 1 non-trump card
    Player* bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, HEARTS));

    Card lead2 = bob->lead_card(SPADES);
    Card assertion_card2 = Card(NINE, HEARTS);
    ASSERT_EQUAL(lead2, assertion_card2);

    delete bob;

    //One left: Normal trump
    Player* cat = Player_factory("Cat", "Simple");
    cat->add_card(Card(TEN, SPADES));

    Card lead3 = cat->lead_card(SPADES);
    Card assertion_card3 = Card(TEN, SPADES);
    ASSERT_EQUAL(lead3, assertion_card3);

    delete cat;

    //Two left: 2 non-trump
    Player* curry = Player_factory("Curry", "Simple");
    curry->add_card(Card(ACE, DIAMONDS));
    curry->add_card(Card(ACE, HEARTS));

    Card lead4 = curry->lead_card(SPADES);
    Card assertion_card4 = Card(ACE, DIAMONDS);
    ASSERT_EQUAL(lead4, assertion_card4);

    delete curry;

    //Two left: 2 trump
    Player* dog = Player_factory("Dog", "Simple");
    dog->add_card(Card(JACK, CLUBS));
    dog->add_card(Card(ACE, SPADES));

    Card lead5 = dog->lead_card(SPADES);
    Card assertion_card5 = Card(JACK, CLUBS);
    ASSERT_EQUAL(lead5, assertion_card5);

    delete dog;

    //Two left: 1 non-trump and 1 trump
    Player* goose = Player_factory("Goose", "Simple");
    goose->add_card(Card(JACK, SPADES));
    goose->add_card(Card(NINE, HEARTS));

    Card lead6 = goose->lead_card(SPADES);
    Card assertion_card6 = Card(NINE, HEARTS);
    ASSERT_EQUAL(lead6, assertion_card6);

    delete goose;
}



TEST(test_simple_lead) {
    //No non-trump card; all trump
    Player* alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(JACK, CLUBS));
    alice->add_card(Card(ACE, SPADES));
    alice->add_card(Card(KING, SPADES));
    alice->add_card(Card(QUEEN, SPADES));
    alice->add_card(Card(JACK, DIAMONDS));

    Card upcard1 = Card(JACK, SPADES);//Trump: SPADES
    alice->add_and_discard(upcard1); //-->discard (JACK, DIAMOND)
    Card lead1 = alice->lead_card(SPADES); //Lead (JACK, SPADES); Five trumps
    Card assert_card1 = Card(JACK, SPADES);
    ASSERT_EQUAL(lead1, assert_card1);

    delete alice;

    //Discard upcard; No non-trump card
    Player* bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(JACK, SPADES));//SPADES
    bob->add_card(Card(ACE, SPADES));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(TEN, SPADES));

    Card upcard2 = Card(NINE, SPADES);//Trump: SPADES
    bob->add_and_discard(upcard2); //-->discard (NINE SPADES)
    Card lead2 = bob->lead_card(SPADES); //-->(JACK, SPADES); Five trumps
    Card assert_card2 = Card(JACK, SPADES);
    ASSERT_EQUAL(lead2, assert_card2);

    delete bob;

    //Only 1 non-trump card
    Player* cat = Player_factory("Cat", "Simple");
    cat->add_card(Card(QUEEN, CLUBS));
    cat->add_card(Card(TEN, CLUBS));
    cat->add_card(Card(JACK, SPADES));//CLUBS
    cat->add_card(Card(TEN, DIAMONDS));
    cat->add_card(Card(NINE, HEARTS));

    Card upcard3 = Card(JACK, CLUBS); //Trump: CLUBS
    cat->add_and_discard(upcard3); //-->discard(NINE, HEARTS)
    Card lead3 = cat->lead_card(CLUBS);
    Card assert_card3 = Card(TEN, DIAMONDS);
    ASSERT_EQUAL(lead3, assert_card3);

    delete cat;

    //2 non-trump card
    Player* cow = Player_factory("Cow", "Simple");
    cow->add_card(Card(JACK, SPADES));
    cow->add_card(Card(JACK, CLUBS));
    cow->add_card(Card(KING, HEARTS));
    cow->add_card(Card(TEN, DIAMONDS));
    cow->add_card(Card(NINE, HEARTS));

    Card upcard3_1 = Card(TEN, SPADES);
    cow->add_and_discard(upcard3_1); //Discard (NINE, HEARTS)
    Card lead3_1 = cow->lead_card(SPADES);
    Card assert_card3_1 = Card(KING, HEARTS);
    ASSERT_EQUAL(lead3_1, assert_card3_1);

    delete cow;


    //General case: Several non-trump card
    Player* dog = Player_factory("Dog", "Simple");
    dog->add_card(Card(KING, DIAMONDS));
    dog->add_card(Card(QUEEN, CLUBS));
    dog->add_card(Card(JACK, HEARTS));
    dog->add_card(Card(TEN, DIAMONDS));
    dog->add_card(Card(NINE, HEARTS));

    Card upcard4 = Card(NINE, SPADES);
    dog->add_and_discard(upcard4); //discard (NINE, HEARTS)
    Card lead4 = dog->lead_card(SPADES);
    Card assert_card4 = Card(KING, DIAMONDS);
    ASSERT_EQUAL(lead4, assert_card4);

    delete dog;

}

TEST(test_simple_player_lead_card) {
    // Bob's hand
    Player* bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(ACE, SPADES));

    // Bob adds a card to his hand and discards one card
    bob->add_and_discard(
        Card(NINE, HEARTS) // upcard
    );

    // Bob leads
    Card card_led = bob->lead_card(HEARTS);

    // Verify the card Bob selected to lead
    Card ace_spades(ACE, SPADES);
    ASSERT_EQUAL(card_led, ace_spades); //check led card

    delete bob;
}


TEST(test_simple_play_not_full) {
    //Trump != Lead
    //One left: follow
    Player* alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(ACE, DIAMONDS));

    Suit trump1 = SPADES;
    Card lead_card1 = Card(QUEEN, DIAMONDS);
    Card play1 = alice->play_card(lead_card1, trump1);
    ASSERT_EQUAL(play1, Card(ACE, DIAMONDS));

    delete alice;

    //One left: not follow
    Player* bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(ACE, CLUBS));

    Suit trump2 = SPADES;
    Card lead_card2 = Card(QUEEN, DIAMONDS);
    Card play2 = bob->play_card(lead_card2, trump2);
    ASSERT_EQUAL(play2, Card(ACE, CLUBS));

    delete bob;

    //Two left: 1 follow + 1 not follow
    Player* cat = Player_factory("Cat", "Simple");
    cat->add_card(Card(NINE, DIAMONDS));
    cat->add_card(Card(ACE, CLUBS));

    Suit trump3 = SPADES;
    Card lead_card3 = Card(QUEEN, DIAMONDS);
    Card play3 = cat->play_card(lead_card3, trump3);
    ASSERT_EQUAL(play3, Card(NINE, DIAMONDS));

    delete cat;

    //Two left: 2 follows
    Player* dog = Player_factory("Dog", "Simple");
    dog->add_card(Card(JACK, DIAMONDS));
    dog->add_card(Card(TEN, DIAMONDS));//highest

    Suit trump4 = SPADES;
    Card lead_card4 = Card(QUEEN, DIAMONDS);
    Card play4 = dog->play_card(lead_card4, trump4);
    ASSERT_EQUAL(play4, Card(JACK, DIAMONDS));

    delete dog;

    //Two left: 2 not follows
    Player* goose = Player_factory("Goose", "Simple");
    goose->add_card(Card(KING, CLUBS));
    goose->add_card(Card(JACK, HEARTS));//lowest

    Suit trump5 = SPADES;
    Card lead_card5 = Card(QUEEN, DIAMONDS);
    Card play5 = goose->play_card(lead_card5, trump5);
    ASSERT_EQUAL(play5, Card(JACK, HEARTS));

    delete goose;

    //Trump == Lead
    Suit trump = SPADES;
    Card lead = Card(JACK, CLUBS);//Lead suit == SPADES

    //One left: 1 follow
    Player* fog = Player_factory("Fog", "Simple");
    fog->add_card(Card(NINE, SPADES));
    Card play6 = fog->play_card(lead, trump);
    ASSERT_EQUAL(play6, Card(NINE, SPADES));
    delete fog;

    //One left: 1 not follow
    Player* horse = Player_factory("Horse", "Simple");
    horse->add_card(Card(JACK, HEARTS));
    Card play7 = horse->play_card(lead, trump);
    ASSERT_EQUAL(play7, Card(JACK, HEARTS));
    delete horse;

    //Two left: 2 follows
    Player* juice = Player_factory("Juice", "Simple");
    juice->add_card(Card(JACK, SPADES));
    juice->add_card(Card(NINE, SPADES));
    Card play8 = juice->play_card(lead, trump);
    ASSERT_EQUAL(play8, Card(JACK, SPADES));//highest
    delete juice;

    //Two left: 2 not follows
    Player* lulu = Player_factory("Lulu", "Simple");
    lulu->add_card(Card(KING, CLUBS));
    lulu->add_card(Card(NINE, HEARTS));
    Card play9 = lulu->play_card(lead, trump);
    ASSERT_EQUAL(play9, Card(NINE, HEARTS));//lowest
    delete lulu;

    //Two left: 1 follows + 1 not follows
    Player* monk = Player_factory("Monk", "Simple");
    monk->add_card(Card(TEN, SPADES));
    monk->add_card(Card(ACE, CLUBS));
    Card play10 = monk->play_card(lead, trump);
    ASSERT_EQUAL(play10, Card(TEN, SPADES));//the only follow
    delete monk;
}


TEST(test_simple_play) {
    //All follows
    Player* alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(ACE, DIAMONDS));
    alice->add_card(Card(KING, DIAMONDS));
    alice->add_card(Card(JACK, DIAMONDS));
    alice->add_card(Card(TEN, DIAMONDS));
    alice->add_card(Card(NINE, DIAMONDS));

    Suit trump1 = SPADES; //Trump and lead are different
    Card lead_card1 = Card(QUEEN, DIAMONDS);
    Card play1 = alice->play_card(lead_card1, trump1);
    ASSERT_EQUAL(play1, Card(ACE, DIAMONDS));

    delete alice;

    //Only 1 follow: left bower
    Player* apple = Player_factory("Apple", "Simple");
    apple->add_card(Card(ACE, DIAMONDS));
    apple->add_card(Card(KING, DIAMONDS));
    apple->add_card(Card(JACK, DIAMONDS));//left 
    apple->add_card(Card(TEN, DIAMONDS));
    apple->add_card(Card(NINE, DIAMONDS));

    Suit trump1_1 = HEARTS; //Trump and lead are same
    Card lead_card1_1 = Card(QUEEN, HEARTS);
    Card play1_1 = apple->play_card(lead_card1_1, trump1_1);
    ASSERT_EQUAL(play1_1, Card(JACK, DIAMONDS));

    delete apple;

    //One follow
    Player* bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, DIAMONDS));
    bob->add_card(Card(ACE, CLUBS));
    bob->add_card(Card(JACK, CLUBS));
    bob->add_card(Card(QUEEN, HEARTS));
    bob->add_card(Card(NINE, SPADES));

    Suit trump2 = SPADES;
    Card lead_card2 = Card(JACK, DIAMONDS);//lead is diamond
    Card play2 = bob->play_card(lead_card2, trump2);
    ASSERT_EQUAL(play2, Card(NINE, DIAMONDS));

    delete bob;

    //All dont follow
    Player* cat = Player_factory("Cat", "Simple");
    cat->add_card(Card(ACE, HEARTS));
    cat->add_card(Card(KING, CLUBS));
    cat->add_card(Card(JACK, CLUBS));//SPADES//double check
    cat->add_card(Card(TEN, CLUBS));
    cat->add_card(Card(NINE, HEARTS));

    Suit trump3 = SPADES;
    Card lead_card3 = Card(TEN, DIAMONDS);
    Card play3 = cat->play_card(lead_card3, trump3);
    ASSERT_EQUAL(play3, Card(NINE, HEARTS));

    delete cat;

    //trump == lead && several follow
    Player* dog = Player_factory("Dog", "Simple");
    dog->add_card(Card(JACK, CLUBS)); //follow
    dog->add_card(Card(ACE, SPADES)); //follow
    dog->add_card(Card(KING, SPADES)); //follow
    dog->add_card(Card(TEN, SPADES)); //follow
    dog->add_card(Card(NINE, CLUBS)); //not follow

    Suit trump4 = SPADES;
    Card lead_card4 = Card(QUEEN, SPADES);
    Card play4 = dog->play_card(lead_card4, trump4);
    ASSERT_EQUAL(play4, Card(JACK, CLUBS));

    delete dog;

    //trump == lead && 0 follow
    Player* dan = Player_factory("Dan", "Simple");
    dan->add_card(Card(KING, CLUBS));
    dan->add_card(Card(QUEEN, HEARTS));
    dan->add_card(Card(JACK, DIAMONDS));
    dan->add_card(Card(JACK, HEARTS));
    dan->add_card(Card(NINE, CLUBS));

    Suit trump4_1 = SPADES;
    Card lead_card4_1 = Card(JACK, CLUBS); //lead == trump
    Card play4_1 = dan->play_card(lead_card4_1, trump4_1);
    ASSERT_EQUAL(play4_1, Card(NINE, CLUBS)); //lowest

    delete dan;

    //trump == lead && 1 follow
    Player* goose = Player_factory("Goose", "Simple");
    goose->add_card(Card(JACK, SPADES));
    goose->add_card(Card(ACE, HEARTS));
    goose->add_card(Card(KING, CLUBS));
    goose->add_card(Card(JACK, DIAMONDS));
    goose->add_card(Card(NINE, CLUBS));

    Suit trump5 = SPADES;
    Card lead_card5 = Card(JACK, CLUBS); //lead == trump
    Card play5 = goose->play_card(lead_card5, trump5);
    ASSERT_EQUAL(play5, Card(JACK, SPADES)); //highest

    delete goose;

}


TEST(test_simple_player_play_card) {
    // Bob's hand
    Player* bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(ACE, SPADES));

    // Bob plays a card
    Card nine_diamonds(NINE, DIAMONDS);
    Card card_played = bob->play_card(
        nine_diamonds,  // Nine of Diamonds is led
        HEARTS    // Trump suit
    );

    // Verify the card Bob played
    ASSERT_EQUAL(card_played, Card(NINE, SPADES));
    delete bob;
}



TEST_MAIN()
