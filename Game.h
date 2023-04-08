#pragma once
#ifndef GAME_H
#define GAME_H


#include "Player.h"
#include "Deck.h"
#include <vector>

class Game {
public:
    Game();
    void play();
    void setup();
private:
    void dealCards();
    void playTrick();
    bool teamWonGame(int team) const;
    void printScores() const;
    std::string suitToString(Suit suit) const;
    void printScores();
    bool teamWonGame(int teamNum);

    std::vector<Player> players_;
    Deck deck_;
    int dealerIndex_;
    std::vector<Card> trickCards_;
    Suit trumpSuit_;
    int trumpCaller_;
    int tricksWon_[2];
    int scores_[2];
};
#endif 



