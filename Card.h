#pragma once
#include <string>
class Card
{
public:
	
	enum suitType { SPADES, HEARTS, CLUBS, DIAMONDS };
	enum suitRank { EIGHT = 1, NINE, TEN, QUEEN, KING, ACE, JACK };
	
	Card();
	Card(suitType _suite, suitRank _rank);
	Card(const Card& _card);
	~Card();
	
	suitRank GetRank() const;
	void DisplayRank() const;
	suitType GetSuit() const;
	void DisplaySuit() const;
	void SetSuit(Card::suitType _type);
	
	static int instances;
private:
	suitType m_suit;
	suitRank m_rank;
};