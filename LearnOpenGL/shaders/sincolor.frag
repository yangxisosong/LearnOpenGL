//设置渐变色
#version 330 core
uniform vec4 ourColor; // 在OpenGL程序代码中设定这个变量
out vec4 color;

void main()
{
    color = ourColor;
}