#include "ModuleIMGUI.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleModel.h"
#include "ModuleCamera.h"
#include "ModuleTexture.h"
#include "ModuleInput.h"
#include "SDL.h"
#include "GL/glew.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "./IL/il.h"
#include "Globals.h"
#include "GL/glew.h"
#include "Leaks.h"
#include <string>
#include <iostream>
#include <filesystem>


//namespace fs = std::experimental::filesystem;

ModuleIMGUI::ModuleIMGUI()
{
}

ModuleIMGUI::~ModuleIMGUI()
{
}

bool ModuleIMGUI::Init()
{
	//glewInit();
	const char* glsl_version = "#version 130";
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	//// Setup Platform/Renderer bindings
	//App->window->gl_context = SDL_GL_CreateContext(App->window->window);
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init(glsl_version);

	//// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//show_demo_window = false;

	return true;
}

update_status ModuleIMGUI::PreUpdate()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();
	return UPDATE_CONTINUE;
}

update_status ModuleIMGUI::Update()
{
	if (testWindow)
	{
		ImGui::Begin("Camera Info", &testWindow);
		ImGui::Text("Camera Position x :%.2f\t", App->Camera->camera_position.x);
		ImGui::Text("Camera Position y :%.2f\t", App->Camera->camera_position.y);
		ImGui::Text("Camera Position z :%.2f\t", App->Camera->camera_position.z);
		ImGui::Separator();
		if (ImGui::Button("Close Me"))
			testWindow = false;
		ImGui::End();
	}


	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("Main Menu"))
	{
		ImGui::MenuItem("Demo Window", NULL, &show_demo_window);
		ImGui::Separator();
		ImGui::MenuItem("Config Windows", NULL, &show_another_window);
		ImGui::MenuItem("Quit", "Alt+F4", &quit);
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Tools"))
	{
		ImGui::MenuItem("Camera constrols Window", NULL, &show_another_window);
		ImGui::MenuItem("Console Window", NULL, &console_window);
		ImGui::MenuItem("Properties", NULL, &properties_window);
		ImGui::MenuItem("Configurations Window", NULL, &config_window);
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Documentation"))
	{
		ImGui::MenuItem("GitHub", NULL, &Git);
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();

	if (quit)
	{
		return UPDATE_STOP;
	}
	if (show_demo_window)
	{
		ImGui::ShowDemoWindow(&show_demo_window);
	}

	if (Git) {
		App->RequestBrowser("https://github.com/telmiuse/1Assigment");
		Git = false;
	}
	//Show Camera controls window.
	if (show_another_window)
	{
		ImGui::Begin("Camera controls", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

		if (ImGui::TreeNode("Camera Position"))
		{
			ImGui::SliderFloat("X", &(App->Camera->frustum.pos.x), -50.0f, 50.0f);
			ImGui::SliderFloat("Y", &(App->Camera->frustum.pos.y), -50.0f, 50.0f);
			ImGui::SliderFloat("Z", &(App->Camera->frustum.pos.z), -50.0f, 50.0f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Camera Up-Front Vectors"))
		{
			ImGui::SliderFloat("Up-X", &(App->Camera->frustum.up.x), -10.0f, 10.0f);
			ImGui::SliderFloat("Up-Y", &(App->Camera->frustum.up.y), -10.0f, 10.0f);
			ImGui::SliderFloat("Up-Z", &(App->Camera->frustum.up.z), -10.0f, 10.0f);

			ImGui::SliderFloat("Front-X", &(App->Camera->frustum.front.x), -10.0f, 10.0f);
			ImGui::SliderFloat("Front-Y", &(App->Camera->frustum.front.y), -10.0f, 10.0f);
			ImGui::SliderFloat("Front-Z", &(App->Camera->frustum.front.z), -10.0f, 10.0f);
			ImGui::TreePop();
		}
		ImGui::Text("Camera near distance: %.3f", App->Camera->frustum.nearPlaneDistance);
		ImGui::Text("Camera far distance: %.3f", App->Camera->frustum.farPlaneDistance);
		float fov = App->Camera->frustum.verticalFov;
		if (ImGui::SliderFloat("Vertical FOV", &fov, 0.01f, math::pi, "%.3f", 1.0f))
		{
			App->Camera->SetFOV(fov);
		}

		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}


	if (properties_window)
	{

		ImGui::Begin("Properities", &properties_window);
		if (ImGui::TreeNode("Transformation"))
		{
			ImGui::Text("Position");
			ImGui::Text("X: %.2f\t", App->model->modelPos.x);
			ImGui::SameLine();
			ImGui::Text("Y: %.2f\t", App->model->modelPos.y);
			ImGui::SameLine();
			ImGui::Text("Z: %.2f\t", App->model->modelPos.z);

			ImGui::Text("Rotation");
			ImGui::Text("X: %.2f\t", App->model->rotation.x);
			ImGui::SameLine();
			ImGui::Text("Y: %.2f\t", App->model->rotation.y);
			ImGui::SameLine();
			ImGui::Text("Z: %.2f\t", App->model->rotation.z);

			ImGui::Text("Scale");
			ImGui::Text("X: %.2f\t", App->model->scale.x);
			ImGui::SameLine();
			ImGui::Text("Y: %.2f\t", App->model->scale.y);
			ImGui::SameLine();
			ImGui::Text("Z: %.2f\t", App->model->scale.z);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Geometry"))
		{
			ImGui::Text("Meshes Loaded: %d", App->model->meshes.size());
			ImGui::Text("LoadedModel contains:");
			ImGui::Text("Vertices: %d", App->model->numVertices);
			ImGui::Text("Indices: %d", App->model->numIndices);
			ImGui::Text("Faces/Triangles: %d", App->model->numFaces);
			ImGui::Text("Center: %d", App->model->centerPoint);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Texture"))
		{
			ImGui::Text("Current Texture Width: %d", App->texture->width);
			ImGui::Text("Current Texture Height: %d", App->texture->height);
			for (unsigned int i = 0; i < App->texture->textures_loaded.size(); i++)
			{
				ImGui::Text("Width: %d", App->texture->textures_loaded[i].width);
				ImGui::Text("Height: %d", App->texture->textures_loaded[i].height);
				if (ImGui::ImageButton((void*)(intptr_t)App->texture->textures_loaded[i].id, ImVec2(128, 128)))
				{
					App->model->UpdateTexture(App->texture->textures_loaded[i]);
				}

			}
			ImGui::TreePop();
		}

		if (ImGui::Button("Close Me"))
			properties_window = false;
		ImGui::End();
	}
	//	//show console window
	if (console_window)
	{
		ImGui::Begin("Console window", &console_window);
		ImGui::TextUnformatted(Buf.begin());
		if (ScrollToBottom)
			ImGui::SetScrollHere(1.0f);
		ScrollToBottom = false;
		ImGui::End();

	}
	if (window_info)
	{
		ImGui::Begin("Our window info", &window_info);
		ImGui::Text("Window width: %d", SDL_GetWindowSurface(App->window->window)->w);
		ImGui::Text("Window width: %d", SDL_GetWindowSurface(App->window->window)->h);
		ImGui::Checkbox("Set Full Screen", &full_screen);
		if (full_screen)
		{
			SDL_SetWindowFullscreen(App->window->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
		else
		{
			SDL_SetWindowFullscreen(App->window->window, 0);
		}
		if (ImGui::Button("Close Me"))
			window_info = false;
		ImGui::End();
	}
	if (renderer_window)
	{
		ImGui::Begin("Renderer info", &renderer_window);
		ImGui::Text("Using Glew %s\n", glewGetString(GLEW_VERSION));
		ImGui::Text("Vendor: %s\n", glGetString(GL_VENDOR));
		ImGui::Text("Renderer: %s\n", glGetString(GL_RENDERER));
		ImGui::Text("OpenGL version supported %s\n", glGetString(GL_VERSION));
		ImGui::Text("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
		if (ImGui::Button("Close Me"))
			renderer_window = false;
		ImGui::End();
	}
	if (input_window)
	{
		ImGui::Begin("Inputs info (Only Valid and Combos)", &input_window);
		ImGui::TextUnformatted(BufInput.begin());
		if (ScrollToBottom2)
			ImGui::SetScrollHere(1.0f);
		ScrollToBottom2 = false;
		if (ImGui::Button("Close Me"))
			input_window = false;
		ImGui::End();
	}

	// Show config window
	if (config_window)
	{
		ImGui::Begin("Configuration window", &config_window);
		ImGui::Separator();
		if (ImGui::TreeNode("Modules"))
		{
			ImGui::Checkbox("Window", &window_info);
			ImGui::Checkbox("Camera", &show_another_window);
			ImGui::Checkbox("Input", &input_window);
			ImGui::Checkbox("Renderer", &renderer_window);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Libraries Configuration"))
		{
			ImGui::BeginChildFrame(ImGui::GetID("libraries"), ImVec2(ImGui::GetWindowContentRegionWidth() - 45, ImGui::GetTextLineHeightWithSpacing() * 7), ImGuiWindowFlags_NoMove);
			ImGui::Text("Dear ImGui %s (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);
			ImGui::Separator();
			SDL_version compiled;
			SDL_version linked;
			SDL_VERSION(&compiled);
			SDL_GetVersion(&linked);

			ImGui::Text("SDL Compiled version: %d.%d.%d\n", compiled.major, compiled.minor, compiled.patch);
			ImGui::Text("SDL Linked version: %d.%d.%d.\n", linked.major, linked.minor, linked.patch);
			ImGui::Separator();
			const char* versionGL = (char*)(glGetString(GL_VERSION));
			ImGui::Text("Glew Version: %s", versionGL);
			ImGui::Separator();
			ImGui::Text("MathGeo Library");
			ImGui::Separator();
			ImGui::Text("DevIl Library");
			ImGui::Separator();
			ImGui::Text("Assimp Library");
			ImGui::EndChildFrame();
			ImGui::TreePop();
		}
		if (ImGui::Button("Close Me"))
			config_window = false;
		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

update_status ModuleIMGUI::PostUpdate()
{
	return UPDATE_CONTINUE;
}

void  ModuleIMGUI::AddLog(const char* fmt, ...)
{
	static va_list  ap;
	va_start(ap, fmt);
	Buf.appendfv(fmt, ap);
	va_end(ap);
	ScrollToBottom = true;
}
void  ModuleIMGUI::AddLogInput(const char* fmt, ...)
{
	static va_list  another;
	va_start(another, fmt);
	BufInput.appendfv(fmt, another);
	va_end(another);
	ScrollToBottom2 = true;
}
bool ModuleIMGUI::CleanUp()
{
	LOG("Destroying program");
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_Quit();
	//Destroy window
	return true;
}
