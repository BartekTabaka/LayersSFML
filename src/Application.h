#include "Layer.h"
#include "Window.h"

#include <SFML/Graphics.hpp>

#include <memory>
#include <concepts>
#include <string>
#include <vector>
#include <print>

enum class TimeUnit {
	Seconds, Milliseconds, Microseconds
};

struct ApplicationSpecification { // Application properties (Window specification included)
	std::string Name = "Application";
	WindowSpecification windowSpec;
};

class Application {
public:
	// Class constructor with default parameters - leave blank for deafult specification or 
	// specify name and window specification
	Application(const ApplicationSpecification& appSpec = ApplicationSpecification());
	//Application(const std::string& name, const ApplicationSpecification& appSpec = ApplicationSpecification());
	~Application();

	void Run();
	void Stop();

	//Dodawanie nowej warstwy
	template<std::derived_from<Layer> TLayer>
	void PushLayer()
	{
		m_LayerStack.push_back(std::make_unique<TLayer>());
	}

	//Wydobycie/otrzymanie warstwy z m_LayerStack
	template<std::derived_from<Layer> TLayer>
	TLayer* GetLayer() {
		// Iteracja przez ka¿d¹ warstwê w m_LayerStack
		for (const auto& layer : m_LayerStack) {
			if (auto casted = dynamic_cast<TLayer*>(layer.get())) { // Rzutujemy ka¿d¹ warstwê na oczekiwany typ 
																	// (TLayer) i sprawdzamy czy taka jest, jeœli:
																	// tak - zwracamy pierwsz¹ któr¹ uda³o siê rzutowaæ,
																	// nie - zwracamy nullptr (informacja ¿e nie ma 
																	//		 warstwy o podanym typie
				return casted;
			}
		}
		return nullptr;
	}

	std::shared_ptr<Window> GetWindow() const; // Returns a pointer to window instance

	static Application& Get(); //Get Instance
	static float GetTime(TimeUnit unit = TimeUnit::Seconds); // Get application runtime
private:
	bool m_Running = false;

	ApplicationSpecification m_Specification;
	std::vector<std::unique_ptr<Layer>> m_LayerStack;
	std::shared_ptr<Window> m_Window;

	friend class Layer;
};
