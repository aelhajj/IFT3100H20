#pragma once

#include <vector>
#include "sceneObject.h"

class Actions {

public:
    stack <SceneObject::Actions> actions;
    stack<SceneObject *> objectActionsWereMadeOn;

};
