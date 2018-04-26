#ifndef _HROCKER_
#define _HROCKER_


#include"cocos2d.h"
USING_NS_CC;

typedef enum {
	tag_rocker,tag_rockerBG
}tagForHRocker;

class HRocker : public Layer
{
public:
	EventListenerTouchOneByOne * listener;
	//����ҡ��
	static HRocker* createHRocker(const char* rockerImageName, const char* rockerBGImageName, Point position);
	//����ҡ��
	void startRocker(bool _isStopOther);
	//ֹͣҡ��
	void stopRocker();
private:
	void rockerInit(const char* rockerImageName, const char* rockerBGImageName, Point position);
	//�õ��뾶Ϊr��Բ����һ���Ƕȶ�Ӧ��x��y����
	Point getAnglePosition(float r, float angle);
	//�Ƿ�ɲ���ҡ��
	bool isCanMove;
	//�õ�ҡ�����û�������ĽǶ�
	float getRad(Point pos1, Point pos2);
	//ҡ�˱�������
	Point rockerBGPosition;
	//ҡ�˱����İ뾶
	float rockerBGR;
	//�����¼�
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	CREATE_FUNC(HRocker);

};


#endif