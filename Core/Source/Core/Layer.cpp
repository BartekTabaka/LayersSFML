#include "Layer.h"
#include "Application.h"

namespace Core {
    void Layer::QueueTransition(std::unique_ptr<Layer> toLayer)
    {
        Application::Get().QueueLayerTransition(this, std::move(toLayer));
    }
}