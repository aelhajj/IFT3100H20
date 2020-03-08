
#include "renderer.h"
#include "histogram.h"


void Renderer::setup() {

    //cam.setPosition(1000, 1000, 0);
    //cam.setDistance(1000);
    camera->setup();
    ofSetBackgroundColor(31);

    //isMode2D = false;

    // Interface de image
    ImageStruct *image = new ImageStruct();
  //  image->image.load("agaragar.jpg");

  //  image->position_x = 100;
  //  image->position_y = 0;
  //  image->width = image->image.getWidth();
  //  image->height = image->image.getHeight();

  //  images.push_back(image);
  //  objects.push_back(image);
  //  ofColor test(44, 44, 44);
  //  ofColor test2(54, 66, 66);
    ofColor colorTest(100, 100, 100);
    //Sphere *sphere = new Sphere(mouse_press_x, mouse_press_y, 100, 100, colorTest);
   // Cube *cube = new Cube(mouse_press_x, mouse_press_y, 100, 100, colorTest);
   // objects3D.push_back(cube);
   //ofEnableDepthTest();
	/*
    light.enable();
    cam.begin();
    ofColor(255, 255);*/
  // Model3D *model3D = new Model3D("teapot.obj");
  // objects3D.push_back(model3D);
  // model3D->getFileExtension();

  /* cam.setDistance(700);*/

     offset_vertical = 32;
    offset_horizontal = 32;


    viewHist = false;

    // redimensionner la fenêtre selon la résolution de l'image
    ofSetWindowShape(screen_width, screen_height);

    // mode dessin par defaut
    draw_mode = SceneObjectType::circle;

    if(Mode != modes::is2D) {
        ofSetBackgroundColor(31);
    // Mode 3D :
       // ofEnableDepthTest();

       // locator_count = 100;

        speed = 100.0f;


        is_flip_axis_y = false;
        //is_active_translation = true;
        //is_active_rotation = false;
        //is_active_proportion = false;

        // initialisation des variables
        offset_x = 0.0f;
        offset_z = 0.0f;

        delta_x = speed;
        delta_z = speed;

       // locator_buffer_head = 0;

        // allocation d'un espace mémoire suffisamment grand pour contenir les données de l'ensemble des localisateurs
       // locators = (Locator*) std::malloc(locator_count * sizeof(Locator));

        reset();
    }

}

void Renderer::draw() {
    if(Mode == modes::is2D) {
        //cam.begin();
        // afficher l'image sur toute la surface de la fenêtre d'affichage
        for (SceneObject *obj : objects) {
            ofPushMatrix();
            //  ofTranslate(image.width / 2, image.heigth / 2, 0);
            //  image.image.setAnchorPercent(0.5f, 0.5f);
            obj->draw();
            ofPopMatrix();
        }

        if (is_mouse_button_pressed) {
            // dessiner la zone de sélection
            draw_zone(
                    mouse_press_x,
                    mouse_press_y,
                    mouse_current_x,
                    mouse_current_y);
        } else {
            if (!croping_zone.empty()) {
                draw_zone(
                        croping_zone[0],
                        croping_zone[1],
                        croping_zone[2],
                        croping_zone[3]);
            }
        }

        if (viewHist) {
            ofPushMatrix();
            ofTranslate(0, 200);
            draw_histogram();
            ofPopMatrix();
        }

        //cam.end();
        // dessiner le curseur
        //draw_cursor(mouse_current_x, mouse_current_y);

    } else if (Mode == modes::is3D) {
    // copier la matrice de transformation courante sur le dessus de la pile

    ofPushMatrix();
    // inverser l'axe Y pour qu'il pointe vers le haut
    ofScale(1.0f, is_flip_axis_y ? -1.0f : 1.0f);

    // transformer l'origine de la scène au milieu de la fenêtre d'affichage
    ofTranslate(center_x + offset_x, is_flip_axis_y ? -center_y : center_y, offset_z);

    // dessiner l'origine de la scène
    //draw_locator(10.0f);
    for (SceneObject3D *obj : objects3D) {
           // ofPushMatrix();
            //  ofTranslate(image.width / 2, image.heigth / 2, 0);
            //  image.image.setAnchorPercent(0.5f, 0.5f);
            obj->draw();
           // ofPopMatrix();
        }

    // revenir à la matrice de transformation précédente dans la pile
    ofPopMatrix();
  } else{
    ofPushMatrix();
    camera->draw();
    ofPopMatrix();
  }
}


Renderer::~Renderer()
{
  
}

void Renderer::draw_zone(float x1, float y1, float x2, float y2) const {
    float x2_clamp = min(max(0.0f, x2), (float) ofGetWidth());
    float y2_clamp = min(max(0.0f, y2), (float) ofGetHeight());

    ofSetLineWidth(radius);
    ofSetColor(255);
    ofNoFill();
    ofDrawRectangle(x1, y1, x2_clamp - x1, y2_clamp - y1);
    ofFill();
    ofDrawEllipse(x1, y1, radius, radius);
    ofDrawEllipse(x1, y2_clamp, radius, radius);
    ofDrawEllipse(x2_clamp, y1, radius, radius);
    ofDrawEllipse(x2_clamp, y2_clamp, radius, radius);
}

void Renderer::draw_histogram() {
    Histogram hist;

    if (imageSelected != nullptr)
        hist.setup(imageSelected->image);
    else
        hist.setup(images.at(0)->image);
    hist.update();
    hist.draw();
}

void Renderer::add_primitive(SceneObjectType type) {
    SceneObject *newShape;
    int x1,x2,y1,y2;


    if (type != SceneObjectType::line || type != SceneObjectType::triangle)
    {
        x1 = mouse_press_x <= mouse_current_x ? mouse_press_x : mouse_current_x;
        x2 = mouse_press_x >= mouse_current_x ? mouse_press_x : mouse_current_x;
        y1 = mouse_press_y <= mouse_current_y ? mouse_press_y : mouse_current_y;
        y2 = mouse_press_y >= mouse_current_y ? mouse_press_y : mouse_current_y;
    }
    else
    {
        x1 = mouse_press_x;
        y1 = mouse_press_y;
        x2 = mouse_current_x;
        y2 = mouse_current_y;
    }
    switch (type) {
        case SceneObjectType::circle:
            newShape = new Circle();

            break;

        case SceneObjectType::point:
            newShape = new Poin();
            break;

        case SceneObjectType::line:
            newShape = new Line();
            break;

        case SceneObjectType::rectangle:
            newShape = new Rectangle();
            break;

        case SceneObjectType::triangle:
            newShape = new Triangle();
            //newShape = new Point();
            break;

        case SceneObjectType::quatrefoil:
        {
             int width = x2 - x1;
             int height = y2 - y1;
             newShape = new Star(x1 + width / 2, y1 + height / 2, x2 - x1, y2 - y1, stroke_size, fill_color, stroke_color);
            break;
        }

        default:
            break;
    }

    newShape->width = x2 - x1;
    newShape->height = y2 - y1;

    newShape->position_x = x1 + newShape->width / 2;
    newShape->position_y = y1 + newShape->height / 2;

    newShape->thickness = stroke_size;
    newShape->borderColor = stroke_color;
    newShape->fillColor = fill_color;

    newShape->update();

    objects.push_back(newShape);

}


void Renderer::add_primitive3D(SceneObjectType3D type) {

    SceneObject3D *newShape;
    ofColor testColor(100, 100, 190);

    switch (type) {
        case SceneObjectType3D::sphere:
            newShape = new Sphere(mouse_press_x, mouse_press_y, 100, 100, testColor);

            break;

        case SceneObjectType3D::cube:
            newShape = new Cube(mouse_press_x, mouse_press_y, 100, 100, testColor);
            break;

        case SceneObjectType3D::cone:
            newShape = new Cone(mouse_press_x, mouse_press_y, 100, 100, testColor);
            break;

        case SceneObjectType3D::cylinder:
            newShape = new Cylinder(mouse_press_x, mouse_press_y, 100, 100, testColor);
            break;

        default:
            break;
    }
    objects3D.push_back(newShape);
}

void Renderer::add_Model3D() {
    Model3D *model3D = new Model3D();
    objects3D.push_back(model3D);
    model3D->getFileExtension();
}

void Renderer::update() {
    if(Mode == modes::is2D) {
        ofPushMatrix();
        ofSetBackgroundColor(background_color);
        if (sceneObjectSelected != nullptr) {
            if (sceneObjectSelected->type == SceneObjectType::image)
                imageSelected = (ImageStruct *) sceneObjectSelected;
                //else if (sceneObjectSelected->type == SceneObjectType::circle)
            else {
                sceneObjectSelected->borderColor = stroke_color;
                sceneObjectSelected->fillColor = fill_color;
                sceneObjectSelected->thickness = stroke_size;
                //cout << (int)sceneObjectSelected->thickness << endl;
            }
        }
        ofPopMatrix();
    } else {
        // Mode 3D :
        camera->update();
        center_x = ofGetWidth() / 2.0f;
        center_y = ofGetHeight() / 2.0f;
    }
}

void Renderer::showBox3D() {
    for (SceneObject3D *obj : objects3D) {
        obj->show_box = !(obj->show_box);
    }
}
    
void Renderer::rotate3D() {
    for (SceneObject3D *obj : objects3D) {
        obj->is_rotating = !(obj->is_rotating);
    }
}

void Renderer::showMesh3D() {
     for (SceneObject3D *obj : objects3D) {
        obj->is_mesh_mode = !(obj->is_mesh_mode);
    }
}

void Renderer::reset() {
    if(Mode == modes::is2D) {
        // todo
        ofLog() << "<Mode 2D : reset>";
    } else {
        offset_x = 0.0f;
        offset_z = 0.0f;

     ofLog() << "<Mode 3D : reset>";
    }
}

void Renderer::image_export() const
{

  // capturer le contenu du framebuffer actif
  ImageStruct * image;
  if (sceneObjectSelected != nullptr)
  {
      image = dynamic_cast<ImageStruct*>(sceneObjectSelected);
  }

  // sauvegarder le fichier image
  image->image.save("./screenshot.jpg");
  ofLog() << "screen shoted";
}
