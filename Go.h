//
// Created by mfbut on 1/20/2018.
//

#ifndef HOARDINGCPPVERSION_GO_H
#define HOARDINGCPPVERSION_GO_H

#include <string>
#include "CSVReader.h"
#include "Space.h"

namespace Monopoly {
  class GameState;
  class Player;
  class Go : public Space {
   public:
    Go(CSVReader& boardFile, GameState& gameState, const int spaceNumber);
    virtual void display() const override ;
    virtual void activate(Player& activatingPlayer) override;

    int getLanding_multiplier() const;
    void setLanding_multiplier(int landing_multiplier);
    int getSalary() const;
    //const std::string& getName() const;
    //void display() const override ;
   private:
    int salary;
    int landing_multiplier;
    std::string name;
    std::unique_ptr<Go> goPtr;
    //const Rules& rules;

  };
}

#endif //HOARDINGCPPVERSION_GO_H
