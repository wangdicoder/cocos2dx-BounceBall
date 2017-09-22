#pragma once
#include "cocos2d.h"

USING_NS_CC;

class WallBall: public Sprite
{
public:
	WallBall();
	virtual ~WallBall();
	bool init(int index);
	static WallBall* create(int index = 1);
	void subtractIndex();

private:
	int m_index;
	LabelAtlas* indexLabel;
};

