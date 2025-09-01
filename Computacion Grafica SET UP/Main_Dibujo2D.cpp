#include <iostream>

//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Shaders

#include "Shader.h"

/*
Nombre: Millan Gaston Alexander
Previo 1
Fecha de entrega: 22 de Agosto de 2025
No. 319325483
*/

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 1200, HEIGHT = 900;
const int COL = 22;
const int FILAS = 16;
const int GRIDF = COL * FILAS;

// Función auxiliar para establecer colores fácilmente
void PonColor(float Colores[][3], int row, int col, float r, float g, float b) {
    if (row >= 0 && row < FILAS && col >= 0 && col < COL) {
        int index = row * COL + col;
        Colores[index][0] = r;
        Colores[index][1] = g;
        Colores[index][2] = b;
    }
}

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica2_Alexander Millan", NULL, NULL);
    glfwSetFramebufferSizeCallback(window, resize);

    if (window == NULL) {
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

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

    // Tamaño de cada cuadrado para 22x16
    const float Ancho = 1.0f / COL;
    const float Alto = 1.0f / FILAS;

    // Vértices base para un cuadrado
    float baseVertices[] = {
        Ancho,  Alto, 0.0f,   1.0f, 0.0f, 0.0f,
        Ancho, -Alto, 0.0f,   0.0f, 1.0f, 0.0f,
        -Ancho, -Alto, 0.0f,   0.0f, 0.0f, 1.0f,
        -Ancho,  Alto, 0.0f,   1.0f, 1.0f, 0.0f
    };

    unsigned int indices[] = { 0, 1, 2, 0, 2, 3 };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(baseVertices), baseVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Posiciones para la cuadrícula
    float gridPositions[GRIDF][2];
    float Colores[GRIDF][3];

    // Inicializar todo con blanco
    for (int row = 0; row < FILAS; row++) {
        for (int col = 0; col < COL; col++) {
            int index = row * COL + col;
            gridPositions[index][0] = (col * 2.0f * Ancho) - (1.0f - Ancho);
            gridPositions[index][1] = (row * 2.0f * Alto) - (1.0f - Alto);
            Colores[index][0] = 1.0f; 
            Colores[index][1] = 1.0f;
            Colores[index][2] = 1.0f;
        }
    }

    // ==================================================

    // Azul claro 
    const float Azul[3] = { 0.4f, 0.6f, 1.0f };

  
    PonColor(Colores, 15, 13, Azul[0], Azul[1], Azul[2]); // A
    PonColor(Colores, 15, 15, Azul[0], Azul[1], Azul[2]); // A
    PonColor(Colores, 15, 17, Azul[0], Azul[1], Azul[2]); // A

   
    PonColor(Colores, 14, 12, Azul[0], Azul[1], Azul[2]); // A
    PonColor(Colores, 14, 14, Azul[0], Azul[1], Azul[2]); // A
    PonColor(Colores, 14, 16, Azul[0], Azul[1], Azul[2]); // A


    PonColor(Colores, 13, 14, Azul[0], Azul[1], Azul[2]); // A

    for (int col = 11; col <= 19; col++) {
        PonColor(Colores, 12, col, 0.0f, 0.0f, 0.0f); // N
    }

    PonColor(Colores, 11, 10, 0.0f, 0.0f, 0.0f); // N
    for (int col = 11; col <= 19; col++) {
        PonColor(Colores, 11, col, Azul[0], Azul[1], Azul[2]); // A
    }
    PonColor(Colores, 11, 20, 0.0f, 0.0f, 0.0f); // N

    PonColor(Colores, 10, 9, 0.0f, 0.0f, 0.0f); // N
    for (int col = 10; col <= 20; col++) {
        PonColor(Colores, 10, col, Azul[0], Azul[1], Azul[2]); // A
    }
    PonColor(Colores, 10, 21, 0.0f, 0.0f, 0.0f); // N


    PonColor(Colores, 9, 1, 0.0f, 0.0f, 0.0f); // N
    PonColor(Colores, 9, 2, 0.0f, 0.0f, 0.0f); // N
    PonColor(Colores, 9, 4, 0.0f, 0.0f, 0.0f); // N
    PonColor(Colores, 9, 5, 0.0f, 0.0f, 0.0f); // N
    PonColor(Colores, 9, 8, 0.0f, 0.0f, 0.0f); // N
    for (int col = 9; col <= 20; col++) {
        PonColor(Colores, 9, col, Azul[0], Azul[1], Azul[2]); // A
    }
    PonColor(Colores, 9, 21, 0.0f, 0.0f, 0.0f); // N

   
    PonColor(Colores, 8, 1, 0.0f, 0.0f, 0.0f); // N
    PonColor(Colores, 8, 2, Azul[0], Azul[1], Azul[2]); // A
    PonColor(Colores, 8, 3, 0.0f, 0.0f, 0.0f); // N
    PonColor(Colores, 8, 4, Azul[0], Azul[1], Azul[2]); // A
    PonColor(Colores, 8, 5, 0.0f, 0.0f, 0.0f); // N
    PonColor(Colores, 8, 8, 0.0f, 0.0f, 0.0f); // N
    for (int col = 9; col <= 16; col++) {
        PonColor(Colores, 8, col, Azul[0], Azul[1], Azul[2]); // A
    }
    PonColor(Colores, 8, 17, 1.0f, 1.0f, 1.0f); // B (blanco)
    PonColor(Colores, 8, 18, 1.0f, 1.0f, 1.0f); // B (blanco)
    PonColor(Colores, 8, 19, Azul[0], Azul[1], Azul[2]); // A
    PonColor(Colores, 8, 20, Azul[0], Azul[1], Azul[2]); // A
    PonColor(Colores, 8, 21, 0.0f, 0.0f, 0.0f); // N

    
    PonColor(Colores, 7, 1, 0.0f, 0.0f, 0.0f); // N
    PonColor(Colores, 7, 2, Azul[0], Azul[1], Azul[2]); // A
    PonColor(Colores, 7, 3, Azul[0], Azul[1], Azul[2]); // A
    PonColor(Colores, 7, 4, Azul[0], Azul[1], Azul[2]); // A
    PonColor(Colores, 7, 5, 0.0f, 0.0f, 0.0f); // N
    PonColor(Colores, 7, 8, 0.0f, 0.0f, 0.0f); // N
    for (int col = 9; col <= 15; col++) {
        PonColor(Colores, 7, col, Azul[0], Azul[1], Azul[2]); // A
    }
    PonColor(Colores, 7, 16, 1.0f, 1.0f, 1.0f); // B (blanco)
    PonColor(Colores, 7, 17, 0.0f, 0.0f, 0.0f); // N
    PonColor(Colores, 7, 18, Azul[0], Azul[1], Azul[2]); // A
    PonColor(Colores, 7, 19, Azul[0], Azul[1], Azul[2]); // A
    PonColor(Colores, 7, 20, 0.0f, 0.0f, 0.0f); // N


    PonColor(Colores, 6, 2, 0.0f, 0.0f, 0.0f); // N
    PonColor(Colores, 6, 3, Azul[0], Azul[1], Azul[2]); // A
    PonColor(Colores, 6, 4, 0.0f, 0.0f, 0.0f); // N
    PonColor(Colores, 6, 7, 0.0f, 0.0f, 0.0f); // N
    for (int col = 8; col <= 20; col++) {
        PonColor(Colores, 6, col, Azul[0], Azul[1], Azul[2]); // A
    }
    PonColor(Colores, 6, 21, 0.0f, 0.0f, 0.0f); // N

    
    PonColor(Colores, 5, 2, 0.0f, 0.0f, 0.0f); // N
    PonColor(Colores, 5, 3, Azul[0], Azul[1], Azul[2]); // A
    PonColor(Colores, 5, 4, Azul[0], Azul[1], Azul[2]); // A
    PonColor(Colores, 5, 5, 0.0f, 0.0f, 0.0f); // N
    PonColor(Colores, 5, 6, 0.0f, 0.0f, 0.0f); // N
    for (int col = 7; col <= 13; col++) {
        PonColor(Colores, 5, col, Azul[0], Azul[1], Azul[2]); // A
    }
    for (int col = 14; col <= 21; col++) {
        PonColor(Colores, 5, col, 1.0f, 1.0f, 1.0f); // B (blanco)
    }
    PonColor(Colores, 5, 21, 0.0f, 0.0f, 0.0f); // N

    
    PonColor(Colores, 4, 3, 0.0f, 0.0f, 0.0f); // N
    for (int col = 4; col <= 8; col++) {
        PonColor(Colores, 4, col, Azul[0], Azul[1], Azul[2]); // A
    }
    for (int col = 9; col <= 15; col++) {
        PonColor(Colores, 4, col, 1.0f, 1.0f, 1.0f); // B (blanco)
    }
    PonColor(Colores, 4, 16, 0.0f, 0.0f, 0.0f); // N
    for (int col = 17; col <= 19; col++) {
        PonColor(Colores, 4, col, 1.0f, 1.0f, 1.0f); // B (blanco)
    }
    PonColor(Colores, 4, 20, 0.0f, 0.0f, 0.0f); // N


    for (int col = 4; col <= 12; col++) {
        PonColor(Colores, 3, col, 0.0f, 0.0f, 0.0f); // N
    }
    PonColor(Colores, 3, 14, 0.0f, 0.0f, 0.0f); // N
    for (int col = 15; col <= 19; col++) {
        PonColor(Colores, 3, col, 0.0f, 0.0f, 0.0f); // N
    }
    PonColor(Colores, 3, 20, 1.0f, 1.0f, 1.0f); // B (blanco)



    // ==================================================
    // FIN DEL PIXEL ART
    // ==================================================

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.8f, 0.9f, 1.0f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.Use();
        glBindVertexArray(VAO);

        for (int i = 0; i < GRIDF; i++) {
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            float currentVertices[24];
            for (int j = 0; j < 4; j++) {
                currentVertices[j * 6 + 0] = baseVertices[j * 6 + 0] + gridPositions[i][0];
                currentVertices[j * 6 + 1] = baseVertices[j * 6 + 1] + gridPositions[i][1];
                currentVertices[j * 6 + 2] = baseVertices[j * 6 + 2];
                currentVertices[j * 6 + 3] = Colores[i][0];
                currentVertices[j * 6 + 4] = Colores[i][1];
                currentVertices[j * 6 + 5] = Colores[i][2];
            }

            glBufferData(GL_ARRAY_BUFFER, sizeof(currentVertices), currentVertices, GL_STATIC_DRAW);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}