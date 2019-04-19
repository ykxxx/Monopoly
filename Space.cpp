//
// Created by mfbut on 1/20/2018.
//
#include <iostream>
#include <memory>
#include "Space.h"
#include "MonopolyUtility.h"
#include "Player.h"
#include "GameState.h"
#include "Go.h"

unsigned long Monopoly::Space::length_of_longest_space_name;

Monopoly::Space::Space(CSVReader& boardFile, GameState& gameState, const int spaceNumber)
    :spaceNumber(spaceNumber), gameState(gameState) {

}

void Monopoly::Space::display() const {
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

void Monopoly::Space::activate(Monopoly::Player& activatingPlayer) {

}

const std::string& Monopoly::Space::getName() const {
  return name;
}

void Monopoly::Space::addPlayer(Monopoly::Player& player) {
  auto playerIt = playersOnSpace.cbegin();
  for (; playerIt != playersOnSpace.cend(); ++playerIt) {
    if (player.getId() < (*playerIt)->getId()) {
      break;
    }
  }
  playersOnSpace.insert(playerIt, &player);
}

void Monopoly::Space::removePlayer(const Monopoly::Player& player) {
  for (auto playerIt = playersOnSpace.cbegin(); playerIt != playersOnSpace.cend(); ++playerIt) {
    if ((*playerIt)->getId() == player.getId()) {
      playersOnSpace.erase(playerIt);
      return;
    }
  }
}

void Monopoly::Space::removeAllPlayers() {
  playersOnSpace.clear();
}

//Monopoly::SpaceType Monopoly::Space::getSpaceType(std::unique_ptr<Space>space) const {
  //return space->spaceType;
//}

int Monopoly::Space::getSpaceNumber() const {
  return spaceNumber;
}
/*

int Monopoly::Space::getSalary() const {
  if (spaceType == SpaceType::goSpace) {
    return goPtr->getSalary();
  } else {
    std::cout << "Get Salary called on non Go Space" << std::endl;
    return -99;
  }
}

int Monopoly::Space::getCost() const {
  if (spaceType == SpaceType::propertySpace) {
    return propertyPtr->getCost();
  } else {
    std::cout << "Get Cost called on non Property Space" << std::endl;
    return -99;
  }
}

int Monopoly::Space::getSetId() const {
  if (spaceType == SpaceType::propertySpace) {
    return propertyPtr->getSetId();
  } else {
    return -99;
  }
}

int Monopoly::Space::getIntraSetId() const {
  if (spaceType == SpaceType::propertySpace) {
    return propertyPtr->getIntraSetId();
  } else {
    return -99;
  }
}

int Monopoly::Space::getBasicRent() const {
  if (spaceType == SpaceType::propertySpace) {
    return propertyPtr->getRent();
  } else {
    return -99;
  }
}


 */





