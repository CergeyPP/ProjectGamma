#version 450 core
#define I 1
#define LIGHTS_MAX 100
#define DIRECTIONAL_LIGHT_TYPE 0
#define POINT_LIGHT_TYPE 1
#define SPOT_LIGHT_TYPE 2

struct Material{
	sampler2D Albedo;
	sampler2D Specular;
	float shininess;
};

struct Light{
	int type;
	float cutoff;
	float linear;
	float quadratic;
	vec4 position;
	vec4 direction;
	vec4 diffuse;
	vec4 specular;
	

};

layout (std140, binding = 1) uniform LightBlock
{
	int lightCount;
	Light light[LIGHTS_MAX];
};

in vec3 Normal;
in vec2 TexCoords;

in vec3 fragPos;

uniform vec3 viewPos;

uniform Material material;
uniform vec4 ambientColor;

out vec4 color;

vec3 calculateDirectionLight(Light directLight, vec3 norm, vec3 FragPos, vec3 viewDir){
	vec3 lightDir = normalize(vec3(-directLight.direction));

	vec3 diffuseLight = max(dot(norm, lightDir),0) * vec3(directLight.diffuse) * directLight.diffuse.a;
	vec3 diffuse = diffuseLight * vec3(texture(material.Albedo, TexCoords));

	vec3 reflectDir = reflect(-lightDir, norm);
	float specularPower = pow(max(dot(viewDir,reflectDir), 0), material.shininess);
	vec3 specular = vec3(directLight.specular) * specularPower * vec3(texture(material.Specular, TexCoords)) * directLight.specular.a;

	return diffuse + specular;
}

vec3 calculatePointLight(Light pointLight, vec3 norm, vec3 FragPos, vec3 viewDir){
	vec3 lightDir = vec3(pointLight.position) - FragPos;
	float distance = length(lightDir) * I;
	float attenuation = I/(1 + pointLight.linear * distance + 
		pointLight.quadratic * pointLight.quadratic * distance);
	lightDir = normalize(lightDir);

	vec3 diffuseLight = max(dot(norm, lightDir),0) * vec3(pointLight.diffuse) * pointLight.diffuse.a;
	vec3 diffuse = diffuseLight * vec3(texture(material.Albedo, TexCoords));

	vec3 reflectDir = reflect(-lightDir, norm);
	float specularPower = pow(max(dot(viewDir,reflectDir), 0), material.shininess);
	vec3 specular = vec3(pointLight.specular) * specularPower * vec3(texture(material.Specular, TexCoords)) * pointLight.specular.a;

	return (diffuse + specular)*attenuation;


}

vec3 calculateSpotLight(Light spotLight, vec3 norm, vec3 FragPos, vec3 viewDir){

	vec3 lightDir = vec3(spotLight.position) - FragPos;
	float distance = length(lightDir) * I;
	float attenuation = I/(1 + spotLight.linear * distance + 
		spotLight.quadratic * spotLight.quadratic * distance);
	lightDir = normalize(lightDir);


	float theta = dot(lightDir, normalize(vec3(-spotLight.direction)));
	float epsilon = 0.1;
	float intensivity = clamp((theta - spotLight.cutoff) / epsilon, 0.0, 1.0);

	vec3 diffuseLight = max(dot(norm, lightDir),0) * vec3(spotLight.diffuse) * spotLight.diffuse.a;
	vec3 diffuse = diffuseLight * vec3(texture(material.Albedo, TexCoords));

	vec3 reflectDir = reflect(-lightDir, norm);
	float specularPower = pow(max(dot(viewDir,reflectDir), 0), material.shininess);
	vec3 specular = vec3(spotLight.specular) * specularPower * vec3(texture(material.Specular, TexCoords)) * spotLight.specular.a;

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
	for (int i = 0; i < lightCount; i++){
		switch(light[i].type){
			case DIRECTIONAL_LIGHT_TYPE:
				resultColor += calculateDirectionLight(light[i], normal, fragPos, viewDir);
			break;
			case POINT_LIGHT_TYPE:
				resultColor += calculatePointLight(light[i], normal, fragPos, viewDir);
			break;
			case SPOT_LIGHT_TYPE:
				resultColor += calculateDirectionLight(light[i], normal, fragPos, viewDir);
			break;
		}
	}

	color = vec4(resultColor, 1.f);
}