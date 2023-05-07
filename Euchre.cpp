#include "pch.h"
#include <iostream>
#include "Game.h"
int main()
{
	
	Game game;
	game.Play();
	std::cout << "Card instances: " << Card::instances << std::endl;
	std::cin.get();
	return 0;
}