// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Pack.h"
#include <cassert>

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack() {
    //std::array<Card, PACK_SIZE> cards; what is this syntan?? array<>
    for (int s = SPADES; s <= DIAMONDS; ++s) {
        for (int r = NINE; r <= ACE; ++r) {
            Suit suit = static_cast<Suit>(s);
            Rank rank = static_cast<Rank>(r);
            int index = s * 6 + (r - 7);
            cards[index] = Card(rank, suit);
        }
    }

    next = 0; //next from 0 or 1;
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) {
    Card card;
    int counter = 0;
    while ((counter < PACK_SIZE) && (pack_input >> card)) {  //counter first
        cards[counter] = card;
        counter += 1;
    }
    next = 0;
}

//REQUIRES: cards remain in the Pack
//EFFECTS: Returns the next card in the pack and increments the next index
//int x : index of next card to be dealt
Card Pack::deal_one() {
    assert(!empty()); //purpose?
    next += 1;
    return cards[next - 1]; //??
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
    next = 0;
}


// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
    for (int i = 0; i < 7; ++i) {
        std::array<Card, PACK_SIZE> copy;
        //Make a copy of the original cards array;
        for (int i = 0; i < PACK_SIZE; ++i) {
            copy[i] = cards[i];
        }

        //Shuffle based on the parity of array cards
        for (int i = 0; i < PACK_SIZE; ++i) {
            if (i % 2 == 1) {
                cards[i] = copy[i / 2];
            }
            else {
                cards[i] = copy[0.5 * i + 12];
            }
        }
    }
    next = 0;
}


bool Pack::empty() const {
    if (next >= 24) {
        return true;
    }
    else {
        return false;
    }
}
