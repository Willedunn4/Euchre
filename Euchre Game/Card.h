#pragma once
#ifndef CARD_H
#define CARD_H

enum class Suit
{
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES,
    NONE
};

class Card
{
public:
    Card(int suit = 0, int rank = 0);

    bool operator<(const Card& other) const;

    int getSuit() const;
    int getRank() const;
    bool isBetterThan(const Card& other) const;
    std::string getSuitAsString() const;
    std::string getRankAsString() const;
    std::string toString() const;
    bool operator==(const Card& other) const;
    bool isBetterThan(const Card& other, Suit trumpSuit, Suit ledSuit) const;
    bool isBetterThan(int suit, int rank) const;

private:
    int m_suit;
    int m_rank;
    int m_leadSuit;
};
#endif