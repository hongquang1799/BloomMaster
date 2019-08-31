attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

#ifdef GL_ES
varying mediump vec2 v_texCoord;
varying mediump vec2 v_blurTexCoords[11];
#else
varying vec2 v_texCoord;
varying vec2 v_blurTexCoords[11];
#endif

void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    v_texCoord = a_texCoord;

	float pixelSize = 1.0 / 100.0;

v_blurTexCoords[0] = vec2(-pixelSize * 5.0 + v_texCoord.x, v_texCoord.y);
v_blurTexCoords[1] = vec2(-pixelSize * 4.0 + v_texCoord.x, v_texCoord.y);
v_blurTexCoords[2] = vec2(-pixelSize * 3.0 + v_texCoord.x, v_texCoord.y);
v_blurTexCoords[3] = vec2(-pixelSize * 2.0 + v_texCoord.x, v_texCoord.y);
v_blurTexCoords[4] = vec2(-pixelSize * 1.0 + v_texCoord.x, v_texCoord.y);
v_blurTexCoords[5] = vec2(pixelSize * 0.0 + v_texCoord.x, v_texCoord.y);
v_blurTexCoords[6] = vec2(pixelSize * 1.0 + v_texCoord.x, v_texCoord.y);
v_blurTexCoords[7] = vec2(pixelSize * 2.0 + v_texCoord.x, v_texCoord.y);
v_blurTexCoords[8] = vec2(pixelSize * 3.0 + v_texCoord.x, v_texCoord.y);
v_blurTexCoords[9] = vec2(pixelSize * 4.0 + v_texCoord.x, v_texCoord.y);
v_blurTexCoords[10] = vec2(pixelSize * 5.0 + v_texCoord.x, v_texCoord.y);

	
}


