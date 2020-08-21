#version 450 core

layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTexCoord;

out vec3 vertexColor;
out vec2 TexCoord;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 md;


void main()
{
    gl_Position = projection * view * md * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    //gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	//vertexColor = aColor;//vec4(0.5, 0.0, 0.0, 1.0);
    TexCoord = aTexCoord;
}