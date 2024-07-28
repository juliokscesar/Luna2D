#version 330 core

in vec2 FragTexCoord;

uniform vec3 u_color;

void main()
{
    // TODO: implement texture
    gl_FragColor = vec4(u_color, 1.0);
}

