#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

#include "cocos2d.h"

using namespace cocos2d;

enum class 

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	HelloWorld();
	virtual ~HelloWorld();

	virtual bool init();

	CREATE_FUNC(HelloWorld);
private:

	void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event) override;
	void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event) override;
	void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event) override;

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) override;
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) override;

	void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);


};

#endif // __HELLOWORLD_SCENE_H__
