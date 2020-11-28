#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib/Geometry/Frustum.h"
#include "MathGeoLib/Math/float3.h"


#define DEGTORAD(angleDegrees) ((angleDegrees) * M_PI / 180.0)


struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleCamera : public Module
{
public:
	float Speed = 0.2f;


public:
	ModuleCamera();
	~ModuleCamera();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	float4x4 proj;
	float4x4 model;
	float4x4 view;
	float3 camera_position;
	Frustum frustum;
	const float4x4 GetView() {
		return frustum.ViewMatrix();
	};


	const float4x4 GetProjection() {
		return frustum.ProjectionMatrix();
	};
	void WindowResized(unsigned width, unsigned height);
	void ModuleCamera::Rotate(const float3x3 rotation_matrix);
	void MoveForward();
	void MoveRight();
	void RotateArrows();
	void MouseRotate();
	void Focus();
	void SetFOV(float fov);
	void SetAspectRatio( float radio );
	void RecalculateRot(float3& vec);
	void RotateCam(const float xAxis, const float yAxis);
	void OrbitCam(const float xAxis, const float yAxis);
	float4x4 LookAt(float3, float3, float3);


protected:
	//Frustum frustum;
	float movement_speed;
	float turn_speed;
	float pitch_angle;
	//float3 camera_position;
	double NOW;
	double LAST;
	double deltaTime;

};
