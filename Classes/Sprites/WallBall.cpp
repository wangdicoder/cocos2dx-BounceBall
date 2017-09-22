#include "WallBall.h"


WallBall::WallBall()
{
}


WallBall::~WallBall()
{
}

WallBall*  WallBall::create(int index)
{
	auto ref = new WallBall();
	ref->init(index);
	ref->autorelease();

	return ref;
}

bool WallBall::init(int index)
{
	if (!Sprite::init())
		return false;

	m_index = index;
	initWithFile("wallball.png");
	auto ballBody = PhysicsBody::createCircle(this->getContentSize().width * 0.5f);
	ballBody->getShape(0)->setRestitution(1.0f);
	ballBody->getShape(0)->setFriction(0.0f);
	ballBody->getShape(0)->setDensity(1.0f);
	ballBody->setGravityEnable(false);
	ballBody->setDynamic(false);
	//ballBody->setGroup(0);
	ballBody->setCategoryBitmask(0x01);
	ballBody->setContactTestBitmask(0x02);
	ballBody->setCollisionBitmask(0x02);
	setTag(1);
	this->setPhysicsBody(ballBody);

	char str[5] = { 0 };
	sprintf(str, "%d", m_index);
	indexLabel = LabelAtlas::create(str, "number.png", 24, 40, '0');
	indexLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	indexLabel->setPosition(getContentSize().width / 2, getContentSize().height / 2);
	this->addChild(indexLabel);

	return true;
}

void WallBall::subtractIndex()
{
	if (m_index - 1 > 0)
	{
		char str[5] = { 0 };
		sprintf(str, "%d", --m_index);
		indexLabel->setString(str);
		log("%d", m_index);
	}
	else if (m_index - 1 <= 0)
	{
		this->removeFromParentAndCleanup(true);
	}
}
