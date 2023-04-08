#include "Main.h"
#include <iostream>
#include "CardEnums.h"

Game::Game() : dealerIndex_(0), trumpCaller_(0), trumpSuit_(Suit::NONE), tricksWon_{ 0, 0 }, scores_{ 0, 0 } {
    players_.push_back(Player(PlayerType::HUMAN));
    players_.push_back(Player(PlayerType::COMPUTER));
    players_.push_back(Player(PlayerType::COMPUTER));
    players_.push_back(Player(PlayerType::COMPUTER));
}
void Game::setup() {
    players_.push_back(Player(PlayerType::HUMAN));
    players_.push_back(Player(PlayerType::COMPUTER));
    players_.push_back(Player(PlayerType::COMPUTER));
    players_.push_back(Player(PlayerType::COMPUTER));
}


void Game::play() {
    std::cout << "Welcome to Euchre!" << std::endl;

    while (!teamWonGame(0) && !teamWonGame(1)) {
        deck_.shuffle();
        dealCards();

        for (int i = 0; i < 5; i++) {
            std::cout << "\nRound " << i + 1 << std::endl;
            playTrick();
        }
        printScores();
        dealerIndex_ = (dealerIndex_ + 1) % 4;
    }

    int winningTeam = (scores_[0] >= 10) ? 0 : 1;
    std::cout << "\nTeam " << winningTeam + 1 << " wins the game!" << std::endl;
}

void Game::dealCards() {
    for (int i = 0; i < 20; i++) {
        players_[i % 4].addCardToHand(deck_.drawCard());
    }
}

void Game::playTrick() {
    trickCards_.clear();
    int currentPlayerIndex = (dealerIndex_ + 1) % 4;
    std::cout << "Dealer is Player " << dealerIndex_ + 1 << std::endl;
    Card upCard = deck_.drawCard();
    std::cout << "Up card is: " << upCard.toString() << std::endl;
    if (static_cast<int>(upCard.getRank()) == static_cast<int>(Rank::JACK)) {
        trumpSuit_ = upCard.getSuit();
        std::cout << "Trump suit is: " << Game::suitToString(trumpSuit_) << std::endl;
        trumpCaller_ = (dealerIndex_ + 1) % 4;
    }

    else {
        std::cout << "No trump suit chosen" << std::endl;
        trumpSuit_ = Suit::NONE;
    }

    for (int i = 0; i < 4; i++) {
        Player& currentPlayer = players_[currentPlayerIndex];
        Card card = currentPlayer.playCard(trickCards_, trumpSuit_, upCard.getSuit());
        trickCards_.push_back(card);
        std::cout << "Player " << currentPlayerIndex + 1 << " played " << card.toString() << std::endl;

        currentPlayerIndex = (currentPlayerIndex + 1) % 4;
    }

    int winningPlayerIndex = 0;
    Card winningCard = trickCards_[0];
    for (int i = 1; i < 4; i++) {
        if (trickCards_[i].isBetterThan(winningCard, trumpSuit_, upCard.getSuit())) {
            winningPlayerIndex = i;
            winningCard = trickCards_[i];
        }
    }

    tricksWon_[winningPlayerIndex % 2]++;
    std::cout << "Player " << winningPlayerIndex + 1 << " wins the trick!" << std::endl;
    scores_[winningPlayerIndex % 2] ++;
} 

bool Game::teamWonGame(int team) const {
    return scores_[team] >= 10;
}

void Game::printScores() const {
    std::cout << "\nScoreboard:" << std::endl;
    std::cout << "Team 1: " << scores_[0] << " tricks won: " << tricksWon_[0] << std::endl;
    std::cout << "Team 2: " << scores_[1] << " tricks won: " << tricksWon_[1] << std::endl;
}

std::string Game::suitToString(Suit suit) const {
    switch (suit) {
    case Suit::CLUBS:
        return "Clubs";
    case Suit::DIAMONDS:
        return "Diamonds";
    case Suit::HEARTS:
        return "Hearts";
    case Suit::SPADES:
        return "Spades";
    default:
        return "None";
    }
}