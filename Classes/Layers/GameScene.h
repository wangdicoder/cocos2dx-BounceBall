#pragma once
#include "cocos2d.h"
#include "Layers\BaseLayer.h"

USING_NS_CC;

class GameScene : public BaseLayer
{
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	virtual bool init() override;
	static Scene* createScene();
	void setPhysicsWorld(PhysicsWorld* world){ this->m_world = world; };
	void update(float dt);
	bool onContactBegin(PhysicsContact& contact);

private:
	PhysicsWorld* m_world;
};

