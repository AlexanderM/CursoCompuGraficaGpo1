

/*
Nombre: Millan Gaston Alexander
Practica 4
Fecha de entrega: 05 de Agosto de 2025
No. 319325483
*/


#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);

const GLint WIDTH = 800, HEIGHT = 600;
float movX = 0.0f;
float movY = 0.0f;
float movZ = -5.0f;
float rot = 0.0f;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica4 Alexander Millan", nullptr, nullptr);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (nullptr == window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Build and compile our shader program
    Shader ourShader("Shader/core.vs", "Shader/core.frag");

    //ºpara las patas - colores variados)
    float vertices[] = {
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, // Front
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Back
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,

        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, // Right
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, // Left
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Bottom
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Top
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    };

    // Set up vertex data for a cube (para el cuerpo - TODO NARANJA)
    float verticesCuerpo[] = {
        -0.5f, -0.5f, 0.5f, 1.0f, 0.5f, 0.2f, // Front (Naranja)
        0.5f, -0.5f, 0.5f, 1.0f, 0.5f, 0.2f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.5f, 0.2f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.5f, 0.2f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.5f, 0.2f,
        -0.5f, -0.5f, 0.5f, 1.0f, 0.5f, 0.2f,

        -0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.2f, // Back (Naranja)
        0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.2f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.5f, 0.2f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.5f, 0.2f,
        -0.5f, 0.5f, -0.5f, 1.0f, 0.5f, 0.2f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.2f,

        0.5f, -0.5f, 0.5f, 1.0f, 0.5f, 0.2f, // Right (Naranja)
        0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.2f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.5f, 0.2f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.5f, 0.2f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.5f, 0.2f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.5f, 0.2f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.5f, 0.2f, // Left (Naranja)
        -0.5f, 0.5f, -0.5f, 1.0f, 0.5f, 0.2f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.2f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.2f,
        -0.5f, -0.5f, 0.5f, 1.0f, 0.5f, 0.2f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.5f, 0.2f,

        -0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.2f, // Bottom (Naranja)
        0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.2f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.5f, 0.2f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.5f, 0.2f,
        -0.5f, -0.5f, 0.5f, 1.0f, 0.5f, 0.2f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.2f,

        -0.5f, 0.5f, -0.5f, 1.0f, 0.5f, 0.2f, // Top (Naranja)
        0.5f, 0.5f, -0.5f, 1.0f, 0.5f, 0.2f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.5f, 0.2f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.5f, 0.2f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.5f, 0.2f,
        -0.5f, 0.5f, -0.5f, 1.0f, 0.5f, 0.2f,
    };

    float verticesBoca[] = {
    -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, // Front (Blanco)
    0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,

    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Back (Blanco)
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,

    0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, // Right (Blanco)
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,

    -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, // Left (Blanco)
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,

    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Bottom (Blanco)
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Top (Blanco)
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
    };

    // (plano 2D) - TODO BLANCO
    float verticesSquare[] = {
        // Positions         // Colors (todo blanco)
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 0.0f,  // Bottom-left
         0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 0.0f,  // Bottom-right
         0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 0.0f,  // Top-right
        -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 0.0f,  // Top-left
    };

    unsigned int indicesSquare[] = {
        0, 1, 2,  // First triangle
        2, 3, 0   // Second triangle
    };
    // (plano 2D) - TODO NEGRO
    float verticesSquareBlack[] = {
        // Positions         // Colors (todo negro)
        -0.5f, -0.5f, 0.0f,  1.0f, 0.96f, 0.86f,  // Bottom-left
         0.5f, -0.5f, 0.0f,  1.0f, 0.96f, 0.86f,  // Bottom-right
         0.5f,  0.5f, 0.0f,  1.0f, 0.96f, 0.86f,  // Top-right
        -0.5f,  0.5f, 0.0f,  1.0f, 0.96f, 0.86f,  // Top-left
    };
    //1.0f, 1.0f, 1.0f,
    unsigned int indicesSquareBlack[] = {
        0, 1, 2,  // First triangle
        2, 3, 0   // Second triangle
    };


    GLuint VBO, VAO; // Para las patas
    GLuint VBOCuerpo, VAOCuerpo; // Para el cuerpo
    GLuint VBOOrejas, VAOOrejas; // Para las orejas
    GLuint VBOBoca, VAOBoca; // Para la boca
    GLuint VBOSquareBlack, VAOSquareBlack, EBOSquareBlack;
    GLuint VBOSquare, VAOSquare, EBOSquare;

    // Configurar VAO y VBO para las patas
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Configurar VAO y VBO para el cuerpo
    glGenVertexArrays(1, &VAOCuerpo);
    glGenBuffers(1, &VBOCuerpo);

    glBindVertexArray(VAOCuerpo);
    glBindBuffer(GL_ARRAY_BUFFER, VBOCuerpo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCuerpo), verticesCuerpo, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Configurar VAO y VBO para las orejas (también naranjas)
    glGenVertexArrays(1, &VAOOrejas);
    glGenBuffers(1, &VBOOrejas);

    glBindVertexArray(VAOOrejas);
    glBindBuffer(GL_ARRAY_BUFFER, VBOOrejas);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Configurar VAO y VBO para la boca
    glGenVertexArrays(1, &VAOBoca);
    glGenBuffers(1, &VBOBoca);

    glBindVertexArray(VAOBoca);
    glBindBuffer(GL_ARRAY_BUFFER, VBOBoca);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBoca), verticesBoca, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

   

    // Configurar VAO, VBO y EBO para el cuadrado
    glGenVertexArrays(1, &VAOSquare);
    glGenBuffers(1, &VBOSquare);
    glGenBuffers(1, &EBOSquare);

    glBindVertexArray(VAOSquare);

    glBindBuffer(GL_ARRAY_BUFFER, VBOSquare);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSquare), verticesSquare, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOSquare);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesSquare), indicesSquare, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    glGenVertexArrays(1, &VAOSquareBlack);
    glGenBuffers(1, &VBOSquareBlack);
    glGenBuffers(1, &EBOSquareBlack);

    glBindVertexArray(VAOSquareBlack);

    glBindBuffer(GL_ARRAY_BUFFER, VBOSquareBlack);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSquareBlack), verticesSquareBlack, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOSquareBlack);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesSquareBlack), indicesSquareBlack, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);




    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window)) {
        Inputs(window);
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.Use();
        glm::mat4 model = glm::mat4(1);
        glm::mat4 view = glm::mat4(1);

        view = glm::translate(view, glm::vec3(movX, movY, movZ));
        view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");

        glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        // Dibujar las patas
        glBindVertexArray(VAO);
        float spacing = 1.5f;
        float height = 0.5f;

        // Pata 1 (frontal izquierda)
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-spacing, height / 2 - 0.5f, -spacing));
        model = glm::scale(model, glm::vec3(0.8f, height, 0.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Pata 2 (frontal derecha)
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(spacing, height / 2 - 0.5f, -spacing));
        model = glm::scale(model, glm::vec3(0.8f, height, 0.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Pata 3 (trasera izquierda)
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-spacing, height / 2 - 0.5f, spacing));
        model = glm::scale(model, glm::vec3(0.8f, height, 0.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Pata 4 (trasera derecha)
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(spacing, height / 2 - 0.5f, spacing));
        model = glm::scale(model, glm::vec3(0.8f, height, 0.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // NARIZ BL
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, height + 1.033f, 2.433));
        model = glm::scale(model, glm::vec3(0.5f, 0.35f, 0.18f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Dibujar el cuerpo 
        glBindVertexArray(VAOCuerpo);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, height + 1.4f, 0.0f));
        model = glm::scale(model, glm::vec3(3.8f, 3.8f, 3.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // COLA NAR 1
        glBindVertexArray(VAOCuerpo);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, height + 2.17f, -1.2f));
        model = glm::scale(model, glm::vec3(1.2003f, 3.0f, 2.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // COLA NAR 2
        glBindVertexArray(VAOCuerpo);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, height + 4.0f, -0.35f));
        model = glm::scale(model, glm::vec3(1.2003f, 0.7f, 0.3f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // NARIZ NAR
        glBindVertexArray(VAOCuerpo);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, height + 1.03f, 2.12));
        model = glm::scale(model, glm::vec3(1.23f, 0.35f, 0.8f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Dibujar las orejas
        glBindVertexArray(VAOOrejas);

        // Oreja izquierda
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.35f, height + 3.8f, 1.4f)); // Posición izquierda y más arriba
        model = glm::scale(model, glm::vec3(1.1f, 1.0f, 0.999f)); // Oreja alta y delgada
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Oreja derecha
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.35f, height + 3.8f, 1.4f)); // Posición derecha y más arriba
        model = glm::scale(model, glm::vec3(1.1f, 1.0f, 0.999f)); // Oreja alta y delgada
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Dibujar la boca
        glBindVertexArray(VAOBoca);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, height + 0.8f, 2.2f)); // Posición frontal del cuerpo
        model = glm::scale(model, glm::vec3(1.2f, 0.8f, 0.6f)); // Boca ancha y plana
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // PANZA(ABAJO)
        glBindVertexArray(VAOBoca);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.2277f, 0.0f)); 
        model = glm::scale(model, glm::vec3(3.83f, 0.45f, 2.2f)); 
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // COLA BL 1
        glBindVertexArray(VAOBoca);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, height + 2.17f, -1.5f));
        model = glm::scale(model, glm::vec3(1.2f, 3.5f, 2.0f)); 
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // COLA BL 2
        glBindVertexArray(VAOBoca);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, height + 4.0f, -0.59f));
        model = glm::scale(model, glm::vec3(1.2f, 0.7f, 0.3f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Dibujar detalles (cuadrados blancos)
        glBindVertexArray(VAOSquare);

        // Ojo izquierdo
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, height + 2.0f, 1.91f)); // Delante del cuerpo
        model = glm::scale(model, glm::vec3(0.9f, 1.2f, 0.0f)); // Plano y pequeño
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Ojo derecho
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, height + 2.0f, 1.91f)); // Delante del cuerpo
        model = glm::scale(model, glm::vec3(0.9f, 1.2f, 0.0f)); // Plano y pequeño
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    
        // Dibujar detalles NEGROS (pupilas de los ojos)
        glBindVertexArray(VAOSquareBlack);

        // Pupila ojo izquierdo
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.273f, height + 2.43f, 1.911f)); // Un poco más adelante
        model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.0f)); // Más pequeño que el ojo
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Pupila ojo derecho
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.273f, height + 2.43f, 1.911f)); // Un poco más adelante
        model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.0f)); // Más pequeño que el ojo
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // oreja bl IZq
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.35f, height + 3.6f, 1.9003f)); // Un poco más adelante
        model = glm::scale(model, glm::vec3(0.55f, 0.7f, 0.0f)); // Más pequeño que el ojo
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Oreja bl Der
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.35f, height + 3.6f, 1.9003f)); // Un poco más adelante
        model = glm::scale(model, glm::vec3(0.55f, 0.7f, 0.0f)); // Más pequeño que el ojo
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // panza
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.7503f, 1.911f)); // Un poco más adelante
        model = glm::scale(model, glm::vec3(1.9f, 1.5f, 1.5f)); // Más pequeño que el ojo
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);





        // Dibujar detalles (cuadrados blancos)
        glBindVertexArray(VAOSquare);

        //// NARIZ BL
        //model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(0.0f, height + 1.0f, 2.51)); // Delante del cuerpo
        //model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.0f)); // Plano y pequeño
        //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        


        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }

    // Limpieza
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAOCuerpo);
    glDeleteBuffers(1, &VBOCuerpo);
    glDeleteVertexArrays(1, &VAOOrejas);
    glDeleteBuffers(1, &VBOOrejas);
    glDeleteVertexArrays(1, &VAOBoca);
    glDeleteBuffers(1, &VBOBoca);
    glDeleteVertexArrays(1, &VAOSquare);  
    glDeleteBuffers(1, &VBOSquare);       
    glDeleteBuffers(1, &EBOSquare);        
    glDeleteVertexArrays(1, &VAOSquareBlack);    
    glDeleteBuffers(1, &VBOSquareBlack);          
    glDeleteBuffers(1, &EBOSquareBlack);
    glfwTerminate();
    return EXIT_SUCCESS;
}

void Inputs(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        movX += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        movX -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
        movY += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
        movY -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        movZ -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        movZ += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        rot += 0.8f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        rot -= 0.8f;
}