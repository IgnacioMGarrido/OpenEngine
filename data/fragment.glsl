varying vec3 fcolor;
uniform sampler2D texSampler; 
varying vec2 ftex;
void main() {
	gl_FragColor = texture2D( texSampler, ftex); //vec4(fcolor, 1);
}
