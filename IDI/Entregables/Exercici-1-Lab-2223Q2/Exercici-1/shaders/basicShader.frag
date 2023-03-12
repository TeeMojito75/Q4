#version 330 core

out vec4 FragColor;
uniform vec3 ColorObj;

void main() {
    FragColor = vec4(ColorObj,1);
}
