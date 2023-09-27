// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <array>
#include "Card.h"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char* const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
Rank string_to_rank(const std::string& str) {
    for (int r = TWO; r <= ACE; ++r) {
        if (str == RANK_NAMES[r]) {
            return static_cast<Rank>(r);
        }
    }
    assert(false); // Input string didn't match any rank
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream& operator<<(std::ostream& os, Rank rank) {
    os << RANK_NAMES[rank];
    return os;
}

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream& operator>>(std::istream& is, Rank& rank) {
    string str;
    if (is >> str) {
        rank = string_to_rank(str);
    }
    return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char* const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
Suit string_to_suit(const std::string& str) {
    for (int s = SPADES; s <= DIAMONDS; ++s) {
        if (str == SUIT_NAMES[s]) {
            return static_cast<Suit>(s);
        }
    }
    assert(false); // Input string didn't match any suit
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream& operator<<(std::ostream& os, Suit suit) {
    os << SUIT_NAMES[suit];
    return os;
}

//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream& operator>>(std::istream& is, Suit& suit) {
    string str;
    if (is >> str) {
        suit = string_to_suit(str);
    }
    return is;
}


/////////////// Write your implementation for Card below ///////////////

Card::Card()
    : rank(TWO), suit(SPADES) { //??::operator resolution
}

Card::Card(Rank rank_in, Suit suit_in)
    : rank(rank_in), suit(suit_in) {
}

Rank Card::get_rank() const {
    return this->rank;
}

Suit Card::get_suit() const {
    return this->suit;
}

Suit Card::get_suit(Suit trump) const {
    if (((this->suit + 2 == trump) || (this->suit - 2 == trump))
        && (this->rank == JACK)) {
        return trump;
    }
    else {
        return this->suit;
    }
}

bool Card::is_face_or_ace() const {
    if ((this->rank == JACK) ||
        (this->rank == QUEEN) ||
        (this->rank == KING) ||
        (this->rank == ACE)) {
        return true;
    }
    else {
        return false;
    }
}

bool Card::is_right_bower(Suit trump) const {
    if ((this->suit == trump) && (this->rank == JACK)) {
        return true;
    }
    else {
        return false;
    }
}

bool Card::is_left_bower(Suit trump) const {
    if ((this->suit == Suit_next(trump)) &&
        (this->rank == JACK)) {
        return true;
    }
    else {
        return false;
    }
}

bool Card::is_trump(Suit trump) const {
    if ((this->suit == trump) ||
        (is_left_bower(trump))) {
        return true;
    }
    else {
        return false;
    }
}

Suit Suit_next(Suit suit) {
    if (suit == SPADES) {
        return CLUBS;
    }
    else if (suit == HEARTS) {
        return DIAMONDS;
    }
    else if (suit == CLUBS) {
        return SPADES;
    }
    else {
        return HEARTS;
    }
}

//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card& a, const Card& b, Suit trump) {
    Rank rankA = a.get_rank();
    Rank rankB = b.get_rank();
    Suit suitA = a.get_suit();
    Suit suitB = b.get_suit();
    if (a.is_right_bower(trump)) {
        return false;
    }
    if (b.is_right_bower(trump)) {
        return true;
    }
    if (a.is_left_bower(trump)) {
        return false;
    }
    if (b.is_left_bower(trump)) {
        return true;
    }
    if (suitA == trump) {
        if (suitB != trump) {
            return false;
        }
        if (rankA < rankB) {
            return true;
        }
        return false;
    }
    if (suitB == trump) {
        if (suitA != trump) {
            return true;
        }
        if (rankA < rankB) {
            return true;
        }
        return false;
    }
    if (rankA < rankB) {
        return true;
    }
    if (rankA > rankB) {
        return false;
    }
    if (suitA < suitB) {
        return true;
    }
    return false;
}

//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card& a, const Card& b, const Card& led_card, Suit trump) {
    Rank rankA = a.get_rank();
    Rank rankB = b.get_rank();
    Suit suitA = a.get_suit();
    Suit suitB = b.get_suit();
    Suit lead = led_card.get_suit(trump);
    if (a.is_right_bower(trump)) {
        return false;
    }
    if (b.is_right_bower(trump)) {
        return true;
    }
    if (a.is_left_bower(trump)) {
        return false;
    }
    if (b.is_left_bower(trump)) {
        return true;
    }

    if (suitA == trump && suitB != trump) {
        return false;
    }
    if (suitA != trump && suitB == trump) {
        return true;
    }
    if (suitA == trump && suitB == trump
        && rankA < rankB) {
        return true;
    }
    if (suitA == trump && suitB == trump
        && rankA > rankB) {
        return false;
    }

    if (suitA == lead && suitB != lead) {
        return false;
    }
    if (suitA != lead && suitB == lead) {
        return true;
    }
    if (suitA == lead && suitB == lead
        && rankA < rankB) {
        return true;
    }
    if (suitA == lead && suitB == lead
        && rankA > rankB) {
        return false;
    }

    if (rankA < rankB) { //Debug1
        return true;
    }
    if (rankA > rankB) {
        return false;
    }
    if (suitA < suitB) {
        return true;
    }
    return false;
}

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator>>
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.get_rank();
    os << " of ";
    os << card.get_suit();
    return os;
}

std::istream& operator>>(std::istream& is, Card& card) {
    string rank; //What is that friend declaration
    string junk;
    string suit;

    is >> rank >> junk >> suit;
    card.rank = string_to_rank(rank);
    card.suit = string_to_suit(suit);
    cout << card << endl;
    return is;
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card& lhs, const Card& rhs) {
    if (lhs.get_rank() < rhs.get_rank()) {
        return true;
    }
    else if (lhs.get_rank() > rhs.get_rank()) {
        return false;
    }
    else {
        if (lhs.get_suit() < rhs.get_suit()) {
            return true;
        }
        else {
            return false;
        }
    }
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card& lhs, const Card& rhs) {
    if ((lhs < rhs) || (lhs == rhs)) {
        return true;
    }
    else {
        return false;
    }
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card& lhs, const Card& rhs) {
    if (lhs.get_rank() > rhs.get_rank()) {
        return true;
    }
    else if (lhs.get_rank() < lhs.get_rank()) {
        return false;
    }
    else {
        if (lhs.get_suit() > rhs.get_suit()) {
            return true;
        }
        else {
            return false;
        }
    }
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card& lhs, const Card& rhs) {
    if ((lhs > rhs) || (lhs == rhs)) {
        return true;
    }
    else {
        return false;
    }
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card& lhs, const Card& rhs) {
    if ((lhs.get_rank() == rhs.get_rank())
        && (lhs.get_suit() == rhs.get_suit())) {
        return true;
    }
    else {
        return false;
    }
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card& lhs, const Card& rhs) {
    if (lhs == rhs) {
        return false;
    }
    else {
        return true;
    }
}

