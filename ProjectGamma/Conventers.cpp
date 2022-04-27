#include "Converters.h"
#include <glm/gtc/type_ptr.hpp>
using namespace physx;


PxVec3 glmVec3ToPhysXVec3(const glm::vec3& vec3)
{
    return PxVec3(vec3.x, vec3.y, vec3.z);
}
PxExtendedVec3 glmVec3ToPhysXExtendedVec3(const glm::vec3& vec3)
{
    return PxExtendedVec3(vec3.x, vec3.y, vec3.z);
}
/** Convert glm::quat to Physx::PxQuat
 @param[in] quat The glm::quat
 @return Converted Physx::PxQuat */
PxQuat glmQuatToPhysXQuat(const glm::quat& quat)
{
    return PxQuat(quat.x, quat.y, quat.z, quat.w);
}
/** Convert Physx::PxVec3 to glm::vec3
 @param[in] vec3 The Physx::PxVec3
 @return Converted glm::vec3 */
glm::vec3 PhysXVec3ToglmVec3(const PxVec3& vec3)
{
    return glm::vec3(vec3.x, vec3.y, vec3.z);
}
glm::vec3 PhysXExtendedVec3ToglmVec3(const PxExtendedVec3& vec3)
{
    return glm::vec3(vec3.x, vec3.y, vec3.z);
}
/** Convert Physx::PxQuat to glm::quat
 @param[in] quat The Physx::PxQuat
 @return Converted glm::quat */
glm::quat PhysXQuatToglmQuat(const PxQuat& quat)
{
    return glm::quat(quat.w, quat.x, quat.y, quat.z);
}

/** Convert glm::mat4 to PhysX::PxMat44
 @param[in] mat4 The glm::mat4
 @return Converted PhysX::PxMat44 */
PxMat44 glmMat4ToPhysxMat4(const glm::mat4& mat4)
{
    PxMat44 newMat;

    newMat[0][0] = mat4[0][0];
    newMat[0][1] = mat4[0][1];
    newMat[0][2] = mat4[0][2];
    newMat[0][3] = mat4[0][3];

    newMat[1][0] = mat4[1][0];
    newMat[1][1] = mat4[1][1];
    newMat[1][2] = mat4[1][2];
    newMat[1][3] = mat4[1][3];

    newMat[2][0] = mat4[2][0];
    newMat[2][1] = mat4[2][1];
    newMat[2][2] = mat4[2][2];
    newMat[2][3] = mat4[2][3];

    newMat[3][0] = mat4[3][0];
    newMat[3][1] = mat4[3][1];
    newMat[3][2] = mat4[3][2];
    newMat[3][3] = mat4[3][3];


    return newMat;
}

/** Convert PhysX::PxMat44 to glm::mat4
 @param[in] mat4 The PhysX::PxMat44
 @param[ou] Converted glm::mat4
 */
glm::mat4 PhysXMat4ToglmMat4(const PxMat44& mat4)
{
    return glm::mat4(glm::make_mat4((float*)&mat4));

}