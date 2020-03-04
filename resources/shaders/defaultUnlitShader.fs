#version 460 core

uniform vec3 tint;
uniform sampler2D tex;

in vec2 TexCoord;
out vec4 FragColor;

void main() 
{
	FragColor = vec4(tint, 1.0) * texture(tex, TexCoord).rgba;
}
