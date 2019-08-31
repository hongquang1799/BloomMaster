
#ifdef GL_ES
precision lowp float;
#endif

varying vec2 v_texCoord;

void main()
{
    vec4 color = texture2D(CC_Texture0, v_texCoord);
	float brightness = color.r * 0.2126 + color.g * 0.7152 + color.b * 0.0722;
	gl_FragColor = vec4(brightness);
	gl_FragColor = color * brightness;
}

