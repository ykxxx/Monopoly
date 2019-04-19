//
// Created by mfbut on 1/20/2018.
//

#ifndef HOARDINGCPPVERSION_SPACE_H
#define HOARDINGCPPVERSION_SPACE_H

#include <memory>
#include <vector>

#include "CSVReader.h"
#include "Rules.h"

//#include "Go.h"
//#include "Property.h"
//#include "FreeParking.h"
//#include "PayToBank.h"
//#include "Jail.h"
//#include "GoToJail.h"

namespace Monopoly {
class Player;
class GameState;
enum class SpaceType { goSpace, propertySpace, freeParking, pay, jail, goToJail };

class Space {
 public:
  static unsigned long length_of_longest_space_name;
  Space(CSVReader& boardFile, GameState& gameState, const int spaceNumber);
  //Line( const Line &obj);
  virtual void display() const;
  virtual void activate(Player&activatingPlayer) = 0;

  int getSpaceNumber() const;
  const std::string& getName() const;
  void addPlayer(Player& player);
  void removePlayer(const Player& player);
  void removeAllPlayers();
  //SpaceType getSpaceType(std::unique_ptr<Space>space) const;
  //SpaceType spaceType;


  //int getSalary() const;
  //int getCost() const;
  //int getSetId() const;
  //int getIntraSetId() const;
  //int getBasicRent() const;

 protected:
  //std::unique_ptr<Go> goPtr;
  //std::unique_ptr<Property> propertyPtr;
  //std::unique_ptr<FreeParking> freeParkingPtr;
  //std::unique_ptr<Pay> payPtr;
  //std::unique_ptr<Jail> jailPtr;
  //std::unique_ptr<GoToJail> goToJailPtr;
  std::string name;
  std::vector<Player*> playersOnSpace;
  int spaceNumber;
  GameState& gameState;
};
}

#endif //HOARDINGCPPVERSION_SPACE_H
