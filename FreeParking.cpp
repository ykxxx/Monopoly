//
// Created by ykx on 2018/2/26.
//

#include <iostream>
#include "FreeParking.h"
#include "Player.h"

int Monopoly::FreeParking::moneyInPool = 0;
Monopoly::FreeParking::FreeParking(CSVReader& boardFile, GameState& gameState, const int spaceNumber)
    : Space(boardFile, gameState, spaceNumber) {

  Space::name = boardFile.get_next_field();
  int money = boardFile.get_next_field_as_int();
  this->setMoneyInPool(-1);
  if(money) {
    moneyInPool += money;
  }
  //spaceType = this->getSpaceType();
}

//Space Number | Space Name | Owner  | Upgrades | Players
//1            | Free       | None   |          | [Free : $1500]
void Monopoly::FreeParking::display() const {

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
//Lucky got $1000 for landing on Grant
void Monopoly::FreeParking::activate(Monopoly::Player &activatingPlayer) {

  std::string player = activatingPlayer.getName();

  if (moneyInPool != 0) {

    std::cout << player << " got $" << getMoneyInPool();
    std::cout << " for landing on " << getName() << std::endl;
    activatingPlayer.giveCash(getMoneyInPool());
    moneyInPool = 0;

  }

}

int Monopoly::FreeParking::getMoneyInPool() const {
  return moneyInPool;
}
void Monopoly::FreeParking::setMoneyInPool(int addMoney) {
  if (addMoney == -1) {
    moneyInPool = 0;
  }
  else {
    moneyInPool += addMoney;
  }
}

