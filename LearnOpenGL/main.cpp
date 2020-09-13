// Std. Includes
#include <string>
#include <windows.h> 

// GLEW
//#define GLEW_STATIC
//#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <glad/glad.h>

// GL includes
#include "Shader.h"
#include "Camera.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include <SOIL.h>
#include "TexureManage.h"
#include "Material.h"
#include "Light.h"
#include "LightSpot.h"
#include "Mesh.h"
#include "Model.h"
#include "testmodel.h"

// Properties
GLuint screenWidth = 800, screenHeight = 600;
// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

std::string string_To_UTF8(const std::string& str);
// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void Do_Movement();

// Camera
Camera camera;
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

//Light
ParallelLight parallelLight = ParallelLight(glm::vec3(0.2f, 0.0f, 3.0f), glm::vec3(glm::radians(90.0f), 0, 0));

PointLight pointLight = PointLight(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(glm::radians(90.0f), 0, 0));

LightSpot SpotLight = LightSpot(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(glm::radians(-45.0f), 0, 0));

#pragma region PositionDate 
// Set up vertex data (and buffer(s)) and attribute pointers
GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
glm::vec3 cubePositions[] = {
glm::vec3(0.0f,  0.0f,  0.0f),
glm::vec3(2.0f,  0.0f, -5.0f),
glm::vec3(-1.5f, -2.2f, -2.5f),
glm::vec3(-3.8f, -2.0f, -12.3f),
glm::vec3(2.4f, -0.4f, -3.5f),
glm::vec3(-1.7f,  3.0f, -7.5f),
glm::vec3(1.3f, -2.0f, -2.5f),
glm::vec3(1.5f,  2.0f, -2.5f),
glm::vec3(1.5f,  0.2f, -1.5f),
glm::vec3(-1.3f,  1.0f, -1.5f) };

GLfloat verticesbox[] = {
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f
};

GLfloat verticesnormal[] = {
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

GLfloat verticesnormalandtexure[] = {
	// Positions          // Normals           // Texture Coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

GLfloat verticesaa[] = {
	0.5f, 0.5f, 0.0f,   // 右上角
	0.5f, -0.5f, 0.0f,  // 右下角
	-0.5f, -0.5f, 0.0f, // 左下角
	-0.5f, 0.5f, 0.0f   // 左上角
};

GLuint indicesaa[] = { // 注意索引从0开始! 
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};
#pragma endregion

struct MouseDown
{
	bool Left;
	bool Middle;
	bool Right;
};

MouseDown mouseState{ false,false,false };



int main()
{
	// 初始化glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//设置glfw 能否改变窗口大小
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	std::string title = string_To_UTF8("LearnOpenGL测试");
	GLFWwindow* window = glfwCreateWindow(800, 600, title.c_str(), NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// 设置回调函数
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	// Options 是否显示鼠标指针
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// 初始化GLEW 设置OpenGL函数指针。
	/*glewExperimental = GL_TRUE;
	glewInit();*/

	// 定义视口尺寸
	glViewport(0, 0, screenWidth, screenHeight);

	// 设置一些OpenGL的选项
	//开启深度检测
	glEnable(GL_DEPTH_TEST);
	// 开启线框模式.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Mesh cube(verticesaa);
	// 加载和编译我们的着色器
	Shader ourShader("./shaders/material.vs", "./shaders/material.frag");
	Shader lightingShader("./shaders/light.vs", "./shaders/light.frag");
	Model ourModel("D:\\work\\work_code\\OpenGlsource\\backpack.obj");
	Shader positintest("./shaders/positiondefault.vs", "./shaders/positiondefault.frag");

	Material* myMaterial = new Material(&ourShader,
		glm::vec3(0.2f, 0.2f, 0.2f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		32.0f);

	vector<float> vecv(verticesaa, verticesaa + sizeof(verticesaa) / sizeof(float));
	vector<int> veci(indicesaa, indicesaa + sizeof(indicesaa) / sizeof(int));
	Mesh a(vecv, veci);

	//unsigned int VBO, VAO, EBO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	////首先绑定顶点数组对象，然后绑定并设置顶点缓冲区，然后配置顶点属性。
	//glBindVertexArray(VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verticesaa), verticesaa, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesaa), indicesaa, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//// 请注意，这是允许的，对glVertexAttribPointer的调用将VBO注册为顶点属性的绑定顶点缓冲区对象，因此之后我们可以安全地解除绑定
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//GLuint VBO, VAO, EBO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);

	//glBindVertexArray(VAO);
	////glGenBuffers(1, &EBO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verticesnormalandtexure), verticesnormalandtexure, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	//glEnableVertexAttribArray(0);
	//// normal attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);
	////texure
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(2);

	//glBindVertexArray(0); // Unbind VAO

	GLuint lightVAO, lightVBO;
	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &lightVBO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesbox), verticesbox, GL_STATIC_DRAW);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);



	// Load and create a texture 
	GLuint texture1;
	GLuint texture2;
	TexureManage texureMange;
	texture1 = texureMange.LoadTexure("./include/container2.png", GL_RGB, GL_RGB, 0);
	texture2 = texureMange.LoadTexure("./include/container2_specular.png", GL_RGB, GL_RGB, 1);

	// 渲染循环
	while (!glfwWindowShouldClose(window))
	{
		// 计算每帧时间
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// 检查和执行事件
		glfwPollEvents();
		Do_Movement();

		// 清除colorbuffer
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw our first triangle
		ourShader.Use();

		GLint viewPosLoc = glGetUniformLocation(ourShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);

		ourShader.SetUniform1f("material.shininess", myMaterial->shininess);
		ourShader.SetUniformTexure("material.diffuse", 0);
		ourShader.SetUniformTexure("material.specular", 1);


		ourShader.SetUniform3f("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		ourShader.SetUniform3f("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		ourShader.SetUniform3f("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
		ourShader.SetUniform3f("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	
		for (int i = 0; i < 4; i++) {
			std::string index = "pointLights["+std::to_string(i)+ "].";
			ourShader.SetUniform3f((index + "position").c_str(), glm::vec3(pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z));
			ourShader.SetUniform3f((index + "ambient").c_str(), glm::vec3(0.05f, 0.05f, 0.05f));
			ourShader.SetUniform3f((index + "diffuse").c_str(), glm::vec3(0.8f, 0.8f, 0.8f));
			ourShader.SetUniform3f((index + "specular").c_str(), glm::vec3(1.0f, 1.0f, 1.0f));
			ourShader.SetUniform1f((index + "constant").c_str(), 1.0f);
			ourShader.SetUniform1f((index + "linear").c_str(), 0.09f);
			ourShader.SetUniform1f((index + "quadratic").c_str(), 0.032f);
		}

		// SpotLight
		ourShader.SetUniform3f("spotLight.position", glm::vec3(camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z));
		ourShader.SetUniform3f("spotLight.direction", glm::vec3(camera.cameraFront.x, camera.cameraFront.y, camera.cameraFront.z));
		ourShader.SetUniform3f("spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		ourShader.SetUniform3f("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f)); 
		ourShader.SetUniform3f("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		ourShader.SetUniform1f("spotLight.constant", 1.0f);
		ourShader.SetUniform1f("spotLight.linear", 0.09);
		ourShader.SetUniform1f("spotLight.quadratic", 0.032);
		ourShader.SetUniform1f("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		ourShader.SetUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		// mvp 矩阵计算
		//glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");
		// Pass them to the shaders
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		
		// render container
		//glBindVertexArray(VAO);
		for (GLuint i = 0; i < 1; i++)
		{
			// Calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			/*GLfloat angle = 20.0f * i;
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));*/
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			ourModel.Draw(&ourShader);
			//cube.Draw(&ourShader);
			//glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//glBindVertexArray(0);


		lightingShader.Use();
	
		// Draw the loaded model
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// It's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//ourModel.Draw(&lightingShader);
		

		glm::mat4 lightview = camera.GetViewMatrix();
		glm::mat4 lightprojection = glm::mat4(1.0f);
		lightprojection = glm::perspective(camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		GLint LightmodelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint LightviewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint LightprojLoc = glGetUniformLocation(lightingShader.Program, "projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(LightviewLoc, 1, GL_FALSE, glm::value_ptr(lightview));
		glUniformMatrix4fv(LightprojLoc, 1, GL_FALSE, glm::value_ptr(lightprojection));

		// Draw the container (using container's vertex attributes)
		glBindVertexArray(lightVAO);
		for (GLuint i = 0; i < 4; i++)
		{
			glm::mat4 lightmodel = glm::mat4(1.0f);
			lightmodel = glm::translate(lightmodel, pointLightPositions[i]);
			lightmodel = glm::scale(lightmodel, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(lightmodel));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

	
		// Create transformations
		positintest.Use();
		glm::mat4 modelplan = glm::mat4(1.0f);
		glm::mat4 viewplan = camera.GetViewMatrix();
		glm::mat4 projectionplan = glm::mat4(1.0f);
		modelplan = glm::rotate(modelplan, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		projectionplan = glm::perspective(camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		// Get their uniform location
		GLint modelLocplan = glGetUniformLocation(positintest.Program, "model");
		GLint viewLocplan = glGetUniformLocation(positintest.Program, "view");
		GLint projLocplan = glGetUniformLocation(positintest.Program, "projection");
		// Pass them to the shaders
		glUniformMatrix4fv(modelLocplan, 1, GL_FALSE, glm::value_ptr(modelplan));
		glUniformMatrix4fv(viewLocplan, 1, GL_FALSE, glm::value_ptr(viewplan));
		// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLocplan, 1, GL_FALSE, glm::value_ptr(projectionplan));
		//a.Draw(&positintest);


		//// 绘制三角形
		//glUseProgram(positintest.Program);
		//glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	////取消分配所有资源
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &lightVBO);
	/*glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);*/
	//glDeleteProgram(shaderProgram);

	//glDeleteVertexArrays(1, &lightVAO);
	//glDeleteBuffers(1, &lightVBO);
	glfwTerminate();
	return 0;
}

//每帧检测按键
void Do_Movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
	if (keys[GLFW_KEY_Q])
		camera.ProcessKeyboard(Camera_Movement::UP, deltaTime);
	if (keys[GLFW_KEY_E])
		camera.ProcessKeyboard(Camera_Movement::DOWN, deltaTime);
}

// 按键回调函数
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
		//shift 加速移动
		if (key == 340)
		{
			camera.MovementSpeed = action ? 2.5f : 1.0f;
		}
	}
}
//鼠标按键回调函数
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		mouseState.Left = action;
		if (!action)
		{
			firstMouse = true;
		}
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		mouseState.Middle = action;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		mouseState.Right = action;
		if (!action)
		{
			firstMouse = true;
		}
		break;
	default:
		return;
	}
}
// 鼠标移动回调函数
glm::vec3 cameraPos;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (mouseState.Left)
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		GLfloat xoffset = xpos - lastX;
		GLfloat yoffset = lastY - ypos;

		lastX = xpos;
		lastY = ypos;

		camera.ProcessMouseMovement(xoffset, yoffset);
	}
	else if (mouseState.Right)
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
			cameraPos = camera.cameraPos;
		}

		GLfloat xoffset = xpos - lastX;
		GLfloat yoffset = lastY - ypos;

		lastX = xpos;
		lastY = ypos;
		
		/*glm::vec3 newpos =
			glm::vec3(camera.cameraPos.x - xoffset* deltaTime, camera.cameraPos.y - yoffset* deltaTime, camera.cameraPos.z);
		camera.cameraPos = newpos;*/
		camera.cameraPos -= camera.cameraUp * yoffset * deltaTime * 2.0f;
		camera.cameraPos -= camera.cameraRight * xoffset * deltaTime * 2.0f;
	}
}

//鼠标滚轮回调函数
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
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