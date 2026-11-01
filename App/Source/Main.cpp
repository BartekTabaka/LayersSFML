#include "Core/Application.h"

#include "AppLayer.h"
#include "OverlayLayer.h"

int main()
{
	Core::ApplicationSpecification appSpec;
	appSpec.Name = "LayersSFML";
	
	Core::Application application(appSpec);
	application.pushLayer<AppLayer>();
	application.pushLayer<OverlayLayer>();
	application.run();
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
