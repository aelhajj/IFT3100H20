
#include "ofMain.h"
#include "application.h"
#include "ofAppGLFWWindow.h"

int main() {
    //ofSetupOpenGL(512, 512, OF_WINDOW);
  ofGLFWWindowSettings windowSettings;
  windowSettings.resizable = false;
  windowSettings.setGLVersion(3, 3);
  windowSettings.numSamples = 4;
  ofCreateWindow(windowSettings);
  ofRunApp(new Application());
}
