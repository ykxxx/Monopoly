//
// Created by ykx on 2018/2/26.
//

#ifndef HW4_GOTOJAIL_H
#define HW4_GOTOJAIL_H

#include <string>
#include "CSVReader.h"
#include "Rules.h"
#include "Space.h"

namespace Monopoly {

class GoToJail : public Space {
 public:
  GoToJail(CSVReader& boardFile, GameState& gameState, const int spaceNumber);
  virtual void display() const override ;
  virtual void activate(Player&activatingPlayer) override;

 private:
  int spaceIndex;
  std::string name;
  //const Rules& rules;

};

}

#endif //HW4_GOTOJAIL_H
