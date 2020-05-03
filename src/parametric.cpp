#include "parametric.h"

void Parametric::setup()
{
  ofSetFrameRate(60);
  ofSetBackgroundColor(0);
  ofSetSphereResolution(32);
  ofDisableDepthTest();

  // paramètres
  line_resolution = 100;
  line_width_outline = 4.0f;
  line_width_curve = 8.0f;

  radius = 32.0f;
  scale = 10.0f;
  offset = 64.0f;

  motion_speed = 250.0f;

  // initialisation des sommets de la ligne
  for (index = 0; index <= line_resolution; ++index)
    line_renderer.addVertex(ofPoint());

  // courbe au lancement de l'application
  curve_id = CurveType::bezier_surface;

  // initialisation de la scène
  reset();
}

void Parametric::reset()
{
  // initialisation des variables
  framebuffer_width  = ofGetWidth();
  framebuffer_height = ofGetHeight();

  // ratios de positionnement dans la fenêtre
  float w_1_8 = framebuffer_width / 8.0f;
  float w_1_4 = framebuffer_width / 4.0f;
  float w_1_2 = framebuffer_width / 2.0f;
  float w_3_4 = framebuffer_width * 3.0f / 4.0f;
  float w_7_8 = framebuffer_width * 7.0f / 8.0f;
  float h_1_5 = framebuffer_height / 5.0f;
  float h_1_3 = framebuffer_height / 3.0f;
  float h_4_5 = framebuffer_height * 4.0f / 5.0f;

  initial_position1 = {w_1_8, h_4_5, 0};
  initial_position2 = {w_1_4, h_1_3, 0};
  initial_position3 = {w_1_2, h_1_5, 0};
  initial_position4 = {w_3_4, h_1_3, 0};
  initial_position5 = {w_7_8, h_4_5, 0};
  initial_position6 = {w_1_8, h_4_5, 10};
  initial_position7 = {w_1_4, h_1_3, 10};
  initial_position8 = {w_1_2, h_1_5, 10};
  initial_position9 = {w_1_8, h_4_5, 20};
  initial_position10 = {w_1_4, h_1_3, 20};
  initial_position11 = {w_1_2, h_1_5, 20};

  // paramètres selon le type de courbe
  switch (curve_id)
  {
    case CurveType::bezier_quadratic:

      curve_name = "Bézier quadratique";

      ctrl_point1 = initial_position1;
      ctrl_point2 = initial_position3;
      ctrl_point3 = initial_position5;
      ctrl_point4 = initial_position5;

      selected_ctrl_point = &ctrl_point2;

      break;

    case CurveType::bezier_cubic:

      curve_name = "Bézier cubique";

      ctrl_point1 = initial_position1;
      ctrl_point2 = initial_position2;
      ctrl_point3 = initial_position4;
      ctrl_point4 = initial_position5;

      selected_ctrl_point = &ctrl_point2;

      break;
    case CurveType::bezier_surface:

      std::vector<float> vectX1 = {initial_position1.x, initial_position2.x, initial_position3.x};
      std::vector<float> vectX2 = {initial_position6.x, initial_position7.x, initial_position8.x};
      std::vector<float> vectX3 = {initial_position9.x, initial_position10.x, initial_position11.x};
      ctrl_pointx.push_back(vectX1);
      ctrl_pointx.push_back(vectX2);
      ctrl_pointx.push_back(vectX3);

      std::vector<float> vectY1 = {initial_position1.y, initial_position2.y, initial_position3.y};
      std::vector<float> vectY2 = {initial_position6.y, initial_position7.y, initial_position8.y};
      std::vector<float> vectY3 = {initial_position9.y, initial_position10.y, initial_position11.y};
      ctrl_pointy.push_back(vectY1);
      ctrl_pointy.push_back(vectY2);
      ctrl_pointy.push_back(vectY3);

      std::vector<float> vectZ1 = {initial_position1.z, initial_position2.z, initial_position3.z};
      std::vector<float> vectZ2 = {initial_position6.z, initial_position7.z, initial_position8.z};
      std::vector<float> vectZ3 = {initial_position9.z, initial_position10.z, initial_position11.z};
      ctrl_pointz.push_back(vectZ1);
      ctrl_pointz.push_back(vectZ2);
      ctrl_pointz.push_back(vectZ3);
      selected_ctrl_pointx = &ctrl_pointx[0][0];
      selected_ctrl_pointy = &ctrl_pointy[0][0];

      break;
  }

  delta_x = motion_speed;
  delta_y = motion_speed;

  ofLog() << "<reset>";
}

void Parametric::update()
{
  for (index = 0; index <= line_resolution; ++index)
  {
    // paramètres selon le type de courbe
    switch (curve_id)
    {
      case CurveType::bezier_quadratic:

        bezier_quadratic(
          index / (float) line_resolution,
          ctrl_point1.x, ctrl_point1.y, ctrl_point1.z,
          ctrl_point2.x, ctrl_point2.y, ctrl_point2.z,
          ctrl_point3.x, ctrl_point3.y, ctrl_point3.z,
          position.x, position.y, position.z);

        // pour masquer le 4ième point de contrôle
        ctrl_point4 = ctrl_point3;

        break;

      case CurveType::bezier_cubic:

        bezier_cubic(
          index / (float) line_resolution,
          ctrl_point1.x, ctrl_point1.y, ctrl_point1.z,
          ctrl_point2.x, ctrl_point2.y, ctrl_point2.z,
          ctrl_point3.x, ctrl_point3.y, ctrl_point3.z,
          ctrl_point4.x, ctrl_point4.y, ctrl_point4.z,
          position.x, position.y, position.z);

        break;

      default:
        break;
    }
    // affecter la position du point sur la courbe
    line_renderer[index] = position;
  }



}

void Parametric::updateFloatAnimation()
{
  if (counter % 10000 == 0)
  {
    counter = 1;
    animation_float = -animation_float;
  }
  animation_float += 2;
  counter++;

}

void Parametric::draw()
{

  for (float u = 0; u <= 1; u += 0.01)
  {
    for (float v = 0; v <= 1; v += 0.01)
    {
      bezier_surface(
        animation_float,
        u, v,
        ctrl_pointx,
        ctrl_pointy,
        ctrl_pointz,
        position.x,  position.y, position.z);
      ofDrawEllipse(position.x*2 + 200, position.y*2, position.z*2, radius/8, radius/8);
    }
  }
  updateFloatAnimation();

  // // dessiner les positions initiales
  // ofSetColor(63, 63, 63);
  // ofDrawEllipse(initial_position1.x, initial_position1.y, radius/2, radius/2);
  // ofDrawEllipse(initial_position2.x, initial_position2.y, radius/2, radius/2);
  // ofDrawEllipse(initial_position3.x, initial_position3.y, radius/2, radius/2);
  // ofDrawEllipse(initial_position4.x, initial_position4.y, radius/2, radius/2);
  // ofDrawEllipse(initial_position5.x, initial_position5.y, radius/2, radius/2);
  //
  // // dessiner la ligne contour
  // ofSetColor(0, 0, 255);
  // ofSetLineWidth(line_width_outline);
  // ofDrawLine(ctrl_point1.x, ctrl_point1.y, ctrl_point2.x, ctrl_point2.y);
  // ofDrawLine(ctrl_point2.x, ctrl_point2.y, ctrl_point3.x, ctrl_point3.y);
  // ofDrawLine(ctrl_point3.x, ctrl_point3.y, ctrl_point4.x, ctrl_point4.y);
  // ofDrawLine(ctrl_point4.x, ctrl_point4.y, ctrl_point1.x, ctrl_point1.y);
  //
  // // dessiner la courbe
  // ofSetColor(0, 255, 0);
  // ofSetLineWidth(line_width_curve);
  // line_renderer.draw();
  //
  // // dessiner les points de contrôle
  // ofSetColor(255, 0, 0);
  // ofDrawEllipse(ctrl_point1.x, ctrl_point1.y, radius, radius);
  // ofDrawEllipse(ctrl_point2.x, ctrl_point2.y, radius, radius);
  // ofDrawEllipse(ctrl_point3.x, ctrl_point3.y, radius, radius);
  // ofDrawEllipse(ctrl_point4.x, ctrl_point4.y, radius, radius);
}
