#include "camera2DComponent.h"
#include <glm/gtx/transform.hpp>
#include "typeConversion.h"
#include "logger.h"
#include "worldComponent.h"
#include "globals.h"

ComponentID Camera2DComponent::ID;

Camera2DComponent::Camera2DComponent(){vanityName = "Camera 2D Component";}
Camera2DComponent::~Camera2DComponent(){}
Camera2DComponent* Camera2DComponent::construct(float inZoom, bool inActive)
{
    zoom = inZoom;
    activeFlag = inActive;

    updateMatrix();
    return this;
}
Camera2DComponent* Camera2DComponent::construct(std::vector<std::string> inArgs)
{
    if(inArgs.size() == 2)
    {
        float zo = stringToFloat(inArgs[0]);
        bool act = stringToBool(inArgs[1]);

        if(zo != -9999)
        {
            this->construct(zo,act);
        }
        else
        {
            Logger() << "Invalid input to Camera 2D Component creation" << std::endl;
        }
    }
    else
    {
        Logger() << "Invalid number of arguments to Camera 2D Component creation" << std::endl;
    }

    return this;
}

void Camera2DComponent::updateMatrix()
{
    projectionMatrix = glm::ortho(-zoom, zoom, -zoom, zoom);

    if(parentEntity != -1)
    {
        if(entities[parentEntity]->hasComponent(WorldComponent::getStaticID()))
        {
            WorldComponent* worldComp = static_cast<WorldComponent*>(entities[parentEntity]->getComponent(WorldComponent::getStaticID()));

            viewMatrix = glm::lookAt(worldComp->position, worldComp->position+glm::vec3(0,0,1), glm::vec3(0,1,0));
        }
    }
}
