#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_


class GameState
{
public:
  GameState(GameStateOptions gameState){this->gameState = gameState;}
  void setGameState(GameStateOptions gameState){this->gameState=gameState;}
  GameStateOptions getGameState(){return gameState;}

private:
  GameStateOptions gameState;
};

#endif
