// IFT3100H20_ImageImport/application.cpp
// Classe principale de l'application.

#include "application.h"

void Application::setup()
{
  ofxDatGui* gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT);
  boutonImporter = (*gui).addButton("Importer Image");
  boutonRogner = (*gui).addButton("Rogner Image");
  (*gui).onButtonEvent(this, &Application::onButtonEvent);
  (*gui).addTextInput("ImageInput", "Path Image");
  textInputImage = (*gui).getTextInput("ImageInput");
  ofSetWindowTitle("importation d'une image");

  ofLog() << "<app::setup>";

  renderer.setup();
}

void Application::onButtonEvent(ofxDatGuiButtonEvent event)
{
  if(event.target == boutonImporter)
  {
    renderer.image.load((*textInputImage).getText());
  }
  if(event.target == boutonRogner)
  {
        float width = renderer.croping_zone[2] - renderer.croping_zone[0];
        float height = renderer.croping_zone[3] - renderer.croping_zone[1];
        int image_width = (int)(width / renderer.image_width * renderer.image.getWidth());
        int image_heigth = (int)(height / renderer.image_heigth * renderer.image.getHeight());
        int pixel_origin_x = (int)((float)renderer.croping_zone[0]/renderer.image_width * renderer.image.getWidth());
        int pixel_origin_y = (int)((float)renderer.croping_zone[1]/renderer.image_heigth * renderer.image.getHeight());
        renderer.image.cropFrom(renderer.image,
                                pixel_origin_x,
                                pixel_origin_y,
                                image_width,
                                image_heigth);
        renderer.image_origin_x = renderer.croping_zone[0];
        renderer.image_origin_y = renderer.croping_zone[1];
        renderer.image_width = width;
        renderer.image_heigth = height;
  }

}

void Application::draw()
{
  renderer.draw();
}

void Application::windowResized(int w, int h)
{
  ofLog() << "<app::windowResized to: (" << w << ", " << h << ")>";
}

// fonction invoquée quand une sélection de fichiers est déposée sur la fenêtre de l'application
void Application::dragEvent(ofDragInfo dragInfo)
{
  ofLog() << "<app::ofDragInfo file[0]: " << dragInfo.files.at(0)
          << " at : " << dragInfo.position << ">";

  // importer le premier fichier déposé sur la fenêtre si c'est une image (attention : aucune validation du type de fichier)
  renderer.image.load(dragInfo.files.at(0));

  // redimensionner la fenêtre selon la résolution de l'image
  if (renderer.image.getWidth() > 0 && renderer.image.getHeight() > 0)
    ofSetWindowShape(renderer.image.getWidth(), renderer.image.getHeight());
}

void Application::mouseMoved(int x, int y)
{
  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

}

void Application::mouseDragged(int x, int y, int button)
{
  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

}

void Application::mousePressed(int x, int y, int button)
{
  renderer.is_mouse_button_pressed = true;
  renderer.croping_zone.clear();

  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

  renderer.mouse_press_x = x;
  renderer.mouse_press_y = y;

}

void Application::mouseReleased(int x, int y, int button)
{
  renderer.is_mouse_button_pressed = false;
  if(y > 100)
  {
    renderer.croping_zone.push_back(renderer.mouse_press_x);
    renderer.croping_zone.push_back(renderer.mouse_press_y);
    renderer.croping_zone.push_back(renderer.mouse_current_x);
    renderer.croping_zone.push_back(renderer.mouse_current_y);
  }

  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

}

void Application::mouseEntered(int x, int y)
{
  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

}

void Application::mouseExited(int x, int y)
{
  renderer.mouse_current_x = x;
  renderer.mouse_current_y = y;

}

void Application::exit()
{
  ofLog() << "<app::exit>";
}
