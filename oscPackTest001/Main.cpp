//============================================================================
// Name        : main.cpp
// Author      : Ira Greenberg
// Org         : Center of Creative Computation, SMU
// Description : Protobyte Development Library
// Date        : October 18, 2011
// Version     : .001
// Usage       : Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported

// Library Usage:
// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit 
// http://creativecommons.org/licenses/by-nc-sa/3.0/ 
// or send a letter to Creative Commons, 
// 444 Castro Street, Suite 900, 
// Mountain View, California, 94041, USA.
//============================================================================

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Toroid.h"
#include "Shader.h"
#include "Abacus.h"
#include "CageFrame.h"
#include "Box.h"

// for OSCPack Stuff - not sure what I need yet
#include <cstring>
//#include <cstdlib>
#include "OscReceivedElements.h"
#include "UdpSocket.h"
#include "OscPacketListener.h"

// custom class
#include "OscReceiveListener.h"
#include "OSCReceiver.h"


//============================================================================
// Window variables
//============================================================================
std::string windowTitle = "Protobyte Development Template";
int windowX = 0, windowY = 0;
// projection int windowW = 1024, windowH = 768;
int windowW = 1920, windowH = 1080;
float bgColR = 0.0, bgColG = 0.0, bgColB = 0.0; // range 0.0-1.0

//============================================================================
// Event Variables
//============================================================================
bool isLeftMouseDown, isRightMouseDown, isCenterMouseDown;
bool is1Pressed, is2Pressed, is3Pressed, is4Pressed, is5Pressed, is6Pressed, is7Pressed, is8Pressed, is9Pressed;

int keyID;
bool resetRotate, resetTranslate, resetScale;   // use R, T, S (case insensitive)

bool isLeftArrowDown, isRightArrowDown, isUpArrowDown, isDownArrowDown; // event flags
bool isLeftArrowHot = true, isRightArrowHot = true, isUpArrowHot = true, isDownArrowHot = true; // logic flags
bool isPeriodDown, isCommaDown; // In and Out along z-axis
bool isPeriodHot = true, isCommaHot = true;

// bead details
bool isIDown, isODown; // bead inner, outer radii
bool isIHot = true, isOHot = true;


bool isCommandKeyDown, isOptionKeyDown, isControlKeyDown; // event flags


//============================================================================
// Camera variables
//============================================================================
float viewAngle = 90.0;
float farClippingPlane = 500;
float nearClippingPlane = .1;

// For GLULookAt
//float eyeX = 0.0, eyeY = 2, eyeZ = -.1; // above
float eyeX = 0.0, eyeY = 0.0, eyeZ = 2.0; // straight on
float viewCenterX = 0.0, viewCenterY = 0.0, viewCenterZ = 0.0;
float cameraVectorX = 0.0, cameraVectorY = 1.0, cameraVectorZ = 0.0;

//============================================================================
// Lighting variables
//============================================================================

// Basic 3-point lighting setup (Key, Fill, Back)
// light0 - Key
float light0Ambient[] = { .65, .6, .9, 0 };
float light0Diffuse[] = {.65, .5, .85, 0 }; // warmer
float light0Specular[] = {  1, 1, 1, 0 };
float light0Pos[4] = { 0, 0, 2, 0 };  // 4th arg 0=infinity, 1=position

// light 1 – Fill
float light1Ambient[] = { .4, .4, .4, 1 };
float light1Diffuse[] = {.5, .2, .5, 1 }; // cooler
float light1Specular[] = {1, 1, 1, 1 };
float light1Pos[4] = {.5, -5.2, 5, 0 };  // 4th arg 0=infinity, 1=position

// light 2 – Back
float light2Ambient[] = { 0, 0, 0, 1 };
float light2Diffuse[] = {1, .6, .1, 1 };
float light2Specular[] = {  .9, .4, .0, 1 };
float light2Pos[4] = { 5.5, -50, -1, 0 };  // 4th arg 0=infinity, 1=position

// Materials
float mat_specular[] = { 1.0, .5, 1.0, 1.0 };
float mat_shininess[] = { 128 }; // use range 0 to 128

//============================================================================
// Fog variables
//============================================================================
bool isFogOn = true;
float fogCol[3]={0.0f,0.0f,0.0f}; //
float density = 0.7;
float fogStart = -2.0f;
float fogEnd = 12.0f;

//============================================================================
// Shader variables
//============================================================================
Shader shader;

//============================================================================
// Global translation variables
//============================================================================
float xTran = 0.0, yTran = 1.2, zTran = -6.5; // was -16.5
float xTranSpeed = 0.0, yTranSpeed = 0.0, zTranSpeed = 0.0;

//============================================================================
// Global rotation variables
//============================================================================
float xRotAngle = 0, yRotAngle = 180, zRotAngle = 0;
float xRotSpeed = 0.0, yRotSpeed = 0.0, zRotSpeed = 0.0;

//============================================================================
// Global scale variables
//============================================================================
float xScale = 4.0, yScale = 4.0, zScale = 4.0;
float xScaleSpeed = 0.0, yScaleSpeed = 0.0, zScaleSpeed = 0.0;

//============================================================================
// Animation
//============================================================================
sf::Clock sfml_clock;

//============================================================================
// OSC Stuff
//============================================================================
const int LISTENING_PORT = 12002;
osc::OSCReceiveListener listener;
//OSCReceiver* listener2;
//sf::Mutex globalMutex; // This mutex will be used to synchronize our threads

//============================================================================
// For custom geometry function calls
// ===========================================================================
Toroid* beadDataModel;
Toroid** toroids;

Abacus* abacus;



//CageFrame* frame;
Box* box;



//============================================================================
// function prototypes
//============================================================================
void initOSC(void* userData);
void runKeyEvents(void* userData);
void initGeom();
void display();
void initGL();
void setCamera(int width, int height);
void setLighting();
void setFog();
void setShaders();
void setInteractiveControls();



//============================================================================
// – NEW THREAD - Initialize OSC to MAX
//============================================================================
void initOSC(void* userData){
    
    OSCReceiver listener2("/dataForMatt", abacus);
    UdpListeningReceiveSocket s(IpEndpointName( IpEndpointName::ANY_ADDRESS, LISTENING_PORT ), &listener2);
    
    //globalMutex.Lock();
    // UdpListeningReceiveSocket s( IpEndpointName( IpEndpointName::ANY_ADDRESS,  LISTENING_PORT ), &listener );
    
    std::cout << "listening for input on port " << LISTENING_PORT << "...\n";
    std::cout << "press ctrl-c to end\n";
    
    s.RunUntilSigInt();
    // Unlock the mutex
    //globalMutex.Unlock();
    
    
    std::cout << "finishing.\n";
}


//============================================================================
// – NEW THREAD - key events
//============================================================================
void runKeyEvents(void* userData) {
    
    
    // Start game loop
    while (true)
    {
        sf::Event Event;
        // BEAD INNER | OUTER RADIUS | DIMENSION
        Dimension3d tempDim = beadDataModel->getDim();
        int tempDetail = beadDataModel->getDetail();
        int tempSegs = beadDataModel->getSegs();
        float tempInnerRadius = beadDataModel->getInnerRadius();
        float tempOuterRadius = beadDataModel->getOuterRadius();
        
        if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == 105){  // i: inner Radius++
            tempInnerRadius+=.01;
            abacus->setBeadDataModel(tempDim, tempDetail, tempSegs, tempInnerRadius, tempOuterRadius);
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 107){ // k: inner Radius--
            tempInnerRadius-=.01;
            abacus->setBeadDataModel(tempDim, tempDetail, tempSegs, tempInnerRadius, tempOuterRadius);
            
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 111){ // o: outer Radius++
            tempOuterRadius+=.01;
            abacus->setBeadDataModel(tempDim, tempDetail, tempSegs, tempInnerRadius, tempOuterRadius);
            
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 108){ // l: outer Radius--
            tempOuterRadius-=.01;
            abacus->setBeadDataModel(tempDim, tempDetail, tempSegs, tempInnerRadius, tempOuterRadius);
            
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 113){ // q: Dimension.w++
            tempDim.w +=.01;
            abacus->setBeadDataModel(tempDim, tempDetail, tempSegs, tempInnerRadius, tempOuterRadius);
            
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 97){ // a: Dimension.w++
            tempDim.w -=.01;
            abacus->setBeadDataModel(tempDim, tempDetail, tempSegs, tempInnerRadius, tempOuterRadius);
            
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 119){ // w: Dimension.h++
            tempDim.h +=.01;
            abacus->setBeadDataModel(tempDim, tempDetail, tempSegs, tempInnerRadius, tempOuterRadius);
            
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 115){ // s: Dimension.h++
            tempDim.h -=.01;
            abacus->setBeadDataModel(tempDim, tempDetail, tempSegs, tempInnerRadius, tempOuterRadius);
            
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 101){ // e: Dimension.w++
            tempDim.d +=.01;
            abacus->setBeadDataModel(tempDim, tempDetail, tempSegs, tempInnerRadius, tempOuterRadius);
            
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 100){ // d: Dimension.w++
            tempDim.d -=.01;
            abacus->setBeadDataModel(tempDim, tempDetail, tempSegs, tempInnerRadius, tempOuterRadius);
            
        }
        
        
    }
    
    
    
    
}


//============================================================================
// Set Some GL states
//============================================================================
void initGL(){
    
    // Explicitely set face winding rule
    glFrontFace(GL_CCW); // or GL_CW
    
    // Hide back faces of surfaces
    glEnable(GL_CULL_FACE);
    
    // enable alpha - requires faces drawn back to front
    // not fully implemented
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Enable Shading style
    glShadeModel(GL_SMOOTH);
    //glShadeModel(GL_FLAT);
    
    // Enable Primitive smoothing
    //glEnable (GL_POLYGON_SMOOTH);  // legacy not recommended use FSAA
    //glEnable (GL_LINE_SMOOTH); // legacy not recommended, also not doing much
    glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE); // not doing much
    //glBlendFunc (GL_SRC_ALPHA_SATURATE, GL_ONE);
    
    // Black Background
    glClearColor(bgColR, bgColG, bgColB, .5);
    
    // Depth Buffer Setup
    glClearDepth(1.0f);
    
    // Enables Depth Testing
    // Draw surfaces based on their distance to the camera,
    // NOT based on their order drawn
    glEnable(GL_DEPTH_TEST);
    
    // The Type Of Depth Testing To Do
    glDepthFunc(GL_LEQUAL);
    
    // Really Nice Perspective Calculations
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    // glEnable(GL_POINT_SIZE);
    // glEnable(GL_LINE_WIDTH);
    // glPointSize(1);
    // glLineWidth(1);
    glEnable(GL_NORMALIZE);
    
}

//============================================================================
// Draw stuff to screen here
//============================================================================
void display() {
    
    
    sf::WindowSettings Settings;
    Settings.DepthBits         = 24; // Request a 24 bits depth buffer
    Settings.StencilBits       = 8;  // Request a 8 bits stencil buffer
    Settings.AntialiasingLevel = 2;  // Request 2 levels of antialiasing
    
    
    sf::Window app(sf::VideoMode(windowW, windowH, 32), windowTitle, sf::Style::Close, Settings);
    app.Create(sf::VideoMode::GetMode(0), "SFML Window", sf::Style::Fullscreen);
    
    //app.SetFramerateLimit(260);
    
    // need Input reference for interactive events
    const sf::Input& Input = app.GetInput();
    
    // initialize some GL states
    initGL();
    
    // set projection
    setCamera(windowW, windowH);
    
    // set lighting
    setLighting();
    
    // set up fog
    //setFog();
    
    // set Shaders
    setShaders();
    
    
    
    // time acccurate approach
    sf::Clock Clock;
    
    //const float Speed = .01f;
    //float Left = 0.f, Right = 0.f;
    //float Top  = 0.f;
    
    
    // Start game loop
    while (app.IsOpened())
    {
        float ElapsedTime = Clock.GetElapsedTime();
        Clock.Reset();
        
        /*if (app.GetInput().IsKeyDown(sf::Key::Left))  Left -= Speed * ElapsedTime;
         if (app.GetInput().IsKeyDown(sf::Key::Right)) Right += Speed * ElapsedTime;
         if (app.GetInput().IsKeyDown(sf::Key::Up))    Top  -= Speed * ElapsedTime;
         if (app.GetInput().IsKeyDown(sf::Key::Down))  Top  += Speed * ElapsedTime;*/
        
        
        
        
        float Framerate = 1.f / app.GetFrameTime();
        //std::cout << "Framerate = " << Framerate << std::endl;
        //std::cout << "ElapsedTime = " << ElapsedTime << std::endl;
        
        
        
        // Process events
        sf::Event Event;
        while (app.GetEvent(Event))
        {
            
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                app.Close();
            
            // Escape key : exit
            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
                app.Close();
            
            // Resize event : adjust viewport
            if (Event.Type == sf::Event::Resized)
                glViewport(0, 0, Event.Size.Width, Event.Size.Height);
        }
        
        
        // Capture keyboard and mouse events
        isLeftArrowDown = Input.IsKeyDown(sf::Key::Left);
        isRightArrowDown = Input.IsKeyDown(sf::Key::Right);
        isUpArrowDown = Input.IsKeyDown(sf::Key::Up);
        isDownArrowDown = Input.IsKeyDown(sf::Key::Down);
        
        isPeriodDown = Input.IsKeyDown(sf::Key::Period);
        isCommaDown = Input.IsKeyDown(sf::Key::Comma);
        
        isIDown = Input.IsKeyDown(sf::Key::Period);
        isODown = Input.IsKeyDown(sf::Key::Period); 
        
        
        
        
        
        //Event.Text.Unicode;
        
        //isLeftMouseDown = Input.IsMouseButtonDown(sf::Mouse::Left);
        //isRightMouseDown = Input.IsMouseButtonDown(sf::Mouse::Right);
        
        // Y-AXIS ROTATION
        if(isLeftArrowDown){
            if (isLeftArrowHot) {
                isLeftArrowHot = false;
                yRotSpeed -= .001;
            }
        } else {
            isLeftArrowHot = true;
        }
        
        if(isRightArrowDown){
            if (isRightArrowHot) {
                isRightArrowHot = false;
                yRotSpeed += .001;
            }
        } else {
            isRightArrowHot = true;
        }
        
        
        // X-AXIS ROTAION
        if(isUpArrowDown){
            if (isUpArrowHot) {
                isUpArrowHot = false;
                xRotSpeed -= .001;
            }
        } else {
            isUpArrowHot = true;
        }
        
        if(isDownArrowDown){
            if (isDownArrowHot) {
                isDownArrowHot = false;
                xRotSpeed += .001;
            }
        } else {
            isDownArrowHot = true;
        }
        
        
        // ZOOM
        if(isPeriodDown){
            if (isPeriodHot) {
                isPeriodHot = false;
                zTranSpeed -= .001;
            }
        } else {
            isPeriodHot = true;
        }
        
        if(isCommaDown){
            if (isCommaHot) {
                isCommaHot = false;
                zTranSpeed += .001;
            }
        } else {
            isCommaHot = true;
        }
        
        // TEST REMOVE BELOW
        /*if (Event.Type == sf::Event::KeyPressed){
         Dimension3d tempDim = beadDataModel->getDim();
         int tempDetail = beadDataModel->getDetail();
         int tempSegs = beadDataModel->getSegs();
         float tempInnerRadius = beadDataModel->getInnerRadius();
         float tempOuterRadius = beadDataModel->getOuterRadius();
         
         int code  = Event.Key.Code;
         if(Event.Key.Code == 105){ // i: inner Radius++
         tempInnerRadius+=.01;
         }
         // this slows stuff down
         //abacus->setBeadDataModel(tempDim, tempDetail, tempSegs, tempInnerRadius, tempOuterRadius);
         }*/
        // TEST REMOVE ABOVE
        
        // if (Event.Type == sf::Event::KeyPressed){
        // std::cout << "key code = " << Event.Key.Code << std::endl;
        //}
        // BEAD INNER | OUTER RADIUS | DIMENSION
        Dimension3d tempDim = beadDataModel->getDim();
        int tempBeadDetail = beadDataModel->getDetail();
        int tempBeadSegs = beadDataModel->getSegs();
        
        float tempInnerRadius = beadDataModel->getInnerRadius();
        float tempOuterRadius = beadDataModel->getOuterRadius();
        
        double tempAmpBoost = abacus->getAmpBoost();
        double tempBeadJitterY = abacus->getBeadJitterY();
        double tempBeadJitterX = abacus->getBeadJitterX();
        
        float tempBeadScaler = abacus->getBeadScaler();
        
        if (Event.Type == sf::Event::KeyPressed && Event.Key.Code == 105){
            tempInnerRadius+=.01;
            abacus->setBeadInnerRadius(tempInnerRadius);
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 107){ // k: inner Radius--
            tempInnerRadius-=.01;
            abacus->setBeadInnerRadius(tempInnerRadius);
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 111){ // o: outer Radius++
            tempOuterRadius+=.01;
            abacus->setBeadOuterRadius(tempOuterRadius);
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 108){ // l: outer Radius--
            tempOuterRadius-=.01;
            abacus->setBeadOuterRadius(tempOuterRadius);
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 113){ // q: Dimension.w++
            tempDim.w +=.001;
            abacus->setBeadDim(tempDim);
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 97){ // a: Dimension.w++
            tempDim.w -=.001;
            abacus->setBeadDim(tempDim);
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 119){ // w: Dimension.h++
            tempDim.h +=.001;
            abacus->setBeadDim(tempDim);
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 115){ // s: Dimension.h++
            tempDim.h -=.001;
            abacus->setBeadDim(tempDim);
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 101){ // e: Dimension.w++
            tempDim.d +=.001;
            abacus->setBeadDim(tempDim);
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 100){ // d: Dimension.w++
            tempDim.d -=.001;
            abacus->setBeadDim(tempDim);
        }  else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 114){ // r: Abacus amp Boost ++
            tempAmpBoost +=.01;
            abacus->setAmpBoost(tempAmpBoost);
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 102){ // f: Abacus amp Boost --
            tempAmpBoost -=.01;
            abacus->setAmpBoost(tempAmpBoost);
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 116 ){ // t: bead JitterY amp Boost ++
            tempBeadJitterY +=.01;
            abacus->setBeadJitterY(tempBeadJitterY);
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 103){ // g: bead JitterY amp Boost --
            tempBeadJitterY -=.01;
            abacus->setBeadJitterY(tempBeadJitterY);
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 121){ // y: bead JitterX amp Boost ++
            tempBeadJitterX +=.01;
            abacus->setBeadJitterX(tempBeadJitterX);
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 104){ // h: bead JitterX amp Boost --
            tempBeadJitterX -=.01;
            abacus->setBeadJitterX(tempBeadJitterX);
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 109){ // m: bead scaler ++
           tempBeadScaler++;
           abacus->setBeadScaler(tempBeadScaler);
        } else  if(Event.Type == sf::Event::KeyPressed &&Event.Key.Code == 110){ // n: bead scaler --
            tempBeadScaler--;
            abacus->setBeadScaler(tempBeadScaler);
        } 
        
        
        // Set the active window before using OpenGL commands
        // It's useless here because active window is always the same,
        // but don't forget it if you use multiple windows or controls
        app.SetActive();
        
        // alter drawing context postion or size
        glViewport(windowX, windowY, windowW, windowH);
        
        // Clear buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Set new background color on clear
        glClearColor(bgColR, bgColG, bgColB, 0.0);
        
        
        // Apply some transformations
        glMatrixMode(GL_MODELVIEW);
        
        // Restore identity matrix
        // - resets  transformations (translate, rotate and scale) each frame
        // 1 | 0 | 0 | 0
        // 0 | 1 | 0 | 0
        // 0 | 0 | 1 | 0
        // 0 | 0 | 1 | 1
        glLoadIdentity();
        
        glPushMatrix();
        
        // Global translation - move stuff
        glTranslatef(xTran, yTran, zTran);
        
        // Global rotation - spin stuff
        
        
        glRotatef(xRotAngle,1.0,0.0,0.0);
        glRotatef(yRotAngle,0.0,1.0,0.0);
        glRotatef(zRotAngle,0.0,0.0,1.0);
        //
        
        // Global scale - resize stuff
        //glScalef(xScale, yScale, zScale);
        
        //==============================//
        //=== BEGIN CUSTOM GEOM DRAW ===//
        //==============================//
        
        //abacus->setAmplitudeByID(listener.getID(), listener.getAmp());
        shader.bind();
        abacus->display();
        shader.unbind();
        
        //=============================//
        //==== END DRAW STUFF HERE ====//
        //=============================//
        glPopMatrix();
        
        
        // Update global transformations
        xTran += xTranSpeed;
        yTran += yTranSpeed;
        zTran += zTranSpeed;
        
        // rotate everything in window
        xRotAngle += xRotSpeed;
        yRotAngle += yRotSpeed;
        zRotAngle += zRotSpeed;
        
        // scale everything in window
        xScale += xScaleSpeed;
        yScale += yScaleSpeed;
        zScale += zScaleSpeed;
        
        //display rendered frame on screen
        app.Display();
        
    }
    
}



//============================================================================
// initialize your custom drawing objects here
//============================================================================
void initGeom() {
    //Toroid(Vector3df loc, Dimension3d dim, int detail, int segs, float innerRadius, float outerRadius):
    beadDataModel = new Toroid(Vector3df(), Dimension3d(.23, .25, .23), 9, 9, .2, .7);
    abacus = new Abacus(Vector3df(), Dimension3d(24.7, 7, 20.8), Tuple3d(9, 9, 9),  Dimension3d(.09, .09, .09), beadDataModel);
}

//============================================================================
// Set up the Camera
//============================================================================
void setCamera(int w, int h){
    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(viewAngle, w/h, nearClippingPlane, farClippingPlane);
    
    // you can move as a virtual camera
    gluLookAt(eyeX, eyeY, eyeZ,                                     // eye x,y,z
              viewCenterX, viewCenterY, viewCenterZ,                // center x,y,z
              cameraVectorX, cameraVectorY, cameraVectorZ);         // Up direction
    
};

//============================================================================
// Set up the lighting
//============================================================================
void setLighting(){
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColorMaterial(GL_FRONT,GL_DIFFUSE);
    //glColorMaterial(GL_FRONT,GL_AMBIENT);
    
    // light0
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
    
    // light1
    glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1Specular);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ambient);
    
    // light2
    glLightfv(GL_LIGHT2, GL_POSITION, light2Pos);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light2Specular);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light2Ambient);
    
    
    // enable the lights/materials
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_SPECULAR);
    glEnable(GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_LIGHTING);
    
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    
}

//============================================================================
// Set up Fog
//============================================================================
void setFog(){
    if(isFogOn){
        // Turn On Fog
        glFogfv(GL_FOG_COLOR, fogCol);
        
        //linear
        glFogi(GL_FOG_MODE,GL_LINEAR);
        glFogi(GL_FOG_START,fogStart);
        glFogi(GL_FOG_END,fogEnd);
        
        // exponential
        //glFogi (GL_FOG_MODE, GL_EXP);//set the fog mode to GL_EXP
        //glFogf(GL_FOG_DENSITY,0.1f);  // Thin the fog out a little
        
        // set the fog to look the nicest, may slow down on older cards
        glHint (GL_FOG_HINT, GL_NICEST);         
        glEnable(GL_FOG);
    }
}

//============================================================================
// Set up shaders
//============================================================================
void setShaders(){
    //const char* vert = "/Users/iragreenberg/Documents/Code/C++/ProtoLib/shaders/shader.vert";
    //const char* frag = "/Users/iragreenberg/Documents/Code/C++/ProtoLib/shaders/shader.frag";
    const char* vert = "/Users/iragreenberg/Dropbox/C3/syzergy/ProtoLib/shaders/shader.vert";
    const char* frag = "/Users/iragreenberg/Dropbox/C3/syzergy/ProtoLib/shaders/shader.frag";
    shader = Shader();
    shader.init(vert, frag);
}

//============================================================================
// Set runtime interactive control
//============================================================================
void setInteractiveControls() {
    
    
    
}


//============================================================================
// main function
//============================================================================
int main (int argc, char **argv) {
    
    
    // User defined initialization
    initGeom();
    
    // call back to process OSC in its own thread
    sf::Thread thread(&initOSC);
    sf::Thread keyEventThread(&runKeyEvents);
    
    
    // Start SFML context in new Thread
    // Start Listening to MAX
    thread.Launch();
    //keyEventThread.Launch();
    
    
    // start dsiplay loop
    display();
    
    
    // required in main
    return 0;
}
