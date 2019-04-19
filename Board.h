//
// Created by mfbut on 1/20/2018.
//

#ifndef HOARDINGCPPVERSION_BOARD_H
#define HOARDINGCPPVERSION_BOARD_H
#include <vector>
#include <memory>
#include <string>
#include "Space.h"
#include "Rules.h"
#include "Go.h"
#include "Jail.h"

namespace Monopoly {

enum class SpaceType;
class GameState;
class Go;
class Property;
class Board {
 public:
  Board(const std::string& boardFileName, GameState& gameState);
  void display() const;
  std::unique_ptr<Monopoly::Space>& getSpace(int spaceNum);
  std::unique_ptr<Monopoly::Space>& getGoSpace();
  int getNumSpaces() const;
  //std::vector<std::unique_ptr<Space>> getSpaces() const;
  void removeAllPlayers();
  std::vector<std::unique_ptr<Space>>spaces;
  Monopoly::Go* getGo();
  Monopoly::Jail* getJail();
  Monopoly::Space& getSpaceRef(int spaceNum);
  std::vector<Property *> getProperty() const;
 protected:
  //std::vector<Space> spaces;
  //SpaceType spaceType;
  //std::vector<std::unique_ptr<Space>>spaces;
  unsigned long calc_length_of_longest_space_name() const;

};
}

#endif //HOARDINGCPPVERSION_BOARD_H
