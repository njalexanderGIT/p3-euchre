#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
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
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
  return {};
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  if(is >> str) {
    rank = string_to_rank(str);
  }
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
  return {};
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  if (is >> str) {
    suit = string_to_suit(str);
  }
  return is;
}


/////////////// Write your implementation for Card below ///////////////

Card::Card() // intialize 2 of spades
  : rank(TWO), suit(SPADES){ }

Card::Card(Rank rank_in, Suit suit_in) // initialize card to rank and suit
  : rank(rank_in), suit(suit_in){ }

Rank Card::get_rank() const { // returns rank
  return rank;
}

Suit Card::get_suit() const { //returns suit
  return suit;
}

Suit Card::get_suit(Suit trump) const { // returns suit with the left bower being trump
  if(is_left_bower(trump)){
    return trump;
  }
  return suit;
}

bool Card::is_face_or_ace() const { 
  return(get_rank() == JACK || get_rank() == QUEEN || get_rank() == KING || get_rank() == ACE);
}

//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(Suit trump) const {
  return(get_rank() == JACK && get_suit() == trump);
}

//EFFECTS Returns true if card is the Jack of the next suit
//red suits (hearts and diamonds) and the black suits (spades and clubs)
bool Card::is_left_bower(Suit trump) const{
  Suit nextSuit = Suit_next(trump);
  return(get_rank() == JACK && get_suit() == nextSuit);
}

//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(Suit trump) const{
  return(get_suit() == trump || is_left_bower(trump));
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


//EFFECTS Prints Card to stream, for example "Two of Spades"
ostream &operator<<(ostream &os, const Card &card){
  os << card.get_rank() << " of " << card.get_suit();
  return os;
}

//EFFECTS Reads a Card from a stream in the format "Two of Spades"
//NOTE The Card class declares this operator>> "friend" function,
//     which means it is allowed to access card.rank and card.suit.
istream & operator>>(std::istream &is, Card &card){
  //"Two of Spades"
  // ""

  string rank_name;
  string filler;
  string suit_name;

  is >> rank_name >> filler >> suit_name;

  Rank rank = string_to_rank(rank_name);
  Suit suit = string_to_suit(suit_name);

  card = Card(rank, suit);

  return is;
  //NOTE: is this right?? do we have to return input stream and why
  //Are we just trying to initialize the empty card with input stream stuff
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
// NOTE: Does this have to include (D > C > H > S)
bool operator<(const Card &lhs, const Card &rhs){
  //NOTE:do we have to include left bower logic

  if(lhs.get_suit() == rhs.get_suit()){
    return lhs.get_rank() < rhs.get_rank();
  }
  return lhs.get_suit() < rhs.get_suit();
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs){
  return(lhs < rhs || lhs == rhs);
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs){
  if(lhs.get_suit() == rhs.get_suit()){
    return lhs.get_rank() > rhs.get_rank();
  }
  return lhs.get_suit() > rhs.get_suit();
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs){
  return(lhs > rhs || lhs == rhs);
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs){
  return(lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit());
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs){
  return !(lhs == rhs);
}

//EFFECTS returns the next suit, which is the suit of the same color
Suit Suit_next(Suit suit){
  //(D > C > H > S)
  //red suits (hearts and diamonds) and the black suits (spades and clubs)
  if (suit == SPADES){
    return CLUBS;
  } else if (suit == HEARTS){
    return DIAMONDS;
  } else if (suit == CLUBS){
    return SPADES;
  } else if (suit == DIAMONDS){
    return HEARTS;
  }
}

//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
//NOTE: See if Comments are too long and if so how to make em shorter
bool Card_less(const Card &a, const Card &b, Suit trump){
  
  if(b == a){ //if the same card, return false because a is not lower than b
    return false;
  } else if (b.is_right_bower(trump)){ //if the rhs is rb, then it's the greatest card
    return true;
  } else if (a.is_right_bower(trump)){ //if the lhs is rb, then a > b
    return false;
  } else if (a.is_left_bower(trump)){ // we know now neither a and b are rb
    return false;                     // so if a is left bower, no b card can beat it
  } else if (b.is_left_bower(trump)){ // if b is left bower and a isn't lb or rb
    return true;                      // then b is greater than a
  } else{
    return a < b; // return if a < b based on regular ranks and suits
  }
}

