
#ifdef GL_ES
precision lowp float;
#endif

varying vec2 v_texCoord;
varying vec2 v_blurTexCoords[11];

void main()
{
   gl_FragColor =  vec4(0.0, 0.0, 0.0, 0.0);
	gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[0]) * 0.0093;
	gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[1]) * 0.028002;
	gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[2]) * 0.065984;
	gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[3]) * 0.121703;
	gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[4]) * 0.175713;
	gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[5]) * 0.198596;
	gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[6]) * 0.175713;
	gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[7]) * 0.121703;
	gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[8]) * 0.065984;
	gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[9]) * 0.028002;
	gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[10]) * 0.0093;
}

