#version 330 core

in vec3 fcolor;
out vec4 FragColor;

uniform vec3 verd;
uniform vec3 verdR;

void main() {
	if (verdR[1] != 0.0) FragColor = vec4(verdR, 1);
	else FragColor = vec4(fcolor*verd, 1);
}

