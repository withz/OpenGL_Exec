#version 450 core

layout(location = 0) in vec3 aPos;
//layout(location = 1) in vec3 aColor;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

//out vec3 vertexColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;



void main()
{
    gl_Position = projection * view * model * transform * vec4(aPos, 1.0);
    //gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    //vertexColor = aColor;//vec4(0.5, 0.0, 0.0, 1.0);
    //TexCoord = aTexCoord;
    Normal = aNormal;
    TexCoord = aTexCoord;
    FragPos = vec3(model * transform * vec4(aPos, 1.0));
}