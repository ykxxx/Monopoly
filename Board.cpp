//
// Created by mfbut on 1/20/2018.
//

#include "Board.h"
#include <iostream>
#include <utility>
#include "MonopolyUtility.h"
#include "Player.h"
#include "Go.h"
#include "Property.h"
#include "FreeParking.h"
#include "PayToBank.h"
#include "GoToJail.h"
#include "Jail.h"
#include "GameState.h"

Monopoly::Board::Board(const std::string& boardFileName, GameState& gameState) {
  CSVReader boardFile(boardFileName);
  constexpr int num_lines_to_skip = 4;

  if (boardFile.good()) {
    boardFile.skip_field();
    const int numSpaces = boardFile.get_next_field_as_int();

    for (int i = 0; i < num_lines_to_skip; ++i) {
      boardFile.skip_line();
    }

    for (int i = 0; i < numSpaces; ++i) {
      std::string space_type_string = boardFile.get_next_field();
      if (space_type_string == "Go") {
        //spaces.resize(i + 1);
        //spaces.at(i) = std::make_unique<Monopoly::Go>(boardFile, gameState, gameState.rules, i);
        spaces.emplace_back(std::make_unique<Go>(boardFile, gameState, i));
        boardFile.skip_line();
      }
      else if (space_type_string == "Property") {
        spaces.emplace_back(std::make_unique<Monopoly::Property>(boardFile, gameState, gameState.rules, i));
      }
      else if (space_type_string == "FreeParking") {
        spaces.emplace_back(std::make_unique<Monopoly::FreeParking>(boardFile, gameState, i));
        boardFile.skip_line();
      }
      else if (space_type_string == "Pay") {
        spaces.emplace_back(std::make_unique<Monopoly::Pay>(boardFile, gameState, gameState.rules, i));
        boardFile.skip_line();
      }
      else if (space_type_string == "GoToJail") {
        spaces.emplace_back(std::make_unique<Monopoly::GoToJail>(boardFile, gameState, i));
        boardFile.skip_line();
      }
      else if (space_type_string == "Jail") {
        spaces.emplace_back(std::make_unique<Monopoly::Jail>(boardFile, gameState, gameState.rules, i));
        boardFile.skip_line();
      }
    }
    std::move(spaces);

    Monopoly::Space::length_of_longest_space_name = calc_length_of_longest_space_name();
    Monopoly::Space::length_of_longest_space_name =
        Utility::max(Monopoly::Space::length_of_longest_space_name, std::string("Space Name").size());

  } else {
    std::cout << "Failed to open board file: " << boardFileName << std::endl;
  }
}

void Monopoly::Board::display() const {

  //const std::string header("Space Number | Space Name | Owner | Upgrades | Players");

  //std::cout << header << std::endl;
  const std::string spaceNumber("Space Number");
  const std::string spaceName("Space Name");
  const std::string owner("Owner");
  const std::string Upgrades("Upgrades");
  const std::string playersString("Players");
  const auto frmt_flags = std::cout.flags();
  std::cout.setf(std::ios::left);

  std::cout << spaceNumber; std::cout << " | ";
  std::cout.width(Space::length_of_longest_space_name);
  std::cout << spaceName; std::cout << " | ";

  std::cout.width(Player::length_of_longest_player_name);
  std::cout << owner; std::cout << " | ";

  std::cout.width(Upgrades.size());
  std::cout << Upgrades << " | ";

  std::cout.width(Player::length_of_longest_player_name);
  std::cout << playersString; std::cout << std::endl;

  int i = 0;
  for (const auto& space : spaces) {
    std::cout.width(spaceNumber.size());
    std::cout << i << " | ";
    space->display();
    std::cout << std::endl;
    ++i;
  }
  std::cout.flags(frmt_flags);
}

unsigned long Monopoly::Board::calc_length_of_longest_space_name() const {
  std::vector<std::string> space_names;
  for (const auto& space : spaces) {
    space_names.emplace_back(space->getName());
  }
  return Utility::get_max_string_length(space_names);
}

std::unique_ptr<Monopoly::Space>& Monopoly::Board::getSpace(int spaceNum) {
  return spaces[spaceNum];
}
std::unique_ptr<Monopoly::Space>& Monopoly::Board::getGoSpace() {
  //for (auto& space : spaces) {
  //if (dynamic_cast <std::unique_ptr<Go> &> (space) != nullptr) {
  //}
  //}
  //this line should never execute
  return spaces[0];
}

int Monopoly::Board::getNumSpaces() const {
  return static_cast<int>(spaces.size());
}

//std::vector<std::unique_ptr<Monopoly::Space>> Monopoly::Board::getSpaces() const {
//return spaces;
//}

void Monopoly::Board::removeAllPlayers() {
  for (auto& space : spaces) {
    space->removeAllPlayers();
  }
}

/*std::vector<Cat*> Zoo::getCats() {
std::vector<Cat*> cats;
for (const auto& animal : animals) {
Cat* cat = dynamic_cast<Cat*>(animal.get());
if(cat){
cats.push_back(cat);
}
}
return cats;
}
 */
Monopoly::Go* Monopoly::Board::getGo() {
  Go* go = nullptr;
  for (const auto& space : spaces) {
    go = dynamic_cast<Go*>(space.get());
  }
  return go;
}
std::vector<Monopoly::Property*> Monopoly::Board::getProperty() const {
  std::vector<Property*> properties;
  for (const auto& space : spaces) {
    Property *property = dynamic_cast<Property *>(space.get());
    if (property){
      properties.push_back(property);
    }
  }
  return properties;
}
Monopoly::Jail* Monopoly::Board::getJail() {
  Jail* jail = nullptr;
  for (const auto& space : spaces) {
    jail = dynamic_cast<Jail*>(space.get());
  }
  return jail;
}
Monopoly::Space& Monopoly::Board::getSpaceRef(int spaceNum) {
  return *spaces.at(spaceNum);
}

