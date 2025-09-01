/*
Nombre: Millan Gaston Alexander
Practica 3
Fecha de entrega: 28 de Agosto de 2025
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

const GLint WIDTH = 800, HEIGHT = 600;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Piramide de Cubos Colorida", nullptr, nullptr);
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

    // Vertices de un cubo unitario (tamaño 1x1x1) con diferentes colores por cara
    GLfloat vertices[] = {
        // Cara frontal - ROJO
   -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
    0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
    0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
   -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
   -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

   // Cara trasera - VERDE
   -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
   -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
   -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,

   // Cara derecha - AZUL
    0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

    // Cara izquierda - AMARILLO
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,

    // Cara inferior - CYAN
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,

    // Cara superior - ROSA
    -0.5f,  0.5f, -0.5f, 1.0f, 0.2f, 0.5f,
     0.5f,  0.5f, -0.5f, 1.0f, 0.2f, 0.5f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.2f, 0.5f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.2f, 0.5f,
    -0.5f,  0.5f,  0.5f, 1.0f, 0.2f, 0.5f,
    -0.5f,  0.5f, -0.5f, 1.0f, 0.2f, 0.5f
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configurar atributos de vértices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Configurar proyección en perspectiva
    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 1000.0f);

    // Tamaño base y espaciado
    const float baseCubeSize = 1.0f;
    const float spacing = 0.2f;
    const float totalWidth = baseCubeSize + spacing;

    // Factores de escala por nivel
    const float scaleLevel1 = 1.0f;  // Base - más grandes
    const float scaleLevel2 = 0.8f;  // Segundo nivel - medianos
    const float scaleLevel3 = 0.6f;  // Tercer nivel - más pequeños

    // Rotaciones para mostrar diferentes caras (eje X, Y, Z, ángulo en radianes)
    glm::vec4 rotations[] = {
        // 6 rotaciones diferentes (una por cada cara)
        glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),           // Cara frontal (roja)
        glm::vec4(0.0f, 1.0f, 0.0f, glm::radians(180.0f)), // Cara trasera (verde)
        glm::vec4(0.0f, 1.0f, 0.0f, glm::radians(90.0f)),  // Cara derecha (azul)
        glm::vec4(0.0f, 1.0f, 0.0f, glm::radians(-90.0f)), // Cara izquierda (amarilla)
        glm::vec4(1.0f, 0.0f, 0.0f, glm::radians(-90.0f)), // Cara superior (rosa)
        glm::vec4(1.0f, 0.0f, 0.0f, glm::radians(90.0f)),  // Cara inferior (cyan)

        // Repetimos algunas para completar los 9 cubos
        glm::vec4(1.0f, 0.0f, 0.0f, glm::radians(180.0f)),  // Combinación 1
        glm::vec4(1.0f, 0.0f, 0.0f, glm::radians(90.0f)),  // Combinación 2
        glm::vec4(0.0f, 0.0f, 1.0f, glm::radians(90.0f))   // Combinación 3
    };

    // Posiciones de los cubos en la pirámide
    glm::vec3 cubePositions[] = {
        // Nivel 1 (base) - 4 cubos - más grandes
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(totalWidth, 0.0f, 0.0f),
        glm::vec3(totalWidth * 2, 0.0f, 0.0f),
        glm::vec3(totalWidth * 3, 0.0f, 0.0f),

        // Nivel 2 - 3 cubos - medianos (reducir altura)
        glm::vec3(totalWidth / 2, baseCubeSize * 0.95f, 0.0f),              // Y = baseCubeSize * 0.8f
        glm::vec3(totalWidth / 2 + totalWidth, baseCubeSize * 0.95f, 0.0f), // Y = baseCubeSize * 0.8f
        glm::vec3(totalWidth / 2 + totalWidth * 2, baseCubeSize * 0.95f, 0.0f), // Y = baseCubeSize * 0.8f

        // Nivel 3 - 2 cubos - más pequeños (reducir altura)
        glm::vec3(totalWidth, baseCubeSize * 1.7f, 0.0f),                  // Y = baseCubeSize * 1.6f  
        glm::vec3(totalWidth + totalWidth, baseCubeSize * 1.7f, 0.0f)      // Y = baseCubeSize * 1.6f
    };

    // Escalas por nivel
    float cubeScales[] = {
        scaleLevel1, scaleLevel1, scaleLevel1, scaleLevel1,  // Nivel 1
        scaleLevel2, scaleLevel2, scaleLevel2,               // Nivel 2
        scaleLevel3, scaleLevel3                             // Nivel 3
    };

    // Calcular el centro de la pirámide
    float pyramidWidth = totalWidth * 3;
    float pyramidHeight = totalWidth * 2;
    glm::vec3 pyramidCenter = glm::vec3(pyramidWidth / 2, pyramidHeight / 2, 0.0f);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.Use();

        // Configurar matriz de vista
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f)); // Alejar más la cámara
        view = glm::rotate(view, glm::radians(-15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::rotate(view, glm::radians(35.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");

        glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glBindVertexArray(VAO);

        // Dibujar los 9 cubos con rotaciones y escalados diferentes
        for (int i = 0; i < 9; i++) {
            glm::mat4 model = glm::mat4(1.0f);

            // Posicionar el cubo (centrado)
            glm::vec3 position = cubePositions[i] - pyramidCenter;
            model = glm::translate(model, position);

            // Aplicar rotación para mostrar cara diferente
            glm::vec4 rotation = rotations[i];
            model = glm::rotate(model, rotation.w, glm::vec3(rotation.x, rotation.y, rotation.z));

            // Aplicar escala según el nivel
            model = glm::scale(model, glm::vec3(cubeScales[i]));

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }

    // Limpieza
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return EXIT_SUCCESS;
}