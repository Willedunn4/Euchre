#include "pch.h"
#include "Card.h"
#include <iostream>
Card::Card() {
	
	instances++;
}
Card::Card(suitType _suite, suitRank _rank)
{
	m_suit = _suite;
	m_rank = _rank;
	instances++;
	
}
Card::Card(const Card& _card)
{
	
	m_suit = _card.GetSuit();
	m_rank = _card.GetRank();
}
int Card::instances = 0;
Card::~Card()
{
	
}
Card::suitRank Card::GetRank() const {
	return m_rank;
}
void Card::DisplayRank() const {
	switch (m_rank) {
	case Card::EIGHT:
		std::cout << "8";
		break;
	case Card::NINE:
		std::cout << "9";
		break;
	case Card::TEN:
		std::cout << "10";
		break;
	case Card::JACK:
		std::cout << "Jack";
		break;
	case Card::QUEEN:
		std::cout << "Queen";
		break;
	case Card::KING:
		std::cout << "King";
		break;
	case Card::ACE:
		std::cout << "Ace";
		break;
	}
}
Card::suitType Card::GetSuit() const {
	return m_suit;
}
void Card::DisplaySuit() const {
	switch (m_suit) {
	case Card::SPADES:
		std::cout << "SPADES";
		break;
	case Card::HEARTS:
		std::cout << "HEARTS";
		break;
	case Card::CLUBS:
		std::cout << "CLUBS";
		break;
	case Card::DIAMONDS:
		std::cout << "DIAMONDS";
		break;
	}
}
void Card::SetSuit(Card::suitType _type) {
	m_suit = _type;
}