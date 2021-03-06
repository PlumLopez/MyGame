#ifndef _STARTSCENE_
#define _STARTSCENE_

#include"MagicTower.h"

USING_NS_CC;
class StartScene : public Scene {
public:
	static Scene* createStartScene();
	virtual bool init();
	void initStartScene();
	CREATE_FUNC(StartScene);

	void buttonStartCALLBACK(Ref* psender);
	void buttonExitCALLBACK(Ref* psender);
};

#endif