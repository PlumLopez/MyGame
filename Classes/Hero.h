#ifndef _HERO_
#define _HERO_

#include"cocos2d.h"
#include"Global.h"
#include"GameMap.h"
#include"AnimationControl.h"
USING_NS_CC;

class Hero : public Node {
	

public:
	int HP; //Ѫ��

	int ATK; //������

	int DEF; //������

	bool init(); //��ʼ��Ӣ��

	CREATE_FUNC(Hero);

	Hero();

	~Hero();

	void move(HeroDirection direction); //��ָ�������ƶ�һ��

	void setFaceDirection(HeroDirection direction);//�����沿����

	void fight();//���

	bool isHeroMoving; // ����Ƿ����ƶ�

	bool isHeroFighting; // ����Ƿ��ڴ��

	bool isDoorOpening; // ����Ƿ��ڿ���

	//void pickUpItem(); // ����

	//void openDoor(int targetDoorGID); // ����

	//void actWithNPC(); // ��npc����

	Sprite *heroSprite; //�洢Ӣ�۵ľ���

	Point targetTileCoord; //��ʱ�����ש������

	Point targetPosition;//��ʱ�����cocos����

	int targetDoorGID; //�ŵ�GID
	
	CollisionType checkCollision(Point heroPosition); //��ײ��⺯��

	void onMoveDone(Node* pTarget, void* data);//�ƶ���ɺ�Ļص�����

};


#endif
