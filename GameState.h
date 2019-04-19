//
// Created by mfbut on 1/20/2018.
//

#ifndef HOARDINGCPPVERSION_GAMESTATE_H
#define HOARDINGCPPVERSION_GAMESTATE_H
#include <vector>
#include <string>
#include <fstream>
#include <memory>

#include "Rules.h"
#include "Move.h"
#include "Board.h"
#include "DiceRoller.h"
#include "Player.h"


namespace Monopoly {
class GameState {
  friend class Board;
  friend class GoToJail;
  friend class Player;
  friend class Space;
  //class Space;
  //friend class Property;
 public:
  static std::vector<std::string> get_player_names();
  GameState(const std::string& RulesFileName,
            const std::string& BoardFileName,
            const std::string& RandomFileName,
            const std::vector<std::string>& playerNames);

  void playGame();
  bool isGameOver() const;
  Player& getCurrentPlayer();
  void make_move(Player& player, Move& move);
  void declareWinner();
  void changeTurn();
  void removeFromGame(Player& player);
  void auction(Property& property);

  void display() const;

 protected:
  void buyUpgrade();
  void sellUpgrade();
  void rollDice(Monopoly::Player& player);


  Rules rules;
  Board board;
  DiceRoller diceRoller;
  int turn_count;
  unsigned long player_turn;
  std::vector<std::unique_ptr<Player> > players;
  std::unique_ptr<Space>newSpace;
};
}

#endif //HOARDINGCPPVERSION_GAMESTATE_H
