#ifndef _ANIMATIONCONTROL_
#define _ANIMATIONCONTROL_

#include"cocos2d.h"
#include"Singleton.h"
#include"GameConstants.h"
USING_NS_CC;



class AnimationControl : public Singleton<AnimationControl>
{
public:
	AnimationControl();
	~AnimationControl();

	//��ʼ������ģ�滺���
	bool initAnimationMap();

	//�������ֵõ�һ������ģ��
	Animation* getAnimation(int key);

	//����һ������ʵ��
	Animate* createAnimate(int key);

	//����һ������ʵ��
	Animate* createAnimate(const char* key);

protected:
	//������ʿ���߶���ģ��
	Animation * createHeroMovingAnimationByDirection(HeroDirection direction);
	
};

#endif