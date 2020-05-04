#include "application.h"
#include "raytracer.h"
#include <thread>


void Application::setup() {
    ofxDatGuiLog::quiet();
    ofSetVerticalSync(true);

    actions = new Actions();
    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
    gui->setAutoDraw(false);

    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
    gui->setAutoDraw(false);

    vector <string> options = {"Rognage", "Selection", "ZoomIn", "ZoomOut", "Rotation", "Dessiner"};
    vector <string> options_shapes3D = {"Sphere", "Cube", "Cone", "Cylinder"};

    menuCursor = gui->addDropdown("select cursor", options);

    boutonModeSwitcher = gui->addButton("Mode actuel : 2D");

    ofxDatGuiFolder *image_folder = gui->addFolder("Image", ofColor::white);
    boutonImporter = image_folder->addButton("Importer Image");
    boutonRogner = image_folder->addButton("Rogner Image");
    boutonHistogram = image_folder->addButton("Afficher Histogramme");

    gui->addBreak();

    ofxDatGuiFolder *filter_folder = gui->addFolder("Filtres 1-5 KEYS", ofColor::orange);

    //  boutonMappingSwitch = filter_folder->addButton("Active Mapping Tonal");
    toggle_mapping_tonal = filter_folder->addToggle("Active Mapping Tonal", true);
    toggle_mapping_tonal->onToggleEvent(this, &Application::onToggleEvent);
    boutonFilterSwitch = filter_folder->addButton("ACES filmic");
    gamma_slider = filter_folder->addSlider("Gamma", 0.0f, 5.0f);
    exposure_slider = filter_folder->addSlider("Exposure", 0.0f, 5.0f);

    //boutonTextureProceduraleSwitch = filter_folder->addButton("Active Texture Procedurale");
    toggle_textural_procedure = filter_folder->addToggle("Active Texture Procedurale", true);
    toggle_textural_procedure->onToggleEvent(this, &Application::onToggleEvent);
    filter_mix_slider = filter_folder->addSlider("Mixage", 0, 1);
    filter_tint_color_picker = filter_folder->addColorPicker("Teinture", ofColor(255, 0, 0, 5));

    // toggle_test = filter_folder-> addToggle("toggle", true);
    // toggle_test->onToggleEvent(this, &Application::onToggleEvent);
    // ofLog() << toggle_test;

    filter_folder->expand();

    gui->addBreak();

    gui->onDropdownEvent(this, &Application::onDropdownEvent);
    gui->onButtonEvent(this, &Application::onButtonEvent);

    ofxDatGuiFolder *primitive_folder = gui->addFolder("Primitive", ofColor::red);

    background_color_picker = primitive_folder->addColorPicker("Canevas", ofColor(20, 20, 20, 5));
    fill_color_picker = primitive_folder->addColorPicker("Remplissage", ofColor(255, 0, 0, 5));
    stroke_color_picker = primitive_folder->addColorPicker("Stroke", ofColor(255, 0, 0, 5));
    stroke_slider = primitive_folder->addSlider("Stroke contour", 0, 10);

    gui->addBreak();
    //primitive_folder->expand();

    ofxDatGuiFolder *primitive3D_folder = gui->addFolder("Primitive 3D", ofColor::blue);

    menu3DShape = gui->addDropdown("Select 3D Shape", options_shapes3D);
    boutonBox3D = gui->addButton("Montrer Boite de délimitation");
    boutonMesh3D = primitive3D_folder->addButton("Afficher mailles");
    boutonAnim3D = gui->addButton("Animation sur mailles");
    boutonRotate3D = gui->addButton("Animation 2");
    boutonModel3D = primitive3D_folder->addButton("Importer Modele 3D");

    ofxDatGuiFolder *illumination_folder = gui->addFolder("Illumination Moderne", ofColor::pink);
    toggle_PBR_shader = illumination_folder->addToggle("Activate Tesselation", false);
    toggle_PBR_shader->onToggleEvent(this, &Application::onToggleEvent);
    metallic_slider = illumination_folder->addSlider("Metallicite", 0, 10);
    roughness_slider = illumination_folder->addSlider("Rugorisite", 0, 10);
    occlusion_slider = illumination_folder->addSlider("Occlusion", 0, 10);
    brightness_slider = illumination_folder->addSlider("Luminosite", 0, 10);
    ambiant_color_picker = illumination_folder->addColorPicker("Couleur de lumiere ambiante", ofColor(255, 0, 0, 5));
    diffuse_color_picker = illumination_folder->addColorPicker("Couleur de lumiere diffuse", ofColor(255, 0, 0, 5));
    specular_color_picker = illumination_folder->addColorPicker("Couleur de lumiere speculaire", ofColor(255, 0, 0, 5));
    light_color_picker = illumination_folder->addColorPicker("Couleur de lumiere", ofColor(255, 0, 0, 5));

    ofxDatGuiFolder *classic_folder = gui->addFolder("Illumination Classique 1-5 KEYS", ofColor::yellow);
    boutonMateriel = classic_folder->addButton("Changer de materiau");
    toggle_illuminate_shader = classic_folder->addToggle("Activate classical shaders", false);
    toggle_illuminate_shader->onToggleEvent(this, &Application::onToggleEvent);
    toggle_light_ambiant = classic_folder->addToggle("Lumiere ambiante", false);
    toggle_light_ambiant->onToggleEvent(this, &Application::onToggleEvent);
    toggle_light_direct = classic_folder->addToggle("Lumiere directionnelle", false);
    toggle_light_direct->onToggleEvent(this, &Application::onToggleEvent);
    toggle_light_point = classic_folder->addToggle("Lumiere ponctuelle", false);
    toggle_light_point->onToggleEvent(this, &Application::onToggleEvent);
    toggle_light_spot = classic_folder->addToggle("Lumiere projecteur", false);
    toggle_light_spot->onToggleEvent(this, &Application::onToggleEvent);
    //  primitive3D_folder->expand();
    //  menu3DShape->expand();

    ofSetWindowTitle("Equipe ###### : Partie 2");

    is_key_press_up = false;
    is_key_press_down = false;
    is_key_press_left = false;
    is_key_press_right = false;

    ofLog() << "<app::setup>";

    renderer.setup();

    cursor = new NormalCursor(&renderer, actions);


}

void Application::onDropdownEvent(ofxDatGuiDropdownEvent event) {
    if (event.target == menuCursor) {
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
    if (event.target == menu3DShape) {
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

void callRaytracer() {
    string command;
    for (int i = 2; i < 256; i *= 2) {
        command = "../raytracer/raytracer 512 512 " + to_string(i);
        std::system(command.c_str());
    }
}

void Application::onButtonEvent(ofxDatGuiButtonEvent event) {

    if (event.target == boutonModeSwitcher) {
        nbClick++;
        if (nbClick % 7 == 1) {
            boutonModeSwitcher->setLabel("Mode actuel : 2D");
            renderer.Mode = Renderer::modes::is2D;
        } else if (nbClick % 7 == 2) {
            boutonModeSwitcher->setLabel("Mode actuel : 3D");
            renderer.Mode = Renderer::modes::is3D;
        } else if (nbClick % 7 == 3) {
            boutonModeSwitcher->setLabel("Mode actuel : Camera");
            renderer.Mode = Renderer::modes::isCamera;
        } else if (nbClick % 7 == 4) {
            boutonModeSwitcher->setLabel("Mode actuel : Raytracer");
            renderer.raytracer->setup();
            renderer.Mode = Renderer::modes::isRaytracer;
            //std::thread t1(callRaytracer);
            //t1.detach();
        } else if (nbClick % 7 == 5) {
            boutonModeSwitcher->setLabel("Mode actuel : Parametric");
            renderer.Mode = Renderer::modes::isParametric;
            renderer.parametric_renderer->setup();
        } else if(nbClick % 7 == 6) {
            boutonModeSwitcher->setLabel("Mode actuel : Illumination moderne");
            renderer.Mode = Renderer::modes::isModernIllumination;
            renderer.update();
        } else {
            boutonModeSwitcher->setLabel("Mode actuel : Catmull_Rom");
            renderer.Mode = Renderer::modes::isCatmull;
            renderer.catmull_rom->setup();
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
        // On regarde si la zone est prete, c'est a dire que le bouton a ete released, et on enregistre
        // les données dans une nouvelle image
        if (renderer.is_ready_croping) {
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
    if (event.target == boutonRotate3D) {
        renderer.rotate3D();
    }
    if (event.target == boutonBox3D) {
        renderer.showBox3D();
    }

    if (event.target == boutonMesh3D) {
        renderer.showMesh3D();
    }
    if (event.target == boutonAnim3D) {
        renderer.showAnim3D();
    }
    if (event.target == boutonFilterSwitch) {
        tone_mapping_type = (!tone_mapping_type);
        renderer.tone_mapping_aces = (!renderer.tone_mapping_aces);
        if (tone_mapping_type)
            boutonFilterSwitch->setLabel("ACES filmic");
        else
            boutonFilterSwitch->setLabel("Reinhard");
    }
    // if (event.target == boutonTextureProceduraleSwitch) {
    //     renderer.texture_procedurale_toggle = (!renderer.texture_procedurale_toggle);
    // }
    // if (event.target == boutonMappingSwitch) {
    //    renderer.tone_mapping_toggle = (!renderer.tone_mapping_toggle);
    // }


}

void Application::onToggleEvent(ofxDatGuiToggleEvent event) {
    //  if (event.target == toggle_test) {
    //     if (event.target->getChecked())
    //         cout << "onToggleEvent: " << event.target->getLabel() << "::" << event.target->getChecked() << endl;
    if (event.target == toggle_mapping_tonal) {
        renderer.tone_mapping_toggle = event.target->getChecked();
    }
    if (event.target == toggle_textural_procedure)
        renderer.texture_procedurale_toggle = event.target->getChecked();
    // }
    if (event.target == toggle_illuminate_shader) {
        if (event.target->getChecked()) {
            toggle_textural_procedure->setChecked(false);
            toggle_mapping_tonal->setChecked(false);
            renderer.tone_mapping_toggle = false;
            renderer.texture_procedurale_toggle = false;

        }

        renderer.illuminate_toggle = event.target->getChecked();
        renderer.lights_toggle = (!event.target->getChecked());
    }
    if (event.target == toggle_light_ambiant)
        renderer.is_active_ligh_ambient = event.target->getChecked();
    if (event.target == toggle_light_direct)
        renderer.is_active_light_directional = event.target->getChecked();
    if (event.target == toggle_light_point)
        renderer.is_active_light_point = event.target->getChecked();
    if (event.target == toggle_light_spot)
        renderer.is_active_light_spot = event.target->getChecked();
    if(event.target == toggle_PBR_shader)
        renderer.tesselation_toggle = !event.target->getChecked();

    renderer.update();

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
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("Point Light On (1) : ",
                       20, 20);
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
    if (!(y < 355 && x < 268)) {
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
    if (renderer.Mode != Renderer::modes::is2D) {
        time_current = ofGetElapsedTimef();
        time_elapsed = time_current - time_last;
        time_last = time_current;

        // déplacement sur le plan XZ en fonction de l'état des flèches du clavier
        if (is_key_press_up)
            renderer.offset_z += renderer.delta_z * time_elapsed;
        //*renderer.parametric_renderer->selected_ctrl_pointy -= renderer.delta_z * time_elapsed;
        if (is_key_press_down)
            renderer.offset_z -= renderer.delta_z * time_elapsed;
        //*renderer.parametric_renderer->selected_ctrl_pointy += renderer.delta_z * time_elapsed;
        if (is_key_press_left)
            renderer.offset_x += renderer.delta_x * time_elapsed;
        //*renderer.parametric_renderer->selected_ctrl_pointx -= renderer.delta_x * time_elapsed;
        if (is_key_press_right)
            renderer.offset_x -= renderer.delta_x * time_elapsed;
        //*renderer.parametric_renderer->selected_ctrl_pointx += renderer.delta_x * time_elapsed;
    } else {

        // Mode 2D:
        renderer.background_color = background_color_picker->getColor();

        renderer.stroke_color = stroke_color_picker->getColor();
        renderer.fill_color = fill_color_picker->getColor();
        renderer.stroke_size = (int) stroke_slider->getValue();
    }

    renderer.tone_mapping_exposure = exposure_slider->getValue();
    renderer.tone_mapping_gamma = gamma_slider->getValue();

    renderer.filter_mix = filter_mix_slider->getValue();
    renderer.filter_tint = filter_tint_color_picker->getColor();

    renderer.material_brightness = brightness_slider->getValue();
    renderer.material_metallic = metallic_slider->getValue();
    renderer.material_occlusion = occlusion_slider->getValue();
    renderer.material_roughness = roughness_slider->getValue();

    renderer.material_color_ambient = ambiant_color_picker->getColor();
    renderer.material_color_diffuse = diffuse_color_picker->getColor();
    renderer.material_color_specular = specular_color_picker->getColor();
    
    renderer.light_color = light_color_picker->getColor();
    renderer.light_intensity = brightness_slider->getValue();

    // if(tone_mapping_type)
    //   tone_mapping_type.set("aces filmic", true);
    //else
    //  tone_mapping_type.set("reinhard", false);

    renderer.update();
}


void Application::keyReleased(int key) {
    switch (key) {
        // MODE 2D :
        std::cout << key << std::endl;
        case 49:  // key 1
            renderer.draw_mode = SceneObjectType::point;
            renderer.kernel_type = ConvolutionKernel::identity;
            renderer.kernel_name = "identité";
            ofLog() << "<mode: point>";

            renderer.shader_active = ShaderType::color_fill;
            ofLog() << "<shader: color fill>";

            break;

        case 50:  // key 2
            renderer.draw_mode = SceneObjectType::circle;
            renderer.kernel_type = ConvolutionKernel::emboss;
            renderer.kernel_name = "bosseler";
            ofLog() << "<mode: cercle>";

            renderer.shader_active = ShaderType::lambert;
            ofLog() << "<shader: lambert>";
            break;

        case 51:  // key 3
            renderer.draw_mode = SceneObjectType::line;
            renderer.kernel_type = ConvolutionKernel::sharpen;
            renderer.kernel_name = "aiguiser";
            ofLog() << "<mode: line>";

            renderer.shader_active = ShaderType::gouraud;
            ofLog() << "<shader: gouraud>";
            break;

        case 52:  // key 4
            renderer.draw_mode = SceneObjectType::rectangle;
            renderer.kernel_type = ConvolutionKernel::edge_detect;
            renderer.kernel_name = "détection de bordure";
            ofLog() << "<mode: rectangle>";

            renderer.shader_active = ShaderType::phong;
            ofLog() << "<shader: phong>";
            break;

        case 53:  // key 5
            renderer.draw_mode = SceneObjectType::triangle;
            renderer.kernel_type = ConvolutionKernel::blur;
            renderer.kernel_name = "flou";

            renderer.shader_active = ShaderType::blinn_phong;
            ofLog() << "<shader: blinn-phong>";
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

        case 111: // touche o
            renderer.camera->enableOrtho();
            break;

        case 112: // touche p
            renderer.camera->disableOrtho();
            break;


        case 115: // key s
            renderer.image_export();
            ofLog() << "screen shoted";
            break;

        default:
            renderer.reset();
            break;

            // default:
            //   break;
    }
    renderer.filter();
}

void Application::keyPressed(int key) {
    std::cout << key << std::endl;
    switch (key) {
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
        case 122: {
            SceneObject *obj = actions->objectActionsWereMadeOn.top();
            obj->undo(actions->actions.top());
            actions->objectActionsWereMadeOn.pop();
            actions->actions.pop();
            break;
        }
        case 127: {
            if (renderer.Mode == Renderer::modes::is2D) {
                auto it = std::find(renderer.objects.begin(), renderer.objects.end(), renderer.sceneObjectSelected);
                if (it != renderer.objects.end()) {
                    renderer.objects.erase(it);
                }

            } else {

            }
        }
        case ' ':
            renderer.camera->changePerspective();
            break;
        default:
            break;
    }
}


void Application::exit() {
    ofLog() << "<app::exit>";
}
