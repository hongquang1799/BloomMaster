#include "BloomScene.h"
#include "BloomEffectNode.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* BloomScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = BloomScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool BloomScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
	auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();

	auto touchListener = EventListenerTouchAllAtOnce::create();
	touchListener->onTouchesBegan = CC_CALLBACK_2(BloomScene::onTouchesBegan, this);
	touchListener->onTouchesMoved = CC_CALLBACK_2(BloomScene::onTouchesMoved, this);
	touchListener->onTouchesEnded = CC_CALLBACK_2(BloomScene::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyReleased = CC_CALLBACK_2(BloomScene::onKeyReleased, this);
	keyBoardListener->onKeyPressed = CC_CALLBACK_2(BloomScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);

	_downScale = _maxDownScale = 1;

	int width = (int)frameSize.width;
	int height = (int)frameSize.height;
	while (width % _maxDownScale == 0 && height % _maxDownScale == 0)
	{
		_maxDownScale = _maxDownScale * 2;
	}
	_maxDownScale = _maxDownScale / 2;

	_bloomEffectNode = BloomEffectNode::create();
	_bloomEffectNode->setBeginGlobalZorder(1.0);
	_bloomEffectNode->setEndGlobalZorder(2.0);
	_bloomEffectNode->setGlobalZOrder(50.0);
	_bloomEffectNode->setDividend(_downScale);
	_bloomEffectNode->setEnabled(false);
	addChild(_bloomEffectNode);

	std::vector<std::string> textureFileNames;

	_sprite = Sprite::create("2.png");
	_sprite->setScale(visibleSize.width / _sprite->getContentSize().width);
	_sprite->setPosition(visibleSize / 2);
	addChild(_sprite);
	_sprite->setGlobalZOrder(1.5);

	_downScaleLabel = Label::createWithTTF("0\n0", "fonts/Myfont.ttf", 20);
	_downScaleLabel->setPosition(visibleSize.width / 2, visibleSize.height - _downScaleLabel->getContentSize().height * 0.7);
	addChild(_downScaleLabel);
	_downScaleLabel->setGlobalZOrder(200.0f);
	_downScaleLabel->setColor(Color3B::RED);

	_frameSizeLabel = Label::createWithTTF(String::createWithFormat("W : %d\nH : %d\nMDS : %d", (int)frameSize.width, (int)frameSize.height, _maxDownScale)->getCString(), "fonts/Myfont.ttf", 20);
	_frameSizeLabel->setPosition(_frameSizeLabel->getContentSize().width * 0.6, visibleSize.height - _frameSizeLabel->getContentSize().height * 0.6);
	addChild(_frameSizeLabel);
	_frameSizeLabel->setGlobalZOrder(200.0f);
	_frameSizeLabel->setColor(Color3B::BLACK);


	float buttonSize = 30.0f;

	ui::Button * buttons[3];

	for (int i = 0; i < 3; i++)
	{
		buttons[i] = ui::Button::create("button.png");
		buttons[i]->setPosition(Vec2(visibleSize.width - buttonSize * 0.7, visibleSize.height - buttonSize * 0.7 - buttonSize * 1.2 * i));
		buttons[i]->setScale(buttonSize / buttons[i]->getContentSize().width);
		this->addChild(buttons[i]);
		buttons[i]->setGlobalZOrder(100.0f);
	}

	_activateButton = buttons[0];
	_increaseButton = buttons[1];
	_decreaseButton = buttons[2];

	_activateButton->addTouchEventListener([=](Ref * sender, ui::Widget::TouchEventType type) 
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			_bloomEffectNode->setEnabled(!_bloomEffectNode->isEnabled());
		}
	});

	_increaseButton->addTouchEventListener([=](Ref * sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (_downScale < _maxDownScale)
			{
				_downScale = _downScale * 2;
				_bloomEffectNode->setDividend(_downScale);
			}
		}
	});

	_decreaseButton->addTouchEventListener([=](Ref * sender, ui::Widget::TouchEventType type)
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			if (_downScale > 1)
			{
				_downScale = _downScale / 2;
				_bloomEffectNode->setDividend(_downScale);
			}
		}
	});

    return true;
}


void BloomScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

BloomScene::BloomScene()
{

}

BloomScene::~BloomScene()
{
	
}

void BloomScene::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	_downScaleLabel->setString(String::createWithFormat("DS : %d", _downScale, Director::getInstance()->getSecondsPerFrame())->getCString());

	CHECK_GL_ERROR_DEBUG();
}

void BloomScene::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
}

void BloomScene::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
}

void BloomScene::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
}

void BloomScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{

}

void BloomScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
	}
}
