#pragma once
#include "Component.h"

enum class LightType : int32_t {
    DIRECTIONAL_LIGHT,
    POINT_LIGHT,
    SPOT_LIGHT,

    LIGHTTYPE_COUNT,
};

class LightComponent :
    public Component
{
public:

    LightType type;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float cutoff;

    float linear;
    float quadratic;

    void setDistance(float distance);
    float getDistance(float distance);

private:

    LightComponent(GameObject* root);
    ~LightComponent();
    
    friend GameObject;
};
