#ifndef _GAME_LAYER_
#define _GAME_LAYER_
#include"MagicTower.h"
USING_NS_CC;

class GameMap;
class Hero;

class GameLayer : public Layer {
public:
	GameLayer();
	
	~GameLayer();


	GameMap * map;

	Hero* hero;

	virtual bool init();

	void extraInit(int floor);

	static GameLayer* createGameLayer(int floor);

	void showTip();

	CREATE_FUNC(GameLayer);

};



#endif
