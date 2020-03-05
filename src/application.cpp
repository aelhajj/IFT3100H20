// IFT3100H20_ImageImport/application.cpp
// Classe principale de l'application.

#include "application.h"


void Application::setup()
{
  ofxDatGui* gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT);
  vector<string> options = {"Rognage", "Selection", "ZoomIn", "ZoomOut", "Rotation"};
  menuCursor = gui->addDropdown("select cursor",options);
  boutonImporter = gui->addButton("Importer Image");
  boutonRogner = gui->addButton("Rogner Image");
  gui->onDropdownEvent(this, &Application::onDropdownEvent);
  gui->onButtonEvent(this, &Application::onButtonEvent);
  ofSetWindowTitle("importation d'une image");

  ofLog() << "<app::setup>";

  renderer.setup();
  cursor = new NormalCursor(&renderer);
}

void Application::onDropdownEvent(ofxDatGuiDropdownEvent event)
{
  if (event.child == 0)
  {
    cursor = new CropCursor(&renderer);
  }
  else if (event.child == 1)
  {
    cursor = new NormalCursor(&renderer);
  }
  else if (event.child == 2)
  {
    cursor = new ZoomInCursor(&renderer);
  }
  else if (event.child == 3)
  {
    cursor = new ZoomOutCursor(&renderer);
  }
  else if (event.child == 4)
  {
    cursor = new RotationCursor(&renderer);
  }
}


void Application::onButtonEvent(ofxDatGuiButtonEvent event)
{
  if(event.target == boutonImporter)
  {
    ofFileDialogResult openFileResult = ofSystemLoadDialog("Select an img");

// Verification qu'un fichier a ete selectionnee
    if (openFileResult.bSuccess)
    {
        ofLog() << "Selected img";

        // Ouvrir le résultat
        openFileSelected(openFileResult);
    } else
    {
        ofLog() << "No img selected";
    }
  }
  if(event.target == boutonRogner)
  {
        std::cout << renderer.is_ready_croping << std::endl;
         if (renderer.is_ready_croping)
         {
          float width = renderer.croping_zone[2] - renderer.croping_zone[0];
          float height = renderer.croping_zone[3] - renderer.croping_zone[1];
          ImageStruct* image = &(renderer.images[renderer.images.size() - 1]);
          int image_width = (int)(width / image->image_width * image->image.getWidth());
          int image_heigth = (int)(height / image->image_heigth * image->image.getHeight());
          int pixel_origin_x = (int)((float)renderer.croping_zone[0]/image->image_width * image->image.getWidth()) - (int)((float)image->image_origin_x/image->image_width * image->image.getWidth());
          int pixel_origin_y = (int)((float)renderer.croping_zone[1]/image->image_heigth * image->image.getHeight()) - (int)((float)image->image_origin_y/image->image_heigth * image->image.getHeight());
          image->image.cropFrom(image->image,
                                  pixel_origin_x,
                                  pixel_origin_y,
                                  image_width,
                                  image_heigth);
          image->image_origin_x = renderer.croping_zone[0];
          image->image_origin_y = renderer.croping_zone[1];
          image->image_width = width;
          image->image_heigth = height;
          renderer.is_ready_croping = false;
        }

  }

}
void Application::openFileSelected(ofFileDialogResult openFileResult)
{
    ofLog() << "name of file :" << openFileResult.getName();
    ofLog() << "path of file :" << openFileResult.getPath();

    ofFile file (openFileResult.getPath());

    if (file.exists())
    {
        // Sauvegarde de l'extension du fichier
        string fileExtension = ofToUpper(file.getExtension());

        // Vérification qu'il s'agit d'une image
        if (fileExtension == "JPG" || fileExtension == "PNG")
        {
            ImageStruct image;
            image.image.load(openFileResult.getPath());
            renderer.images.push_back(image);
        }

    }
}

void Application::draw()
{
  renderer.draw();
  cursor->drawCursor();
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
  cursor->onMouseMoved(x,y);
}

void Application::mouseDragged(int x, int y, int button)
{
  cursor->onMouseDragged(x,y);
}

void Application::mousePressed(int x, int y, int button)
{
  cursor->onMousePressed(x,y);
}

void Application::mouseReleased(int x, int y, int button)
{
  cursor->onMouseReleased(x,y);
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
