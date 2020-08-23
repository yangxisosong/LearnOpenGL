#pragma once
#include <SOIL.h>
#include <GL/glew.h>
#include <string>

class TexureManage
{
public:
	TexureManage();

	GLuint LoadTexure(std::string imgpath, GLuint rgb, GLenum rgba, int param);
};

