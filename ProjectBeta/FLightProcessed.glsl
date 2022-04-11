#version 450 core
#define POINTLIGHTS_MAX 100
#define SPOTLIGHTS_MAX 100

struct Material{
	sampler2D Albedo;
	sampler2D Specular;
	float shininess;
};

struct DirectLight{
	vec3 direction;

	vec3 diffuse;
	vec3 specular;
};

struct PointLight{
	vec3 position;

	//float constant = 1.f;
	float linear;
	float quadratic;

	vec3 diffuse;
	vec3 specular;
};

struct SpotLight{
	vec3 position;
	vec3 direction;
	float cutoff;

	//float constant = 1.f;
	float linear;
	float quadratic;

	vec3 diffuse;
	vec3 specular;
};

in vec3 Normal;
in vec2 TexCoords;

in vec3 fragPos;

uniform vec3 viewPos;

uniform Material material;
uniform vec4 ambientColor;

uniform DirectLight directLight;
uniform PointLight pointLight[POINTLIGHTS_MAX];
uniform SpotLight spotLight[SPOTLIGHTS_MAX];

out vec4 color;

vec3 calculateDirectionLight(DirectLight directLight, vec3 norm, vec3 FragPos, vec3 viewDir){
	vec3 lightDir = normalize(-directLight.direction);

	vec3 diffuseLight = max(dot(norm, lightDir),0) * directLight.diffuse;
	vec3 diffuse = diffuseLight * vec3(texture(material.Albedo, TexCoords));

	vec3 reflectDir = reflect(-lightDir, norm);
	float specularPower = pow(max(dot(viewDir,reflectDir), 0), material.shininess);
	vec3 specular = directLight.specular * specularPower * vec3(texture(material.Specular, TexCoords));

	return diffuse + specular;
}

vec3 calculatePointLight(PointLight pointLight, vec3 norm, vec3 FragPos, vec3 viewDir){
	vec3 lightDir = pointLight.position - FragPos;
	float distance = length(lightDir);
	float attenuation = 1/(1 + pointLight.linear * distance + 
		pointLight.quadratic * pointLight.quadratic * distance);
	lightDir = normalize(lightDir);

	vec3 diffuseLight = max(dot(norm, lightDir),0) * pointLight.diffuse;
	vec3 diffuse = diffuseLight * vec3(texture(material.Albedo, TexCoords));

	vec3 reflectDir = reflect(-lightDir, norm);
	float specularPower = pow(max(dot(viewDir,reflectDir), 0), material.shininess);
	vec3 specular = pointLight.specular * specularPower * vec3(texture(material.Specular, TexCoords));

	return (diffuse + specular)*attenuation;
}

vec3 calculateSpotLight(SpotLight spotLight, vec3 norm, vec3 FragPos, vec3 viewDir){
	vec3 lightDir = spotLight.position - FragPos;
	float distance = length(lightDir);
	float attenuation = 1/(1 + spotLight.linear * distance + 
		spotLight.quadratic * spotLight.quadratic * distance);
	lightDir = normalize(lightDir);

	vec3 diffuseLight = max(dot(norm, lightDir),0) * spotLight.diffuse;
	vec3 diffuse = diffuseLight * vec3(texture(material.Albedo, TexCoords));

	vec3 reflectDir = reflect(-lightDir, norm);
	float specularPower = pow(max(dot(viewDir,reflectDir), 0), material.shininess);
	vec3 specular = spotLight.specular * specularPower * vec3(texture(material.Specular, TexCoords));

	return (diffuse + specular)*attenuation;
}

void main(){

	if (texture(material.Albedo, TexCoords).a < 0.05){
		discard;
	}

	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - fragPos);

	vec3 ambientLight = ambientColor.a * vec3(ambientColor);
	vec3 ambient = ambientLight  * vec3(texture(material.Albedo, TexCoords));

	//vec3 diffuse = vec3(0,0,0) * vec3(texture(material.Albedo, TexCoords));
	//vec3 specular = vec3(0,0,0) * vec3(texture(material.SpecularMap, TexCoords));

	vec3 resultColor = ambient;
	resultColor += calculateDirectionLight(directLight, normal, fragPos, viewDir);
	for (int i = 0; i < POINTLIGHTS_MAX; i++){
		resultColor += calculatePointLight(pointLight[i], normal, fragPos, viewDir);
	}
	for (int i = 0; i < SPOTLIGHTS_MAX; i++){
		resultColor += calculateSpotLight(spotLight[i], normal, fragPos, viewDir);
	}

	color = vec4(resultColor, 1.f);

}