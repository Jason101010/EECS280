// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"
#include <algorithm>
#include <cassert>
using namespace std;


class SimplePlayer : public Player {
private:
    string name;
    vector<Card> hand;

public:
    SimplePlayer(const string& name_in)
        : name(name_in) {}

    const std::string& get_name() const {
        return name;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card& c) {
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card& upcard, bool is_dealer,
        int round, Suit& order_up_suit) const {
        assert((round == 1) || (round == 2));
        Suit upcard_suit = upcard.get_suit(); //Have not decided trump

        //Round == 1
        if (round == 1) {
            int counter = 0;
            for (size_t i = 0; i < hand.size(); ++i) {
                int index = static_cast<int>(i);
                if (hand[index].is_trump(upcard_suit)
                    && hand[index].is_face_or_ace()) {
                    counter += 1;
                }
            }
            //If to order up
            if (counter >= 2) {
                order_up_suit = upcard_suit;
                return true;
                //If any player orders up, the upcard’s suit becomes trump
                //and the dealer is given the option to
                //replace one of their cards with the upcard.
            }
            //If not to order up
            return false;
        }

        //Round == 2
        else {
            Suit next_order_up = Suit_next(upcard_suit);
            //Screw the dealer
            if (is_dealer) {
                order_up_suit = next_order_up;
                return true;
            }

            //If have not reached the dealer
            int counter = 0;
            for (size_t i = 0; i < hand.size(); ++i) {
                int index = static_cast<int>(i);
                if (hand[index].is_trump(next_order_up)
                    && hand[index].is_face_or_ace()) {
                    counter += 1;
                }
            }
            if (counter >= 1) {
                order_up_suit = next_order_up;
                return true;
            }
            return false;
        }
    }



    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card& upcard) {
        assert(hand.size() >= 1);
        hand.push_back(upcard);

        //Trump has been presented
        Card min = hand[0];
        int min_index = 0;
        for (size_t i = 1; i < hand.size(); ++i) {
            int index = static_cast<int>(i);
            if (Card_less(hand[index], min, upcard.get_suit())) {
                min = hand[index];
                min_index = index;
            }
        }
        hand.erase(hand.begin() + min_index);
        assert(hand.size() <= MAX_HAND_SIZE);
    }


    //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(Suit trump) {
        assert(hand.size() >= 1);
        vector<Card> non_trump_v;
        vector<Card> trump_v;
        Card lead;

        for (size_t i = 0; i < hand.size(); ++i) {
            int index = static_cast<int>(i);
            if (hand[index].is_trump(trump)) {
                trump_v.push_back(hand[index]);
            }
            else {
                non_trump_v.push_back(hand[index]);
            }
        }

        //If the player has any non-trump card
        if (!non_trump_v.empty()) {
            lead = non_trump_v[0];
            for (size_t i = 0; i < non_trump_v.size(); ++i) {
                int index = static_cast<int>(i);
                if (Card_less(lead, non_trump_v[index], trump)) {  
                    lead = non_trump_v[index];
                }
            }
        }

        //If only have trump card
        else {
            lead = trump_v[0];
            for (size_t i = 0; i < trump_v.size(); ++i) {
                int index = static_cast<int>(i);
                if (Card_less(lead, trump_v[index], trump)) {
                    lead = trump_v[index];
                }
            }
        }

        //Find the index of lead in hand
        int lead_index = 0;
        for (size_t i = 0; i < hand.size(); ++i) {
            int index = static_cast<int>(i);
            if (hand[index] == lead) {
                lead_index = index;
            }
        }

        //Remove lead from hand
        hand.erase(hand.begin() + lead_index);
        return lead; //Return what??
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card& led_card, Suit trump) {
        assert(hand.size() >= 1);
        vector<Card> follow_suit;
        vector<Card> not_follow_suit;
        Suit led_suit = led_card.get_suit(trump);
        Card play;

        for (size_t i = 0; i < hand.size(); ++i) {
            int index = static_cast<int>(i);
            if (hand[index].get_suit(trump) == led_suit) {
                follow_suit.push_back(hand[index]);
            }
            else {
                not_follow_suit.push_back(hand[index]);
            }
        }

        //Find the highest card that follows suit
        if (!follow_suit.empty()) {
            play = follow_suit[0];
            for (size_t i = 0; i < follow_suit.size(); ++i) {
                int index = static_cast<int>(i);
                if (Card_less(play, follow_suit[index], led_card, trump)) {
                    play = follow_suit[index];
                }
            }
        }

        //Find the lowest card in their hand
        else {
            play = not_follow_suit[0];
            for (size_t i = 0; i < not_follow_suit.size(); ++i) {
                int index = static_cast<int>(i);
                if (Card_less(not_follow_suit[index], play, led_card, trump)) {
                    play = not_follow_suit[index];
                }
            }
        }

        //Find and remove play in hand
        int play_index = 0;
        for (size_t i = 0; i < hand.size(); ++i) {
            int index = static_cast<int>(i);
            if (hand[index] == play) {
                play_index = index;
            }
        }

        //Remove lead from hand
        hand.erase(hand.begin() + play_index);
        return play;
    }

    ~SimplePlayer() {}

};




class HumanPlayer : public Player {
private:
    string name;
    vector<Card> hand;
    void print_hand() const {
        for (size_t i = 0; i < hand.size(); ++i)
            cout << "Human player " << name << "'s hand: "
            << "[" << i << "] " << hand[i] << "\n";
    }

public:
    HumanPlayer(const string& name_in)
        : name(name_in) {}

    const std::string& get_name() const {
        return name;
    }

    void add_card(const Card& c) {
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
        std::sort(hand.begin(), hand.end());
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card& upcard, bool is_dealer,
        int round, Suit& order_up_suit) const { //Override need same signature
        assert((round == 1) || (round == 2));
        print_hand();
        cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";

        string decision;
        cin >> decision;

        if (decision != "pass") {
            Suit ordered_up = string_to_suit(decision);
            order_up_suit = ordered_up;
            return true;
        }
        else {
            return false;
        }
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card& upcard) {
        assert(hand.size() >= 1);
        std::sort(hand.begin(), hand.end());
        print_hand();                          //Procedure Order
        hand.push_back(upcard);

        cout << "Discard upcard: [-1]\n";
        cout << "Human player " << name << ", please select a card to discard:\n";
        int discard_index;
        cin >> discard_index;
        hand.erase(hand.begin() + discard_index);
        std::sort(hand.begin(), hand.end());
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(Suit trump) {
        assert(hand.size() >= 1);
        std::sort(hand.begin(), hand.end());

        print_hand();
        cout << "Human player " << name << ", please select a card:\n";
        int lead_index;
        cin >> lead_index;
        Card lead = hand[lead_index];
        hand.erase(hand.begin() + lead_index);
        return lead;
    }


    //REQUIRES Player has at least one card
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card& led_card, Suit trump) {
        assert(hand.size() >= 1);
        std::sort(hand.begin(), hand.end());

        print_hand();
        cout << "Human player " << name << ", please select a card:\n";
        int play_index;
        cin >> play_index;
        Card lead = hand[play_index];
        hand.erase(hand.begin() + play_index);
        return lead;
    }

};





//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player* Player_factory(const std::string& name, const std::string& strategy) {
    // We need to check the value of strategy and return
    // the corresponding player type.
    if (strategy == "Simple") {
        // The "new" keyword dynamically allocates an object.
        return new SimplePlayer(name);
    }
    if (strategy == "Human") {
        return new HumanPlayer(name);
    }
    // Invalid strategy if we get here
    assert(false);
    return nullptr;
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
    os << p.get_name();
    return os;
}
