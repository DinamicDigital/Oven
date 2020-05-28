#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

typedef struct {
	Vector3 position;
	Vector3 scale;
	Vector3 rotation;
} Entity;

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

    Entity first_cube = (Entity) { 
    	(Vector3){0},
    	(Vector3){2.0f, 2.0f, 2.0f},
    	(Vector3){0}
    };
    // TODO: Handle multiple objects!
	bool collision = false;

	Model m_x_arrow = LoadModel("res/Arrow.obj");
	Entity x_arrow = (Entity) {
		(Vector3){1.0f, 0, 0},
		(Vector3){1.0f, 1.0f, 1.0f},
		(Vector3){0.0f, 0, 0}
	};
	Model m_y_arrow = LoadModel("res/Arrow.obj");
	Entity y_arrow = (Entity) {
		(Vector3){0, 1.0f, 0},
		(Vector3){1.0f, 1.0f, 1.0f},
		(Vector3){0, 0, -90.0f}
	};
    
    Model m_z_arrow = LoadModel("res/Arrow.obj");
	Entity z_arrow = (Entity) {
		(Vector3){0, 0, 1.0f},
		(Vector3){1.0f, 1.0f, 1.0f},
		(Vector3){0, 90.0f, 0}
	};
    
    
    Ray mouse_picker_ray = {0};

    

    // TODO: Implement our own editor style camera, as this one is weird.
    SetCameraMode(camera, CAMERA_FREE);

    SetTargetFPS(60);


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
    	
    	UpdateCamera(&camera);

    	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    	{
    		if (!collision)
    		{
    			mouse_picker_ray = GetMouseRay(GetMousePosition(), camera);
    			collision = CheckCollisionRayBox(mouse_picker_ray,
											(BoundingBox){
												(Vector3){ first_cube.position.x - first_cube.scale.x/2, first_cube.position.y - first_cube.scale.y/2, first_cube.position.z - first_cube.scale.z/2 },
                                        		(Vector3){ first_cube.position.x + first_cube.scale.x/2, first_cube.position.y + first_cube.scale.y/2, first_cube.position.z + first_cube.scale.z/2 }
                                        	});
    		}
    		else collision = false;
    	}

    	

    	Matrix tmp = MatrixIdentity();

    	tmp = MatrixMultiply(tmp, MatrixRotateX(DEG2RAD * x_arrow.rotation.x));
    	tmp = MatrixMultiply(tmp, MatrixRotateY(DEG2RAD * x_arrow.rotation.y));
    	tmp = MatrixMultiply(tmp, MatrixRotateZ(DEG2RAD * x_arrow.rotation.z));
    	
    	m_x_arrow.transform = tmp;

    	tmp = MatrixIdentity();

    	tmp = MatrixMultiply(tmp, MatrixRotateX(DEG2RAD * y_arrow.rotation.x));
    	tmp = MatrixMultiply(tmp, MatrixRotateY(DEG2RAD * y_arrow.rotation.y));
    	tmp = MatrixMultiply(tmp, MatrixRotateZ(DEG2RAD * y_arrow.rotation.z));
    	
    	m_y_arrow.transform = tmp;


    	tmp = MatrixIdentity();

    	tmp = MatrixMultiply(tmp, MatrixRotateX(DEG2RAD * z_arrow.rotation.x));
    	tmp = MatrixMultiply(tmp, MatrixRotateY(DEG2RAD * z_arrow.rotation.y));
    	tmp = MatrixMultiply(tmp, MatrixRotateZ(DEG2RAD * z_arrow.rotation.z));
    	
    	m_z_arrow.transform = tmp;


        BeginDrawing();

            ClearBackground(DARKGRAY);
            
			BeginMode3D(camera);

				if (collision)
				{
					DrawCubeV(first_cube.position, first_cube.scale, RED);
	            	DrawCubeWiresV(first_cube.position, first_cube.scale, MAROON);

	            	DrawCubeWires(first_cube.position, first_cube.scale.x + 0.2f, first_cube.scale.y + 0.2f, first_cube.scale.z + 0.2f, GREEN);
				}
				else
				{
					DrawCubeV(first_cube.position, first_cube.scale, RED);
	            	DrawCubeWiresV(first_cube.position, first_cube.scale, MAROON);
				}

				DrawModel(m_x_arrow, x_arrow.position, 0.2f, RED);
				DrawModel(m_y_arrow, y_arrow.position, 0.2f, GREEN);
				DrawModel(m_z_arrow, z_arrow.position, 0.2f, BLUE);




	            DrawGrid(100, 1.0f);
	        EndMode3D();
            	
        EndDrawing();
    }
    
    CloseWindow();

	return 0;
}