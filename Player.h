#pragma once

#include "Card.h"
#include <vector>

enum class PlayerType { HUMAN, COMPUTER };

class Player {
public:
    Player(PlayerType type);

    PlayerType getType() const;

    std::vector<Card> getHand() const;
    void addCardToHand(Card card);
    virtual Card playCard(const std::vector<Card>& trickCards, Suit trump, Suit trickSuit);
    std::vector<Card> getCardsOfSuit(Suit suit) const;
    Suit getSuitWithLeastCards() const;
    Card getLowestCardOfSuit(const std::vector<Card>& cards) const;
    std::vector<Card> hand_;
private:
    PlayerType type_;
};

class HumanPlayer : public Player {
public:
    using Player::Player;
    virtual Card playCard(const std::vector<Card>& trickCards, Suit trump, Suit trickSuit) override;
};

class ComputerPlayer : public Player {
public:
    using Player::Player;
    virtual Card playCard(const std::vector<Card>& trickCards, Suit trump, Suit trickSuit) override;
};

