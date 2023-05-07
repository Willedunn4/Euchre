#include "Card.h"

#include <iostream>


bool Card::operator<(const Card& other) const
{
    return false;
}

Card::Card(Suit suit, int rank) {
    m_suit(suit), m_rank(rank)
    {
    }
}

Suit Card::getSuit() const {
    return m_suit;
}

int Card::getRank() const {
    return m_rank;
}

std::string Card::getSuitAsString() const {
    switch (m_suit) {
    case Suit::HEARTS:
        return "Hearts";
    case Suit::DIAMONDS:
        return "Diamonds";
    case Suit::CLUBS:
        return "Clubs";
    case Suit::SPADES:
        return "Spades";
    }
}

std::string Card::getRankAsString() const {
    switch (m_rank) {
    case 9:
        return "9";
    case 10:
        return "10";
    case 11:
        return "Jack";
    case 12:
        return "Queen";
    case 13:
        return "King";
    case 14:
        return "Ace";
    }
}
std::string Card::toString() const {
    return getRankAsString() + " of " + getSuitAsString();
}

bool Card::operator==(const Card& other) const {
    return m_suit == other.m_suit && m_rank == other.m_rank;
}

bool Card::isBetterThan(const Card& other, Suit trumpSuit, Suit ledSuit) const {
    if (m_suit == other.m_suit) {
        if (m_suit == trumpSuit) {
            return m_rank > other.m_rank;
        }
        else {
            return m_rank > other.m_rank && other.m_suit != ledSuit;
        }
    }
    else if (m_suit == trumpSuit) {
        return true;
    }
    else {
        return false;
    }
}

Suit Card::stringToSuit(const std::string& suitString) {
    if (suitString == "Hearts") {
        return Suit::HEARTS;
    }
    else if (suitString == "Diamonds") {
        return Suit::DIAMONDS;
    }
    else if (suitString == "Clubs") {
        return Suit::CLUBS;
    }
    else if (suitString == "Spades") {
        return Suit::SPADES;
    }
}
bool Card::isBetterThan(const Card& other, Suit trump, Suit lead) const {
    if (m_suit == other.getSuit()) {
        return m_rank > other.getRank();
    }
    else if (m_suit == trump) {
        return true;
    }
    else if (other.getSuit() == trump) {
        return false;
    }
    else if (m_suit == lead) {
        return true;
    }
    else {
        return false;
    }
}


