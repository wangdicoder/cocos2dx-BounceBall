#include "BaseLayer.h"


BaseLayer::BaseLayer()
{
}


BaseLayer::~BaseLayer()
{
}

bool BaseLayer::init()
{
	if (!Layer::init())
		return false;

	size = Director::getInstance()->getWinSize();

	return true;
}