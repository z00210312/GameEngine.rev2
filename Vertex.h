#pragma once
#include "glew.h"
struct Vertex {
	struct Position {
		float x;
		float y;
	} position;
	struct Color {
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	} color;
	struct UV {
		float u;
		float v;
	} uv;
};
#pragma once
