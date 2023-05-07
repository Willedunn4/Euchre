#include "pch.h"
#include "Game.h"
#include "Deck.h"
#include "Hand.h"
#include "Dealer.h"
#include <iostream>
#include <time.h>
Game::Game()
{
}
Game::~Game()
{
}
void Game::Play()
{
	Deck* deck = new Deck();
	srand(time(0));
	std::cout << "\t\t\t\t<Welcome to a game of Euchre!>\n\n";
	m_dealerchoice = rand() % 3 + 1;
	InitPlayers(*deck);
	SetDealerIndex();
	Hand::s_turn = MinNumberConstraint(m_playersArray[m_dealerIndex].GetPlayerNumber() + 1, 1, MAX_PLAYERS);
	m_playersArray[m_dealerIndex].ShuffleDeck();

	std::cout << "\t\t\t-----Player " << m_dealerIndex + 1 << " is shuffling deck!-----" << std::endl;
	
	StartingDeal();
	
	m_Trumpcard = &m_playersArray[m_dealerIndex].TopCardCopy();

	
	ChoosingTrump();
	
	Hand::s_turn = MinNumberConstraint(m_dealerIndex + 2, 1, MAX_PLAYERS);

	
	while (m_playersArray[m_dealerIndex].GetHand().size() > 0)
	{
		std::cout << "\t\t\t-----Round Of Euchre Gameplay-----" << std::endl;
		DisplayCurPlayerHand(MinNumberConstraint(Hand::s_turn, 1, MAX_PLAYERS));
		
		srand(time(0));
		
		m_leadingCard = m_playersArray[Hand::s_turn - 1].PlayCard(rand() % m_playersArray[Hand::s_turn - 1].GetHand().size() + 1);
		m_firstCard = *m_leadingCard;
		m_leadingCardOwner = Hand::s_turn;
		std::cout << "\t\t\t-----Player " << Hand::s_turn << " played the first card!-----" << std::endl;
		Hand::s_turn = MinNumberConstraint(++Hand::s_turn, 1, MAX_PLAYERS);
		DisplayTrumpSuitCopy(false);
		DisplayFirstCard();
		DisplayLeadingCard();
		
		for (int i = 0; i < MAX_PLAYERS - 1; i++)
		{
			DisplayCurPlayerHand(MinNumberConstraint(Hand::s_turn, 1, MAX_PLAYERS));
			ResetCardCheck();

			SameSuitPlay();
			if (!m_wasCardPlayed) {
				TrumpCardPlay();
				if (!m_wasCardPlayed) {
					LeftBowerPlay();
					if (!m_wasCardPlayed) {
						AnyCardPlay();
					}
				}
			}
			DisplayTrumpSuitCopy(false);
			DisplayFirstCard();
			DisplayLeadingCard();
			Hand::s_turn = MinNumberConstraint(++Hand::s_turn, 1, MAX_PLAYERS);
		}
		EndOfRoundPlay();
	}
	std::cout << "\t\t\t-----END OF GAME!-----" << std::endl;

	
	FreeAllMemoryOnHeap();
}

void Game::InitPlayers(Deck& _deck) {
	
	Dealer dealer(&_deck, m_dealerchoice, true);
	int playerNumbers[4];
	playerNumbers[dealer.GetPlayerNumber() - 1] = dealer.GetPlayerNumber();
	m_playersArray[dealer.GetPlayerNumber() - 1] = dealer;
	
	Dealer p1(&_deck, SetPlayerNumber(playerNumbers), false);
	Dealer p2(&_deck, SetPlayerNumber(playerNumbers), false);
	Dealer p3(&_deck, SetPlayerNumber(playerNumbers), false);
	AssignPlayersOrder(dealer);
	AssignPlayersOrder(p1);
	AssignPlayersOrder(p2);
	AssignPlayersOrder(p3);
	
	for (size_t i = 0; i < MAX_PLAYERS; i++) {
		if (i % 2 == 0) {
			m_playersArray[i].Team = 'A';
		}
		else {
			m_playersArray[i].Team = 'B';
		}
	}

}

int Game::SetPlayerNumber(int* _arrnum) {
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (i + 1 != _arrnum[i]) {
			_arrnum[i] = i + 1;
			return i + 1;
		}
	}
	return 0;
}

void Game::AssignPlayersOrder(Dealer& _player) {
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (i + 1 == _player.GetPlayerNumber()) {
			m_playersArray[i] = _player;
		}
	}
}

void Game::SetDealerIndex() {
	for (size_t i = 0; i < MAX_PLAYERS; i++)
	{
		if (m_playersArray[i].isDealer) {
			m_dealerIndex = i;
		}
	}
}

void Game::StartingDeal() {
	int index = m_dealerIndex + 1;
	
	while (index != m_dealerIndex)
	{
		if (index > MAX_PLAYERS - 1) {
			index = 0;
		}
		m_playersArray[m_dealerIndex].DealCards(m_playersArray[index], 3);//d3
		index++;
		if (index > MAX_PLAYERS - 1) {
			index = 0;
		}
		if (index == m_dealerIndex) {
			m_playersArray[m_dealerIndex].DealCards(m_playersArray[index], 3);
		}
	}

	
	index = m_dealerIndex + 1;
	while (index != m_dealerIndex)
	{
		if (index > MAX_PLAYERS - 1) {
			index = 0;
		}
		m_playersArray[m_dealerIndex].DealCards(m_playersArray[index], 2);
		index++;
		if (index > MAX_PLAYERS - 1) {
			index = 0;
		}
		if (index == m_dealerIndex) {
			m_playersArray[m_dealerIndex].DealCards(m_playersArray[index], 2);
		}
	}
}

void Game::FreeAllMemoryOnHeap() {
	m_Trumpcard = 0;

	
	m_playersArray[m_dealerIndex].FreeDeckCardsMemory();

	
	for (size_t i = 0; i < MAX_PLAYERS; i++)
	{
		m_playersArray[i].FreeDeckMemory();
	}
	
	for (size_t i = 0; i < MAX_PLAYERS; i++)
	{
		m_playersArray[i].FreeHandCardsMemory();
	}
}

void Game::DisplayTrumpSuit(bool _showrank) const {
	std::cout << "The Trump is:\n";
	if (_showrank) {
		std::cout << "\tRank: ";
		m_Trumpcard->DisplayRank();
		std::cout << "; ";
	}
	else {
		std::cout << "\t";
	}
	std::cout << "Suit: ";
	m_Trumpcard->DisplaySuit();
	std::cout << std::endl;
}
void Game::DisplayTrumpSuitCopy(bool _showrank) const {
	std::cout << "The Trump is:\n";
	if (_showrank) {
		std::cout << "\tRank: ";
		m_TrumpCardCopy.DisplayRank();
		std::cout << "; ";
	}
	else {
		std::cout << "\t";
	}
	std::cout << "Suit: ";
	m_TrumpCardCopy.DisplaySuit();
	std::cout << std::endl;
}

void Game::DisplayAllHands() const {
	for (size_t i = 0; i < MAX_PLAYERS; i++) {
		m_playersArray[m_playersArray[i].GetPlayerNumber() - 1].DisplayHand();
	}
}

int Game::MinNumberConstraint(int _num, const int _min, const int _max) {
	if (_num < _min || _num >_max) {
		return _num = _min;
	}
	return _num;
}

void Game::DisplayCurPlayerHand(int _playernum) {
	m_playersArray[MinNumberConstraint(_playernum - 1, 0, MAX_PLAYERS - 1)].DisplayHand();
}

void Game::ChoosingTrump() {
	bool firstBidPass = false;
	for (size_t i = 0; i < MAX_PLAYERS; i++)
	{
		DisplayCurPlayerHand(Hand::s_turn);
		DisplayTrumpSuit(true);
		std::cout << "Player " << Hand::s_turn << ", Would you like this to be the Trump?\n";
		if (m_playersArray[Hand::s_turn - 1].TrumpThreshold(m_Trumpcard->GetSuit())) {
			std::cout << "\n\t\t\t-----Player " << Hand::s_turn << " confirmed the Trump-----" << std::endl;
			srand(time(0));
			std::cout << "\t\t-----Player " << m_dealerIndex + 1 << " is replacing a card w/ the Trump-----" << std::endl;
			m_playersArray[m_dealerIndex].PlayCard(rand() % 4 + 1, true);
			m_playersArray[m_dealerIndex].AddCard(m_Trumpcard);
			m_TrumpCardCopy = *m_Trumpcard;
			DisplayTrumpSuit(false);
			break;
		}
		else {
			std::cout << "\t\t\t-----I'll Pass!-----" << std::endl;
			if (i == 3) {
				firstBidPass = true;
			}
		}
		
		Hand::s_turn = MinNumberConstraint(++Hand::s_turn, 1, MAX_PLAYERS);
	}
	if (firstBidPass)
	{
		std::cout << "The Dealer Team <--Team " << m_playersArray[m_dealerIndex].Team << "--> has confirmed the Trump:" << std::endl;
		m_Trumpcard->SetSuit(m_playersArray[m_dealerIndex].FavoredSuit());
		m_TrumpCardCopy = *m_Trumpcard;
		
		delete m_Trumpcard;
		m_Trumpcard = 0;
		DisplayTrumpSuitCopy(false);
	}
}

void Game::ResetCardCheck() {
	m_wasCardPlayed = false;
}

void Game::SameSuitPlay()
{
	
	if (m_leadingCard->GetRank() != Card::JACK && m_leadingCard->GetSuit() != m_TrumpCardCopy.GetSuit()
		|| m_leadingCard->GetRank() != Card::JACK && m_leadingCard->GetSuit() == m_TrumpCardCopy.GetSuit()
		|| m_leadingCard->GetRank() == Card::JACK && m_leadingCard->GetSuit() != m_TrumpCardCopy.GetSuit())
	{
		
		for (int j = 0; j < m_playersArray[Hand::s_turn - 1].GetHand().size(); j++)
		{

			
			if (m_playersArray[Hand::s_turn - 1].GetHand()[j]->GetSuit() == m_firstCard.GetSuit())
			{
				
				if (m_playersArray[Hand::s_turn - 1].GetHand()[j]->GetRank() > m_leadingCard->GetRank())
				{
					if (m_leadingCard != NULL) {
						delete m_leadingCard;
						m_leadingCard = 0;
					}
					m_leadingCard = m_playersArray[Hand::s_turn - 1].PlayCard(MinNumberConstraint(j + 1, 1, m_playersArray[Hand::s_turn - 1].GetHand().size()));
					m_leadingCardOwner = m_playersArray[Hand::s_turn - 1].GetPlayerNumber();
					m_wasCardPlayed = true;
					std::cout << "Player " << Hand::s_turn << " played the same suit card!" << std::endl;
					break;
				}
				else
				{
					m_playersArray[Hand::s_turn - 1].PlayCard(MinNumberConstraint(j + 1, 1, m_playersArray[Hand::s_turn - 1].GetHand().size()), true);
					m_wasCardPlayed = true;
					std::cout << "Player " << Hand::s_turn << " played the same suit card!" << std::endl;
					break;
				}

			}

		}
	}
}
void Game::TrumpCardPlay() {
	
	if (m_leadingCard->GetRank() != Card::JACK && m_leadingCard->GetSuit() != m_TrumpCardCopy.GetSuit()
		|| m_leadingCard->GetRank() != Card::JACK && m_leadingCard->GetSuit() == m_TrumpCardCopy.GetSuit()
		|| m_leadingCard->GetRank() == Card::JACK && m_leadingCard->GetSuit() != m_TrumpCardCopy.GetSuit())
	{
		
		for (int j = 0; j < m_playersArray[Hand::s_turn - 1].GetHand().size(); j++)
		{
			
			if (m_playersArray[Hand::s_turn - 1].GetHand()[j]->GetSuit() == m_TrumpCardCopy.GetSuit())
			{
				
				if (m_leadingCard != NULL) {
					delete m_leadingCard;
					m_leadingCard = 0;
				}
				m_leadingCard = m_playersArray[Hand::s_turn - 1].PlayCard(MinNumberConstraint(j + 1, 1, m_playersArray[Hand::s_turn - 1].GetHand().size()));
				m_leadingCardOwner = m_playersArray[Hand::s_turn - 1].GetPlayerNumber();
				m_wasCardPlayed = true;
				std::cout << "Player " << Hand::s_turn << " played a trump card!" << std::endl;
				break;
			}

		}
	}
}
void Game::LeftBowerPlay() {
	
	if (m_leadingCard->GetRank() != Card::JACK && m_leadingCard->GetSuit() != m_TrumpCardCopy.GetSuit()
		|| m_leadingCard->GetRank() != Card::JACK && m_leadingCard->GetSuit() == m_TrumpCardCopy.GetSuit()
		|| m_leadingCard->GetRank() == Card::JACK && m_leadingCard->GetSuit() != m_TrumpCardCopy.GetSuit())
	{
		for (int j = 0; j < m_playersArray[Hand::s_turn - 1].GetHand().size(); j++)
		{
			
			if (m_playersArray[Hand::s_turn - 1].GetHand()[j]->GetRank() == Card::JACK)
			{
				
				switch (m_TrumpCardCopy.GetSuit())
				{
				case Card::CLUBS:

					if (m_playersArray[Hand::s_turn - 1].GetHand()[j]->GetSuit() == Card::SPADES) {
						
						if (m_leadingCard != NULL) {
							delete m_leadingCard;
							m_leadingCard = 0;
						}
						m_leadingCard = m_playersArray[Hand::s_turn - 1].PlayCard(MinNumberConstraint(j + 1, 1, m_playersArray[Hand::s_turn - 1].GetHand().size()));
						m_leadingCardOwner = m_playersArray[Hand::s_turn - 1].GetPlayerNumber();
						m_wasCardPlayed = true;
					}
					break;
				case Card::SPADES:
					if (m_playersArray[Hand::s_turn - 1].GetHand()[j]->GetSuit() == Card::CLUBS) {
						
						if (m_leadingCard != NULL) {
							delete m_leadingCard;
							m_leadingCard = 0;
						}
						m_leadingCard = m_playersArray[Hand::s_turn - 1].PlayCard(MinNumberConstraint(j + 1, 1, m_playersArray[Hand::s_turn - 1].GetHand().size()));
						m_leadingCardOwner = m_playersArray[Hand::s_turn - 1].GetPlayerNumber();
						m_wasCardPlayed = true;
					}
					break;
				case Card::DIAMONDS:
					if (m_playersArray[Hand::s_turn - 1].GetHand()[j]->GetSuit() == Card::HEARTS) {
						
						if (m_leadingCard != NULL) {
							delete m_leadingCard;
							m_leadingCard = 0;
						}
						m_leadingCard = m_playersArray[Hand::s_turn - 1].PlayCard(MinNumberConstraint(j + 1, 1, m_playersArray[Hand::s_turn - 1].GetHand().size()));
						m_leadingCardOwner = m_playersArray[Hand::s_turn - 1].GetPlayerNumber();
						m_wasCardPlayed = true;
					}
					break;
				case Card::HEARTS:
					if (m_playersArray[Hand::s_turn - 1].GetHand()[j]->GetSuit() == Card::DIAMONDS) {
						
						if (m_leadingCard != NULL) {
							delete m_leadingCard;
							m_leadingCard = 0;
						}
						m_leadingCard = m_playersArray[Hand::s_turn - 1].PlayCard(MinNumberConstraint(j + 1, 1, m_playersArray[Hand::s_turn - 1].GetHand().size()));
						m_leadingCardOwner = m_playersArray[Hand::s_turn - 1].GetPlayerNumber();
						m_wasCardPlayed = true;
					}
					break;
				default:
					break;
				}
				if (m_wasCardPlayed) {
					std::cout << "Player " << Hand::s_turn << " played a Left Bower!" << std::endl;
					break;
				}
			}
		}
	}
}
void Game::AnyCardPlay() {
	std::cout << "Player " << Hand::s_turn << " played any card!" << std::endl;
	
	srand(time(0));
	
	m_playersArray[Hand::s_turn - 1].PlayCard(rand() % m_playersArray[Hand::s_turn - 1].GetHand().size() + 1, true);
}
void Game::EndOfRoundPlay() {
	std::cout << "Player " << m_leadingCardOwner << " wins this round!" << std::endl;
	m_playersArray[m_leadingCardOwner - 1].tricks++;
	Hand::s_turn = m_leadingCardOwner;
	ResetCardCheck();
	
	delete m_leadingCard;
	m_leadingCard = 0;
}
void Game::DisplayLeadingCard() {
	std::cout << "****WINNING CARD****\n";
	std::cout << "\tRank: ";
	m_leadingCard->DisplayRank();
	std::cout << " Suit: ";
	m_leadingCard->DisplaySuit();
	std::cout << std::endl;
}
void Game::DisplayFirstCard() {
	std::cout << "****FIRST CARD****\n";
	std::cout << "\tRank: ";
	m_firstCard.DisplayRank();
	std::cout << " Suit: ";
	m_firstCard.DisplaySuit();
	std::cout << std::endl;
}