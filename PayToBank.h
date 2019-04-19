//
// Created by ykx on 2018/2/26.
//

#ifndef HW4_PAYTOBANK_H
#define HW4_PAYTOBANK_H

#include <string>
#include "CSVReader.h"
#include "Rules.h"
#include "Space.h"

namespace Monopoly {

class Pay : public Space{
 public:
  Pay(CSVReader& boardFile, GameState& gameState, const Rules& rules, const int numSpace);
  virtual void display() const override ;
  virtual void activate(Player& activatingPlayer) override;

 private:
  int moneyPayToBank;
  std::string name;
  const Rules& rules;

};

};
#endif //HW4_PAYTOBANK_H
