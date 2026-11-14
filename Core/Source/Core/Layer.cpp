#include "Layer.h"

#include <algorithm>

#include "Application.h"

namespace Core 
{
    void Layer::onUpdate(float dT)
    {
        m_Time += dT;
    }

    void Layer::onRender()
    {
        auto window = Application::get().getWindow();
        for (auto& obj : m_Objects) {
            window->draw(*obj);
        }
    }

    void Layer::queueTransition(std::unique_ptr<Layer> toLayer)
    {
        Application::get().queueLayerTransition(this, std::move(toLayer));
    }

    std::string Layer::generateUniqueObjectName(std::string_view repeatedName)
    {
        std::string newObjectName = std::string(repeatedName);

        size_t suffixStart = newObjectName.size();
        while (suffixStart > 0 && std::isdigit(static_cast<unsigned char>(newObjectName[suffixStart - 1]))) {
            --suffixStart;
        }

        // No numeric suffix
        if (suffixStart == newObjectName.size()) {
            newObjectName += '1';
        }
        // Numeric suffix found
        else {
            unsigned int suffix = std::stoul(newObjectName.substr(suffixStart));
            newObjectName = newObjectName.substr(0, suffixStart) + std::to_string(suffix + 1);
        }

        return newObjectName;
    }

    void Layer::addObject(std::unique_ptr<RenderObject> obj)
    {
        std::string newObjName = obj->getName();
        if (newObjName.empty()) 
            newObjName = "Object1";
        
        // Check if an object with this name already exists in our vector
        while (std::any_of(m_Objects.begin(), m_Objects.end(), [&](const auto& existingObj) {
            return newObjName == existingObj->getName();
        })) {
            newObjName = generateUniqueObjectName(newObjName);
        }

        obj->m_Name = newObjName;
        m_Objects.push_back(std::move(obj));
    }

    bool Layer::onMouseButtonPressed(const MouseButtonPressedEvent& event)
    {
        auto mousePos = Application::get().getWindow()->getMousePosWindow();
        for (auto obj = m_Objects.rbegin(); obj != m_Objects.rend(); ++obj) {
            if ((*obj)->isHit(mousePos)) {
                (*obj)->onClick();
                return true;
            }
        }

        return false;
    }

    bool Layer::onMouseMoved(const MouseMovedEvent& event)
    {
        auto mousePos = event.getCurrentMousePosition();
        for (auto& obj : m_Objects) {
            obj->updateHover(mousePos);
        }

        return false;
    }
}