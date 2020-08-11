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

//窗口大小变化回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// 按键回调函数
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

std::string string_To_UTF8(const std::string& str);
// settings
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

//顶点着色器
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 color;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   ourColor = color;\n"
"}\0";
//片元着色器
const char* fragmentShaderSource = "#version 330 core\n"
"in vec3 ourColor;\n"
"out vec4 FragColor;\n"
//"uniform vec4 ourColor; // 在OpenGL程序代码中设定这个变量\n"
"void main()\n"
"{\n"
//"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"   FragColor = vec4(ourColor,1.0f);\n"
"}\n\0";


int main(int argc, char* argv[])
{
    //初始化窗口
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //创建窗口（设置窗口大小）
    std::string title = string_To_UTF8("LearnOpenGL测试");
    GLFWwindow* window = glfwCreateWindow(800, 600, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

	// 设置按键回调函数
	glfwSetKeyCallback(window, key_callback);
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);
    ////初始化GLAD
    //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //{
    //    std::cout << "Failed to initialize GLAD" << std::endl;
    //    return -1;
    //}

    // 编译并编译我们的着色器程序
    // ------------------------------------

	// Build and compile our shader program
	Shader ourShader("./shaders/sincolor.vs", "./shaders/sincolor.frag");


    // 设置顶点数据（和缓冲区）并配置顶点属性
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
		 // 位置              // 颜色
	    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
	    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
	     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
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
    //首先绑定顶点数组对象，然后绑定并设置顶点缓冲区，然后配置顶点属性。
    glBindVertexArray(VAO);
    //0. 复制顶点数组到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verangle), verangle, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesangle), indicesangle, GL_STATIC_DRAW);
    /*
    * glVertexAttribPointer 参数说明
    *1.第一个参数指定我们要配置的顶点属性。还记得我们在顶点着色器中使用layout(location = 0)定义了position顶点属性的位置值(Location)吗？它可以把顶点属性的位置值设置为0。
    *因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入0。
    *2.第二个参数指定顶点属性的大小。顶点属性是一个vec3，它由3个值组成，所以大小是3。
    *3.第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中vec*都是由浮点数值组成的)。
    *4.第四个参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是-1）到1之间。我们把它设置为GL_FALSE。
    *5.第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。由于下个组位置数据在3个float之后，
    *我们把步长设置为3 * sizeof(float)。要注意的是由于我们知道这个数组是紧密排列的（在两个顶点属性之间没有空隙）我们也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）。
    *一旦我们有更多的顶点属性，我们就必须更小心地定义每个顶点属性之间的间隔，我们在后面会看到更多的例子（译注: 这个参数的意思简单说就是从这个属性第二次出现的地方到整个数组0位置之间有多少字节）。
    *6.最后一个参数的类型是void*，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，所以这里是0。我们会在后面详细解释这个参数。
    */
    // 位置属性
    // 1. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
    // 请注意，这是允许的，对glVertexAttribPointer的调用将VBO注册为顶点属性的绑定顶点缓冲区对象，因此之后我们可以安全地解除绑定
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // 切记：当VAO处于活动状态时，请勿取消绑定EBO，因为绑定元素缓冲区对象存储在VAO中； 保持EBO约束.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // 您可以取消绑定VAO，这样其他VAO调用就不会意外修改此VAO，但这很少发生。 
    //修改其他VAO无论如何都需要调用glBindVertexArray，因此通常在没有直接必要时，我们不会取消绑定VAO（也不绑定VBO）。
    glBindVertexArray(0);

    // 开启线框模式.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 渲染循环
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // 输入控制
        // -----
        processInput(window);

        // 渲染
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 激活着色器
        //glUseProgram(shaderProgram);
        ourShader.Use();

		// 更新uniform颜色
		GLfloat timeValue = glfwGetTime();
        auto m_pi= glm::pi<float>();
        GLfloat greenValue = (sin(timeValue));
        GLfloat redValue = (sin(timeValue + m_pi * 2 / 3));
        GLfloat blueValue = (sin(timeValue + m_pi * 4 / 3));
        //通过uniform 设置颜色
		GLint vertexColorLocation = glGetUniformLocation(ourShader.Program, "ourColor");
		glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);
        // 绘制三角形
        // 2. 当我们渲染一个物体时要使用着色器程序
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: 交换缓冲区和轮询IO事件（按下/释放键，移动鼠标等）
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // optional: 一旦资源用完了，就取消所有资源的分配:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    //glDeleteProgram(shaderProgram);

    // glfw: 终止，清除所有先前分配的GLFW资源
    // ----------------------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// 处理所有输入：查询GLFW是否在此帧中按下/释放了相关的按键并做出相应的反应
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw：只要窗口大小更改（通过操作系统或用户调整大小），此回调函数就会执行
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // 确保视口与新窗口尺寸匹配； 请注意，宽度和高度将大大大于视网膜显示屏上指定的宽度和高度。
    glViewport(0, 0, width, height);
}
// string 转换为 UTF-8 编码
// ---------------------------------------------------------------------------------------------
std::string string_To_UTF8(const std::string& str)
{
    int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

    wchar_t* pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
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
//按键加测 exc退出程序
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}