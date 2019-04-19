//
// Created by ykx on 2018/2/26.
//

#include "GoToJail.h"
#include "Player.h"
#include "Board.h"
#include "GameState.h"
#include "Jail.h"
#include <iostream>

Monopoly::GoToJail::GoToJail(CSVReader& boardFile, GameState& gameState, const int spaceNumber)
: Space(boardFile, gameState, spaceNumber) {

  Space::name = boardFile.get_next_field();
  spaceIndex = boardFile.get_next_field_as_int();

}
//2            | TheSlammer | None     |          |
void Monopoly::GoToJail::display() const {

  const auto frmt_flags = std::cout.flags();

  //display space name
  std::cout.width(length_of_longest_space_name);
  std::cout << getName() << " | ";

  //display owner
  std::cout.width(Monopoly::Player::length_of_longest_player_name);
  const std::string temp = "None";
  std::cout << temp << " | ";
  //display upgrades
  std::cout << "         | ";

  std::cout.flags(frmt_flags);

  auto player = playersOnSpace.cbegin();
  for (; player != playersOnSpace.cend(); ++player) {
    if (player + 1 == playersOnSpace.cend()) {
      break;
    }

    (*player)->display();
    std::cout << ", ";

  }

  if (player != playersOnSpace.cend()) {
    (*player)->display();
  }
}
//Criminal, you were sent to TheSlammer for 2 turns
void Monopoly::GoToJail::activate(Monopoly::Player &activatingPlayer) {

  std::string player = activatingPlayer.getName();
  std::string jail = gameState.board.spaces.at(spaceIndex).get()->getName();
  Jail* jailPtr = gameState.board.getJail();
  int numTurn = (*jailPtr).getNumTurn();
  std::cout << player << ", you were sent to " << jail;
  std::cout << " for " << numTurn << " turns" << std::endl;
  activatingPlayer.moveTo(gameState.board.getSpaceRef(spaceIndex), true);
  activatingPlayer.inJail = true;
  activatingPlayer.jailTurn = 0;

}

