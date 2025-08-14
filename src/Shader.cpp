#include "Config.h"

class Shader
{
public:
    ~Shader();
    unsigned int Init();

private:
    unsigned int shaderProgram;

    unsigned int GenerateShader(const string& sourceFile, unsigned int shaderType);
    unsigned int CreateShaderProgram(const string& vertSourceFile, const string& fragSourceFile);
};

unsigned int Shader::Init()
{
    shaderProgram = CreateShaderProgram
    (
        "../src/Shader/vert.shader", 
		"../src/Shader/frag.shader"
    );
    
    return shaderProgram;
}

Shader::~Shader()
{
    glDeleteProgram(shaderProgram);
}

unsigned int Shader::GenerateShader(const string& sourceFile, unsigned int shaderType){
    ifstream file;
    string line;
    stringstream bufferLine;

    file.open(sourceFile);
    while(getline(file, line)){
        bufferLine << line << "\n";
    }

    string sourceString = bufferLine.str();
    const char *shaderSource = sourceString.c_str();
    bufferLine.str("");
    file.close();

    unsigned int shader =  glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    int sucess;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &sucess);
    if(!sucess){
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        cout << "Unable to make vertex shader." << endl;
        return -1;
    }

    return shader;
}

unsigned int Shader::CreateShaderProgram(const string& vertSourceFile, const string& fragSourceFile){
    unsigned int vertShader = GenerateShader(vertSourceFile, GL_VERTEX_SHADER);
    unsigned int fragShader = GenerateShader(fragSourceFile, GL_FRAGMENT_SHADER);

    int sucess;
    char infoLog[512];
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &sucess);
    if(!sucess){
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cout << "Unable to link programme." << endl;
        return -1;
    }
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    return program;
}