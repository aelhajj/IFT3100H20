#include "camera.h"


void Camera::setup()
{
  model.loadModel("teapot.fbx", 20);
  boundBox.setScale(5);
  model2.loadModel("teapot.fbx", 20);

  viewport1.x = 0;
	viewport1.y = 0;
	viewport1.width = 900;
	viewport1.height = 450;

  viewport2.x = 0;
  viewport2.y = 450;
  viewport2.width = 900;
  viewport2.height = 450;
  offset_camera = 700;

  camera_target = {0.0f, 0.0f, 0.0f};
  camera = &camera_front;
  camera_front.setPosition(0,0,-offset_camera);
  camera_left.setPosition(-offset_camera,0,0);

  model.setRotation(0, 180, 1, 0, 0);
	model.setScale(1, 1, 1);
  glm::vec3 eulerAngle = {-180,0,0};
  boundBox.setOrientation(eulerAngle);
  boundBox.setPosition(model.getPosition());
  model2.setPosition(150, 150, 150);
  model2.setRotation(0, 180, 1, 0, 0);
  model2.setScale(1, 1, 1);
  camera_front.lookAt(model.getPosition());
  camera_left.lookAt(model.getPosition());
  speed_translation = 1;
  is_camera_move_forward = false;
  is_camera_move_backward = false;

}

void Camera::update()
{
  if (is_camera_move_forward)
  {
    camera_front.dolly(-speed_translation);
    camera_left.dolly(-speed_translation);
  }
  if (is_camera_move_backward)
  {
    camera_front.dolly(speed_translation);
    camera_left.dolly(speed_translation);
  }
}

void Camera::draw()
{
  ofEnableDepthTest();
  light.enable();
  ofEnableLighting();
  if(!is_split_screen)
  {
    camera->begin();
    model.drawFaces();
    boundBox.draw();
    model2.drawFaces();
    camera->end();
    light.disable();
  }
  else
  {
    camera_front.begin(viewport1);
    model.drawFaces();
    boundBox.draw();
    model2.drawFaces();
    camera_front.end();
    camera_left.begin(viewport2);
    model.drawFaces();
    boundBox.draw();
    model2.drawFaces();
    camera_left.end();
  }

  ofDisableLighting();
  ofDisableDepthTest();
}

void Camera::changeObjectYoulookAt()
{
  if(is_looking_model1)
  {
    camera_front.lookAt(model2.getPosition());
    camera_left.lookAt(model2.getPosition());
    is_looking_model1 = false;
  }
  else
  {
    camera_front.lookAt(model.getPosition());
    camera_left.lookAt(model.getPosition());
    is_looking_model1 = true;
  }

}

void Camera::enableOrtho()
{
  camera_left.enableOrtho();
  camera_front.enableOrtho();
}
void Camera::disableOrtho()
{
  camera_left.disableOrtho();
  camera_front.disableOrtho();
}

void Camera::changePerspective()
{
  if(camera == &camera_front)
    camera = &camera_left;
  else
    camera = &camera_front;
}
