//
// Created by ykx on 2018/2/26.
//

#include "Jail.h"
#include "Player.h"
#include "GameState.h"
#include "FreeParking.h"
#include <iostream>

Monopoly::Jail::Jail(CSVReader& boardFile, GameState& gameState, const Rules& rule, const int spaceNumber)
    : Space(boardFile, gameState, spaceNumber), rules(rule){

  Space::name = boardFile.get_next_field();
  turnInJail = boardFile.get_next_field_as_int();
  moneyToGetOut = boardFile.get_next_field_as_int();

}
void Monopoly::Jail::display() const {

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
//Criminal you are in jail for 2 turns.
//Would you like to pay $50 to leave jail early?
//y for yes and n for no: Criminal please enter your move
void Monopoly::Jail::activate(Monopoly::Player& activatingPlayer) {
//You are still stuck in jail
  std::string name = activatingPlayer.getName();
  std::string jail = this->getName();
  int turnLeftInJail = turnInJail - activatingPlayer.jailTurn;
  int money = activatingPlayer.getCash();
  char move;
  int num;
  activatingPlayer.jailTurn++;

  if (activatingPlayer.inJail) {
    if (turnLeftInJail > 0 ) {
      std::cout << name << " you are in jail for " << turnLeftInJail << " turns." << std::endl;
      if (money >= moneyToGetOut) {
        std::cout << "Would you like to pay $" << moneyToGetOut << " to leave jail early?" << std::endl;
        std::cout << "y for yes and n for no: ";
        std::cin >> move;

        if (move == 'y') {
          activatingPlayer.inJail = false;
          activatingPlayer.jailTurn = 0;
          activatingPlayer.payBank(moneyToGetOut);
          if (rules.isPut_money_in_free_parking()) {
            FreeParking::setMoneyInPool(moneyToGetOut);
          }
        }
      }
    }
    else if (turnLeftInJail == 0) {
      if (money >= moneyToGetOut) {
      std::cout << name << " ,you had to pay $" << moneyToGetOut << " to get out of jail" << std::endl;
      activatingPlayer.inJail = false;
      activatingPlayer.jailTurn = 0;
      activatingPlayer.payBank(moneyToGetOut);
        if (rules.isPut_money_in_free_parking()){
          FreeParking::setMoneyInPool(moneyToGetOut);
        }
      }
      else {
        //Criminal went bankrupt when paying to leave jail
      std::vector<Property*> downgradeableProperties = activatingPlayer.getDowngradeableProperties(rules);
        //Student went bankrupt by landing on StudentFees
        if (downgradeableProperties.size() == 0) {
        std::cout << name << " went bankrupt when paying to leave jail" << std::endl;
        activatingPlayer.payBank(money);
        activatingPlayer.bankrupt = true;
        }
        else if (downgradeableProperties.size() > 0){
          while (money < moneyToGetOut && downgradeableProperties.size() > 0) {
            std::cout << "You have $" << money << " but you owe $" << moneyToGetOut << std::endl;
            std::cout << "Pick an upgrade to sell to make up the difference" << std::endl;
            for (unsigned long i = 0; i < downgradeableProperties.size(); ++i) {
              std::cout << i << ". " << downgradeableProperties.at(i)->getName() << " [$"
                        << downgradeableProperties.at(i)->getUpgradeCost() / 2 << "]" << std::endl;
            }
            std::cout << "Your choice: ";
            std::cin >> num;
            downgradeableProperties.at(num)->downgrade();
            downgradeableProperties = activatingPlayer.getDowngradeableProperties(rules);
          }
          if (rules.isPut_money_in_free_parking()){
            FreeParking::setMoneyInPool(moneyToGetOut);
          }
        }
      }
    }
  }

}
int Monopoly::Jail::getNumTurn() {
  return turnInJail;
}
