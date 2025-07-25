#include "Config.h"

const char *vertexShaderSource = "#version 330 core\n"
    "layout(location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragCol;\n"
    "void main()\n"
    "{\n"
    "FragCol = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

int main()
{
    if (!glfwInit())
        return -1;
    
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window;
    window = glfwCreateWindow(640, 480, "GLFW CMake starter", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if(!gladLoadGL(glfwGetProcAddress)){
        cout << "GLAD failed to init" << endl;
        return -1;
    }
    glClearColor( 0.4f, 0.3f, 0.4f, 0.0f );

    /// ======================== Drawing the triangle below =================
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // vertex shader 
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    int success;
    char infoLog[512];
    // checking if vertex shader compiled properly
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "Unable to compile vertex shader" << endl;
        return -1;
    }

    // checking if fragment shader compiled properly
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "Unable to compile frgment shader" << endl;
        return -1;
    }

    // creating the shader programme to link the vertex and fragment shader together
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // checking if linking was sucesseful
    glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cout << "There was an error creating the shader programme." << endl;
        return -1;
    }

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /// 0 = this is the value we set in the vertex shader (location = 0)
    /// 3 = vec3 we set in the shader, if we used vec4 in the vertshader then the value was 4
    /// GL_FLOAT = data type of vec
    /// GL_FALSSE = the data is already normalized, so we set it false
    /// 3 * sizeof(float) = stride size
    // The last parameter is of type void* and thus requires that weird cast. This is the offset of where the position data begins in the buffer. 
    // Since the position data is at the start of the data array this value is just 0. We will explore this parameter in more detail later on
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}




// //================================================ Git Example code Below ======================================

// #include "Config.h"

// typedef struct Vertex
// {
//     vec2 pos;
//     vec3 col;
// } Vertex;

// static const Vertex vertices[3] =
// {
//     { { -0.6f, -0.4f }, { 1.f, 0.f, 0.f } },
//     { {  0.6f, -0.4f }, { 0.f, 1.f, 0.f } },
//     { {   0.f,  0.6f }, { 0.f, 0.f, 1.f } }
// };

// static const char* vertex_shader_text =
// "#version 330\n"
// "uniform mat4 MVP;\n"
// "in vec3 vCol;\n"
// "in vec2 vPos;\n"
// "out vec3 color;\n"
// "void main()\n"
// "{\n"
// "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
// "    color = vCol;\n"
// "}\n";

// static const char* fragment_shader_text =
// "#version 330\n"
// "in vec3 color;\n"
// "out vec4 fragment;\n"
// "void main()\n"
// "{\n"
// "    fragment = vec4(color, 1.0);\n"
// "}\n";

// static void error_callback(int error, const char* description)
// {
//     fprintf(stderr, "Error: %s\n", description);
// }

// static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
// {
//     if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, GLFW_TRUE);
// }

// int main(void)
// {
    // glfwSetErrorCallback(error_callback);

    // if (!glfwInit())
    //     exit(EXIT_FAILURE);

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Triangle", NULL, NULL);
    // if (!window)
    // {
    //     glfwTerminate();
    //     exit(EXIT_FAILURE);
    // }

    // glfwSetKeyCallback(window, key_callback);

//     glfwMakeContextCurrent(window);
//     gladLoadGL(glfwGetProcAddress);
//     glfwSwapInterval(1);

//     // NOTE: OpenGL error checks have been omitted for brevity

//     GLuint vertex_buffer;
//     glGenBuffers(1, &vertex_buffer);
//     glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
//     glCompileShader(vertex_shader);

//     const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
//     glCompileShader(fragment_shader);

//     const GLuint program = glCreateProgram();
//     glAttachShader(program, vertex_shader);
//     glAttachShader(program, fragment_shader);
//     glLinkProgram(program);

//     const GLint mvp_location = glGetUniformLocation(program, "MVP");
//     const GLint vpos_location = glGetAttribLocation(program, "vPos");
//     const GLint vcol_location = glGetAttribLocation(program, "vCol");

//     GLuint vertex_array;
//     glGenVertexArrays(1, &vertex_array);
//     glBindVertexArray(vertex_array);
//     glEnableVertexAttribArray(vpos_location);
//     glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
//                           sizeof(Vertex), (void*) offsetof(Vertex, pos));
//     glEnableVertexAttribArray(vcol_location);
//     glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
//                           sizeof(Vertex), (void*) offsetof(Vertex, col));

//     while (!glfwWindowShouldClose(window))
//     {
//         int width, height;
//         glfwGetFramebufferSize(window, &width, &height);
//         const float ratio = width / (float) height;

//         glViewport(0, 0, width, height);
//         glClear(GL_COLOR_BUFFER_BIT);

//         mat4x4 m, p, mvp;
//         mat4x4_identity(m);
//         mat4x4_rotate_Z(m, m, (float) glfwGetTime());
//         mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
//         mat4x4_mul(mvp, p, m);

//         glUseProgram(program);
//         glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) &mvp);
//         glBindVertexArray(vertex_array);
//         glDrawArrays(GL_TRIANGLES, 0, 3);

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     glfwDestroyWindow(window);

//     glfwTerminate();
//     exit(EXIT_SUCCESS);
// }

//! [code]
