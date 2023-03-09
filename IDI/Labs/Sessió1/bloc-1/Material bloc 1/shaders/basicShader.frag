#version 330 core

out vec4 FragColor;
in vec3 fColor;

void main() {
    FragColor = vec4(fColor, 1);
    // if (gl_FragCoord.x > 345) FragColor = vec4(1., 0., 0.,1);
    if (int(gl_FragCoord.y)/10 % 2 == 0 ||int(gl_FragCoord.x)/10 % 2 == 0) discard;
}

