#include "Module.h"
#include "SDL.h"
#include "GL/glew.h"
#include "MathGeoLib/MathGeoLib.h"

class ModuleExTriangle : public Module
{
public:
	ModuleExTriangle();
	~ModuleExTriangle();
	bool Init();
	void DrawMesh(Mesh mesh);
	void SetUpMesh(Mesh mesh);
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	unsigned vtx_shader;
	unsigned frg_shader;

private:
	GLuint vbo, vao, ebo;
};


