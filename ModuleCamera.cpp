
#include "Application.h"
#include "ModuleCamera.h"
#include "ModuleWindow.h"
#include "MathGeoLib/Math/float3x3.h"
#include "ModuleInput.h"
#include <GL/glew.h>

#include <iostream>

using namespace std;

ModuleCamera::ModuleCamera()
{
	pitch_angle = 1.0f;
}

// Destructor
ModuleCamera::~ModuleCamera()
{

}

// Called before render is available
bool ModuleCamera::Init()
{

	frustum.ComputeProjectionMatrix();
	camera_position = float3(0, 1, -2);
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 200.0f);
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD(1) * 90.0f, 1.3f);
	frustum.SetPos(camera_position);
	frustum.SetFront(float3::unitZ);
	frustum.SetUp(float3::unitY);
	

	return true;
}

update_status ModuleCamera::PreUpdate()
{

	float4x4 projectionGL = frustum.ProjectionMatrix().Transposed(); //<-- Important to transpose!



	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(*(projectionGL.v));

	MoveForward();
	MoveRight();
	MouseRotate();

	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT) {
		Speed = 4.0f;
	}
	else {
		Speed = 2.0f;
	}





	frustum.SetPos(camera_position);
	float4x4 viewMatrix = frustum.ViewMatrix();
	viewMatrix.Transpose();
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(*(viewMatrix.v));
	
	return UPDATE_CONTINUE;
}

void ModuleCamera::MouseRotate() {

	if (App->input->GetMouseButtonDown(3) == KEY_REPEAT) {



		int aux = App->input->GetMouseMotion().x;
		int mousexoldNow = App->input->GetMousePosition().x;
		int mouseXnow = aux + mousexoldNow;
		if ((mousexoldNow - mouseXnow) < 0) {
			Rotate(frustum.WorldMatrix().RotatePart().RotateY(-0.05f));
		}
		if ((mousexoldNow - mouseXnow) > 0) {
			Rotate(frustum.WorldMatrix().RotatePart().RotateY(+0.05f));
		}

		int auxy = App->input->GetMouseMotion().y;
		int mouseyoldNow = App->input->GetMousePosition().y;
		int mouseynow = auxy + mouseyoldNow;
		if ((mouseyoldNow - mouseynow) > 0) {

			float radians_angle = DEGTORAD(pitch_angle);
			float3 lookAtVector = frustum.Front() * cos(radians_angle) + frustum.Up() * sin(radians_angle);
			lookAtVector.Normalize();

			float3 upVector = frustum.WorldRight().Cross(lookAtVector);
			frustum.SetFront(lookAtVector);
			frustum.SetUp(upVector);
		}
		if ((mouseyoldNow - mouseynow) < 0) {

			float radians_angle = DEGTORAD(pitch_angle);
			float3 lookAtVector = frustum.Front() * cos(-radians_angle) + frustum.Up() * sin(-radians_angle);
			lookAtVector.Normalize();

			float3 upVector = frustum.WorldRight().Cross(lookAtVector);
			frustum.SetFront(lookAtVector);
			frustum.SetUp(upVector);
		}

	}

}

void ModuleCamera::Rotate() {

	if (App->input->GetKey(SDL_SCANCODE_UP)) {
		float radians_angle = DEGTORAD(pitch_angle);
		float3 lookAtVector = frustum.Front() * cos(radians_angle) + frustum.Up() * sin(radians_angle);
		lookAtVector.Normalize();

		float3 upVector = frustum.WorldRight().Cross(lookAtVector);
		frustum.SetFront(lookAtVector);
		frustum.SetUp(upVector);
		LOG("Up");
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN)) {
		float radians_angle = DEGTORAD(pitch_angle);
		float3 lookAtVector = frustum.Front() * cos(-radians_angle) + frustum.Up() * sin(-radians_angle);
		float aux = lookAtVector.Normalize();

		float3 upVector = frustum.WorldRight().Cross(lookAtVector);
		frustum.SetFront(lookAtVector);
		frustum.SetUp(upVector);
		LOG("Down");
	}




	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		Rotate(frustum.WorldMatrix().RotatePart().RotateY(0.005f));
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		Rotate(frustum.WorldMatrix().RotatePart().RotateY(-0.005f));
	}

}

void ModuleCamera::MoveRight() {



	if (App->input->GetKey(SDL_SCANCODE_D)) {
		frustum.Translate(frustum.WorldRight() * Speed);
		camera_position = frustum.Pos();
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		frustum.Translate(frustum.WorldRight() * -Speed);
		camera_position = frustum.Pos();
	}
}

void ModuleCamera:: MoveForward() {

	if (App->input->GetScrool() == SCROOL_UP) {
		frustum.Translate(frustum.Front() * -Speed);
		camera_position = frustum.Pos();
	}
	if (App->input->GetScrool() == SCROOL_DOWN) {
		frustum.Translate(frustum.Front() * Speed);
		camera_position = frustum.Pos();
	}


	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		frustum.Translate(frustum.Front() * Speed);
		camera_position = frustum.Pos();
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		frustum.Translate(frustum.Front() * -Speed);
		camera_position = frustum.Pos();
	}


}

// Called every draw update
update_status ModuleCamera::Update()
{

	return UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate()
{



	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleCamera::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	SDL_GL_DeleteContext(App->window->window);

	return true;
}

void ModuleCamera::WindowResized(unsigned width, unsigned height)
{
}

void ModuleCamera::Rotate(const float3x3 rotation_matrix)
{
	vec oldFront = frustum.Front().Normalized();
	frustum.SetFront(rotation_matrix.MulDir(oldFront));
	vec oldUp = frustum.Up().Normalized();
	frustum.SetUp(rotation_matrix.MulDir(oldUp));

}

