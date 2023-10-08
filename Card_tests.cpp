#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_card_get_suit_trump){
    Card c(ACE, HEARTS);

    // these should all return HEARTS since it is the trump
    ASSERT_EQUAL(HEARTS, c.get_suit()); // does not consider trump
    ASSERT_EQUAL(HEARTS, c.get_suit(HEARTS));
    ASSERT_EQUAL(HEARTS, c.get_suit(SPADES));
    ASSERT_EQUAL(HEARTS, c.get_suit(CLUBS));
}

TEST(test_card_is_face_or_ace){
    Card face_card(KING, HEARTS);
    Card ace_card(ACE, CLUBS);
    Card not_face_card(NINE, SPADES);

    ASSERT_EQUAL(true, face_card.is_face_or_ace());
    ASSERT_EQUAL(true, ace_card.is_face_or_ace());
    ASSERT_EQUAL(false, not_face_card.is_face_or_ace());
}

TEST(test_card_is_right_bower){
    Card right_bower(JACK, HEARTS);
    Card not_right_bower(JACK, DIAMONDS);

    ASSERT_EQUAL(true, right_bower.is_right_bower(HEARTS));
    ASSERT_EQUAL(false, not_right_bower.is_right_bower(HEARTS));
}

TEST(test_card_is_left_bower){
    Card left_bower(JACK, CLUBS);
    Card not_left_bower(JACK, SPADES);

    ASSERT_EQUAL(true, left_bower.is_left_bower(SPADES));
    ASSERT_EQUAL(false, not_left_bower.is_left_bower(SPADES));
}

TEST(test_card_is_trump){
    Card trump_card(ACE, HEARTS);
    Card not_trump_card(NINE, CLUBS);

    ASSERT_EQUAL(true, trump_card.is_trump(HEARTS));
    ASSERT_EQUAL(false, not_trump_card.is_trump(HEARTS));
}

TEST(test_suit_next){
    ASSERT_EQUAL(CLUBS, Suit_next(SPADES)); // from spades to clubs
    ASSERT_EQUAL(DIAMONDS, Suit_next(HEARTS)); // from hearts to diamonds
    ASSERT_EQUAL(SPADES, Suit_next(CLUBS)); // from clubs to spades
    ASSERT_EQUAL(HEARTS, Suit_next(DIAMONDS)); // from diamonds to hearts
}

TEST(test_card_less){ //not taking into account suit led
    
    Suit trump = DIAMONDS;
    Card a(JACK, HEARTS);
    Card b(JACK, DIAMONDS);
    Card c(ACE, DIAMONDS);
    Card d(KING, HEARTS);

    ASSERT_EQUAL(true, Card_less(a,b,trump));
    ASSERT_EQUAL(true, Card_less(c,a,trump));
    ASSERT_EQUAL(true, Card_less(d,a,trump));
    ASSERT_EQUAL(false, Card_less(c,d,trump));
}

// Add more test cases here

TEST_MAIN()