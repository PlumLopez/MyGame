#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"MagicTower.h"

USING_NS_CC;

class Enemy : public Ref
{
public:
	Enemy(void);
	~Enemy(void);

	Enemy(int gid);

	int HP;
	int ATK;
	int DEF;


	//������TileMap�ϵķ�λ
	Point position;

	//�����ʼ��ͼ��ID
	int startGID;

	//�������ֵ��е�index
	int index;
};

#endif