#version 450 core

in vec3 vertexColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec4 xColor;
uniform sampler2D ourTexture_w;
uniform sampler2D ourTexture_c;

void main()
{
	//FragColor = vec4(vertexColor, 1.0);//xColor;//vertexColor;//vec4(1.0f, 0.5f, 0.2f, 1.0f);
	FragColor = mix(texture(ourTexture_w, TexCoord), texture(ourTexture_c, TexCoord), 0.5);
	//FragColor = texture(ourTexture_c, TexCoord) * xColor;
	//FragColor = texture(ourTexture_c, TexCoord);
}