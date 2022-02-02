#include "FreeCameraComponent.h"
#include "../../../Window/WindowInterface.h"
#include "../../TransformationComponent//TransformationComponent.h"
#include <GLFW/glfw3.h>
#include "../../../ServiceLocator/ServiceLocator.h"

void CFreeCameraComponent::Update(float DeltaTime)
{
	CCameraComponent::Update(DeltaTime);

	assert(ParentTransformationComponent != nullptr);
	glm::vec3 CameraRight = GetCameraRight();

	if (CameraControlInput.MoveForwardKey != -1 &&  WindowInterface->IsKeyPressed(CameraControlInput.MoveForwardKey))
	{
		ParentTransformationComponent->Translate(CameraControlInput.CameraMoveSpeed * CameraForward * DeltaTime);
	}
	if (CameraControlInput.MoveBackwardKey != -1 && WindowInterface->IsKeyPressed(CameraControlInput.MoveBackwardKey))
	{
		ParentTransformationComponent->Translate(-CameraControlInput.CameraMoveSpeed * CameraForward * DeltaTime);
	}
	if (CameraControlInput.MoveLeftKey != -1 && WindowInterface->IsKeyPressed(CameraControlInput.MoveLeftKey))
	{
		ParentTransformationComponent->Translate(-CameraControlInput.CameraMoveSpeed * CameraRight * DeltaTime);
	}
	if (CameraControlInput.MoveRightKey != -1 && WindowInterface->IsKeyPressed(CameraControlInput.MoveRightKey))
	{
		ParentTransformationComponent->Translate(CameraControlInput.CameraMoveSpeed * CameraRight * DeltaTime);
	}
	if (CameraControlInput.MoveUpKey != -1 && WindowInterface->IsKeyPressed(CameraControlInput.MoveUpKey))
	{
		ParentTransformationComponent->Translate(CameraControlInput.CameraMoveSpeed * CameraUp * DeltaTime);
	}
	if (CameraControlInput.MoveDownKey != -1 && WindowInterface->IsKeyPressed(CameraControlInput.MoveDownKey))
	{
		ParentTransformationComponent->Translate(-CameraControlInput.CameraMoveSpeed * CameraUp * DeltaTime);
	}

	IWindowInterface::FMousePosition CurrentMousePosition = WindowInterface->GetMousePosition();
	float xOffset = CameraControlInput.MouseSensitivity * (CurrentMousePosition.PosX - LastMouseX) * DeltaTime;
	float yOffset = CameraControlInput.MouseSensitivity * (LastMouseY - CurrentMousePosition.PosY) * DeltaTime;
	
	LastMouseX = CurrentMousePosition.PosX;
	LastMouseY = CurrentMousePosition.PosY;
	IncrementRotationEulerAngles(xOffset, yOffset);
}

void CFreeCameraComponent::Start()
{
	WindowInterface = ServiceLocator::GetWindow();
	assert(WindowInterface != nullptr);
	CCameraComponent::Start();
	IWindowInterface::FMousePosition CurrentMousePosition = WindowInterface->GetMousePosition();
	LastMouseX = CurrentMousePosition.PosX;
	LastMouseY = CurrentMousePosition.PosY;
	SetupMovementControls();
}

void CFreeCameraComponent::SetupMovementControls(FFreeCameraControlInput InCameraControl)
{
	CameraControlInput = InCameraControl;
}

void CFreeCameraComponent::SetupMovementControls()
{
	CameraControlInput.CameraMoveSpeed = 4.0f;
	CameraControlInput.MouseSensitivity = 5.0f;
	CameraControlInput.MoveBackwardKey = GLFW_KEY_S;
	CameraControlInput.MoveForwardKey = GLFW_KEY_W;
	CameraControlInput.MoveDownKey = GLFW_KEY_Q;
	CameraControlInput.MoveUpKey = GLFW_KEY_E;
	CameraControlInput.MoveLeftKey = GLFW_KEY_A;
	CameraControlInput.MoveRightKey = GLFW_KEY_D;
}
