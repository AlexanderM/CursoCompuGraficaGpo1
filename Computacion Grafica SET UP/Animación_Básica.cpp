/* Nombre: Millan Gaston Alexander
Practica 10
Fecha de entrega: 31 de Octubre de 2025
No. 319325483 */

#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"

// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void Animation();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 8.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;

// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(0.0f,2.0f, 0.0f),
    glm::vec3(0.0f,0.0f, 0.0f),
    glm::vec3(0.0f,0.0f,  0.0f),
    glm::vec3(0.0f,0.0f, 0.0f)
};

float vertices[] = {
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

glm::vec3 Light1 = glm::vec3(0);

// Variables para la rotación orbital
float orbitAngleDog = 0.0f;     
float orbitAngleBall = 180.0f;   
float orbitRadius = 1.8f;       
float orbitSpeed = 30.0f;       
bool OrbitAnimation = false;   

// Variables para la animación de salto
bool isJumping = false;          
bool isPreparing = false;       
float jumpProgress = 0.0f;       
float preparationProgress = 0.0f; 
float jumpSpeed = 2.0f;          
float preparationSpeed = 3.0f;   
float maxJumpHeight = 1.5f;      

// Alturas actuales para interpolación
float currentDogHeight = 0.0f;
float currentBallHeight = 0.0f;

// Rotación diagonal del perro durante el salto
float currentDogTilt = 0.0f;    
float currentDogLean = 0.0f;     

// Para controlar que solo salten cuando se encuentren
bool canJump = true;
float encounterThreshold = 0.3f; 

// Deltatime
GLfloat deltaTime = 0.0f;   
GLfloat lastFrame = 0.0f;   

int main()
{
    // Init GLFW
    glfwInit();

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica10 Alexander Millan", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Set the required callback functions
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // GLFW Options

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
    Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");

    // models
    Model Dog((char*)"Models/RedDog.obj");
    Model Piso((char*)"Models/piso.obj");
    Model Ball((char*)"Models/ball.obj");

    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Set texture units
    lightingShader.Use();
    glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
    glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Calculate deltatime of current frame
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
        DoMovement();
        Animation();

        // Clear the colorbuffer
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // OpenGL options
        glEnable(GL_DEPTH_TEST);

        // Use cooresponding shader when setting uniforms/drawing objects
        lightingShader.Use();

        glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);

        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        // Directional light
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.6f, 0.6f, 0.6f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.6f, 0.6f, 0.6f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.3f, 0.3f, 0.3f);

        // Point light 1
        glm::vec3 lightColor;
        lightColor.x = abs(sin(glfwGetTime() * Light1.x));
        lightColor.y = abs(sin(glfwGetTime() * Light1.y));
        lightColor.z = sin(glfwGetTime() * Light1.z);

        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 0.2f, 0.2f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);

        // SpotLight
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.2f, 0.2f, 0.8f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.2f, 0.2f, 0.8f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(18.0f)));

        // Set material properties
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 5.0f);

        // Create camera transformations
        glm::mat4 view;
        view = camera.GetViewMatrix();

        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
        GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glm::mat4 model(1);

        // Carga de modelo 
        view = camera.GetViewMatrix();

        // Piso
        model = glm::mat4(1);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Piso.Draw(lightingShader);

        // Perro - con rotación diagonal CORREGIDA y orientación fija
        model = glm::mat4(1);
        // Calcular posición orbital usando trigonometría
        float dogX = orbitRadius * cos(glm::radians(orbitAngleDog));
        float dogZ = orbitRadius * sin(glm::radians(orbitAngleDog));
        model = glm::translate(model, glm::vec3(dogX, currentDogHeight, dogZ));

        // CALCULO CORREGIDO: Ángulo basado en posición para mirar al centro
        float lookAtAngle = atan2(dogX, dogZ) * 180.0f / glm::pi<float>() + 90.0f;
        model = glm::rotate(model, glm::radians(lookAtAngle), glm::vec3(0.0f, 1.0f, 0.0f));

        // ROTACIÓN ADICIONAL: Girar el modelo 180 grados para que mire correctamente
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        // Aplicar rotación diagonal durante el salto
        model = glm::rotate(model, glm::radians(currentDogTilt), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(currentDogLean), glm::vec3(0.0f, 0.0f, 1.0f));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
        Dog.Draw(lightingShader);

        // Pelota - rotación orbital en dirección contraria con salto
        model = glm::mat4(1);
        glEnable(GL_BLEND);//Activa la funcionalidad para trabajar el canal alfa
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Calcular posición orbital en dirección contraria
        float ballX = orbitRadius * cos(glm::radians(orbitAngleBall));
        float ballZ = orbitRadius * sin(glm::radians(orbitAngleBall));
        model = glm::translate(model, glm::vec3(ballX, currentBallHeight, ballZ));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
        Ball.Draw(lightingShader);
        glDisable(GL_BLEND);  //Desactiva el canal alfa 
        glBindVertexArray(0);

        // Also draw the lamp object, again binding the appropriate shader
        lampShader.Use();
        // Get location objects for the matrices on the lamp shader (these could be different on a different shader)
        modelLoc = glGetUniformLocation(lampShader.Program, "model");
        viewLoc = glGetUniformLocation(lampShader.Program, "view");
        projLoc = glGetUniformLocation(lampShader.Program, "projection");

        // Set matrices
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        model = glm::mat4(1);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        model = glm::mat4(1);
        model = glm::translate(model, pointLightPositions[0]);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
    // Camera controls
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (keys[GLFW_KEY_T])
    {
        pointLightPositions[0].x += 0.01f;
    }
    if (keys[GLFW_KEY_G])
    {
        pointLightPositions[0].x -= 0.01f;
    }

    if (keys[GLFW_KEY_Y])
    {
        pointLightPositions[0].y += 0.01f;
    }

    if (keys[GLFW_KEY_H])
    {
        pointLightPositions[0].y -= 0.01f;
    }
    if (keys[GLFW_KEY_U])
    {
        pointLightPositions[0].z -= 0.1f;
    }
    if (keys[GLFW_KEY_J])
    {
        pointLightPositions[0].z += 0.01f;
    }
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }

    if (keys[GLFW_KEY_SPACE])
    {
        active = !active;
        if (active)
        {
            Light1 = glm::vec3(1.0f, 1.0f, 0.0f);
        }
        else
        {
            Light1 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
        }
    }

    // Tecla para activar/desactivar la animación orbital
    if (keys[GLFW_KEY_O] && action == GLFW_PRESS)
    {
        OrbitAnimation = !OrbitAnimation;  // Rotación orbital con tecla O
    }
}

void Animation() {
    // Animación de rotación orbital
    if (OrbitAnimation)
    {
        // Perro gira en sentido antihorario (positivo)
        orbitAngleDog += orbitSpeed * deltaTime;
        if (orbitAngleDog >= 360.0f) orbitAngleDog -= 360.0f;

        // Pelota gira en sentido horario (negativo)
        orbitAngleBall -= orbitSpeed * deltaTime;
        if (orbitAngleBall <= -360.0f) orbitAngleBall += 360.0f;

        // Detectar cuando están uno encima del otro (misma posición XZ)
        // Calculamos las posiciones actuales
        glm::vec2 dogPos = glm::vec2(
            orbitRadius * cos(glm::radians(orbitAngleDog)),
            orbitRadius * sin(glm::radians(orbitAngleDog))
        );

        glm::vec2 ballPos = glm::vec2(
            orbitRadius * cos(glm::radians(orbitAngleBall)),
            orbitRadius * sin(glm::radians(orbitAngleBall))
        );

        // Calculamos la distancia entre ellos
        float distance = glm::length(dogPos - ballPos);

        // Si están muy cerca (uno encima del otro) y podemos saltar
        if (distance < encounterThreshold && canJump && !isJumping && !isPreparing)
        {
            isPreparing = true;
            preparationProgress = 0.0f;
            canJump = false;
        }

        // Permitir saltar de nuevo cuando se hayan separado lo suficiente
        if (distance > encounterThreshold * 3.0f)
        {
            canJump = true;
        }
    }

    // Fase de preparación (breve, antes del salto)
    if (isPreparing)
    {
        preparationProgress += preparationSpeed * deltaTime;

        if (preparationProgress <= 1.0f)
        {
            // El perro se inclina hacia atrás en preparación para el salto
            currentDogTilt = 30.0f * preparationProgress; // Inclinación 
            currentDogLean = 15.0f * preparationProgress; 
        }
        else
        {
            // Termina la preparación y comienza el salto
            isPreparing = false;
            isJumping = true;
            jumpProgress = 0.0f;
        }
    }

    // Animación de salto con rotación diagonal - PERRO SALTA ANTES
    if (isJumping)
    {
        jumpProgress += jumpSpeed * deltaTime;

        if (jumpProgress <= 1.0f)
        {
            // PERRO SALTA PRIMERO - en los primeros 0.3 segundos
            if (jumpProgress <= 0.3f)
            {
                float t = jumpProgress / 0.3f; // 0 a 1 en los primeros 0.3
                currentDogHeight = maxJumpHeight * sin(t * glm::pi<float>() * 0.5f);

                // Rotación diagonal durante el salto
                currentDogTilt = 30.0f - 60.0f * t; // De +30° (atrás) a -30° (adelante)
                currentDogLean = 15.0f - 30.0f * t;  // De +15° a -15°
            }
            // PELOTA SALTA DESPUÉS - en los siguientes 0.7 segundos
            else
            {
                float t = (jumpProgress - 0.3f) / 0.7f; // 0 a 1 en los últimos 0.7
                currentBallHeight = maxJumpHeight * sin(t * glm::pi<float>() * 0.5f);

                // El perro comienza a bajar mientras la pelota salta
                currentDogHeight = maxJumpHeight * (1.0f - t);

                // El perro regresa a su posición normal gradualmente
                currentDogTilt = -30.0f * (1.0f - t); // De -30° a 0°
                currentDogLean = -15.0f * (1.0f - t);  // De -15° a 0°
            }
        }
        else
        {
            // Fin del salto, resetear todo
            currentDogHeight = 0.0f;
            currentBallHeight = 0.0f;
            currentDogTilt = 0.0f;
            currentDogLean = 0.0f;
            isJumping = false;
        }
    }
    else if (!isPreparing)
    {
        // Si no hay salto ni preparación, asegurarse de que estén en posición normal
        currentDogHeight = 0.0f;
        currentBallHeight = 0.0f;
        currentDogTilt = 0.0f;
        currentDogLean = 0.0f;
    }
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}