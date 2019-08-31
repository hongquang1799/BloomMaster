#include "BloomEffectNode.h"

BloomEffectNode::BloomEffectNode()
{
	_enabled = true;

	_brightFBO.id = 0;
	_brightFBO.texture = nullptr;
}

BloomEffectNode::~BloomEffectNode()
{
	glDeleteFramebuffers(1, &_normalFBO.id);
	glDeleteFramebuffers(1, &_horizontalBlurFBO.id);
	glDeleteFramebuffers(1, &_verticalBlurFBO.id);
	glDeleteFramebuffers(1, &_brightFBO.id);

	CC_SAFE_RELEASE(_normalFBO.texture);
	CC_SAFE_RELEASE(_horizontalBlurFBO.texture);
	CC_SAFE_RELEASE(_verticalBlurFBO.texture);
	CC_SAFE_RELEASE(_brightFBO.texture);
}

bool BloomEffectNode::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	_renderer = Director::getInstance()->getRenderer();

	vertices[0] = 0.0;
	vertices[1] = 0.0;
	vertices[2] = 0.0;
	vertices[3] = visibleSize.height;
	vertices[4] = visibleSize.width;
	vertices[5] = 0.0;
	vertices[6] = visibleSize.width;
	vertices[7] = visibleSize.height;

	texCoords[0] = 0.0;
	texCoords[1] = 0.0;
	texCoords[2] = 0.0;
	texCoords[3] = 1.0;
	texCoords[4] = 1.0;
	texCoords[5] = 0.0;
	texCoords[6] = 1.0;
	texCoords[7] = 1.0;

	_brightGLProgram = GLProgram::createWithFilenames("shader/bright.vert", "shader/bright.frag");
	_horizontalBlurGLProgram = GLProgram::createWithFilenames("shader/horizontal_blur.vert", "shader/horizontal_blur.frag");
	_verticalBlurGLProgram = GLProgram::createWithFilenames("shader/vertical_blur.vert", "shader/vertical_blur.frag");
	_combineGLProgram = GLProgram::createWithFilenames("shader/combine.vert", "shader/combine.frag");

	auto shaderCache = ShaderCache::getInstance();
	shaderCache->addGLProgram(_brightGLProgram, "BRIGHT");
	shaderCache->addGLProgram(_horizontalBlurGLProgram, "HORIZONTAL_BLUR");
	shaderCache->addGLProgram(_verticalBlurGLProgram, "VERTICAL_BLUR");
	shaderCache->addGLProgram(_combineGLProgram, "COMBINE");

	auto glview = Director::getInstance()->getOpenGLView();
	int pixelWidth = (int)glview->getFrameSize().width;
	int pixelHeight = (int)glview->getFrameSize().height;

	_normalFBO = this->generateFrameBuffer(pixelWidth, pixelHeight);

	return true;
}

void BloomEffectNode::onBegin()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _normalFBO.id);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void BloomEffectNode::onEnd() 
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	vertices[3] = visibleSize.height / _dividend;
	vertices[4] = visibleSize.width / _dividend;
	vertices[6] = visibleSize.width / _dividend;
	vertices[7] = visibleSize.height / _dividend;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, texCoords);

    /////////////////////////////////////////////////////////////////////

    glBindTexture(GL_TEXTURE_2D, _normalFBO.texture->getName());
    BlendFunc blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    GL::blendFunc(blendFunc.src, blendFunc.dst);

    _brightGLProgram->use();
    _brightGLProgram->setUniformsForBuiltins();

    glBindFramebuffer(GL_FRAMEBUFFER, _brightFBO.id);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//    ////////////////////////////////////////////////////

    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, texCoords);

    glBindTexture(GL_TEXTURE_2D, _brightFBO.texture->getName());
    blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    GL::blendFunc(blendFunc.src, blendFunc.dst);

    _horizontalBlurGLProgram->use();
    _horizontalBlurGLProgram->setUniformsForBuiltins();

    glBindFramebuffer(GL_FRAMEBUFFER, _horizontalBlurFBO.id);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

//    //////////////////////////////////////////////////////////////////////
//
    glBindTexture(GL_TEXTURE_2D, _horizontalBlurFBO.texture->getName());

    _verticalBlurGLProgram->use();
    _verticalBlurGLProgram->setUniformsForBuiltins();

    glBindFramebuffer(GL_FRAMEBUFFER, _verticalBlurFBO.id);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    CHECK_GL_ERROR_DEBUG();

}

void BloomEffectNode::onDraw()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	vertices[3] = visibleSize.height;
	vertices[4] = visibleSize.width;
	vertices[6] = visibleSize.width;
	vertices[7] = visibleSize.height;

	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, texCoords);

    glBindTexture(GL_TEXTURE_2D, _verticalBlurFBO.texture->getName());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _normalFBO.texture->getName());
    BlendFunc blendFunc = BlendFunc::ADDITIVE;
    GL::blendFunc(blendFunc.src, blendFunc.dst);

    _combineGLProgram->use();
    _combineGLProgram->setUniformsForBuiltins(_modelViewTransform);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glActiveTexture(GL_TEXTURE0);

    CHECK_GL_ERROR_DEBUG();
}

void BloomEffectNode::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	if (_enabled)
	{
		_frameBeginCommand.init(_beginGlobalZorder);
		_frameBeginCommand.func = CC_CALLBACK_0(BloomEffectNode::onBegin, this);
		_renderer->addCommand(&_frameBeginCommand);

		_frameEndCommand.init(_endGlobalZorder);
		_frameEndCommand.func = CC_CALLBACK_0(BloomEffectNode::onEnd, this);
		_renderer->addCommand(&_frameEndCommand);

		_drawCommand.init(_globalZOrder);
		_drawCommand.func = CC_CALLBACK_0(BloomEffectNode::onDraw, this);
		renderer->addCommand(&_drawCommand);
	}
}

FBO BloomEffectNode::generateFrameBuffer(int pixelWidth, int pixelHeight)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	void *data = nullptr;
	auto dataLen = pixelWidth * pixelHeight * 4;
	data = malloc(dataLen);

	memset(data, 0, dataLen);

	GLuint id;
	Texture2D * texture;
	texture = new (std::nothrow) Texture2D();
	texture->initWithData(data, dataLen, Texture2D::PixelFormat::RGBA8888, pixelWidth, pixelHeight, visibleSize);

	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->getName(), 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	CC_SAFE_FREE(data);

	CHECK_GL_ERROR_DEBUG();

	FBO fbo;
	fbo.id = id;
	fbo.texture = texture;

	return fbo;
}

void BloomEffectNode::setBeginGlobalZorder(float Zorder)
{
	_beginGlobalZorder = Zorder;
}

void BloomEffectNode::setEndGlobalZorder(float Zorder)
{
	_endGlobalZorder = Zorder;
}

void BloomEffectNode::setEnabled(bool flag)
{
	_enabled = flag;
}

bool BloomEffectNode::isEnabled()
{
	return _enabled;
}

void BloomEffectNode::setDividend(int dividend)
{
	_dividend = dividend;

	if (_brightFBO.id != 0)
	{
		glDeleteFramebuffers(1, &_horizontalBlurFBO.id);
		glDeleteFramebuffers(1, &_verticalBlurFBO.id);
		glDeleteFramebuffers(1, &_brightFBO.id);

		CC_SAFE_RELEASE(_horizontalBlurFBO.texture);
		CC_SAFE_RELEASE(_verticalBlurFBO.texture);
		CC_SAFE_RELEASE(_brightFBO.texture);
	}

	auto glview = Director::getInstance()->getOpenGLView();
	int pixelWidth = (int)glview->getFrameSize().width;
	int pixelHeight = (int)glview->getFrameSize().height;

	_horizontalBlurFBO = this->generateFrameBuffer((int)floor(pixelWidth / _dividend), (int)floor(pixelHeight / _dividend));
	_verticalBlurFBO = this->generateFrameBuffer((int)floor(pixelWidth / _dividend), (int)floor(pixelHeight / _dividend));
	_brightFBO = this->generateFrameBuffer((int)floor(pixelWidth / _dividend), (int)floor(pixelHeight / _dividend));
}

