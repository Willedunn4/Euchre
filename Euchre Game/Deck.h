#pragma once

#include "Card.h"

#include <vector>
#include <random>
#include <chrono>


class Deck {
public:
	Deck();
	void shuffle();
	Card drawCard();
private:
	std::vector<Card> cards_;
	int nextCardIndex_;
};

Deck::Deck() {
	for (int rank = 9; rank <= 14; ++rank) {
		cards_.push_back(Card(Suit::HEARTS, rank));
		cards_.push_back(Card(Suit::DIAMONDS, rank));
		cards_.push_back(Card(Suit::CLUBS, rank));
		cards_.push_back(Card(Suit::SPADES, rank));
	}
	nextCardIndex_ = 0;
}

void Deck::shuffle() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(cards_.begin(), cards_.end(), std::default_random_engine(seed));
	nextCardIndex_ = 0;
}

Card Deck::drawCard() {
	Card card = cards_[nextCardIndex_];
	nextCardIndex_++;
	return card;
}