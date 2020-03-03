#version 460 core

layout (location = 0) in vec4 vertex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;

void main() 
{
	TexCoord = vertex.zw;
	gl_Position = projection * view * model * vec4(vertex.xy, 0.0f, 1.0f);
}
