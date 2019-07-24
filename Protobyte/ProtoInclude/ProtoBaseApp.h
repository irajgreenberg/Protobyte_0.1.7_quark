#ifndef _PROTO_BASEAPP_H_
#define _PROTO_BASEAPP_H_

#include "poly2tri.h" // tesselator not currently utilized
#include <thread>
#include <mutex>
#include <memory>
#include <stdexcept>

// include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

// add Protobyte core classes
#include "ProtoContext.h";
#include "ProtoDimension2.h"
#include "ProtoDimension3.h"
#include "ProtoPlane.h"
#include "ProtoGroundPlane.h"
#include "ProtoTransformFunction.h"
#include "ProtoTexture.h"
#include "ProtoShader.h"
#include "ProtoColor3.h"
#include "ProtoColor4.h"
#include "ProtoBlock.h"
#include "ProtoLathe.h"
#include "ProtoMath.h"
#include "ProtoVector2.h"
#include "ProtoVector3.h"
#include "ProtoCylinder.h"
#include "ProtoToroid.h"
#include "ProtoSpline3.h"
#include "ProtoSphere.h"
#include "ProtoTube.h"
#include "ProtoLight.h"
#include "ProtoCore.h"
#include "ProtoTuple4.h"
#include "ProtoEllipse.h"
#include "ProtoPath3.h"
#include "ProtoPath2.h"
#include "ProtoRectangle.h"
#include "ProtoException.h"
//#include "ProtoJuncusEffusus.h"
//#include "ProtoCephalopod.h"

// preproc dir for relative resource loading
// from http://stackoverflow.com/questions/143174/how-do-i-get-the-directory-that-a-program-is-running-from
// http://www.daniweb.com/software-development/cpp/threads/202937/ifdef-with-boolean-and-or
//#include <stdio.h>  /* defines FILENAME_MAX */
//#if defined (_WIN32) || defined (_WIN64)
//#include <direct.h>
//#define GetCurrentDir _getcwd
//#else
//#include <unistd.h>
//#define GetCurrentDir getcwd
//#endif
// end relative loading proproc dir


// for offset into the FBO interleaved buffer (ugly I know!)
#define BUFFER_OFFSET(i) ((void*)(i))

namespace ijg {

	// forward declare
	class Protoplasm;

	class ProtoBaseApp {

		// enable private access
		friend class ProtoPlasm;
		friend class ProtoPath2;

	public:
		//ProtoBaseApp();
		
		// GLFW Mouse events
		void setMouseButton(int mouseAction, int mouseButton, int mouseMods);

		// GLFW Key events
		void setKeyEvent(int key, int scancode, int action, int mods);

		// GLFW Window events
		void setWindowFrameSize(const Dim2i& windowFrameSize);

		//static ProtoBaseApp* baseApp;
		//static ProtoBaseApp* getBaseApp();
		std::shared_ptr<ProtoContext> ctx;

	private:
		void setWidth(int canvasWidth);
		void setHeight(int canvasHeight);
		/* MOVED TO PUBLIC void setSize(const Dim2i& canvasSize);*/

		ProtoRectangle backgroundPlane;
		void _init();
		void _run(const Vec2f& mousePos, const Vec4i& windowCoords = Vec4i(0, 0, 1, 1)/*, int mouseBtn, int key*/);
		void setFrameCount(float frameCount);
		int canvasWidth{ 0 }, canvasHeight{ 0 };
		int width{ 0 }, height{ 0 };
		Dim2i canvasSize;
		Dim2i windowFrameSize;
		int frameCount{ 0 };
		float frameRate{ 0.0f };
		Col3f bgColor;
		int shadowSharpnessWidth{ 0 }, shadowSharpnessHeight{ 0 };
		int shadowMapWidth{ 0 }, shadowMapHeight{ 0 };



		// for relatively accurate pixel values in 2D
		float defaultCameraDepth = 850.0f;

		float viewAngle{ 65.0f * PI / 180.0f };
		float nearDist{ 0.1f };
		float farDist{ 3000.0f };
		float aspectRatio{ 0.0f };
		float left{ 0.0f };
		float right{ 0.0f };
		float top{ 0.0f };
		float bottom{ 0.0f };

		void hermite();


	public:
		void setSize(const Dim2i& canvasSize); 
		void _initUniforms(ProtoShader* shader_ptr); // temporarily here. put back in private eventually
		// Mouse fields
		float mouseX, mouseY, mouseLastFrameX, mouseLastFrameY;
		// 1, 2, or 3
		int mouseButton{ 0 };
		int mouseAction{ 0 };
		int mouseMods{ 0 };
		bool isMousePressed;

		// for arcball
		float arcballRotX{ 0.0f }, arcballRotY{ 0.0f };
		float arcballRotXLast{ 0.0f }, arcballRotYLast{ 0.0f };
		float mouseXIn{ 0.0f }, mouseYIn{ 0.0f };
		//bool isArcballOn;

		// Key Fields
		int key{ 0 };
		int scancode{ 0 };
		int action{ 0 };

		enum Format {
			STL,
			TXT,
			RTF
		};

		// shader
		ProtoShader shader;
		ProtoShader shader3D, shader2D;

		// For Perspective vals
		void setViewAngle(float viewAngle);
		void setAspectRatio(float aspectRatio);
		void setNearDist(float nearDist);
		void setFarDist(float farDist);
		float getViewAngle();
		float getAspectRatio();
		float getNearDist();
		float getFarDist();

		// For Orthogonal vals
		void setLeft(float left);
		void setRight(float right);
		void setBottom(float bottom);
		void setTop(float top);
		float getLeft();
		float getRight();
		float getBottom();
		float getTop();

		// For view matrix
		void setSceneCenter(const Vec3& axis);
		void setEyePosition(const Vec3& eyePos);
		void setUpAxis(const Vec3& axis);

		enum ProjectionType {
			PERSPECTIVE,
			ORTHOGONAL
		};
		void setProjection(ProjectionType projType, float viewAngle, float aspect, float nearDist, float farDist);

		void setProjectionType(ProjectionType projType);

		/***********************************
		*           path plotting
		*beginPath(), endPath(), closePath()
		***********************************/
		std::vector<Vec3f> path;

		// color flags/fields for immediate mode drawing
		bool isStroke, isFill;
		Col4f fillColor, strokeColor;
		float lineWidth;

		// flag for shadowing
		bool areShadowsEnabled;

		//int SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT;

		/************************************
		 **********   FUNCTIONS   ***********
		 ***********************************/
		// pure virtual funcs require override
		virtual void init() = 0;
		virtual void run() = 0;
		virtual void display() = 0;

		virtual bool ProtoBaseApp::createShadowMap();
		// controls size of shadow map

		void setShadowMapSize(int shadowMapWidth, int shadowMapHeight);
		void setShadowSharpness(int shadowSharpnessWidth = 256, int shadowSharpnessHeight = 256);
		Tup2i getShadowSharpness() const;

		// mouse/key events
		virtual void keyPressed();
		virtual void mousePressed();
		virtual void mouseRightPressed();
		virtual void mouseReleased();
		virtual void mouseRightReleased();
		virtual void mouseMoved();
		virtual void mouseDragged();

		// window events
		virtual void onResized();
		virtual void onClosed();

		//arcball
		void arcballBegin();
		void arcballEnd();


		// frame values
		void setFrameRate(float frameRate);
		float getFrameRate() const;
		//setFrameCount() moved to private - bw
		//void setFrameCount(float frameCount);
		int getFrameCount() const;

		// set background color
		void setBackground(float r, float g, float b);
		/*void setBackground(float r, float g, float b, float a);*/
		void setBackground(float c);
		void setBackground(const Col3f& col);
		void setBackground(const std::string& image);
		//void setBackground(const Col4f& col);

		bool areShadowsOn;
		void setShadowsOn(bool areShadowsOn);
		void shadowsOn();
		void shadowOff();

		// maximum 8 lights
		void setLight(int lightID, const Vec3& Position, const Vec3& intensity);

		// get window properties **READ ONLY**
		int getWidth()const;
		int getHeight()const;
		Dim2i getSize()const;

		//addtional get window properties -bw
		int getCanvasWidth() const;
		int getCanvasHeight() const;
		Dim2i getCanvasSize() const;
		Dim2i getWindowFrameSize() const;

		// image loading using SFML
		// IS THIS STILL BEING USED?? - NO MORE SFML
		void loadImage(std::string url);

		// shaders stuff
		void GLSLInfo(ProtoShader* shader);

		// LIGHTS
		void lightsOn();
		void lightsOff();

		//// create traditional interface for GPU controlled transforms
		void translate(float tx, float ty, float tz = 0.0f);
		void translate(const Vec2f& tXY);
		void translate(const Vec3f& tXYZ);
		void rotate(float angle, float axisX, float axisY, float axisZ);
		void rotate(float angle, const Vec3f& rXYZ);
		void scale(float s);
		void scale(float sx, float sy, float sz);
		void scale(const Vec3f& sXYZ);
		//implements transform matrix stack
		void push();
		void pop();

		// some utilities
		float radians(float degs);

		/***********BEGIN************
		 2D Automatic Procedural API
		 ***************************/
		enum Registration{
			CENTER,
			CORNER, // assumed top left
			CORNER_TR,
			CORNER_BR,
			CORNER_BL,
			RANDOM
		};

		// functions that flag  enable/disable 2D lighting
		void enable2DRendering();
		void disable2DRendering();

		//void calculate2DBuffers(float prims[], int inds[], int primsCount, int indsCount);

		// Styles API
		void fill(const Col4f& col);
		void fill(float gray);
		void fill(float gray, float a);
		void fill(float r, float g, float b);
		void fill(float r, float g, float b, float a);
		void noFill();

		void stroke(const Col4f& col);
		void stroke(float gray);
		void stroke(float gray, float a);
		void stroke(float r, float g, float b);
		void stroke(float r, float g, float b, float a);
		void noStroke();
		void strokeWeight(float lineWidth = 1.0);

		// points around ellipse
		int ellipseDetail;

		// Primitives API
		// Precalculating buffers for 2D primitives for efficiency
		// updated with glBufferSubData and binding vbo/vao

		// point buffer ids
		float ptPrims[7];
		GLuint vaoPtID, vboPtID;
		void _createPt();

		// point buffer ids
		float linePrims[14];
		GLuint vaoLineID, vboLineID;
		void _createLine();
		
		// rect buffer ids
		float rectPrims[28];
		GLuint vaoRectID, vboRectID;
		void _createRect();

		// quad buffer ids
		float quadPrims[28];
		GLuint vaoQuadID, vboQuadID;
		void _createQuad();

		// ellipse buffer ids
		std::vector<float> ellipsePrims;
		std::vector<int> ellipseInds;
		GLuint vaoEllipseID, vboEllipseID, indexVboEllipseID;
		void _createEllipse();

		// star buffer ids
		std::vector<float> starPrims, starStrokePrims;
		GLuint vaoStarID, vboStarID;
		void _createStar();

		// path buffer ids (for begin(), vertex(), end())
		bool isPathRecording;

		//std::vector<float> pathPrims;
		// class for pathPrims
		struct PathPrims {
			float x, y, z, r, g, b, a;
			PathPrims(float x, float y, float z, float r, float g, float b, float a) :
				x(x), y(y), z(z), r(r), g(g), b(b), a(a){}

			Vec3f vec() {
				return Vec3f(x, y, z);
			}
		};

		std::vector<PathPrims> pathPrimsFill;
		std::vector<PathPrims> pathPrimsStroke;


		std::vector<GLdouble> tessellatedPrims;
		std::vector<std::vector<GLdouble>> pathPrimsForTessellator;
		std::vector<int> pathInds;
		GLuint vaoPathID, vboPathID, indexVboPathID;
		void _createPath();
		enum PathRenderMode {
			POLYGON, TRIANGLES, TRIANGLE_STRIP, TRIANGLE_FAN, LINES, LINE_STRIP, LINE_LOOP
		} pathRenderMode;
		// keeps track of where curveVertices inserted in path
		//std::vector<int> curveVertexInsertionIndices;
		//std::vector < std::pair<Vec3f, char> > pathVerticesAll;
		// pos, type, fill, stroke, weight
		std::vector < std::tuple<Vec3f, char, Col4f, Col4f, float> > pathVerticesAll;

		//3D
		// box buffer ids
		// (x, y, z, nx, ny, nz, r, g, b, a, u, v, tx, ty, tz)
		Vec2f textureScale;
		const static int boxPrimCount = 24 * 15;
		float boxPrims[boxPrimCount];
		float boxPrimsOrig[boxPrimCount];
		int boxInds[24]; // 6 faces
		GLuint vaoBoxID, vboBoxID, indexVboBoxID;
		void _createBox();

		// primitive funcs
		void point(float x, float y); 
		void point(Vec2 v);
		void point(float x, float y, float z);
		void point(Vec3 v);

		// primitive funcs
		void line(float x1, float y1, float x2, float y2);
		void line(float x1, float y1, float z1, float x2, float y2, float z2);
		void line(Vec2 t1, Vec2 t2);
		void line(Vec3 t1, Vec3 t2);

		void rect(float x, float y, float w, float h, Registration reg = CORNER);
		void rect(float x, float y, float z, float w, float h, Registration reg = CORNER);
		void rect(const Vec2& pt0, const Vec2& pt1, Registration reg = CORNER);
		void rect(float radius1, float radius2, Registration reg = CENTER);
		void quad(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, Registration reg = CENTER);
		void quad(const Vec2& pt0, const Vec2& pt1, const Vec2& pt2, const Vec2& pt3, Registration reg = CENTER);
		void ellipse(float x, float y, float z, float w, float h, Registration reg = CENTER); 
		void ellipse(float x, float y, float w, float h, Registration reg = CENTER);
		void ellipse(float r0, float r1, Registration reg = CENTER);
		void ellipse(float r, Registration reg = CENTER);
		void ellipse(float x, float y, float r, Registration reg = CENTER);
		void triangle(const Vec2& pt0, const Vec2& pt1, const Vec2& pt2);
		void triangle(float x0, float y0, float x1, float y1, float x2, float y2);
		void poly(int sides, float radius);
		void poly(int sides, float radius1, float radius2);
		void star(int sides, float innerRadius, float outerRadius, Registration reg = CENTER);
		void star(int sides, const Vec2& radiusAndRatio);

		// 3D Primitives
		void box(float sz, Registration reg = CENTER);
		void box(float w, float h, float d, Registration reg = CENTER);
		//void sphere(float sz);
		//void sphere(float w, float h, float d);


		// Drawing Methods API
		void beginPath(PathRenderMode pathRenderMode = POLYGON);
		void endPath(PathEnd pathEnd = OPEN);

		// straight path
		void vertex(const Vec2f& vec);
		void vertex(const Vec3f& vec);
		void vertex(float x, float y);
		void vertex(float x, float y, float z);

		// NEW
		//void line(float x1, float y1, float x2, float y2);
		//void line(float x1, float y1, float z1, float x2, float y2, float z2);

		/*void point(float x, float y);
		void point(float x, float y, float z); */

		// Catmull-Rom spline curve
		void curveVertex(const Vec2f& vec);
		void curveVertex(const Vec3f& vec);
		void curveVertex(float x, float y);
		void curveVertex(float x, float y, float z);

		int _curveDetail = 4;
		float _curveTension = 0;
		float _curveBias = 0;
		std::vector<int> curveDetails;
		std::vector<float> curveTensions;
		std::vector<float> curveBiases;
		std::vector<float> pathStrokeWeights;
		void curveDetail(int curveDetail = 20);
		void curveTension(float curveTension = 0);
		void curveBias(float curveBias = 0);
		//void curveStrokeWeight(float curveStrokeWeight = 0);

		/****END 2D API****/

		// Lighting and Materials
		void setSpecular(const Col4f& spec);
		void setShininess(float shininess);
		void setDiffuseMaterial(const Col4f& diff);
		void setAmbientMaterial(const Col4f& amb);

		/**
		* Final function call prior to User defined display call
		* Includes optional shadowing implementation, using
		* double pass with shadow map framebuffer.
		*/
		virtual void render(int x = 0, int y = 0, int scaleFactor = 1); 

		// begin save functions
		void save(std::string name = "img", int scaleFactor = 1);
		//void threadSave(std::string name, int scaleFactor); // thread safe save with mutex locking
		std::mutex mtx;
		//void saveTiles(int rows, int columns);
		bool stitchTiles(std::string url, std::string  name, int tiles);
		/****END Save/Thread/Other****/

		// FOR TESTING ONLY
		// default no Texture (white_tile.jpg)
		Texture noDiffuseTexture, noBumpTexture;
		ProtoTexture boxDiffuseMapTexture;
		GLint boxDiffuseMapLoc;
		GLint diffuseMapLocation;

		ProtoTexture boxBumpMapTexture;
		GLint boxBumpMapLoc;
		GLint bumpMapLocation;

		void noTexture();
		void diffuseTexture(const ProtoTexture& diffuseTexture);
		void bumpTexture(const ProtoTexture& bumpTexture);

		void printModelMatrix();
		void printViewMatrix();
		void printProjectionMatrix();
		void printModelViewMatrix();
		void printModelViewProjectionMatrix();

	};

	// inline methods

	inline void ProtoBaseApp::setFrameRate(float frameRate){
		this->frameRate = frameRate;
	}
	inline void ProtoBaseApp::setFrameCount(float frameCount){
		this->frameCount = frameCount;
	}

	inline float ProtoBaseApp::getFrameRate() const{
		return frameRate;
	}
	inline int ProtoBaseApp::getFrameCount() const{
		return frameCount;
	}


	inline void ProtoBaseApp::setProjection(ProjectionType projType, float viewAngle, float aspect, float nearDist, float farDist){
		//if (projType == PERSPECTIVE){
		//	ctx->setProjectionMatrix(glm::perspective(viewAngle, aspect, nearDist, farDist));
		//	//P = glm::frustum(left, right, bottom, top, nearDist, farDist);
		//	//translate(0, 0, -600);
		//	concat();
		//}
		//else {
		//	//ortho (T const &left, T const &right, T const &bottom, T const &top, T const &zNear, T const &zFar)
		//	P = glm::ortho(left, right, bottom, top, nearDist, farDist);
		//	concat();
		//}
	}

	// perspective projection
	inline void ProtoBaseApp::setViewAngle(float viewAngle){
		this->viewAngle = viewAngle;
	}
	inline void ProtoBaseApp::setAspectRatio(float aspectRatio){
		this->aspectRatio = aspectRatio;
	}
	inline void ProtoBaseApp::setNearDist(float nearDist){
		this->nearDist = nearDist;
	}
	inline void ProtoBaseApp::setFarDist(float farDist){
		this->farDist = farDist;
	}
	inline float ProtoBaseApp::getViewAngle() {
		return viewAngle;
	}
	inline float ProtoBaseApp::getAspectRatio() {
		return aspectRatio;
	}
	inline float ProtoBaseApp::getNearDist() {
		return nearDist;
	}
	inline float ProtoBaseApp::getFarDist() {
		return farDist;
	}


	// Orthogonal projection
	inline void  ProtoBaseApp::setLeft(float left){
		this->left = left;
	}
	inline void  ProtoBaseApp::setRight(float right){
		this->right = right;
	}
	inline void  ProtoBaseApp::setBottom(float bottom){
		this->bottom = bottom;
	}
	inline void  ProtoBaseApp::setTop(float top){
		this->top = top;
	}
	inline float  ProtoBaseApp::getLeft() {
		return left;
	}
	inline float  ProtoBaseApp::getRight() {
		return right;
	}
	inline float  ProtoBaseApp::getBottom() {
		return bottom;
	}
	inline float  ProtoBaseApp::getTop() {
		return top;
	}

	// SET 8 LEIGHTS
	inline void ProtoBaseApp::setLight(int lightID, const Vec3& Position, const Vec3& intensity) {
		
			/*if (lightID < 0 || lightID > 7)
				throw std::runtime_error("Maximum light count is 8. Use index values 0-7");*/

			try
			{
				if (lightID < 0 || lightID > 7)
				{
					lightID = 0; // set to 0
					throw lightID;
				}
				ctx->setLight(lightID, Position, intensity);
			}
			catch (int id)
			{
				std::cout << "Exception: Light index value " << id << " is out of range. Value \'0\' will be used. Legal values are 0-7. \n";
				//std::cout << "ENTER to continue\n";
				//int opt;
				//std::cin >> opt;
				//// add condition a code
				//if (opt == std::cin.get()){
				//	return;
				//}
				
			}

	}

	inline void ProtoBaseApp::setShadowsOn(bool areShadowsOn) { //not used I believe
		this->areShadowsOn = areShadowsOn;
	}

	inline void ProtoBaseApp::shadowsOn(){
		areShadowsEnabled = true;
	}

	inline void ProtoBaseApp::shadowOff(){
		areShadowsEnabled = false;
	}

	inline void ProtoBaseApp::printModelMatrix() {
		ctx->printModelMatrix();
	}
	inline void ProtoBaseApp::printViewMatrix() {
		ctx->printViewMatrix();
	}
	inline void ProtoBaseApp::printProjectionMatrix() {
		ctx->printProjectionMatrix();
	}
	inline void ProtoBaseApp::printModelViewMatrix() {
		ctx->printModelViewMatrix();
	}
	inline void ProtoBaseApp::printModelViewProjectionMatrix() {
		ctx->printModelViewProjectionMatrix();
	}

	// Rendering display() switches
#define POINTS ProtoGeom3::POINTS
#define WIREFRAME ProtoGeom3::WIREFRAME
#define LINES ProtoGeom3::LINES // not used yet
#define SURFACE ProtoGeom3::SURFACE

	// make this intuitive
#define arcBallBegin arcballBegin
#define arcBallEnd arcballEnd
#define beginArcball arcballBegin
#define endArcball arcballEnd
#define beginArcBall arcballBegin
#define endArcBall arcballEnd

	// immediate mode path plotting
#define beginShape beginPath // processing style
#define endShape endPath // processing style

	// enable/disable 3D lighting
#define disableLights enable2DRendering
#define enableLights disable2DRendering


	// remove this old stuff
	//#define pushMatrix glPushMatrix
	//#define popMatrix glPopMatrix
	//
	//#define translatef glTranslatef
	//#define rotatef glRotatef 
	//#define scalef glScalef 

	//#define light0 lights.at(0)
	//#define light1 lights.at(1)
	//#define light2 lights.at(2)
	//#define light3 lights.at(3)
	//#define light4 lights.at(4)
	//#define light5 lights.at(5)
	//#define light6 lights.at(6)
	//#define light7 lights.at(7)

#define background setBackground

}

//inline void ProtoBaseApp::setViewport(int width, int height){
//	glViewport(0, 0, width, height);
//}

#endif /* defined(PROTO_BASEAPP_H) */
