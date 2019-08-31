#ifndef BLOOM_EFFECT_NODE_H
#define BLOOM_EFFECT_NODE_H

#include "cocos2d.h"

using namespace cocos2d;

struct FBO
{
	GLuint id;
	Texture2D * texture;
};

class BloomEffectNode : public cocos2d::Node
{
public:
	BloomEffectNode();
	virtual ~BloomEffectNode();

    virtual bool init();

	void setDividend(int dividend);

	void setEnabled(bool flag);
	bool isEnabled();

	void setBeginGlobalZorder(float Zorder);
	void setEndGlobalZorder(float Zorder);

	void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;
 
	CREATE_FUNC(BloomEffectNode);
private:
	bool _enabled;
	int _dividend;
	float _beginGlobalZorder;
	float _endGlobalZorder;

	GLfloat vertices[8];
	GLfloat texCoords[8];

	FBO _normalFBO;
	FBO _horizontalBlurFBO;
	FBO _verticalBlurFBO;
	FBO _brightFBO;

	GLProgram * _brightGLProgram;
	GLProgram * _horizontalBlurGLProgram;
	GLProgram * _verticalBlurGLProgram;
	GLProgram * _combineGLProgram;

	Renderer * _renderer;

	CustomCommand _frameBeginCommand;
	CustomCommand _frameEndCommand;
	CustomCommand _drawCommand;

	void onBegin();
	void onEnd();

	void onDraw();

	FBO generateFrameBuffer(int pixelWidth, int pixelHeight);
};

#endif // __HELLOWORLD_SCENE_H__
