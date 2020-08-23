#version 450 core

// Phong
struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};


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
	vec3 norm = normalize(Normal);
	vec3 light_dir = normalize(LightPosition - FragPos);
	vec3 reflect_dir = reflect(-light_dir, norm);
	vec3 view_dir = normalize(ViewPosition - FragPos);
	vec3 halfway_dir = normalize(ViewPosition - FragPos + LightPosition - FragPos);

	float distance = length(LightPosition - FragPos);
	float attenuation = 1.0 / (1.0 + 0.2 * distance + 0.5 * distance * distance) * 30;

	vec3 ambient = 0.8 * LightColor * texture(diffuseTexture, TexCoord).xyz * material.ambient;
	vec3 diffuse = max(dot(norm, light_dir), 0.0) * LightColor * texture(diffuseTexture, TexCoord).xyz * material.diffuse;
	vec3 specular = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess) * LightColor * texture(specularTexture, TexCoord).xyz * material.specular;
	specular = pow(max(dot(norm, halfway_dir), 0.0), material.shininess) * LightColor * texture(specularTexture, TexCoord).xyz * material.specular;
	vec3 light = ambient + 2.5 * diffuse + specular;

	FragColor = vec4(light * attenuation, 1.0);
	FragColor.rgb = pow(FragColor.rgb, vec3(1 / 2.2));
}