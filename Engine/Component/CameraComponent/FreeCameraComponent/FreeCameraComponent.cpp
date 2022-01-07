#include "FreeCameraComponent.h"
#include "../../../Window/WindowInterface.h"
#include "../../TransformationComponent//TransformationComponent.h"
#include <GLFW/glfw3.h>

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
	assert(WindowInterface != nullptr);
	CCameraComponent::Start();
	IWindowInterface::FMousePosition CurrentMousePosition = WindowInterface->GetMousePosition();
	LastMouseX = CurrentMousePosition.PosX;
	LastMouseY = CurrentMousePosition.PosY;
}

void CFreeCameraComponent::SetupMovementControls(IWindowInterface* InWindowInterface, FFreeCameraControlInput InCameraControl)
{
	WindowInterface = InWindowInterface;
	CameraControlInput = InCameraControl;
}
