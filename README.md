### Telm Engine Real
3D Game Engine
Author: Telm Francesc Serra Malagrava

For our first assignment, we aim to deliver a simple geometry viewer supporting drag and drop and orbital
camera. 

![alt tex](https://github.com/telmiuse/1Assigment/blob/main/EngineReal/giT.PNG)

Models: BakerHouse.fbx , Fox.fbx , Totoro.fbx


### Instructions:
1.	 The engine start with the BakerHouse Module
2.	 Inside the Folder "Modules" u can choose one of them, same for textures in the folder "Textures"
3.	 Drag&Drop its allowed

### Key Inputs
-	Window Control
	· Quit Application - Hit Escape Keyboard Key, "X" on Window LeftMouseCLick
	· Resize Window Drag & Drop Sides of Application Window.
	· Set Fullsize "FULLSIZE" on Window LEft Mouse Click

 Camera Controls 
    - Move Camera Front/Back/Left/Right/Up/Down with W/S/A/D/Q/E Keyboard Keys correspondingly, ONLY when Right Mouse Click.

    - Rotate Camera 
    
      1. Around Camera's Axis (X, Y) Move Mouse (Left/Right, Up/Down) accordingly , ONLY when Right Mouse Click.

      2. Around Model's Axis (X, Y) Move Mouse (Left/Right, Up/Down) accordingly, ONLY when Left Mouse Click & Left ALT Keyboard Key.
 

   - Zoom Camera In/Out Mouse Scroll Button Up/Down

- Model Controls
   - Drop fbx Model Drag & Drop Model within Application Window.

   - Drop png Texture Drag & Drop Texture within Application Window.

#### IMGUI Inputs
- All windows contains "Close Me" Button option to close.
 
- Main Menu

   - Visit Github Page of Documentation - "GitHube" Option.

   - Quit Application - Hit Quit Option.

- Tools

   - Properties 

     - Texture - Select texture for uploaded model, Checkers.png texture available.

   - Configuration Window

     - Modules - Window - Set Fullsize - Hit Checkbox.

     - Modules - Camera - Render Grid Checkbox. 

     - Modules - Camera - Render Axis on Loaded Model Checkbox.

     - Modules - Camera - Adjust Position/Up-Front Vectors Sliders.

     - Modules - Camera - Adjust FOV Slider.

### IMGUI Info:

- Main Menu

   - Demo Window - Shows Demo Window of IMGUI library.

   - About Window - Show About info regarding the Application Game Engine.

   - About Window - Show Config/Build Info Checkbox, displays System/Software Configuration settings and Frame Rate.

- Tools

   - Console Window - Shows Application Logs

   - Properties - Model Transformation Info

   - Properties - Model Geometry Info

   - Properties - Model current Texture Info
   
   - Configuration Window - Window/Camera/Input/Renderer Application information.

   - Configuration Window - Libraries Information.


### Prerequisities

- Install [Assimp Library](https://github.com/assimp/assimp/releases/tag/v3.3.1/)

- Install [DevIL-Windows-SDK-1.8.0 Library](http://openil.sourceforge.net/download.php)

- Install [glew-2.1.0-win32 Library](http://glew.sourceforge.net/)

- Install [SDL2 Library](https://www.libsdl.org/download-2.0.php)

- Install [SDL2_image Library](https://www.libsdl.org/projects/SDL_image/)

- Install [MathGeoLib Library](https://github.com/juj/MathGeoLib)

- Install [ImGui-master Library](https://github.com/ocornut/imgui)

### Build with

- Windows SDK VS version 10.0.17763.0

- Visual Studio 2017 v141
