#include "GameScene.h"
#include "StartScene.h"
#include "GameManager.h"
#include "GameoverLayer.h"
#include "..\Sprites\WallBall.h"

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setAutoStep(false);
	Vec2 gravity(0.0f, 0.0f);
	scene->getPhysicsWorld()->setGravity(gravity);

	auto layer = GameScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!BaseLayer::init())
		return false;

	auto edge = Node::create();
	auto edgeBody = PhysicsBody::createEdgeBox(size, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeBody->getShape(0)->setRestitution(1.0f);
	edgeBody->getShape(0)->setFriction(0);
	edgeBody->getShape(0)->setDensity(1.0f);
	edge->setPosition(size.width/2, size.height/2);
	edge->setPhysicsBody(edgeBody);
	this->addChild(edge);
	edge->setTag(0);

	for (int i = 0; i < 5; i++)
	{
		auto wallBall = WallBall::create(5);
		wallBall->setPosition(size.width / 2 + wallBall->getContentSize().width * i, size.height - wallBall->getContentSize().height * 1.7f);
		this->addChild(wallBall);
	}


	schedule([&](float dt){
		auto ball = Sprite::create("ball.png");
		ball->setPosition(100, 100);
		auto ballBody = PhysicsBody::createCircle(ball->getContentSize().width * 0.5f);
		ballBody->getShape(0)->setRestitution(1.0f);
		ballBody->getShape(0)->setFriction(0.0f);
		ballBody->getShape(0)->setDensity(1.0f);
		ballBody->setGravityEnable(false);
		ballBody->setCategoryBitmask(0x02);
		ballBody->setContactTestBitmask(0x01);
		ballBody->setCollisionBitmask(0x01);
		Vect force = Vect(1000000.0f, 1000000.0f);
		ballBody->applyImpulse(force);
		ball->setPhysicsBody(ballBody);
		this->addChild(ball);
	}, 0.1f, 3, 0, "shotball");
	


	scheduleUpdate();

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

void GameScene::update(float dt)
{
	//fix physics bug
	for (int i = 0; i < 3; ++i)
		m_world->step(1 / 180.0f);

}

bool GameScene::onContactBegin(PhysicsContact& contact)
{
	auto sp1 = (WallBall*)contact.getShapeA()->getBody()->getNode();
	auto sp2 = (WallBall*)contact.getShapeB()->getBody()->getNode();

	if (sp1->getTag() == 1)
		sp1->subtractIndex();
	if (sp2->getTag() == 1)
		sp2->subtractIndex();

	return true;
}