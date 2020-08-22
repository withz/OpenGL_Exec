#version 450 core

// Phong
struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};


//in vec3 vertexColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 Color;
uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform vec3 ViewPosition;

uniform Material material;




uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;




void main()
{
	//FragColor = vec4(vertexColor, 1.0);//xColor;//vertexColor;//vec4(1.0f, 0.5f, 0.2f, 1.0f);
	//FragColor = mix(texture(ourTexture_w, TexCoord), texture(ourTexture_c, TexCoord), 0.5);
	//FragColor = texture(ourTexture_c, TexCoord) * xColor;
	//FragColor = texture(ourTexture_c, TexCoord);
	vec3 norm = normalize(Normal);
	vec3 light_dir = normalize(LightPosition - FragPos);
	vec3 reflect_dir = reflect(-light_dir, norm);
	vec3 view_dir = normalize(ViewPosition - FragPos);

	float distance = length(LightPosition - FragPos);
	float attenuation = 1.0 / (1.0 + 0.2 * distance + 0.5 * distance * distance) * 30;

	vec3 ambient = 0.5 * LightColor * material.ambient;
	vec3 diffuse = max(dot(norm, light_dir), 0.0) * LightColor * texture(diffuseTexture, TexCoord).xyz * material.diffuse;
	vec3 specular = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess) * LightColor * texture(specularTexture, TexCoord).xyz * material.specular;
	vec3 light = ambient + diffuse + specular;

	FragColor = vec4(light * attenuation, 1.0);
}