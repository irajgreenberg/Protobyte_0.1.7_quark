/*!  \brief  ProtoWorld.cpp: Top Level Master class
 ProtoWorld.cpp
 Protobyte Library v02
 
 Created by Ira on 7/25/13.
 Copyright (c) 2013 Ira Greenberg. All rights reserved.
 
 Library Usage:
 This work is licensed under the Creative Commons
 Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 To view a copy of this license, visit
 http://creativecommons.org/licenses/by-nc-sa/3.0/
 or send a letter to Creative Commons,
 444 Castro Street, Suite 900,
 Mountain View, California, 94041, USA.
 
 This notice must be retained any source distribution.
 
 \ingroup common
 This class is part of the group common (update)
 \sa NO LINK
 
 http://www.avid-insight.co.uk/2009/11/opengl-gotcha-remember-gl_light0/ nice blog about 
 order of ops with camera/lights
 */

#include "ProtoWorld.h"



namespace ijg {
    std::ostream& operator<<(std::ostream& out, const ProtoWorld& protoWorld){
        out << "ijg::protoWorld@"<< &protoWorld;
        return out;
    }
}

using namespace ijg;

//ProtoWorld* ProtoWorld::singletonWorld = nullptr;
//std::once_flag ProtoWorld::protoOnceFlag;

float counter = 0;
// initialize static vars
// cameras
unsigned char ProtoWorld::cameraCount=0;
const unsigned char ProtoWorld::CAMERA_COUNT_MAX=4;

//Lights
unsigned char ProtoWorld::lightCount=0;
const unsigned char ProtoWorld::LIGHT_COUNT_MAX=8;


ProtoBoundsf ProtoWorld::canvasBounds = ProtoBoundsf(0,0,0,0);
// added comment for git test


// cstr
ProtoWorld::ProtoWorld(){
    
    worldRotSpeed = Vec3f(0,0,0);
    worldView = SINGLE_VIEW;
    activeCamera = 0;
    
    
    setDefaultProjection();
    init();
}

// cstr
ProtoWorld::ProtoWorld(float canvasWidth, float canvasHeight):
canvasWidth(canvasWidth), canvasHeight(canvasHeight){
    worldRotSpeed = Vec3f(0,0,0);
    init();
}


void ProtoWorld::init(){
    glLights[0] = GL_LIGHT0;
    glLights[1] = GL_LIGHT1;
    glLights[2] = GL_LIGHT2;
    glLights[3] = GL_LIGHT3;
    glLights[4] = GL_LIGHT4;
    glLights[5] = GL_LIGHT5;
    glLights[6] = GL_LIGHT6;
    glLights[7] = GL_LIGHT7;
}

void ProtoWorld::add(std::unique_ptr<ProtoCamera> camera){
	trace("add(camera) called???? =");
    assert(static_cast<int>(ProtoWorld::cameraCount)<= 4);
    
    if(ProtoWorld::cameraCount < ProtoWorld::CAMERA_COUNT_MAX){
        camera->setName("cam_"+ std::to_string(ProtoWorld::cameraCount));
        cameras.push_back(std::move(camera)); // change ownership
        ProtoWorld::cameraCount++;
    }
    for(int i=0; i<cameras.size(); ++i){
        //std::cout << "cameras.at("<<i<<")->getName() = " << cameras.at(i)->getName() << std::endl;
    }
    //std::cout << "ProtoWorld::cameraCount = "<< static_cast<int>(ProtoWorld::cameraCount) << std::endl;
}

void ProtoWorld::add(std::unique_ptr<ProtoGeom3> geomObj) {
    geoms.push_back(std::move(geomObj)); // change ownership
    //std::cout << " geomObj added @ " << &geomObj << std::endl;
}

void ProtoWorld::add(std::shared_ptr<ProtoGeom3> geomObj) {
    // std::cout << " geomObj added @ " << &geomObj << std::endl;
    sharedGeoms.push_back(geomObj); // change ownership
}

// not sure this is a good idea
void ProtoWorld::add(const ProtoGeom3* geomObj) {
}


//void ProtoWorld::remove(ProtoCamera* camera){
//    if(cameras.size()>0){
//        for(cameraObjsIter=cameras.begin(); cameraObjsIter < cameras.end(); ++cameraObjsIter){
//            if( (*cameraObjsIter)->getUniqueID() == camera->getUniqueID()){
//                cameras.erase(cameraObjsIter);
//
//            }
//        }
//    }
//    std::cout << "cameras.size() = " << cameras.size() << std::endl;
//}


// Lighting handled through world
void ProtoWorld::setDiffuse(Light lightID, const ProtoColor4f& color, const ProtoColor4f& material){
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    
}
void ProtoWorld::setSpecular(Light lightID, const ProtoColor4f& color, const ProtoColor4f& material, float shininess){
    
}
void ProtoWorld::setShininess(float shininess){
    
}
void ProtoWorld::setAmbient(Light lightID, const ProtoColor4f& color, const ProtoColor4f& material){
    
}
void ProtoWorld::setEmission(Light lightID, const ProtoColor4f& color, const ProtoColor4f& material){
    
}


// add Shared pointer lights
void ProtoWorld::add(std::shared_ptr<ProtoLight> light){
    
    if (lights.size() < LIGHT_COUNT_MAX){
        lights.push_back(light);
    } else {
        std::cout << "WARNING: ProtoWorld includes 8 lights, wthe maximum number allowed.\n";
    }
}


// run world
void ProtoWorld::run() {
	//trace("In World RUN()");
    // if animated
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    

    
    //std::cout << "geoms = " << &geoms << std::endl;
    
   //glMatrixMode(GL_MODELVIEW);
    // uncomment glLoadIdentity to allow rotated but not animated state
    // glLoadIdentity();
    // world rot speed
    //    glRotatef(worldRotSpeed.x, 1, 0, 0);
    //    glRotatef(worldRotSpeed.y, 0, 1, 0);
    //    glRotatef(worldRotSpeed.z, 0, 0, 1);
    
    switch(worldView){
            
        case SINGLE_VIEW:
            glPushMatrix();
        {
            // if there no camera there is probably a reason ;-)
				// NOTE I need to eventually re think this whole design approach:
				// quesitons: 
				// 1. Do I want a world/camera abstraction
				// 2. Should there be a a simple "newbie" default world setup?
				// 3. These questions arose when I needed to print high res images
				// and needed more low level access ton controlling underlying transform matrices
				// I can probably have all these working together, but I need a plan/design
				if (cameras.size()==0){
              
               // trace("*********** Camera size = 0 ***********");
                //std::unique_ptr<protocamera> camera1(new protocamera());
                //add(std::move(camera1));
                //cameras.at(0)->setviewport(0, 0, canvaswidth, canvasheight); // mpt really needed
                //cameras.at(0)->setprojection(fovangle, canvaswidth/canvasheight, nearclipplane, farclipplane);
                //cameras.at(0)->project();
                
                // FIX THIS EVENTUALLY - hard coded 0 instead of using activeCamera ***********************************
            } else {
			//	trace("*********** Camera size = 1 ***********");
                cameras.at(0)->setViewPort(0, 0, canvasWidth, canvasHeight); // scale to window coords
                cameras.at(0)->project(); // project to normalized screen coords
            }
            
            
            // draw geometry
            draw();
        }
            glPopMatrix();
            
            break;
        case DOUBLE_VIEW_LANDSCAPE:
            glPushMatrix();
        {
            if (cameras.size()==0){
                std::unique_ptr<ProtoCamera> camera1(new ProtoCamera());
                add(std::move(camera1));
                std::unique_ptr<ProtoCamera> camera2(new ProtoCamera());
                add(std::move(camera2));
                
                // top
                cameras.at(0)->setViewPort(0, canvasHeight/2, canvasWidth, canvasHeight/2);
                cameras.at(0)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(0)->project();
                // draw geometry
                draw();
                
                
                // bottom
                cameras.at(1)->setViewPort(0, 0, canvasWidth, canvasHeight/2);
                cameras.at(1)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(1)->project();
                // draw geometry
                draw();
                
                
            } else if (cameras.size()==1){
                std::unique_ptr<ProtoCamera> camera2(new ProtoCamera());
                add(std::move(camera2));
                
                // top
                cameras.at(0)->setViewPort(0, canvasHeight/2, canvasWidth, canvasHeight/2);
                cameras.at(0)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(0)->project();
                // draw geometry
                draw();
                
                
                // bottom
                cameras.at(1)->setViewPort(0, 0, canvasWidth, canvasHeight/2);
                cameras.at(1)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(1)->project();
                // draw geometry
                draw();
                
            } else {
                
                //cameras.at(0)->setViewPort(0, canvasHeight/2, canvasWidth, canvasHeight/2);
                cameras.at(0)->project();
                // draw geometry
                draw();
                
                //cameras.at(1)->setViewPort(0, 0, canvasWidth, canvasHeight/2);
                cameras.at(1)->project();
                // draw geometry
                draw();
                
            }
        }
            glPopMatrix();
            
            break;
        case DOUBLE_VIEW_PORTRAIT:
            glPushMatrix();
        {
            if (cameras.size()==0){
                std::unique_ptr<ProtoCamera> camera1(new ProtoCamera());
                add(std::move(camera1));
                std::unique_ptr<ProtoCamera> camera2(new ProtoCamera());
                add(std::move(camera2));
                
                // Left
                cameras.at(0)->setViewPort(0, 0, canvasWidth/2, canvasHeight);
                cameras.at(0)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(0)->project();
                // draw geometry
                draw();
                
                
                // Right
                cameras.at(1)->setViewPort(canvasWidth/2, 0, canvasWidth/2, canvasHeight);
                cameras.at(1)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(1)->project();
                // draw geometry
                draw();
                
                
            } else if (cameras.size()==1){
                std::unique_ptr<ProtoCamera> camera2(new ProtoCamera());
                add(std::move(camera2));
                
                // Left
                cameras.at(0)->setViewPort(0, 0, canvasWidth/2, canvasHeight);
                cameras.at(0)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(0)->project();
                // draw geometry
                draw();
                
                
                // Right
                cameras.at(1)->setViewPort(canvasWidth/2, 0, canvasWidth/2, canvasHeight);
                cameras.at(1)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(1)->project();
                // draw geometry
                draw();
                
            } else {
                //cameras.at(0)->setViewPort(0, 0, canvasWidth/2, canvasHeight);
                cameras.at(0)->project();
                // draw geometry
                draw();
                
                //cameras.at(1)->setViewPort(canvasWidth/2, 0, canvasWidth/2, canvasHeight);
                cameras.at(1)->project();
                // draw geometry
                draw();
                
            }
        }
            glPopMatrix();
            
            break;
            
            
            
        case QUAD_VIEW:
            // right now only handle 0 or 4 cameras
            if (cameras.size() == 4){ // cameras are already loaded
                
                // check bottom left camera for viewport
                //                if (cameras.at(0)->getViewPort().x == 0 && cameras.at(0)->getViewPort().y == 0 &&
                //                    cameras.at(0)->getViewPort().w == 0 && cameras.at(0)->getViewPort().h == 0){
                //
                //                    //cameras.at(0)->setViewPort(0, 0, canvasWidth/2, canvasHeight/2);
                //                }
                //
                //                if (cameras.at(1)->getViewPort().x == 0 && cameras.at(0)->getViewPort().y == 0 &&
                //                    cameras.at(1)->getViewPort().w == 0 && cameras.at(0)->getViewPort().h == 0){
                //
                //                    //cameras.at(1)->setViewPort(0, canvasHeight/2, canvasWidth/2, canvasHeight/2); //TL
                //                }
                //
                //                if (cameras.at(2)->getViewPort().x == 0 && cameras.at(0)->getViewPort().y == 0 &&
                //                    cameras.at(2)->getViewPort().w == 0 && cameras.at(0)->getViewPort().h == 0){
                //
                //                    //cameras.at(2)->setViewPort(canvasWidth/2, canvasHeight/2, canvasWidth/2, canvasHeight/2); //TR
                //                }
                //
                //                if (cameras.at(3)->getViewPort().x == 0 && cameras.at(0)->getViewPort().y == 0 &&
                //                    cameras.at(3)->getViewPort().w == 0 && cameras.at(0)->getViewPort().h == 0){
                //
                //                    // cameras.at(3)->setViewPort(canvasWidth/2, 0, canvasWidth/2, canvasHeight/2); //BR
                //                }
                
                cameras.at(0)->project();
                draw();
                cameras.at(1)->project();
                draw();
                cameras.at(2)->project();
                draw();
                cameras.at(3)->project();
                draw();
                
            } else {
                while (cameras.size()<4) { // create camera since none exists
                    std::unique_ptr<ProtoCamera> camera1(new ProtoCamera());
                    add(std::move(camera1));
                    std::cout << "camera size = " << cameras.size() << std::endl;
                }
                
                cameras.at(0)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(0)->setViewPort(0, 0, canvasWidth/2, canvasHeight/2); //BL
                cameras.at(0)->project();
                draw();
                
                cameras.at(1)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(1)->setViewPort(0, canvasHeight/2, canvasWidth/2, canvasHeight/2); //TL
                cameras.at(1)->project();
                draw();
                
                cameras.at(2)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(2)->setViewPort(canvasWidth/2, canvasHeight/2, canvasWidth/2, canvasHeight/2); //TR
                cameras.at(2)->project();
                draw();
                
                cameras.at(3)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(3)->setViewPort(canvasWidth/2, 0, canvasWidth/2, canvasHeight/2); //BR
                cameras.at(3)->project();
                draw();
                
            }
            
            
    }
    
    /**************************************************
     *                   LIGHTING                     *
     *************************************************/
    
    //test
    for(std::size_t i=0; i<lights.size(); ++i){
        if(lights.at(i)->getIsOn()){
           // std::cout << "light " << i << "is on" << std::endl;
            glEnable(glLights[i]);
            
            // set Lights
            float position[4] = {
                lights.at(i)->getPosition().x,
                lights.at(i)->getPosition().y,
                lights.at(i)->getPosition().z,
                0
            };
            
            float diffuse[4] = {
                lights.at(i)->getDiffuse().getR(),
                lights.at(i)->getDiffuse().getG(),
                lights.at(i)->getDiffuse().getB(),
                lights.at(i)->getDiffuse().getA()
            };
            
            float ambient[4] = {
                lights.at(i)->getAmbient().getR(),
                lights.at(i)->getAmbient().getG(),
                lights.at(i)->getAmbient().getB(),
                lights.at(i)->getAmbient().getA()
            };
            
            float specular[4] = {
                lights.at(i)->getSpecular().getR(),
                lights.at(i)->getSpecular().getG(),
                lights.at(i)->getSpecular().getB(),
                lights.at(i)->getSpecular().getA()
            };
            
           // glPushMatrix();
           // glMatrixMode(GL_MODELVIEW);
           // glLoadIdentity();

            glLightfv(glLights[i], GL_POSITION, position);
           // glPopMatrix();
            
            glLightfv(glLights[i], GL_AMBIENT, ambient);
            glLightfv(glLights[i], GL_DIFFUSE, diffuse);
            glLightfv(glLights[i], GL_SPECULAR, specular);
            
            
        } else {
            glDisable(glLights[i]);
        }
    }
    

    
}

// stop world
void ProtoWorld::stop(){
}

void ProtoWorld::draw() {
    
    
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //std::cout << "in world draw" << std::endl;
    // utlize shader
    //shader.bind();
    for(int i=0; i<geoms.size(); ++i){
        //std::cout << "geoms.size() = " << geoms.size() << std::endl;
        //renderer->draw(geoms.at(i));
        //geoms.at(i)->display(ProtoGeom3::VERTEX_BUFFER_OBJECT, ProtoGeom3::SURFACE);
    }
    
    
    
    for(int i=0; i<sharedGeoms.size(); ++i){
        //sharedGeoms.at(i)->display(ProtoGeom3::VERTEX_BUFFER_OBJECT, ProtoGeom3::SURFACE);
    }
    // shader.unbind();
}

void ProtoWorld::rotate(const Vec3f& worldRot) {
    
}

void ProtoWorld::setWorldRotSpeed(const Vec3f& worldRotSpeed){
    this->worldRotSpeed = worldRotSpeed;
}

void ProtoWorld::setDefaultProjection(float fovAngle, float nearClipPlane, float farClipPlane) {
    this->fovAngle = fovAngle;
    this->nearClipPlane = nearClipPlane;
    this->farClipPlane = farClipPlane;
}

void ProtoWorld::setWorldView(WorldView worldView){
    this->worldView = worldView;
    
}

void ProtoWorld::setActiveCamera(int activeCamera){
    this->activeCamera = activeCamera;
}

// set states
//void setRenderState(ProtoRenderer::RenderModeEnum renderMode, float pointSize) {
//   // this->renderMode = renderMode;
//}

//void ProtoWorld::setLights() {
//    
//    /**********************************
//     *           LIGHTING             *
//     *********************************/
//    // Light01
//    GLfloat light01_ambient[] = {0.2, 0.2, 0.2, 1.0};
//    GLfloat light01_diffuse[] = {.65, .65, .65, 1.0};
//    GLfloat light01_specular[] = {.8, .8, .8, 1.0};
//    GLfloat light01_position[] = {-20, 10, 5.0, 0.0};
//    
//    //materials
//    GLfloat light01_mat_specular[] = {.85, .8, .92, 1.0};
//    GLfloat light01_mat_shininess[] = {18}; // max 128
//    
//    
//    // light 01
//    glMaterialfv(GL_FRONT, GL_SPECULAR, light01_mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, light01_mat_shininess);
//    
//    glLightfv(GL_LIGHT0, GL_AMBIENT, light01_ambient);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, light01_diffuse);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, light01_specular);
//    glLightfv(GL_LIGHT0, GL_POSITION, light01_position);
//    
//    
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//}

void ProtoWorld::updateCanvasSize(float canvasWidth, float canvasHeight){
    this->canvasWidth = canvasWidth;
    this->canvasHeight = canvasHeight;
    //std::cout << "cameras.size() = " << cameras.size() << std::endl;
    
    
    if(ProtoWorld::QUAD_VIEW){
        if(cameras.size()==4){
            cameras.at(0)->setAspectRatio(canvasWidth/canvasHeight);
            cameras.at(1)->setAspectRatio(canvasWidth/canvasHeight);
            cameras.at(2)->setAspectRatio(canvasWidth/canvasHeight);
            cameras.at(3)->setAspectRatio(canvasWidth/canvasHeight);
            
            cameras.at(0)->setViewPort(0, 0, canvasWidth/2,canvasHeight/2);
            cameras.at(1)->setViewPort(0, canvasHeight/2, canvasWidth/2, canvasHeight/2);
            cameras.at(2)->setViewPort(canvasWidth/2, canvasHeight/2, canvasWidth/2, canvasHeight/2);
            cameras.at(3)->setViewPort(canvasWidth/2, 0, canvasWidth/2, canvasHeight/2);
        }
    }
}

int ProtoWorld::getGeomCount() {
    return static_cast<int>(geoms.size());
}




/****************************************************
 *** global convenience functions Implementations ***
 ***************************************************/

namespace ijg {
    // single geometric obj
    //    void add(ProtoGeom3* geomObj){
    //        ProtoWorld* w = ProtoWorld::getInstance();
    //        w->add(geomObj);
    //    }
    
    // ADD ProtoGeomComposite pointers
    //void add(ProtoGeomComposite* compositeObj); // composite geometric obj
    
    // ADD shared pointer
    void add(std::shared_ptr<ProtoGeom3> geomObj){}
    
    // ADD raw pointer
    void add(const ProtoGeom3* geomObj){}
    
    //+++++ CAMERA +++++
    // ADD camera obs
    void add(std::unique_ptr<ProtoCamera> camera){}
    
    //+++++ LIGHTS +++++
    void add(std::unique_ptr<ProtoLight> light){}
    
    void add(ProtoLight* light){}
}

/************************************
 *** END function implementations ***
 ***********************************/





