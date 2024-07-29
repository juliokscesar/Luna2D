#version 330 core

in vec2 FragTexCoord;

uniform sampler2D u_texUnit;
uniform float u_tilingFactor = 1.0f;

void main()
{
    vec4 texColor = texture(u_texUnit, FragTexCoord * u_tilingFactor);
    if (texColor.a < 0.5)
	discard;

    gl_FragColor = texColor;
}

