#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();

	auto layer = HelloWorld::create();
	scene->addChild(layer);

	return scene;
}

bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto touchListener = EventListenerTouchAllAtOnce::create();
	touchListener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
	touchListener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
	touchListener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	keyBoardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);

	//rapidjson::Document document;

	//document.SetObject();

	//// create a rapidjson array type with similar syntax to std::vector
	//rapidjson::Value array(rapidjson::kArrayType);

	//// must pass an allocator when the object may need to allocate memory
	//rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	//// chain methods as rapidjson provides a fluent interface when modifying its objects
	//array.PushBack("hello", allocator); array.PushBack("world", allocator);//"array":["hello","world"]

	//document.AddMember("Name", "XYZ", allocator);
	//document.AddMember("Rollnumer", 2, allocator);
	//document.AddMember("array", array, allocator);

	//// create a rapidjson object type
	//rapidjson::Value object(rapidjson::kObjectType);
	//object.SetObject();
	//object.AddMember("Math", "50", allocator);
	//object.AddMember("Science", "70", allocator);
	//object.AddMember("English", "50", allocator);
	//object.AddMember("Social Science", "70", allocator);
	//document.AddMember("Marks", object, allocator);
	////	fromScratch["object"]["hello"] = "Yourname";

	//rapidjson::Value& v = object["Math"];
	////v.Set("9999", allocator);
	//v.SetString("9999");

	//rapidjson::StringBuffer strbuf;
	//rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
	//document.Accept(writer);

	//log("JsonData = %s", strbuf.GetString());
	//log("JsonData name = %s", document["Name"].GetString());
	//log("JsonData rollnumber = %d", document["Rollnumer"].GetInt());
	//log("JsonData array = %s", document["array"][rapidjson::SizeType(0)].GetString());
	//log("JsonData array = %s", document["array"][1].GetString());

	//int a = allocator.Size();

	

	return true;
}

HelloWorld::HelloWorld()
{

}

HelloWorld::~HelloWorld()
{

}

void HelloWorld::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{


}

void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{

}

void HelloWorld::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{

}

void HelloWorld::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{

}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{

}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

}

