/*  date = May 25th 2026 11:17 PM  */

/*  date = May 20th 2026 09:18 Vector2M  */

// #include <stdio.h>
#include <math.h>
#include "third_party/raylib/include/raylib.h"
#include "penguin.h"

#define ArrayLength(a) (sizeof((a))/sizeof((a)[0]))

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

Color BACKGROUND = {16, 16, 16, 255};


Vector2 Screen(Vector2 p)
{
	// -1..1 -> 0..2 -> 0..1 -> 0..w
	return (Vector2) {
		((p.x + 1) / 2) * SCREEN_WIDTH,
		(1-((p.y + 1) / 2)) * SCREEN_HEIGHT 
	};
}

void Point(Vector2 v)
{
	float s = 20;
	v = Screen(v);
	DrawRectangle(v.x - s/2, v.y - s/2, s, s, GREEN);
}

Vector2 Project(Vector3 v)
{
	return (Vector2) {
		v.x/v.z,
		v.y/v.z
	};
}

Vector3 TranslateZ(Vector3 v, float dz)
{
	v.z += dz;
	return v;
}

Vector3 RotateXZ(Vector3 v, float angle)
{
	Vector3 vec = v;
	vec.x = v.x * cosf(angle) - v.z * sinf(angle);
	vec.z = v.x * sinf(angle) + v.z * cosf(angle);
	return vec;
}

void Line(Vector2 a, Vector2 b)
{
	DrawLine(a.x, a.y, b.x, b.y, GREEN);
}

int main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Renderer");
	SetTargetFPS(60);
	float dz = 1;
	float angle = 0;
	for (; !WindowShouldClose() ;)
	{
		float dt = 1/60.0f;
		angle += PI*dt;	// numerically integrate angular velocity to get angle(0) + .. + angle(t-1) + angle(t)
		BeginDrawing();
		// TODO
		ClearBackground(BACKGROUND);

		// vertices
		// for (int i = 0; i < ArrayLength(vs); ++i)
		// {
		// 	Point(Project(TranslateZ(RotateXZ(vs[i], angle), 1))); 
		// }

		// faces
		for (int row = 0; row < ArrayLength(fs); ++row)
		{
			for (int col = 0; col < FS_COL; ++col)
			{
				Vector3 a = vs[fs[row][col]];
				Vector3 b = vs[fs[row][(col+1)%FS_COL]];
				Line(
					Screen(Project(TranslateZ(RotateXZ(a, angle), dz))),
					Screen(Project(TranslateZ(RotateXZ(b, angle), dz)))
					);
			}

		}

		EndDrawing();

	}

	CloseWindow();

	return 0;
}