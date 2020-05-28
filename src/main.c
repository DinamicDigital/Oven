#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

int main(int argc, char* argv[])
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Oven");


    Camera3D camera = {0};
    camera.position	= (Vector3){10.0f, 10.0f, 10.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.type = CAMERA_PERSPECTIVE;
    Vector3 cam_forward = {0.0f, 0.0f, -1.0f};

    Vector3 cube_pos = {0.0f, 0.0f, 0.0f};

    // TODO: Implement our own editor style camera, as this one is weird.
    SetCameraMode(camera, CAMERA_FREE);

    SetTargetFPS(60);


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
    	
    	UpdateCamera(&camera);
		
    	
        BeginDrawing();

            ClearBackground(DARKGRAY);
            
			BeginMode3D(camera);

	            DrawCube(cube_pos, 2.0f, 2.0f, 2.0f, RED);
	            DrawCubeWires(cube_pos, 2.0f, 2.0f, 2.0f, MAROON);

	            DrawGrid(100, 1.0f);
	        EndMode3D();
            	
        EndDrawing();
    }
    
    CloseWindow();

	return 0;
}