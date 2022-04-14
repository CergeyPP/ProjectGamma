#version 450 core
layout(location = 0) in vec3 position;
layout(location = 2) in vec2 texCoords;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

out vec2 TexCoords;

void main(){
	gl_Position = Projection * View * Model * vec4(position, 1);
	TexCoords = texCoords;
}