#include <windows.h>   
#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

//// GLAD
//#include <glad/glad.h>

// Other includes
#include "Shader.h"
#include <glm/gtc/constants.hpp> // glm::pi

//���ڴ�С�仯�ص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// �����ص�����
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

std::string string_To_UTF8(const std::string& str);
// settings
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

//������ɫ��
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 color;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   ourColor = color;\n"
"}\0";
//ƬԪ��ɫ��
const char* fragmentShaderSource = "#version 330 core\n"
"in vec3 ourColor;\n"
"out vec4 FragColor;\n"
//"uniform vec4 ourColor; // ��OpenGL����������趨�������\n"
"void main()\n"
"{\n"
//"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"   FragColor = vec4(ourColor,1.0f);\n"
"}\n\0";


int main(int argc, char* argv[])
{
    //��ʼ������
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //�������ڣ����ô��ڴ�С��
    std::string title = string_To_UTF8("LearnOpenGL����");
    GLFWwindow* window = glfwCreateWindow(800, 600, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

	// ���ð����ص�����
	glfwSetKeyCallback(window, key_callback);
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);
    ////��ʼ��GLAD
    //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //{
    //    std::cout << "Failed to initialize GLAD" << std::endl;
    //    return -1;
    //}

    // ���벢�������ǵ���ɫ������
    // ------------------------------------

	// Build and compile our shader program
	Shader ourShader("./shaders/sincolor.vs", "./shaders/sincolor.frag");


    // ���ö������ݣ��ͻ������������ö�������
    // ------------------------------------------------------------------
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
	float verangle[] = {
		// 0.0f,  0.5f, 0.0f,  // top right
		// 0.5f, -0.5f, 0.0f,  // bottom right
		//-0.5f, -0.5f, 0.0f,  // bottom left
		 // λ��              // ��ɫ
	    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
	    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
	     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
	};
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
	unsigned int indicesangle[] = {  // note that we start from 0!
	   0, 1, 2,  // first Triangle
	};
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    //���Ȱ󶨶����������Ȼ��󶨲����ö��㻺������Ȼ�����ö������ԡ�
    glBindVertexArray(VAO);
    //0. ���ƶ������鵽�����й�OpenGLʹ��
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verangle), verangle, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesangle), indicesangle, GL_STATIC_DRAW);
    /*
    * glVertexAttribPointer ����˵��
    *1.��һ������ָ������Ҫ���õĶ������ԡ����ǵ������ڶ�����ɫ����ʹ��layout(location = 0)������position�������Ե�λ��ֵ(Location)�������԰Ѷ������Ե�λ��ֵ����Ϊ0��
    *��Ϊ����ϣ�������ݴ��ݵ���һ�����������У������������Ǵ���0��
    *2.�ڶ�������ָ���������ԵĴ�С������������һ��vec3������3��ֵ��ɣ����Դ�С��3��
    *3.����������ָ�����ݵ����ͣ�������GL_FLOAT(GLSL��vec*�����ɸ�����ֵ��ɵ�)��
    *4.���ĸ��������������Ƿ�ϣ�����ݱ���׼��(Normalize)�������������ΪGL_TRUE���������ݶ��ᱻӳ�䵽0�������з�����signed������-1����1֮�䡣���ǰ�������ΪGL_FALSE��
    *5.�����������������(Stride)�������������������Ķ���������֮��ļ���������¸���λ��������3��float֮��
    *���ǰѲ�������Ϊ3 * sizeof(float)��Ҫע�������������֪����������ǽ������еģ���������������֮��û�п�϶������Ҳ��������Ϊ0����OpenGL�������岽���Ƕ��٣�ֻ�е���ֵ�ǽ�������ʱ�ſ��ã���
    *һ�������и���Ķ������ԣ����Ǿͱ����С�ĵض���ÿ����������֮��ļ���������ں���ῴ����������ӣ���ע: �����������˼��˵���Ǵ�������Եڶ��γ��ֵĵط�����������0λ��֮���ж����ֽڣ���
    *6.���һ��������������void*��������Ҫ���ǽ��������ֵ�ǿ������ת��������ʾλ�������ڻ�������ʼλ�õ�ƫ����(Offset)������λ������������Ŀ�ͷ������������0�����ǻ��ں�����ϸ�������������
    */
    // λ������
    // 1. ���ö�������ָ��
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
    // ��ע�⣬��������ģ���glVertexAttribPointer�ĵ��ý�VBOע��Ϊ�������Եİ󶨶��㻺�����������֮�����ǿ��԰�ȫ�ؽ����
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // �мǣ���VAO���ڻ״̬ʱ������ȡ����EBO����Ϊ��Ԫ�ػ���������洢��VAO�У� ����EBOԼ��.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // ������ȡ����VAO����������VAO���þͲ��������޸Ĵ�VAO��������ٷ����� 
    //�޸�����VAO������ζ���Ҫ����glBindVertexArray�����ͨ����û��ֱ�ӱ�Ҫʱ�����ǲ���ȡ����VAO��Ҳ����VBO����
    glBindVertexArray(0);

    // �����߿�ģʽ.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // ��Ⱦѭ��
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // �������
        // -----
        processInput(window);

        // ��Ⱦ
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ������ɫ��
        //glUseProgram(shaderProgram);
        ourShader.Use();

		// ����uniform��ɫ
		GLfloat timeValue = glfwGetTime();
        auto m_pi= glm::pi<float>();
        GLfloat greenValue = (sin(timeValue));
        GLfloat redValue = (sin(timeValue + m_pi * 2 / 3));
        GLfloat blueValue = (sin(timeValue + m_pi * 4 / 3));
        //ͨ��uniform ������ɫ
		GLint vertexColorLocation = glGetUniformLocation(ourShader.Program, "ourColor");
		glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);
        // ����������
        // 2. ��������Ⱦһ������ʱҪʹ����ɫ������
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: ��������������ѯIO�¼�������/�ͷż����ƶ����ȣ�
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // optional: һ����Դ�����ˣ���ȡ��������Դ�ķ���:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    //glDeleteProgram(shaderProgram);

    // glfw: ��ֹ�����������ǰ�����GLFW��Դ
    // ----------------------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// �����������룺��ѯGLFW�Ƿ��ڴ�֡�а���/�ͷ�����صİ�����������Ӧ�ķ�Ӧ
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw��ֻҪ���ڴ�С���ģ�ͨ������ϵͳ���û�������С�����˻ص������ͻ�ִ��
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // ȷ���ӿ����´��ڳߴ�ƥ�䣻 ��ע�⣬��Ⱥ͸߶Ƚ�����������Ĥ��ʾ����ָ���Ŀ�Ⱥ͸߶ȡ�
    glViewport(0, 0, width, height);
}
// string ת��Ϊ UTF-8 ����
// ---------------------------------------------------------------------------------------------
std::string string_To_UTF8(const std::string& str)
{
    int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

    wchar_t* pwBuf = new wchar_t[nwLen + 1];//һ��Ҫ��1����Ȼ�����β�� 
    ZeroMemory(pwBuf, nwLen * 2 + 2);

    ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

    int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

    char* pBuf = new char[nLen + 1];
    ZeroMemory(pBuf, nLen + 1);

    ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

    std::string retStr(pBuf);

    delete[]pwBuf;
    delete[]pBuf;

    pwBuf = NULL;
    pBuf = NULL;

    return retStr;
}

// Is called whenever a key is pressed/released via GLFW
//�����Ӳ� exc�˳�����
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}