
#include "ofMain.h"
#include "application.h"
#include "ofAppGLFWWindow.h"

int main() {
    ofSetupOpenGL(512, 512, OF_WINDOW);
    ofRunApp(new Application());

}
