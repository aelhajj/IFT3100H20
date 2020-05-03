
#include "renderer.h"
#include "histogram.h"

void Renderer::setup() {
    ofSetSphereResolution(32);

    camera->setup();
    ofSetBackgroundColor(31);
    ofDisableArbTex();

    // Interface de image
    ImageStruct *image = new ImageStruct();

    ofColor colorTest(100, 100, 100);

    offset_vertical = 32;
    offset_horizontal = 32;


    viewHist = false;

    // redimensionner la fenêtre selon la résolution de l'image
    ofSetWindowShape(screen_width, screen_height);

    // mode dessin par defaut
    draw_mode = SceneObjectType::circle;

    // filtre de convolution par defaut
    kernel_type = ConvolutionKernel::sharpen;
    kernel_name = "sharpen";

    // mappage tonal par defaut
    tone_mapping_exposure = 1.0f;
    tone_mapping_gamma = 2.2f;
    // tone_mapping_toggle = false;
    tone_mapping_aces = true;

    filter_mix = 0.5f;
    filter_tint.set(255, 255, 255);

    image_source.load("teapot.jpg");

    // dimensions de l'image source
    image_width = image_source.getWidth();
    image_height = image_source.getHeight();

    // initialiser l'image de destination
    image_destination.allocate(image_width, image_height, OF_IMAGE_COLOR);
    // image_source.allocate(image_width, image_height, OF_IMAGE_COLOR);
    //objects.push_back(image_destination);

    if (Mode != modes::is2D) {
        // Mode 3D :
        speed = 100.0f;
        is_flip_axis_y = false;
        // initialisation des variables
        offset_x = 0.0f;
        offset_z = 0.0f;

        delta_x = speed;
        delta_z = speed;

        reset();
    }

    tone_mapping_toggle = false;
    texture_procedurale_toggle = true;

    shader.load("shader/tone_mapping_330_vs.glsl", "shader/tone_mapping_330_fs.glsl");
    shader_texture_procedurale.load("shader/texture_procedurale_vs.glsl", "shader/texture_procedurale_fs.glsl");
    shader_lights.load(
            "shader/pbr_330_vs.glsl",
            "shader/pbr_330_fs.glsl");
    // charger, compiler et linker les sources des shaders
    // paramètres
    oscillation_amplitude = 32.0f;
    oscillation_frequency = 7500.0f;
    speed_motion = 150.0f;
    initial_x = 0.0f;
    initial_z = -100.0f;
    scale_cube = 100.0f;
    scale_sphere = 80.0f;
    scale_teapot = 0.618f;
    position_3d_y = 0;
    position_3d_x = 0;

    // initialisation des variables
    offset_x = initial_x;
    offset_z = initial_z;

    delta_x = speed_motion;
    delta_z = speed_motion;
    teapot.loadModel("geometry/teapot.obj");
    teapot.disableMaterials();

    shader_color_fill.load(
            "shader/color_fill_330_vs.glsl",
            "shader/color_fill_330_fs.glsl");

    shader_lambert.load(
            "shader/lambert_330_vs.glsl",
            "shader/lambert_330_fs.glsl");

    shader_gouraud.load(
            "shader/gouraud_330_vs.glsl",
            "shader/gouraud_330_fs.glsl");

    shader_phong.load(
            "shader/phong_330_vs.glsl",
            "shader/phong_330_fs.glsl");

    shader_blinn_phong.load(
            "shader/blinn_phong_330_vs.glsl",
            "shader/blinn_phong_330_fs.glsl");

    // shader actif au lancement de la scène
    shader_active = ShaderType::blinn_phong;


    illuminate_toggle = true;
    lights_toggle = true;
    if (lights_toggle) {
        // charger les textures du matériau
        texture_diffuse.load("materiau/metal_plate_diffuse_1k.jpg");
        texture_metallic.load("materiau/metal_plate_metallic_1k.jpg");
        texture_roughness.load("materiau/metal_plate_roughness_1k.jpg");
        texture_occlusion.load("materiau/metal_plate_ao_1k.jpg");

        // paramètres des textures du matériau
        texture_diffuse.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
        texture_metallic.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
        texture_roughness.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
        texture_occlusion.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);

    }
    reset();
}

void Renderer::draw() {


    if (Mode == modes::is2D) {
        if (tone_mapping_toggle)// && image_source.isAllocated())
        {
            //ofPushMatrix();
            shader.begin();

            // passer les attributs uniformes au shader
            shader.setUniformTexture("image", image_destination.getTexture(), 1);

            shader.setUniform1f("tone_mapping_exposure", tone_mapping_exposure);
            shader.setUniform1f("tone_mapping_gamma", tone_mapping_gamma);
            shader.setUniform1i("tone_mapping_aces", tone_mapping_aces);

            // shader.end();

        }

        if (texture_procedurale_toggle) {
            shader_texture_procedurale.begin();
            shader_texture_procedurale.setUniform3f("tint", filter_tint.r / 255.0f, filter_tint.g / 255.0f,
                                                    filter_tint.b / 255.0f);
            shader_texture_procedurale.setUniform1f("factor", filter_mix);
            shader_texture_procedurale.setUniform1f("width", screen_width);
            shader_texture_procedurale.setUniform1f("height", screen_height);
        }
        //cam.begin();
        // afficher l'image sur toute la surface de la fenêtre d'affichage
        for (SceneObject *obj : objects) {
            ofPushMatrix();
            obj->draw();
            ofPopMatrix();
        }

        // dessiner l'image de droite
        image_destination.draw(
                image_width + offset_horizontal * 2,
                offset_vertical,
                image_width,
                image_height);

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
            ofTranslate(0, 800);
            draw_histogram();
            ofPopMatrix();
        }
        shader.end();

    } else if (Mode == modes::is3D) {
        
        // copier la matrice de transformation courante sur le dessus de la pile
        if (tone_mapping_toggle)// && image_source.isAllocated())
        {
            ofPushMatrix();
            shader.begin();

            // passer les attributs uniformes au shader
          //  shader.setUniformTexture("image", image_destination.getTexture(), 1);
          shader.setUniformTexture("image", texture_diffuse, 1);

            shader.setUniform1f("tone_mapping_exposure", tone_mapping_exposure);
            shader.setUniform1f("tone_mapping_gamma", tone_mapping_gamma);
            shader.setUniform1i("tone_mapping_aces", tone_mapping_aces);

            ofPopMatrix();

        }
        if (illuminate_toggle) {
            ofEnableDepthTest();
            ofEnableLighting();

            // activer la lumière dynamique
            light.enable();
            shader_illuminate->begin();
            shader_lights.begin();
            if (texture_procedurale_toggle) {

                shader_texture_procedurale.begin();
                shader_texture_procedurale.setUniform3f("tint", filter_tint.r / 255.0f, filter_tint.g / 255.0f,
                                                        filter_tint.b / 255.0f);
                shader_texture_procedurale.setUniform1f("factor", filter_mix);
                shader_texture_procedurale.setUniform1f("width", screen_width);
                shader_texture_procedurale.setUniform1f("height", screen_height);
            }
            ofPushMatrix();

            // transformer l'origine de la scène au milieu de la fenêtre d'affichage
            ofTranslate(center_x + offset_x, center_y, offset_z);

            ofPushMatrix();
            // positionner la sphère
            ofTranslate(
                    position_sphere.x,
                    position_sphere.y,
                    position_sphere.z);

            // dessiner une sphère
            ofDrawSphere(0.0f, 0.0f, 0.0f, scale_sphere);

            ofPopMatrix();

            ofPushMatrix();

            // positionner le teapot
            teapot.setPosition(
                    position_teapot.x,
                    position_teapot.y + 15.0f,
                    position_teapot.z);

            // dimension du teapot
            teapot.setScale(
                    scale_teapot,
                    scale_teapot,
                    scale_teapot);

            // dessiner un teapot
            teapot.draw(OF_MESH_FILL);

            ofPopMatrix();
            

            for (SceneObject3D *obj : objects3D) {
                obj->draw();
            }
            ofPopMatrix();
            shader_illuminate->end();
            shader_lights.end();
            light.disable();

            // désactiver l'éclairage dynamique
            ofDisableLighting();
            ofDisableDepthTest();
        }


        /* ofPushMatrix();
          // inverser l'axe Y pour qu'il pointe vers le haut
          ofScale(1.0f, is_flip_axis_y ? -1.0f : 1.0f);

          // transformer l'origine de la scène au milieu de la fenêtre d'affichage
          ofTranslate(center_x + offset_x, is_flip_axis_y ? -center_y : center_y, offset_z);

          // dessiner l'origine de la scène
          //draw_locator(10.0f);
          for (SceneObject3D *obj : objects3D) {
              obj->draw();
          }

          // revenir à la matrice de transformation précédente dans la pile
          ofPopMatrix();*/
    } else if (Mode == modes::isCamera) {
        ofPushMatrix();
        camera->draw();
        ofPopMatrix();
    } else {
        if (count % 1000 == 0) {
            raytracer->setup();
        } else {
            count++;
        }
        if (count == 1000) {
            count = 1;
        }
        raytracer->draw();
    }

    if (tone_mapping_toggle)
        shader.end();

    if (texture_procedurale_toggle)
        shader_texture_procedurale.end();


}


Renderer::~Renderer() {

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
    int x1, x2, y1, y2;


    if (type != SceneObjectType::line || type != SceneObjectType::triangle) {
        x1 = mouse_press_x <= mouse_current_x ? mouse_press_x : mouse_current_x;
        x2 = mouse_press_x >= mouse_current_x ? mouse_press_x : mouse_current_x;
        y1 = mouse_press_y <= mouse_current_y ? mouse_press_y : mouse_current_y;
        y2 = mouse_press_y >= mouse_current_y ? mouse_press_y : mouse_current_y;
    } else {
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
            break;

        case SceneObjectType::quatrefoil: {
            int width = x2 - x1;
            int height = y2 - y1;
            newShape = new Star(x1 + width / 2, y1 + height / 2, x2 - x1, y2 - y1, stroke_size, fill_color,
                                stroke_color);
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
    // Test, pour pas que les objets se stack dans la zone d'affichage l'un par dessus l'autre.
    // if (!objects3D.empty())
    //   objects3D.pop_back();
    SceneObject3D *newShape;
    ofColor testColor(100, 100, 190);

    // position_3d_y += 100;
    position_3d_x += 400;


    switch (type) {
        case SceneObjectType3D::sphere:
            newShape = new Sphere(mouse_press_x + position_3d_x, mouse_press_y + position_3d_y, 100, 100, testColor);

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
    newShape->setTexture(image_destination);//image_destination);
    objects3D.push_back(newShape);
}

void Renderer::add_Model3D() {
    // Test, pour pas que les objets se stack dans la zone d'affichage l'un par dessus l'autre.
    if (!objects3D.empty())
        objects3D.pop_back();
    Model3D *model3D = new Model3D();
    objects3D.push_back(model3D);
    model3D->getFileExtension();
}

void Renderer::update() {
    if (Mode == modes::is2D) {
        ofPushMatrix();
        ofSetBackgroundColor(background_color);
        if (sceneObjectSelected != nullptr) {
            if (sceneObjectSelected->type == SceneObjectType::image)
                imageSelected = (ImageStruct *) sceneObjectSelected;
            else {
                sceneObjectSelected->borderColor = stroke_color;
                sceneObjectSelected->fillColor = fill_color;
                sceneObjectSelected->thickness = stroke_size;
            }
        }
        ofPopMatrix();
    } else {
        // Mode 3D :
        camera->update();
        center_x = ofGetWidth() / 2.0f;
        center_y = ofGetHeight() / 2.0f;

        // transformer la lumière
        light.setGlobalPosition(
                ofMap(ofGetMouseX() / (float) ofGetWidth(), 0.0f, 1.0f, -center_x, center_y),
                ofMap(ofGetMouseY() / (float) ofGetHeight(), 0.0f, 1.0f, -center_y, center_y),
                -offset_z * 1.5f);
        shader_lights.begin();

        shader_lights.setUniform3f("material_color_ambient", material_color_ambient.r / 255.0f,
                                   material_color_ambient.g / 255.0f, material_color_ambient.b / 255.0f);
        shader_lights.setUniform3f("material_color_diffuse", material_color_diffuse.r / 255.0f,
                                   material_color_diffuse.g / 255.0f, material_color_diffuse.b / 255.0f);
        shader_lights.setUniform3f("material_color_specular", material_color_specular.r / 255.0f,
                                   material_color_specular.g / 255.0f, material_color_specular.b / 255.0f);

        shader_lights.setUniform1f("material_brightness", material_brightness);
        shader_lights.setUniform1f("material_metallic", material_metallic);
        shader_lights.setUniform1f("material_roughness", material_roughness);
        shader_lights.setUniform1f("material_occlusion", material_occlusion);

        shader_lights.setUniform3f("material_fresnel_ior", material_fresnel_ior);

        shader_lights.setUniformTexture("texture_diffuse", texture_diffuse.getTexture(), 1);
        shader_lights.setUniformTexture("texture_metallic", texture_metallic.getTexture(), 2);
        shader_lights.setUniformTexture("texture_roughness", texture_roughness.getTexture(), 3);
        shader_lights.setUniformTexture("texture_occlusion", texture_occlusion.getTexture(), 4);

        shader_lights.setUniform1f("light_intensity", light_intensity);
        shader_lights.setUniform3f("light_color", light_color.r / 255.0f, light_color.g / 255.0f,
                                   light_color.b / 255.0f);
        shader_lights.setUniform3f("light_position", glm::vec4(light.getGlobalPosition(), 0.0f) *
                                                     ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));

        shader_lights.setUniform1f("tone_mapping_exposure", tone_mapping_exposure);
        shader_lights.setUniform1f("tone_mapping_gamma", tone_mapping_gamma);
        shader_lights.setUniform1i("tone_mapping_toggle", tone_mapping_toggle);

        shader_lights.end();
    }
    for (SceneObject3D *obj : objects3D) {
        obj->setTexture(image_destination);
    }
    illuminate();
    filter();
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

void Renderer::showAnim3D() {
    for (SceneObject3D *obj : objects3D) {
        obj->is_animate = !(obj->is_animate);
    }
}

void Renderer::reset() {
    if (Mode == modes::is2D) {
        // todo
        ofLog() << "<Mode 2D : reset>";
    } else {
        center_x = ofGetWidth() / 2.0f;
        center_y = ofGetHeight() / 2.0f;
        offset_x = 0.0f;
        offset_z = 0.0f;
        position_teapot.set(ofGetWidth() * (1.0f / 4.0f), 50.0f, 0.0f);
        position_sphere.set(0.0f, 0.0f, 0.0f);
        ofLog() << "<Mode 3D : reset>";

        // paramètres du matériau
        material_color_ambient = ofColor(63, 63, 63);
        material_color_diffuse = ofColor(255, 255, 255);
        material_color_specular = ofColor(255, 255, 255);

        material_metallic = 0.5f;
        material_roughness = 0.5f;
        material_occlusion = 1.0f;
        material_brightness = 1.0f;

        material_fresnel_ior = glm::vec3(0.04f, 0.04f, 0.04f);

        // paramètres de la lumière
        light_color = ofColor(255, 255, 255);
        light_intensity = 10.0f;
        light_motion = true;

        // paramètres de mappage tonal
        tone_mapping_exposure = 1.0f;
        tone_mapping_toggle = true;
    }
}

void Renderer::image_export() const {

    // capturer le contenu du framebuffer actif
    ImageStruct *image;
    if (sceneObjectSelected != nullptr) {
        image = dynamic_cast<ImageStruct *>(sceneObjectSelected);
    }

    // sauvegarder le fichier image
    image->image.save("./screenshot.jpg");
    ofLog() << "screen shoted";
}

void Renderer::filter() {
    // activer le filtre

    // résolution du kernel de convolution
    const int kernel_size = 3;

    // décalage à partir du centre du kernel
    const int kernel_offset = kernel_size / 2;

    // nombre de composantes de couleur (RGB)
    const int color_component_count = 3;

    // indices de l'image
    int x, y;

    // indices du kernel
    int i, j;

    // index des composantes de couleur
    int c;

    // index du pixel de l'image source utilisé pour le filtrage
    int pixel_index_img_src;

    // index du pixel de l'image de destination en cours de filtrage
    int pixel_index_img_dst;

    // index du pixel de l'image de destination en cours de filtrage
    int kernel_index;

    // valeur à un des indices du kernel de convolution
    float kernel_value;

    // extraire les pixels de l'image source
    ofPixels pixel_array_src = image_source.getPixels();

    // extraire les pixels de l'image de destination
    ofPixels pixel_array_dst = image_destination.getPixels();

    // couleur du pixel lu dans l'image source
    ofColor pixel_color_src;

    // couleur du pixel à écrire dans l'image de destination
    ofColor pixel_color_dst;

    // somme du kernel appliquée à chaque composante de couleur d'un pixel
    float sum[color_component_count];

    // itération sur les rangées des pixels de l'image source
    for (y = 0; y < image_height; ++y) {
        // itération sur les colonnes des pixels de l'image source
        for (x = 0; x < image_width; ++x) {
            // initialiser le tableau où les valeurs de filtrage sont accumulées
            for (c = 0; c < color_component_count; ++c)
                sum[c] = 0;

            // déterminer l'index du pixel de l'image de destination
            pixel_index_img_dst = (image_width * y + x) * color_component_count;

            // itération sur les colonnes du kernel de convolution
            for (j = -kernel_offset; j <= kernel_offset; ++j) {
                // itération sur les rangées du kernel de convolution
                for (i = -kernel_offset; i <= kernel_offset; ++i) {
                    // déterminer l'index du pixel de l'image source à lire
                    pixel_index_img_src = (image_width * (y - j) + (x - i)) * color_component_count;

                    // lire la couleur du pixel de l'image source
                    pixel_color_src = pixel_array_src.getColor(pixel_index_img_src);

                    // déterminer l'indice du facteur à lire dans le kernel de convolution
                    kernel_index = kernel_size * (j + kernel_offset) + (i + kernel_offset);

                    // extraction de la valeur à cet index du kernel
                    switch (kernel_type) {
                        case ConvolutionKernel::identity:
                            kernel_value = convolution_kernel_identity.at(kernel_index);
                            break;

                        case ConvolutionKernel::emboss:
                            kernel_value = convolution_kernel_emboss.at(kernel_index);
                            break;

                        case ConvolutionKernel::sharpen:
                            kernel_value = convolution_kernel_sharpen.at(kernel_index);
                            break;

                        case ConvolutionKernel::edge_detect:
                            kernel_value = convolution_kernel_edge_detect.at(kernel_index);
                            break;

                        case ConvolutionKernel::blur:
                            kernel_value = convolution_kernel_blur.at(kernel_index);
                            break;

                        default:
                            kernel_value = convolution_kernel_identity.at(kernel_index);
                            break;
                    }

                    // itération sur les composantes de couleur
                    for (c = 0; c < color_component_count; ++c) {
                        // accumuler les valeurs de filtrage en fonction du kernel de convolution
                        sum[c] = sum[c] + kernel_value * pixel_color_src[c];
                    }
                }
            }

            // déterminer la couleur du pixel à partir des valeurs de filtrage accumulées pour chaque composante
            for (c = 0; c < color_component_count; ++c) {
                // conversion vers entier et validation des bornes de l'espace de couleur
                pixel_color_dst[c] = (int) ofClamp(sum[c], 0, 255);
            }

            // écrire la couleur à l'index du pixel en cours de filtrage
            pixel_array_dst.setColor(pixel_index_img_dst, pixel_color_dst);
        }
    }

    // écrire les pixels dans l'image de destination
    image_destination.setFromPixels(pixel_array_dst);


//  ofLog() << "<convolution filter done>";
}

void Renderer::illuminate() {
    // transformer la lumière
    light.setGlobalPosition(
            ofMap(ofGetMouseX() / (float) ofGetWidth(), 0.0f, 1.0f, -ofGetWidth() / 2.0f, ofGetWidth() / 2.0f),
            ofMap(ofGetMouseY() / (float) ofGetHeight(), 0.0f, 1.0f, -ofGetHeight() / 2.0f, ofGetHeight() / 2.0f),
            -offset_z * 1.5f);

    // mise à jour d'une valeur numérique animée par un oscillateur
    float oscillation =
            oscillate(ofGetElapsedTimeMillis(), oscillation_frequency, oscillation_amplitude) + oscillation_amplitude;

    // passer les attributs uniformes au shader de sommets
    switch (shader_active) {
        case ShaderType::color_fill:
            shader_name = "Color Fill";
            shader_illuminate = &shader_color_fill;
            shader_illuminate->begin();
            shader_illuminate->setUniform3f("color", 1.0f, 1.0f, 0.0f);
            shader_illuminate->end();
            break;

        case ShaderType::lambert:
            shader_name = "Lambert";
            shader_illuminate = &shader_lambert;
            shader_illuminate->begin();
            shader_illuminate->setUniform3f("color_ambient", 0.1f, 0.1f, 0.1f);
            shader_illuminate->setUniform3f("color_diffuse", 0.6f, 0.6f, 0.6f);
            shader_illuminate->setUniform3f("light_position", glm::vec4(light.getGlobalPosition(), 0.0f) *
                                                              ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
            shader_illuminate->end();
            break;

        case ShaderType::gouraud:
            shader_name = "Gouraud";
            shader_illuminate = &shader_gouraud;
            shader_illuminate->begin();
            shader_illuminate->setUniform3f("color_ambient", 0.1f, 0.1f, 0.1f);
            shader_illuminate->setUniform3f("color_diffuse", 0.6f, 0.6f, 0.0f);
            shader_illuminate->setUniform3f("color_specular", 1.0f, 1.0f, 0.0f);
            shader_illuminate->setUniform1f("brightness", oscillation);
            shader_illuminate->setUniform3f("light_position", glm::vec4(light.getGlobalPosition(), 0.0f) *
                                                              ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
            shader_illuminate->end();
            break;

        case ShaderType::phong:
            shader_name = "Phong";
            shader_illuminate = &shader_phong;
            shader_illuminate->begin();
            shader_illuminate->setUniform3f("color_ambient", 0.1f, 0.1f, 0.1f);
            shader_illuminate->setUniform3f("color_diffuse", 0.6f, 0.0f, 0.6f);
            shader_illuminate->setUniform3f("color_specular", 1.0f, 1.0f, 0.0f);
            shader_illuminate->setUniform1f("brightness", oscillation);
            shader_illuminate->setUniform3f("light_position", glm::vec4(light.getGlobalPosition(), 0.0f) *
                                                              ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
            shader_illuminate->end();
            break;

        case ShaderType::blinn_phong:
            shader_name = "Blinn-Phong";
            shader_illuminate = &shader_blinn_phong;
            shader_illuminate->begin();
            shader_illuminate->setUniform3f("color_ambient", 0.1f, 0.1f, 0.1f);
            shader_illuminate->setUniform3f("color_diffuse", 0.0f, 0.6f, 0.6f);
            shader_illuminate->setUniform3f("color_specular", 1.0f, 1.0f, 0.0f);
            shader_illuminate->setUniform1f("brightness", oscillation);
            shader_illuminate->setUniform3f("light_position", glm::vec4(light.getGlobalPosition(), 0.0f) *
                                                              ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
            shader_illuminate->end();
            break;

        default:
            break;
    }

}

float Renderer::oscillate(float time, float frequency, float amplitude) {
    return sinf(time * 2.0f * PI / frequency) * amplitude;
}

