#include "Application.h"

// Instancja klasy dostêpna wszêdzie
static Application* s_Appication = nullptr;

Application::Application(const ApplicationSpecification& appSpec)
{
	s_Appication = this;


}

Application& Application::Get() {
	assert(s_Appication);
	return *s_Appication;
}
