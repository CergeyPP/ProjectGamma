#pragma once
#include "Component.h"

enum class LightType : int32_t {
    DIRECTIONAL_LIGHT,
    POINT_LIGHT,
    SPOT_LIGHT,

    LIGHTTYPE_COUNT,
};

struct Light {
    LightType type;
    float cutoff;
    float linear;
    float quadratic;
    glm::vec4 position;
    glm::vec4 direction;
    glm::vec4 diffuse;
    glm::vec4 specular;
};

class LightComponent :
    public Component
{
public:

    Light light;

    void setDistance(float distance);
    float getDistance(float distance);

private:

    LightComponent(GameObject* root);
    ~LightComponent();
    
    friend GameObject;
};
