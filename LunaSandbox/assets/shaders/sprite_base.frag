#version 330 core

in vec2 FragTexCoord;

uniform sampler2D u_texUnit;

void main()
{
    gl_FragColor = texture(u_texUnit, FragTexCoord);
}

