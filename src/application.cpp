#include "application.h"


void Application::setup() {
    ofxDatGuiLog::quiet();
    ofSetVerticalSync(true);

    actions = new Actions();
    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
    gui->setAutoDraw(false);

    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
    gui->setAutoDraw(false);

    vector <string> options = {"Rognage", "Selection", "ZoomIn", "ZoomOut", "Rotation", "Dessiner"};
    vector <string> options_shapes3D = { "Sphere", "Cube", "Cone", "Cylinder" };

    menuCursor = gui->addDropdown("select cursor", options);

    boutonModeSwitcher = gui->addButton("Mode actuel : 2D");

    ofxDatGuiFolder *image_folder = gui->addFolder("Image", ofColor::white);
    boutonImporter = image_folder->addButton("Importer Image");
    boutonRogner = image_folder->addButton("Rogner Image");
    boutonHistogram = image_folder->addButton("Afficher Histogramme");

    image_folder->expand();

    gui->addBreak();

    gui->onDropdownEvent(this, &Application::onDropdownEvent);
    gui->onButtonEvent(this, &Application::onButtonEvent);

    ofxDatGuiFolder *primitive_folder = gui->addFolder("Primitive", ofColor::red);

    background_color_picker = primitive_folder->addColorPicker("Canevas", ofColor(20, 20, 20, 5));
    fill_color_picker = primitive_folder->addColorPicker("Remplissage", ofColor(255, 0, 0, 5));
    stroke_color_picker = primitive_folder->addColorPicker("Stroke", ofColor(255, 0, 0, 5));
    stroke_slider = primitive_folder->addSlider("Stroke contour", 0, 10);

    ofxDatGuiFolder *primitive3D_folder = gui->addFolder("Primitive 3D", ofColor::blue);
    
    menu3DShape = gui->addDropdown("Select 3D Shape", options_shapes3D);
    boutonBox3D = gui->addButton("Montrer Boite de délimitation");
    boutonMesh3D = primitive3D_folder->addButton("Afficher mailles");
    boutonAnim3D = gui->addButton("Animation sur mailles");
    boutonRotate3D = gui->addButton("Animation 2");
    boutonModel3D = primitive3D_folder->addButton("Importer Modele 3D");
    

    primitive_folder->expand();
    primitive3D_folder->expand();
    menu3DShape->expand();

    ofSetWindowTitle("Equipe ###### : Partie 1");

    is_key_press_up = false;
    is_key_press_down = false;
    is_key_press_left = false;
    is_key_press_right = false;

    ofLog() << "<app::setup>";

    renderer.setup();
    //renderer.isMode2D = true;
    cursor = new NormalCursor(&renderer, actions);


}

void Application::onDropdownEvent(ofxDatGuiDropdownEvent event) {
  if(event.target == menuCursor) {
        if (event.child == 0) {
        cursor = new CropCursor(&renderer);
    } else if (event.child == 1) {
        cursor = new NormalCursor(&renderer, actions);
    } else if (event.child == 2) {
        cursor = new ZoomInCursor(&renderer, actions);
    } else if (event.child == 3) {
        cursor = new ZoomOutCursor(&renderer, actions);
    } else if (event.child == 4) {
        cursor = new RotationCursor(&renderer, actions);
    } else if (event.child == 5) {
        cursor = new DrawCursor(&renderer);
    }
  }
  if(event.target == menu3DShape) {
    if (event.child == 0) {
        renderer.add_primitive3D(SceneObjectType3D::sphere);
    } else if (event.child == 1) {
        renderer.add_primitive3D(SceneObjectType3D::cube);
    } else if (event.child == 2) {
        renderer.add_primitive3D(SceneObjectType3D::cone);
    } else if (event.child == 3) {
        renderer.add_primitive3D(SceneObjectType3D::cylinder);
    }
  }


}


void Application::onButtonEvent(ofxDatGuiButtonEvent event) {

    if(event.target == boutonModeSwitcher) {
        nbClick++;
        if(nbClick % 3 == 1)
        {
          boutonModeSwitcher->setLabel("Mode actuel : 2D");
          renderer.Mode = Renderer::modes::is2D;
        }
        else if(nbClick % 3 == 2)
        {
          boutonModeSwitcher->setLabel("Mode actuel : 3D");
          renderer.Mode = Renderer::modes::is3D;
        }
        else
          {
            boutonModeSwitcher->setLabel("Mode actuel : Camera");
            renderer.Mode = Renderer::modes::isCamera;
          }

    }

    if (event.target == boutonImporter) {
        ofFileDialogResult openFileResult = ofSystemLoadDialog("Select an img");

        // Verification qu'un fichier a ete selectionnee
        if (openFileResult.bSuccess) {
            ofLog() << "Selected img";

            // Ouvrir le résultat
            openFileSelected(openFileResult);
        } else {
            ofLog() << "No img selected";
        }
    }
    if (event.target == boutonRogner) {
      if(renderer.is_ready_croping)
      {
              float width = renderer.croping_zone[2] - renderer.croping_zone[0];
              float height = renderer.croping_zone[3] - renderer.croping_zone[1];
              ImageStruct *image = renderer.images[renderer.images.size() - 1];
              int image_width = (int) (width / image->width * image->image.getWidth());
              int image_heigth = (int) (height / image->height * image->image.getHeight());
              int pixel_origin_x = (int) ((float) renderer.croping_zone[0] / image->width * image->image.getWidth()) -
                                   (int) ((float) image->position_x / image->width * image->image.getWidth());
              int pixel_origin_y = (int) ((float) renderer.croping_zone[1] / image->height * image->image.getHeight()) -
                                   (int) ((float) image->position_y / image->height * image->image.getHeight());
              image->image.cropFrom(image->image,
                                    pixel_origin_x,
                                    pixel_origin_y,
                                    image_width,
                                    image_heigth);
              image->position_x = renderer.croping_zone[0];
              image->position_y = renderer.croping_zone[1];
              image->width = width;
              image->height = height;
              renderer.croping_zone.clear();
              renderer.is_ready_croping = false;
      }
    }
    if (event.target == boutonHistogram) {
        renderer.viewHist = (!renderer.viewHist);
    }
    if (event.target == boutonModel3D) {
      renderer.add_Model3D();
    }
    if(event.target == boutonRotate3D) {
      renderer.rotate3D();
    }
    if(event.target == boutonBox3D) {
      renderer.showBox3D();
    }

    if(event.target == boutonMesh3D) {
      renderer.showMesh3D();
    }
    if(event.target == boutonAnim3D) {
      renderer.showAnim3D();
    }
    

}

void Application::openFileSelected(ofFileDialogResult openFileResult) {
    ofLog() << "name of file :" << openFileResult.getName();
    ofLog() << "path of file :" << openFileResult.getPath();

    ofFile file(openFileResult.getPath());

    if (file.exists()) {
        // Sauvegarde de l'extension du fichier
        string fileExtension = ofToUpper(file.getExtension());

        // Vérification qu'il s'agit d'une image
        if (fileExtension == "JPG" || fileExtension == "PNG") {
            ImageStruct *image = new ImageStruct();
            image->image.load(openFileResult.getPath());
            image->width = image->image.getWidth();
            image->height = image->image.getHeight();
            image->position_x = 0;
            image->position_y = 0;
            renderer.objects.push_back(image);
            renderer.images.push_back(image);
        }
    }
}

void Application::draw() {
    renderer.draw();
    cursor->drawCursor();
    gui->update();
    gui->draw();

}


void Application::windowResized(int w, int h) {
    ofLog() << "<app::windowResized to: (" << w << ", " << h << ")>";
}

// fonction invoquée quand une sélection de fichiers est déposée sur la fenêtre de l'application
void Application::dragEvent(ofDragInfo dragInfo) {
    ofLog() << "<app::ofDragInfo file[0]: " << dragInfo.files.at(0)
            << " at : " << dragInfo.position << ">";

    // importer le premier fichier déposé sur la fenêtre si c'est une image (attention : aucune validation du type de fichier)
    renderer.image.load(dragInfo.files.at(0));

    // redimensionner la fenêtre selon la résolution de l'image
    if (renderer.image.getWidth() > 0 && renderer.image.getHeight() > 0)
        ofSetWindowShape(renderer.image.getWidth(), renderer.image.getHeight());
}

void Application::mouseMoved(int x, int y) {
    cursor->onMouseMoved(x, y);
}

void Application::mouseDragged(int x, int y, int button) {
    cursor->onMouseDragged(x, y);
}

void Application::mousePressed(int x, int y, int button) {
     if (!(y < 355 && x < 268))
     {
       std::cout << x << " " << y << std::endl;
       cursor->onMousePressed(x, y);
     }

}

void Application::mouseReleased(int x, int y, int button) {
    cursor->onMouseReleased(x, y);
}

void Application::mouseEntered(int x, int y) {
    renderer.mouse_current_x = x;
    renderer.mouse_current_y = y;

}

void Application::mouseExited(int x, int y) {
    renderer.mouse_current_x = x;
    renderer.mouse_current_y = y;

}

void Application::update() {
    if(renderer.Mode != Renderer::modes::is2D) {
        time_current = ofGetElapsedTimef();
        time_elapsed = time_current - time_last;
        time_last = time_current;

        // déplacement sur le plan XZ en fonction de l'état des flèches du clavier
        if (is_key_press_up)
            renderer.offset_z += renderer.delta_z * time_elapsed;
        if (is_key_press_down)
            renderer.offset_z -= renderer.delta_z * time_elapsed;
        if (is_key_press_left)
            renderer.offset_x += renderer.delta_x * time_elapsed;
        if (is_key_press_right)
            renderer.offset_x -= renderer.delta_x * time_elapsed;
    } else {

        // Mode 2D:
        renderer.background_color = background_color_picker->getColor();

        renderer.stroke_color = stroke_color_picker->getColor();
        renderer.fill_color = fill_color_picker->getColor();
        renderer.stroke_size = (int) stroke_slider->getValue();
    }

    renderer.update();
}


void Application::keyReleased(int key)
{
  switch (key)
  {
    // MODE 2D :
    std::cout << key << std::endl;
    case 49:  // key 1
      renderer.draw_mode = SceneObjectType::point;
      ofLog() << "<mode: point>";
      break;

    case 50:  // key 2
      renderer.draw_mode = SceneObjectType::circle;
      ofLog() << "<mode: cercle>";
      break;

    case 51:  // key 3
      renderer.draw_mode = SceneObjectType::line;
      ofLog() << "<mode: line>";
      break;

    case 52:  // key 4
      renderer.draw_mode = SceneObjectType::rectangle;
      ofLog() << "<mode: rectangle>";
      break;

    case 53:  // key 5
      renderer.draw_mode = SceneObjectType::triangle;
      ofLog() << "<mode: triangle>";
      break;

    case 54:
      renderer.draw_mode = SceneObjectType::quatrefoil;
      ofLog() << "<mode: primitive composee : quatrefoil>";

    // Mode 3D

    case OF_KEY_LEFT: // key ←
      is_key_press_left = false;
      break;

    case OF_KEY_UP: // key ↑
      is_key_press_up = false;
      renderer.camera->is_camera_move_forward = false;
      break;

    case OF_KEY_RIGHT: // key →
      is_key_press_right = false;
      break;

    case OF_KEY_DOWN: // key ↓
      is_key_press_down = false;
      renderer.camera->is_camera_move_backward = false;
      break;

    case 101: // key e
     // renderer.is_active_rotation = !renderer.is_active_rotation;
     // ofLog() << "<rotation is active: " << renderer.is_active_rotation << ">";
      break;

    case 102: // key f
     // renderer.is_flip_axis_y = !renderer.is_flip_axis_y;
     // ofLog() << "<axis Y is flipped: " << renderer.is_flip_axis_y << ">";
    break;

    case 111: // touche o
    renderer.camera->enableOrtho();
    break;

    case 112: // touche p
    renderer.camera->disableOrtho();
    break;

    case 114: // key r
     // renderer.is_active_proportion = !renderer.is_active_proportion;
     // ofLog() << "<proportion is active: " << renderer.is_active_proportion << ">";
      break;

    case 115: // key s
      renderer.image_export();
      ofLog() << "screen shoted";
     // renderer.is_active_translation = !renderer.is_active_translation;
     // ofLog() << "<translation is active: " << renderer.is_active_translation << ">";
      break;

    default:
      renderer.reset();
      break;

   // default:
   //   break;
  }
}

void Application::keyPressed(int key)
{
 std::cout << key << std::endl;
 switch (key)
  {
    case OF_KEY_LEFT: // key ←
      is_key_press_left = true;
      renderer.camera->changeObjectYoulookAt();
      break;

    case OF_KEY_UP: // key ↑
      is_key_press_up = true;
      renderer.camera->is_camera_move_forward = true;
      break;

    case OF_KEY_RIGHT: // key →
      renderer.camera->changeObjectYoulookAt();
      is_key_press_right = true;
      break;

    case OF_KEY_DOWN: // key ↓
      renderer.camera->is_camera_move_backward = true;
      is_key_press_down = true;
      break;
    case 102: // key f
      renderer.camera->is_split_screen = (!renderer.camera->is_split_screen);
      break;
    case 122:
    {
      SceneObject* obj = actions->objectActionsWereMadeOn.top();
      obj->undo(actions->actions.top());
      actions->objectActionsWereMadeOn.pop();
      actions->actions.pop();
      break;
    }
    case 127:
    {
      if (renderer.Mode == Renderer::modes::is2D)
      {
        auto it = std::find(renderer.objects.begin(), renderer.objects.end(), renderer.sceneObjectSelected);
        if (it != renderer.objects.end())
        {
          renderer.objects.erase(it);
        }

      }
      else
      {

      }
    }
    case ' ':
      renderer.camera->changePerspective();
      break;
    default:
      break;
  }
}


void Application::exit()
{
    ofLog() << "<app::exit>";
}
