#include"cocos2d.h"
#include"HRocker.h"

HRocker * HRocker::createHRocker(const char * rockerImageName, const char * rockerBGImageName, Point position)
{
	HRocker* layer = HRocker::create();
	if (layer) {
		layer->rockerInit(rockerImageName, rockerBGImageName, position);
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

void HRocker::startRocker(bool _isStopOther)
{
	//�������ÿɼ������ü���
	Sprite* rocker = (Sprite*)getChildByTag(tag_rocker);
	rocker->setVisible(true);
	Sprite* rockerBG = (Sprite*)getChildByTag(tag_rockerBG);
	rockerBG->setVisible(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void HRocker::stopRocker()
{
	//�������ò��ɼ���ȡ������
	Sprite* rocker = (Sprite*)getChildByTag(tag_rocker);
	rocker->setVisible(false);
	Sprite* rockerBG = (Sprite*)getChildByTag(tag_rockerBG);
	rockerBG->setVisible(false);
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
}

void HRocker::rockerInit(const char * rockerImageName, const char * rockerBGImageName, Point position)
{
	//��ӱ���ͼ
	Sprite* spRockerBG = Sprite::create(rockerBGImageName);
	spRockerBG->setVisible(true);
	spRockerBG->setPosition(position);
	spRockerBG->setScale(0.2f);
	addChild(spRockerBG, 0, tag_rockerBG);
	//��Ӱ�ťͼ
	Sprite* spRocker = Sprite::create(rockerImageName);
	spRocker->setVisible(true);
	spRocker->setPosition(position);
	spRocker->setOpacity(180);
	spRocker->setScale(0.2f);
	addChild(spRocker, 1, tag_rocker);
	//ҡ�˱���ͼ����
	rockerBGPosition = position;
	//ҡ�˱���ͼ�뾶
	rockerBGR = spRockerBG->getContentSize().width*0.5*0.2;
	
	listener = EventListenerTouchOneByOne::create();
	//�󶨼����¼�
	listener->onTouchBegan = CC_CALLBACK_2(HRocker::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HRocker::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HRocker::onTouchEnded, this);
	listener->setSwallowTouches(true);

}

Point HRocker::getAnglePosition(float r, float angle)
{

	return Vec2(r*cos(angle),r*sin(angle));
}

float HRocker::getRad(Point pos1, Point pos2)
{
	//�õ����������x��y����ֵ
	float px1 = pos1.x;
	float py1 = pos1.y;
	float px2 = pos2.x;
	float py2 = pos2.y;
	//������߳���
	float x = px2 - px1;
	float y = py2 - py1;
	//���ù��ɶ����������ֱ�߾���
	float xie = sqrt(x*x + y * y);
	float cos = x / xie;
	float rad = acos(cos);
	//������y����<ҡ�˵�y����ʱ��ȡ��
	if (py1 > py2) {
		rad = -rad;
	}
	return rad;
}

bool HRocker::onTouchBegan(Touch * touch, Event * event)
{
	Sprite* sp = (Sprite*)getChildByTag(tag_rocker);
	//�õ�����������
	Point point = touch->getLocation();
	//�ж��Ƿ񵥻���sp������飺boundingbox���������С֮�ڵ���������
	if (sp->boundingBox().containsPoint(point)) {
		isCanMove = true;
	}
	return true;
	return false;
}

void HRocker::onTouchMoved(Touch * touch, Event * event)
{
	if (!isCanMove) {
		return;
	}
	Sprite* sp = (Sprite*)getChildByTag(tag_rocker);
	Point point = touch->getLocation();
	//�ж�����Բ�ĵľ����Ƿ����ҡ�˱����İ뾶
	if (sqrt(pow(point.x - rockerBGPosition.x, 2) + pow(point.y - rockerBGPosition.y, 2)) >= rockerBGR) {
		//�õ�������ҡ�˱���Բ���γɵĽǶ�
		float angle = getRad(rockerBGPosition, point);
		//ȷ��СԲ�˶��ڱ���ͼ��
		sp->setPosition(getAnglePosition(rockerBGR, angle) + rockerBGPosition);
	}
	else {
		sp->setPosition(point);
	}
}

void HRocker::onTouchEnded(Touch * touch, Event * event)
{
	if (!isCanMove) {
		return;
	}
	Sprite* rocker = (Sprite*)getChildByTag(tag_rocker);
	Sprite* rockerBG = (Sprite*)getChildByTag(tag_rockerBG);
	rocker->stopAllActions();
	rocker->runAction(MoveTo::create(0.08f, rockerBG->getPosition()));
	isCanMove = false;

}



