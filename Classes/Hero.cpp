#include"Hero.h"

bool Hero::init()
{
	if (!Node::init())
	{
		return false;
	}

	heroSprite = Sprite::createWithSpriteFrame(AnimationControl::instance()->getAnimation(kdown)->getFrames().at(0)->getSpriteFrame());

	heroSprite->setAnchorPoint(Point::ZERO);

	this->addChild(heroSprite);

	ATK = DEF = 100;
	HP = 1000;
	YellowKeys = 5;
	BlueKeys = 1;
	RedKeys = 1;

	isHeroMoving = isHeroFighting = isDoorOpening = false;
	return true;
}

Hero::Hero()
{
	Global::instance()->hero = this;
}

Hero::~Hero()
{
}

void Hero::move(HeroDirection direction)
{
	if (isHeroMoving)
	{
		return;
	}

	//�ƶ��ľ���
	Point moveByPosition;

	//���ݷ�������ƶ��ľ���
	switch (direction)
	{
	case kdown:
		moveByPosition = Point(0, -32);
		break;
	case kleft:
		moveByPosition = Point(-32, 0);
		break;
	case kright:
		moveByPosition = Point(32, 0);
		break;
	case kup:
		moveByPosition = Point(0, 32);
		break;
	}

	//����Ŀ�����꣬�õ�ǰ��ʿ��������ƶ�����
	targetPosition = this->getPosition() + moveByPosition;

	//����checkCollision�����ײ���ͣ������ǽ�ڡ�����ţ���ֻ��Ҫ������ʿ�ĳ���
	CollisionType collisionType = checkCollision(targetPosition);

	if (collisionType == kwall
		//|| collisionType == kenemy
		//|| collisionType == knpc
		|| collisionType == kdoor
		)
	{
		setFaceDirection((HeroDirection)direction);
		return;
	}

	//heroSprite���������߶���
	heroSprite->runAction(AnimationControl::instance()->createAnimate(direction));

	//�������λ�ƣ�����ʱ����onMoveDone���� �ѷ�����Ϣ���ݸ�onMoveDone����
	Action *action = Sequence::create(
		MoveBy::create(0.20f, moveByPosition),
		CallFuncN::create(CC_CALLBACK_1(Hero::onMoveDone, this, (void*)direction)),
		NULL);

	this->runAction(action);

	isHeroMoving = true;
}

CollisionType Hero::checkCollision(Point heroPosition)
{
	auto map = Global::instance()->gameMap;
	targetTileCoord = map->tileCoordForPosition(heroPosition);

	//�����߽�
	if (heroPosition.x < 0
		|| targetTileCoord.x > map->getMapSize().width - 1
		|| targetTileCoord.y < 0
		|| targetTileCoord.y > map->getMapSize().height - 1)
	{
		return kwall;
	}

	//��ȡǽ�ڲ��Ӧ�����ͼ��ID
	int targetTileGID = Global::instance()->gameMap->WallLayer->getTileGIDAt(targetTileCoord);

	//���ͼ��ID��Ϊ0����ʾ��ǽ
	if (targetTileGID)
	{
		return kwall;
	}

	//�����Ʒ���Ӧ�����ͼ��ID
	targetTileGID = Global::instance()->gameMap->ItemLayer->getTileGIDAt(targetTileCoord);

	//���ͼ��ID��Ϊ0����ʾ����Ʒ
	if (targetTileGID) {
		pickUpItem();
		return kitem;
	}

	//����Ų��Ӧ�����ͼ��ID
	targetTileGID = Global::instance()->gameMap->DoorLayer->getTileGIDAt(targetTileCoord);
	
	//���ͼ��ID��Ϊ0����ʾ����
	if (targetTileGID) {
		openDoor(targetTileGID);
		return kdoor;
	}


	//��ù�����Ӧ�����ͼ��ID
	targetTileGID = Global::instance()->gameMap->enemyLayer->getTileGIDAt(targetTileCoord);

	//���ͼ��ID��Ϊ0����ʾ�е���
	if (targetTileGID) {
		return kenemy;
	}



	int index = targetTileCoord.x + targetTileCoord.y * Global::instance()->gameMap->getMapSize().width;

	//��npc�ֵ��в�ѯ
	NPC *npc = Global::instance()->gameMap->npcDict.at(index);
	if (npc != NULL)
	{
		actWithNPC();
		return knpc;
	}

	//��Teleport�ֵ��в�ѯ
	Teleport *teleport = Global::instance()->gameMap->teleportDict.at(index);
	if (teleport != NULL)
	{
		doTeleport(teleport);
		return kteleport;
	}


	return knull;
}


void Hero::setFaceDirection(HeroDirection direction) {
	heroSprite->setTextureRect(Rect(0, 32 * direction, 32, 32));
}

void Hero::onMoveDone(Node* pTarget, void* data) {
	int direction = (int)data;
	setFaceDirection((HeroDirection)direction);
	isHeroMoving = false;

}

void Hero::doTeleport(Teleport *teleport) {

}

void Hero::actWithNPC() {

}

void Hero::openDoor(int gid) {
	if (isDoorOpening) {
		return;
	}

	targetDoorGID = gid;
	isDoorOpening = true;

	schedule(schedule_selector(Hero::DoorOpeningUpdate), 0.1f);
}

void Hero::pickUpItem() {

	Global::instance()->gameMap->ItemLayer->removeTileAt(targetTileCoord);

}

void Hero::DoorOpeningUpdate(float dt) {
	
	int NextGid = Global::instance()->gameMap->DoorLayer->getTileGIDAt(targetTileCoord) + 4;

	if (NextGid - targetDoorGID > 12) {
		Global::instance()->gameMap->DoorLayer->removeTileAt(targetTileCoord);
		unschedule(schedule_selector(Hero::DoorOpeningUpdate));
		isDoorOpening = false;
	}
	else {
		Global::instance()->gameMap->DoorLayer->setTileGID(NextGid,targetTileCoord);
	}
}
