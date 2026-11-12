#include "Layer.h"

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

    void Layer::addObject(std::unique_ptr<RenderObject> obj)
    {
        m_Objects.push_back(std::move(obj));
    }

    bool Layer::onMouseButtonPressed(MouseButtonPressedEvent& event)
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

    bool Layer::onMouseMoved(MouseMovedEvent& event)
    {
        auto mousePos = event.getMousePosition();
        for (auto& obj : m_Objects) {
            obj->updateHover(mousePos);
        }

        return false;
    }
}