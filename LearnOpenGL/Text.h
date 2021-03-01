#pragma once
#include "Shader.h"
#include <windows.h> 

struct Character {
	GLuint     TextureID;  // 字形纹理ID
	glm::ivec2 Size;       // 字形大大小
	glm::ivec2 Bearing;    // 字形基于基线和起点的位置
	GLuint     Advance;    // 起点到下一个字形起点的距离
};

class Text
{
public:
	Text();
	~Text();

private:
	GLuint VAO, VBO;
	std::map<GLchar, Character> Characters;
public:
	void RenderText(Shader& s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
};

Text::Text()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Text::~Text()
{
}

void Text::RenderText(Shader& s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	// 激活合适的渲染状态
	s.Use();
	glUniform3f(glGetUniformLocation(s.Program, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// 对文本中的所有字符迭代
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// 当前字符的VBO
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// 在方块上绘制字形纹理
		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		// 更新当前字符的VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// 绘制方块
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// 更新位置到下一个字形的原点，注意单位是1/64像素
		x += (ch.Advance >> 6) * scale; //(2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
