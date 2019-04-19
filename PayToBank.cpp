//
// Created by ykx on 2018/2/26.
//

#include "PayToBank.h"
#include "Player.h"
#include "FreeParking.h"
#include "GameState.h"
#include <iostream>

Monopoly::Pay::Pay(CSVReader& boardFile, GameState& gameState, const Monopoly::Rules &rules, const int spaceNumber)
    : Space(boardFile, gameState, spaceNumber), rules(rules) {

  Space::name = boardFile.get_next_field();
  moneyPayToBank = boardFile.get_next_field_as_int();

}


void Monopoly::Pay::display() const {

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
//Unlucky paid the bank $1000 for landing on StudentFees
void Monopoly::Pay::activate(Monopoly::Player &activatingPlayer) {
  std::string player = activatingPlayer.getName();
  int cash = activatingPlayer.getCash();
  int amount = moneyPayToBank;
  int sell_num;

  if (activatingPlayer.getCash() >= amount) {
    std::cout << player  << " paid the bank $" << amount;
    std::cout << " for landing on " << getName() << std::endl;
    activatingPlayer.payBank(amount);

    if (rules.isPut_money_in_free_parking()) {
      FreeParking::setMoneyInPool(amount);
    }

  }
  else {
    std::vector<Property*> downgradeableProperties = activatingPlayer.getDowngradeableProperties(rules);
    //Student went bankrupt by landing on StudentFees
    if (downgradeableProperties.size() == 0) {
      std::cout << player << " went bankrupt " << " by landing on " << getName() << std::endl;
      activatingPlayer.payBank(cash);
      gameState.removeFromGame(activatingPlayer);
    }
    else {
      while (cash < amount && downgradeableProperties.size() > 0) {
        std::cout << "You have $" << cash << " but you owe $" << amount << std::endl;
        std::cout << "Pick an upgrade to sell to make up the difference" << std::endl;
        for (unsigned long i = 0; i < downgradeableProperties.size(); ++i) {
          std::cout << i << ". " << downgradeableProperties.at(i)->getName() << " [$"
                    << downgradeableProperties.at(i)->getUpgradeCost() / 2 << "]" << std::endl;
        }
        std::cout << "Your choice: ";
        std::cin >> sell_num;
        downgradeableProperties.at(sell_num)->downgrade();
        downgradeableProperties = activatingPlayer.getDowngradeableProperties(rules);
      }
    }
  }

}



//Unlucky paid the bank $1000 for landing on StudentFees