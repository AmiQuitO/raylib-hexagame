#include "main.h"

int main() {
	InitWindow(800, 600, "Window");
	SetWindowState(FLAG_VSYNC_HINT);
	SetTargetFPS(60);

	World.GenerateMap();

	Camera2D camera;
	camera.target = { 0, 0 };
	//camera.target = {(float)GetScreenHeight() / 2, (float)GetScreenWidth() / 2};
	camera.offset = {0, 0};
	camera.rotation = 0;
    camera.zoom = 1.0f;

	while (!WindowShouldClose()) {
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f/camera.zoom);

            camera.target = Vector2Add(camera.target, delta);
        }

        // Zoom based on mouse wheel
        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            // Get the world point that is under the mouse
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
            
            // Set the offset to where the mouse is
            camera.offset = GetMousePosition();

            // Set the target to match, so that the camera maps the world space point 
            // under the cursor to the screen space point under the cursor at any zoom
            camera.target = mouseWorldPos;

            // Zoom increment
            const float zoomIncrement = 0.125f;

            camera.zoom += (wheel*zoomIncrement);
            if (camera.zoom < zoomIncrement) camera.zoom = zoomIncrement;
        }
		
		BeginDrawing();
			ClearBackground(BLACK);
			BeginMode2D(camera);
				World.DrawMap();	
			EndMode2D();
			DrawFPS(0, 0);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}