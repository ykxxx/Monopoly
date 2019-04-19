//
// Created by ykx on 2018/2/26.
//

#ifndef HW4_JAIL_H
#define HW4_JAIL_H

#include <string>
#include "CSVReader.h"
#include "Rules.h"
#include "Space.h"

namespace Monopoly {

class Jail : public Space {
 // class Player;
  //friend class GoToJail;
 public:
  Jail(CSVReader& boardFile, GameState& gameState, const Rules& rules, const int spaceNumber);
  virtual void display() const override;
  virtual void activate(Player& activatingPlayer) override;
  //virtual void activate(Player&activatingPlayer) = 0;
  int getNumTurn();

 private:
  std::string name;
  int turnInJail;
  int moneyToGetOut;
  const Rules& rules;

};

};

#endif //HW4_JAIL_H
