#include "Core/Application.h"

#include "AppLayer.h"
#include "OverlayLayer.h"

int main()
{
	Core::ApplicationSpecification appSpec;
	appSpec.Name = "LayersSFML";
	
	Core::Application application(appSpec);
	application.PushLayer<AppLayer>();
	application.PushLayer<OverlayLayer>();
	application.Run();
}

////////////////////////////
//
//  Pamiêtaj o opcji "Automatycznie zamknij okno po zakoñczeniu debugowania"
// 
//	TODO:
//  1. Stworzenie w³asnych typów eventów
//  2. Uzupe³nienie OverlayLayer
//  3. Dodanie VoidLayer
//
////////////////////////////
