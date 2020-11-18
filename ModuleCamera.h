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
	void WindowResized(unsigned width, unsigned height);
	void ModuleCamera::Rotate(const float3x3 rotation_matrix);
	void MoveForward();
	void MoveRight();
	void Rotate();
	void MouseRotate();

protected:
	Frustum frustum;
	float movement_speed;
	float turn_speed;
	float pitch_angle;
	float3 camera_position;

};
