#include "Layer.h"

#include "Application.h"

namespace Core {
    void Layer::queueTransition(std::unique_ptr<Layer> toLayer)
    {
        Application::get().queueLayerTransition(this, std::move(toLayer));
    }
}