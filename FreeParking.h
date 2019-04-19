//
// Created by ykx on 2018/2/26.
//

#ifndef HW4_FREEPARKING_H
#define HW4_FREEPARKING_H

#include <string>

#include "CSVReader.h"
#include "Rules.h"
#include "Space.h"

namespace Monopoly {
class Player;

class FreeParking : public Space {
  //friend class Pay;

 public:
  //static unsigned long length_of_longest_space_name;
  FreeParking(CSVReader& boardFile, GameState& gameState, const int spaceNumber);
  virtual void display() const override ;
  virtual void activate(Player& activatingPlayer) override ;

  int getMoneyInPool() const;
  static void setMoneyInPool(int addMoney);

 private:
  static int moneyInPool;
  std::string name;
  //const Rules& rules;
  //SpaceType spaceType;

};

};

#endif //HW4_FREEPARKING_H
