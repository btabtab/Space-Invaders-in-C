#include <stdlib.h>
#include <memory.h>
#include "raylib.h"
typedef struct Invader
{
	Vector2 position;
	int x_dir;
} Invader;
typedef Invader Projectile;
typedef struct Player
{
	Vector2 position;
	Projectile *projectile;
} Player;
int main(void)
{
	Player player = {(Vector2){150.f, 270.f}, NULL};
	int invader_count = 5;
	Invader *invaders[invader_count];
	for (int i = 0; i != invader_count; i++)
	{
		invaders[i] = malloc(sizeof(Invader));
		invaders[i]->position = (Vector2){i * 40, i + 10};
		invaders[i]->x_dir = -1.f;
	}
	InitWindow(300, 300, "C-Space Invaders - JME");
	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		for (int i = 0; i != invader_count; i++)
		{
			if(invaders[i] != NULL)
			{
				if (invaders[i]->position.x > 290.f && invaders[i]->x_dir == +1)
				{invaders[i]->position.y += 30.f;invaders[i]->x_dir = (-1);}
				if (invaders[i]->position.x < 10.f && invaders[i]->x_dir == -1)
				{invaders[i]->position.y += 30.f;invaders[i]->x_dir = (+1);}
				invaders[i]->position.x += invaders[i]->x_dir;
				DrawCircle(invaders[i]->position.x, invaders[i]->position.y, i / 2 + 10, GRAY);
				if (CheckCollisionCircles(player.position, 15.f, invaders[i]->position, 10.f)){exit(0);}
				if(player.projectile != NULL)
				{
					player.projectile->position.y -= 0.5f;
					DrawCircle(player.projectile->position.x, player.projectile->position.y, 4, WHITE);
					if (CheckCollisionCircles(player.projectile->position, 4, invaders[i]->position, 10.f))
					{
						free(player.projectile); player.projectile = NULL;
						free(invaders[i]); invaders[i] = NULL;
					}
				}
			}
		}
		//printf("\nloop restart\n");
		if(player.projectile != NULL)
		{if(player.projectile->position.y < 0){free(player.projectile); player.projectile = NULL;}}
		DrawCircle(player.position.x, player.position.y, 15.f, RED);
		BeginDrawing();
		ClearBackground(DARKBLUE);
		DrawGrid(1000, 10.f);
		EndDrawing();
		if (IsKeyPressed(KEY_SPACE) && player.projectile != NULL){free(player.projectile); player.projectile = malloc(sizeof(Projectile)); player.projectile->position = player.position;}
		if (IsKeyPressed(KEY_SPACE) && player.projectile == NULL){player.projectile = malloc(sizeof(Projectile)); player.projectile->position = player.position;}
		if (IsKeyDown(KEY_A)){player.position.x += -10.f;}
		if (IsKeyDown(KEY_D)){player.position.x += +10.f;}
	}
	CloseWindow(); // Close window and OpenGL context
	return 0;
}