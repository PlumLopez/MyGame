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
		|| collisionType == kenemy
		|| collisionType == kdoor
		|| collisionType == knpc)
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

	if (heroPosition.x < 0
		|| targetTileCoord.x > map->getMapSize().width - 1
		|| targetTileCoord.y < 0
		|| targetTileCoord.y > map->getMapSize().height - 1)
	{
		return kwall;
	}
}


void Hero::setFaceDirection(HeroDirection direction) {
	heroSprite->setTextureRect(Rect(0, 32 * direction, 32, 32));
}

void Hero::onMoveDone(Node* pTarget, void* data) {
	int direction = (int)data;
	setFaceDirection((HeroDirection)direction);
	isHeroMoving = false;

}