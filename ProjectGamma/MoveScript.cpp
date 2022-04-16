#include "MoveScript.h"
#include "InputComponent.h"

void MoveScript::Update(float deltaTime)
{
	if (moveVector != glm::vec2(0)) {
		glm::mat4 transMatrix = getRoot()->getTransformMatrix();

		glm::vec3 forward = glm::vec3(transMatrix * glm::vec4(1, 0, 0, 1.f) - transMatrix * glm::vec4(0, 0, 0, 1.f));

		glm::vec3 right = glm::cross(forward, glm::vec3(0, 1, 0));

		glm::vec3 up = glm::cross(forward, -right);

		glm::vec3 finalMoveVec = forward * moveVector.x + right * moveVector.y;

		finalMoveVec = glm::normalize(finalMoveVec);

		getRoot()->translate(finalMoveVec * deltaTime * 6.f);
	}
}

MoveScript::MoveScript(GameObject* root)
	: ScriptableComponent(root)
{
	moveVector = glm::vec2(0);

	auto inputList = getRoot()->getComponent<InputComponent>();
	for (auto elem : inputList) {
		InputComponent* input = (InputComponent*)elem;
		__hook(&InputComponent::onHorizontal, input, &MoveScript::onHorizontal, this);
		__hook(&InputComponent::onVertical, input, &MoveScript::onVertical, this);
		__hook(&InputComponent::onLook, input, &MoveScript::onLook, this);
	}
}

MoveScript::~MoveScript()
{
	auto inputList = getRoot()->getComponent<InputComponent>();
	for (auto elem : inputList) {
		__unhook(&InputComponent::onHorizontal, (InputComponent*)elem, &MoveScript::onHorizontal);
		__unhook(&InputComponent::onVertical, (InputComponent*)elem, &MoveScript::onVertical);
		__unhook(&InputComponent::onLook, (InputComponent*)elem, &MoveScript::onLook);
	}
}

void MoveScript::onLook(glm::vec2& value)
{
	glm::quat qRot = getRoot()->getRot();

	float sensivity = 16.f;

	glm::vec3 euler = glm::vec3(0, -sensivity * value.x / 100.f / 180 * 3.14, -sensivity * value.y / 100.f / 180 * 3.14);
	glm::quat zRot = glm::quat(/*glm::vec3(0, euler.y, 0)) * */qRot * glm::quat(glm::vec3(0, 0, euler.z)));
	//printf("q(%f %f %f %f) = v(%f %f %f)\n", qRot.w, qRot.x, qRot.y, qRot.z, euler.x, euler.y, euler.z);
	glm::mat4 testMatrix = glm::mat4_cast(zRot);
	if (glm::vec4(testMatrix * glm::vec4(0, 1, 0, 1)).y > 0) {
		qRot = zRot;
	}
	 
	qRot = glm::quat(glm::vec3(0, euler.y, 0)) * qRot;
	/*glm::vec3 euler = glm::eulerAngles(qRot);
	euler.y += sensivity * value.x / 1280;
	std::cout << "X axis : " << euler.x << " Y axis: " << euler.y << " Z axis: " << euler.z << std::endl;
	euler.x += sensivity * value.y / 720;
	euler.z = 0;
	qRot = glm::quat(euler);*/

	getRoot()->setRot(qRot);
}

void MoveScript::onVertical(float& value)
{
	moveVector.x += value;
}

void MoveScript::onHorizontal(float& value)
{
	moveVector.y += value;
}
