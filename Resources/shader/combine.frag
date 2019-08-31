
#ifdef GL_ES
precision lowp float;
#endif

varying vec2 v_texCoord;

void main()
{
vec4 color1 = texture2D(CC_Texture0, v_texCoord);
vec4 color2 = texture2D(CC_Texture1, v_texCoord);

	gl_FragColor = color1 + color2;
}

