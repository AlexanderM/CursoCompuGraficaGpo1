/* Nombre: Millan Gaston Alexander
Practica 5
Fecha de entrega: 12 de Septiembre de 2025
No. 319325483 */

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);

const GLint WIDTH = 1200, HEIGHT = 800;

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rot = 0.0f;

//For model
float	hombro = 0.0f;
float   codo = 0.0f;
float muneca = 0.0f;
float dedo1 = 0.0f;
float dedo2 = 0.0f;
float dedo3 = 0.0f;
float dedo4 = 0.0f;
float dedo5 = 0.0f;

// Falanges de cada dedo
float falange1_1 = 0.0f, falange1_2 = 0.0f;
float falange2_1 = 0.0f, falange2_2 = 0.0f;
float falange3_1 = 0.0f, falange3_2 = 0.0f;
float falange4_1 = 0.0f, falange4_2 = 0.0f;
float falange5_1 = 0.0f, falange5_2 = 0.0f;

// L?mites de rotaci?n COMPLETOS para ambas direcciones
const float MAX_HOMBRO = 90.0f;
const float MIN_HOMBRO = -90.0f;

const float MAX_CODO = 120.0f;
const float MIN_CODO = 0.0f;

const float MAX_MUNECA = 45.0f;
const float MIN_MUNECA = -45.0f;

const float MAX_DEDOS_SUPERIORES = 90.0f;
const float MIN_DEDOS_SUPERIORES = -30.0f;

const float MAX_DEDOS_INFERIORES = 30.0f;
const float MIN_DEDOS_INFERIORES = -90.0f;

const float MAX_FALANGES_SUP = 10.0f;
const float MIN_FALANGES_SUP = -60.0f;

const float MAX_FALANGES = 60.0f;
const float MIN_FALANGES = -10.0f;

int main() {
    glfwInit();
    //Verificaci?n de compatibilidad 
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 5 Alexander Millan", nullptr, nullptr);

    int screenWidth, screenHeight;

    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    //Verificaci?n de errores de creacion ventana
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    //Verificaci?n de errores de inicializaci?n de glew
    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define las dimensiones del viewport
    glViewport(0, 0, screenWidth, screenHeight);

    // Setup OpenGL options
    glEnable(GL_DEPTH_TEST);

    // enable alpha support
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Build and compile our shader program
    Shader ourShader("Shader/core.vs", "Shader/core.frag");

    // Set up vertex data (and buffer(s)) and attribute pointers
    float vertices[] = {
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f,  0.5f, 0.5f,
        0.5f,  0.5f, 0.5f,
        -0.5f,  0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,

        -0.5f, -0.5f,-0.5f,
        0.5f, -0.5f,-0.5f,
        0.5f,  0.5f,-0.5f,
        0.5f,  0.5f,-0.5f,
        -0.5f,  0.5f,-0.5f,
        -0.5f, -0.5f,-0.5f,

        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  -0.5f, 0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

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
        -0.5f, 0.5f, -0.5f,
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Enlazar Vertex Array Object
    glBindVertexArray(VAO);

    // Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); // Unbind VAO

    glm::mat4 projection = glm::mat4(1);
    projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);
    glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        Inputs(window);
        glfwPollEvents();

        // Render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.Use();
        glm::mat4 model = glm::mat4(1);
        glm::mat4 view = glm::mat4(1);
        glm::mat4 modelTemp = glm::mat4(1.0f);
        glm::mat4 modelTemp2 = glm::mat4(1.0f);

        //View set up 
        view = glm::translate(view, glm::vec3(movX, movY, movZ));
        view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
        GLint uniformColor = ourShader.uniformColor;

        glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));

        glBindVertexArray(VAO);

        //Model Bicep
        model = glm::rotate(model, glm::radians(hombro), glm::vec3(0.0f, 0.0, 1.0f));
        modelTemp = model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
        color = glm::vec3(6.0f, 1.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //model Antebrazo
        model = glm::translate(modelTemp, glm::vec3(1.5f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(codo), glm::vec3(0.0f, 1.0f, 0.0f));
        modelTemp = model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
        color = glm::vec3(1.0f, 0.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //model Palma
        model = glm::translate(modelTemp, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(muneca), glm::vec3(1.0f, 0.0f, 0.0f));
        modelTemp = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
        color = glm::vec3(0.7f, 6.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // DEDOS SUPERIORES (3 dedos)

        // Dedo 1 Superior (centro)
        model = glm::translate(modelTemp, glm::vec3(0.25f, 0.35f, 0.0f));
        model = glm::rotate(model, glm::radians(dedo1), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.2f, 0.2f));
        color = glm::vec3(0.0f, 1.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Falange 1 del Dedo 1
        model = glm::translate(modelTemp2, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(falange1_1), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.2f, 0.2f));
        color = glm::vec3(0.0f, 0.8f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Dedo 2 Superior (derecha)
        model = glm::translate(modelTemp, glm::vec3(0.25f, 0.35f, 0.25f));
        model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.2f, 0.2f));
        color = glm::vec3(0.0f, 0.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Falange 1 del Dedo 2
        model = glm::translate(modelTemp2, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(falange2_1), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.2f, 0.2f));
        color = glm::vec3(0.0f, 0.0f, 0.8f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Dedo 3 Superior (izquierda)
        model = glm::translate(modelTemp, glm::vec3(0.25f, 0.35f, -0.25f));
        model = glm::rotate(model, glm::radians(dedo3), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.2f, 0.2f));
        color = glm::vec3(1.0f, 1.0f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Falange 1 del Dedo 3
        model = glm::translate(modelTemp2, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(falange3_1), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.2f, 0.2f));
        color = glm::vec3(0.8f, 0.8f, 0.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // DEDOS INFERIORES (2 dedos)

        // Dedo 4 Inferior (derecha)
        model = glm::translate(modelTemp, glm::vec3(0.25f, -0.35f, 0.15f));
        model = glm::rotate(model, glm::radians(dedo4), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.2f, 0.2f));
        color = glm::vec3(1.0f, 0.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Falange 1 del Dedo 4
        model = glm::translate(modelTemp2, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(falange4_1), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.2f, 0.2f));
        color = glm::vec3(0.8f, 0.0f, 0.8f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Dedo 5 Inferior (izquierda)
        model = glm::translate(modelTemp, glm::vec3(0.25f, -0.35f, -0.15f));
        model = glm::rotate(model, glm::radians(dedo5), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.2f, 0.2f));
        color = glm::vec3(0.0f, 1.0f, 1.0f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Falange 1 del Dedo 5
        model = glm::translate(modelTemp2, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(falange5_1), glm::vec3(0.0f, 0.0f, 1.0f));
        modelTemp2 = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.2f, 0.2f));
        color = glm::vec3(0.0f, 0.8f, 0.8f);
        glUniform3fv(uniformColor, 1, glm::value_ptr(color));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return EXIT_SUCCESS;
}

void Inputs(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Movimiento de c?mara (sin l?mites)
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        movX += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        movX -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        movY += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        movY -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        movZ -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        movZ += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        rot += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        rot -= 0.18f;

    // Movimiento de hombro con l?mites en AMBOS lados
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && hombro < MAX_HOMBRO)
        hombro += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && hombro > MIN_HOMBRO)
        hombro -= 0.18f;

    // Movimiento de codo con l?mites en AMBOS lados
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && codo < MAX_CODO)
        codo += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && codo > MIN_CODO)
        codo -= 0.18f;

    // Movimiento de mu?eca con l?mites en AMBOS lados
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && muneca < MAX_MUNECA)
        muneca += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS && muneca > MIN_MUNECA)
        muneca -= 0.18f;

    // Movimiento de dedos SUPERIORES con l?mites en AMBOS lados
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && dedo1 < MAX_DEDOS_SUPERIORES)
        dedo1 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && dedo1 > MIN_DEDOS_SUPERIORES)
        dedo1 -= 0.18f;

    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && dedo2 < MAX_DEDOS_SUPERIORES)
        dedo2 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS && dedo2 > MIN_DEDOS_SUPERIORES)
        dedo2 -= 0.18f;

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && dedo3 < MAX_DEDOS_SUPERIORES)
        dedo3 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && dedo3 > MIN_DEDOS_SUPERIORES)
        dedo3 -= 0.18f;

    // Movimiento de dedos INFERIORES con l?mites en AMBOS lados
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS && dedo4 < MAX_DEDOS_INFERIORES)
        dedo4 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && dedo4 > MIN_DEDOS_INFERIORES)
        dedo4 -= 0.18f;

    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && dedo5 < MAX_DEDOS_INFERIORES)
        dedo5 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS && dedo5 > MIN_DEDOS_INFERIORES)
        dedo5 -= 0.18f;

    // Movimiento de falanges con l?mites en AMBOS lados
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && falange1_1 < MAX_FALANGES_SUP)
        falange1_1 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && falange1_1 > MIN_FALANGES_SUP)
        falange1_1 -= 0.18f;

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && falange2_1 < MAX_FALANGES_SUP)
        falange2_1 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && falange2_1 > MIN_FALANGES_SUP)
        falange2_1 -= 0.18f;

    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS && falange3_1 < MAX_FALANGES_SUP)
        falange3_1 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS && falange3_1 > MIN_FALANGES_SUP)
        falange3_1 -= 0.18f;

    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS && falange4_1 < MAX_FALANGES)
        falange4_1 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS && falange4_1 > MIN_FALANGES)
        falange4_1 -= 0.18f;

    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS && falange5_1 < MAX_FALANGES)
        falange5_1 += 0.18f;
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS && falange5_1 > MIN_FALANGES)
        falange5_1 -= 0.18f;
}
