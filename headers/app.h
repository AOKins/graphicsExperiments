#ifndef _MYAPP_H_
#define _MYAPP_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <vector>

#include "object.h"
#include "shader.h"
#include "camera.h"

class application {
protected: 
    bool running;

    SDL_Window * window;
    SDL_GLContext context;    
    shader * shaderApp;

    GLuint * vertexArrayID;
    GLuint * vertexBufferID;
    GLuint * elementBufferID;
    // Dimensions of the window
    int window_width, window_height;
    // Tracker for number of mouse clicks made (left increases, right decreases)
    int mouseClick = 0;

    // Vector that holds object data
    std::vector<object> objects;

    // Camera that user controls
    camera mainCamera;

    // Background color
    GLfloat bg_color[4] = {0.01f,0.001f,0.01f,0.0f};

public:
    // Default constructor, calls initialize and sets running to false
    application();
    ~application();

    // Sets up the window and context, also initialization of GLEW
    void initialize();

    // Handles the start of the application
    void start();

    // Simple loop method that keeps the application running with processing of events and calls render
    void loop();
    
    // Perform the necessarry rendering
    void render(double ctime, double ltime);

    // Processor for an event, identifies the appriopriate handler for an identified event
    void event(SDL_Event * event, double deltaTime);

    // Simple getter for getting running boolean value
    bool isRunning();

    // Handler for when the mouse moves
    void onMouseMove(SDL_MouseMotionEvent * mouse_event);

    // Handler for when a mouse button is pressed
    void onMouseButton(SDL_MouseButtonEvent * button);

    // Handler for when a key press is made
    void onKeyPress(SDL_KeyboardEvent * key_event, double deltaTime);    
    
    void close();

};

#endif