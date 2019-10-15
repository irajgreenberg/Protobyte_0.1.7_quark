# Protobyte_0.1.7_quark
Protobyte Library Development 

## Thanks for your interest in Protobyte ('**Pb**').

**Pb** is a C++ creative coding library, very much in the tradition of the great [Processing](https://processing.org/) and [openFrameworks](https://openframeworks.cc/) projects. Unlike these other projects, **Pb** was not developed to be publicly released, but instead emerged out of my own idiosyncratic creative mucking. Some people on Facebook wanted to learn more about **Pb**, and to even try it; so I thought it was high time to at least give a quick start intro. I strongly recommend you read this entire document prior to attempting to work with **Pb** (_you've been warned_.)

### Platform and IDE
At present, **Pb** runs on Windows 10+, in the Microsoft Visual Studio 2019, version 16.1.5. In theory, **Pb** should be able to run on OSX and Linux and in any IDE that supports C++. 

### How it works:
The following files coordinate most of the setup of **Pb**, usually quietly in the background:

* _ProtoMain.cpp_
* _ProtoPlasm.cpp_
* _ProtoBaseApp.cpp_

**ProtoMain** is the ignition key for **Pb** and works autonomously. The only reason to touch ProtoMain is to set the size of your canvas.

```
int main(int argc, char const** argv) {
  new ijg::ProtoPlasm (2500, 1268, "ProtoController", new ProtoController());
  return EXIT_SUCCESS;
}
```

Including the numerical size arguments is actually optional. By default, **Pb** creates project windows at 1920 x 1080.

This code will create a default 1920 x 1080 project window

```
int main(int argc, char const** argv) {
  new ijg::ProtoPlasm ("ProtoController", new ProtoController());
  return EXIT_SUCCESS;
}
```

**ProtoPlasm** manages **Pb** integration with [GLFW](https://www.glfw.org/) and [GLEW](http://glew.sourceforge.net/). GLFW is a cross-platform windowing library. GLEW loads required [OpenGL](https://www.opengl.org/) extensions, not included in Windows. OpenGL is a cross-platform, decently high performance graphics library. You shouldn't need to mess with ProtoPlasm, but if you do, **Pb** may abruptly stop working .

**ProtoBaseApp** handles most of the heavy lifting enabling **Pb** to be relatively easy to work in. Similarly to ProtoPlasm, ProtoBaseApp does not need to be touched and doing so can cause immediate pain. That said, the most direct way to expand **Pb** is through ProtoBaseApp. Kidding aside, ProtoBaseApp is where much of future development will occur. If this sort of thing sounds fun to you, please get in touch.

Each new **Pb** project also includes the files:
* ProtoController.h
* ProtoController.cpp

These files are created from templates, with just enough included boilerplate code for your project to compile and run. Shortly, we'll review a simple example using these files.

In addition to the files discussed, you may also add functions and new classes to your **Pb** projects. If they're really useful, please send them my way for consideration of inclusion in the core library.

### Pb Projects
**Pb** has library dependencies and linking requirements. These are all handled behind the scenes for you, assuming you work with the provided templated project. In addition, a project **ProtoCreator.sh** script is included with **Pb**. It is most highly recommended that you use the provided script to create your projects, or who knows what the hell will happen. Though the entire Protobyte library may be installed anywhere on your computer, the internal directory/file structure must remain intact

You can use [Git BASH](https://gitforwindows.org/) to execute the shell script. Git BASH is a BASH emulator for Windows. For something more comprehensive [Linux BASH shell in Windows](https://docs.microsoft.com/en-us/windows/wsl/install-win10). 

### Creating your 1st Pb Project
Navigate within the ProtoCreator directory. It's relative path to the external Protobyte_0.1.7_quark project directory:

```/Protobyte/ProtoCreator```

The simplest way to create a new project is to type:

```./*.sh```

This will create a new project named according to the current date and time, (e.g. sketch_20190708223909). Your new project directory should also open up.

A better approach is to name your project at creation:

```./*.sh MyFirstProject```

Assuming you've installed Visual Studio, you should be able to simply double click the **.vcxproj** file in the project directory. This will load your project in Visual Studio. Please note, you'll need to have C++ language support installed in Visual Studio; if you don't, it should load automatically.

You should now be able to click the green arrow (_Local Windows Debugger_) and have your project build and run.

**Congratulations on running your 1st Pb project!**

Though **Pb**'s blank canvas is a thing of beauty, I imagine you'd like to do more. ProtoController.h and ProtoController.cpp are where you'll add your code to get started creating. In the great tradition of Processing and openFrameworks, **Pb** automatically includes functions to ```init()``` (initialize), ```run()``` and ```display()```. These functions will always execute in this order, with ```run``` and ```display``` by default running approx 60 f.p.s. Mouse, key and window events are are also automatically captured, using the provided functions.

Next is the eponymous "Hello World" program, **in Pb** style:


**ProtoController.h** within the class declaration, add:

```
         Sphere s;
         int starCount{ 2000 };
         std::vector<Vec> starLocs;
```




**ProtoController.cpp:**

Within init() add:

```
	setLight(0, Vec3(0, 0, 100), { 1, .85, .85 });
	setLight(1, Vec3(-200, 200, 100), { 1, .5, .1 });
	s = Sphere(36, 24, Col4(0), "corroded_red.jpg");
	s.setDiffuseMaterial({ 1, 1, 1 });
	s.setAmbientMaterial(.25);
	s.createBumpMap("corroded_red.jpg");
	s.setTextureScale({ .5, .5 });

	s.setSpecularMaterial({ 1, 1, 1 });
	s.setShininess(50);
	for (int i = 0; i < starCount; i++) {
		starLocs.push_back(Vec(random(-getWidth()/2, getWidth()/2), 
                    random(-getHeight()/2, getHeight()/2), random(-500, -100)));
	}

```


within display():

```
	background(0);
	for (int i = 0; i < starCount; i++) {
		strokeWeight(random(1, 5));
		stroke(random(1));
		point(starLocs.at(i).x, starLocs.at(i).y, starLocs.at(i).z);
	}

	scale(300);
	rotate(radians(15), Vec(0, 0, 1)),
	rotate(radians(getFrameCount()*.2), Vec(0, .875, 0)), 
	s.display();

```




