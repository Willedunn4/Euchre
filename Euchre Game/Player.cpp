#include "Player.h"
#include <algorithm>
#include <iostream>




Player::Player(PlayerType type) : type_(type) {}

PlayerType Player::getType() const {
    return type_;
}

std::vector<Card> Player::getHand() const {
    return hand_;
}

void Player::addCardToHand(Card card) {
    hand_.push_back(card);
}

Card Player::playCard(const std::vector<Card>& trickCards, Suit trump, Suit trickSuit) {

    Suit suitToFollow = trickSuit;
    std::vector<Card> sameSuitCards = getCardsOfSuit(suitToFollow);

    if (sameSuitCards.empty()) {
        Suit suitToPlay = getSuitWithLeastCards();
        std::vector<Card> cardsToPlay = getCardsOfSuit(suitToPlay);
        return getLowestCardOfSuit(cardsToPlay);
    }
    else {
        return getLowestCardOfSuit(sameSuitCards);
    }
}

std::vector<Card> Player::getCardsOfSuit(Suit suit) const
{
    return std::vector<Card>();
}

Suit Player::getSuitWithLeastCards() const
{
    return Suit();
}

Card Player::getLowestCardOfSuit(const std::vector<Card>& cards) const
{
    Card lowestCard(cards[0]); // Initialize with the first card in the vector
    bool isFirstCard = true;
    for (const auto& card : cards)
    {
        if (card.getSuit() == lowestCard.getSuit())
        {
            if (isFirstCard)
            {
                lowestCard = card;
                isFirstCard = false;
            }
            else if (card.isBetterThan(lowestCard.getSuit(), lowestCard.getRank()))
            {
                lowestCard = card;
            }
        }
    }
    return lowestCard;
}




Card HumanPlayer::playCard(const std::vector<Card>& trickCards, Suit trump, Suit trickSuit) {
    std::cout << "Your hand: ";
    for (int i = 0; i < hand_.size(); i++) {
        std::cout << i + 1 << ": " << hand_[i].toString() << " ";
    }
    std::cout << std::endl;

    while (true) {
        std::cout << "Enter the number of the card you want to play (1-" << hand_.size() << "): ";
        int index;
        std::cin >> index;
        if (index >= 1 && index <= hand_.size()) {
            Card card = hand_[index - 1];
            hand_.erase(hand_.begin() + index - 1);
            std::cout << "You played: " << card.toString() << std::endl;
            return card;
        }
        else {
            std::cout << "Invalid input. Please try again." << std::endl;
        }
    }
}

Card ComputerPlayer::playCard(const std::vector<Card>& trickCards, Suit trump, Suit trickSuit) {
    std::vector<Card> validCards;
    for (const auto& card : getHand()) {
        if (trickCards.empty()) {
            if (card.getSuit() == trickSuit) {
                validCards.push_back(card);
            }
        }
        else {
            validCards.push_back(card);
        }
    }

    if (validCards.empty()) {
        // No valid card can be played, so return a random card
        std::random_shuffle(hand_.begin(), hand_.end());
        Card card = hand_.front();
        hand_.erase(hand_.begin());
        std::cout << "Computer played: " << card.toString() << std::endl;
        return card;
    }

}
