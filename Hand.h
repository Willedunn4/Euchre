#pragma once
#include <vector>
#include "Card.h"
class Hand
{
public:
	
	Hand();
	Hand(int _player, bool _isdealer);
	Hand(const Hand& _hand);
	~Hand();

	
	void DisplayHand() const;
	void AddCard(Card* _card);
	void FreeHandCardsMemory();
	
	Card* PlayCard(int _cardpos, bool _wanttodiscard = false);
	std::vector<Card*>& GetHand();
	int GetPlayerNumber() const;

	
	static int s_turn;
	
	int tricks;
	bool isDealer;
	char Team;
protected:
	std::vector<Card*> hand;
	int m_player;
};
