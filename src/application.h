// IFT3100H20_ImageImport/application.h
// Classe principale de l'application.

#pragma once

#include "ofMain.h"
#include "renderer.h"
#include "cursor.h"
#include "ofxDatGui.h"

class Application : public ofBaseApp
{
public:

  Renderer renderer;
  ofxDatGuiButton* boutonImporter;
  ofxDatGuiButton* boutonRogner;
  ofxDatGuiButton* boutonHistogram;
  ofxDatGuiDropdown* menuCursor;
  Cursor* cursor;
  void setup();
  void draw();

  void windowResized(int w, int h);

  void dragEvent(ofDragInfo dragInfo);
  void onButtonEvent(ofxDatGuiButtonEvent event);
  void onDropdownEvent(ofxDatGuiDropdownEvent event);

  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);

  void openFileSelected(ofFileDialogResult openFileResult);

  void exit();
};
