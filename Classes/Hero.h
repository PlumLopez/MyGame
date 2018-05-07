#ifndef _HERO_
#define _HERO_

#include"MagicTower.h"
USING_NS_CC;

class Teleport;
class Hero : public Node {
	

public:
	int HP; //Ѫ��

	int ATK; //������

	int DEF; //������

	int YellowKeys;

	int BlueKeys;

	int RedKeys;



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

	void pickUpItem(); // ����

	void openDoor(int targetDoorGID); // ����

	void DoorOpeningUpdate(float dt);

	void actWithNPC(); // ��npc����

	void doTeleport(Teleport *teleport); //����

	Sprite *heroSprite; //�洢Ӣ�۵ľ���

	Sprite* Fighting; //ս��ͼƬ�ľ���

	Point targetTileCoord; //��ʱ�����ש������

	Point targetPosition;//��ʱ�����cocos����

	int targetDoorGID; //�ŵ�GID
	
	CollisionType checkCollision(Point heroPosition); //��ײ��⺯��

	void onMoveDone(Node* pTarget, int data);//�ƶ���ɺ�Ļص�����

};


#endif
