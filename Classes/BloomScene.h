#ifndef BLOOM_SCENE_H
#define BLOOM_SCENE_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class BloomEffectNode;

class BloomScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

	BloomScene();
	virtual ~BloomScene();

    virtual bool init();
 
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	CREATE_FUNC(BloomScene);
private:
	BloomEffectNode * _bloomEffectNode;

	Sprite * _sprite;

	ui::Button * _activateButton;
	ui::Button * _increaseButton;
	ui::Button * _decreaseButton;
	ui::Button * _changeButton;

	int _downScale;
	int _maxDownScale;
	Label * _downScaleLabel;

	Label * _frameSizeLabel;
	
	void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event) override;
	void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event) override;
	void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event) override;

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) override;
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) override;

	void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);

	CustomCommand cmd;
};

#endif // __HELLOWORLD_SCENE_H__
