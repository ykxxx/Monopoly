//
// Created by mfbut on 1/20/2018.
//

#include "Go.h"
#include "Player.h"
#include "Board.h"
#include "Rules.h"
#include <iostream>

Monopoly::Go::Go(CSVReader& boardFile, GameState& gameState, const int spaceNumber)
    : Monopoly::Space(boardFile, gameState, spaceNumber), landing_multiplier(1) {

  //goPtr = std::make_unique<Go>(boardFile, gameState, rules, spaceNumber);
  salary = boardFile.get_next_field_as_int();
  Space::name = boardFile.get_next_field();

}

void Monopoly::Go::display() const {

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

void Monopoly::Go::activate(Monopoly::Player &activatingPlayer) {

  //activatingPlayer.giveCash(goPtr->getSalary() * (rules.getSalary_multiplier_for_landing_on_go() - 1));

}

int Monopoly::Go::getSalary() const {
  return salary;
}

//const std::string& Monopoly::Go::getName() const {
  //return name;
//}

int Monopoly::Go::getLanding_multiplier() const {
  return landing_multiplier;
}

void Monopoly::Go::setLanding_multiplier(int landing_multiplier) {
  this->landing_multiplier = landing_multiplier;
}

