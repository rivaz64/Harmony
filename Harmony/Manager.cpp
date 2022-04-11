#include "Manager.h"
#include "Controller.h"
#include "Pawn.h"
#include "Controller.h"
#include "GoToPoint.h"
#include "LookTo.h"
#include "flags.h"
namespace Harmony{



Manager::Manager()
{
	states.insert({"GoToPoint",new GoToPoint});
	states.insert({"LookTo",new LookTo});
}

void
Manager::addPawn(Pawn* pawn, PAWNS::E type)
{
	switch (type)
	{
	case PAWNS::GOER:
		controllers.push_back(new Controller({states["GoToPoint"]},{},{})); 
		break;

	case PAWNS::VIEW:
		controllers.push_back(new Controller({states["LookTo"]},{},{})); 
		break;

	case PAWNS::CHANGER:
		controllers.push_back(new Controller({states["GoToPoint"],states["LookTo"]},
																				 {{0,(uint)Messages::OnFinish,Transition((uint)STATES::LookTo)}},{})); 

		break;

	default:
		break;
	}
  pawn->m_controller = controllers[controllers.size()-1];
	pawn->m_controller->m_pawn = pawn;
}

void 
Manager::update(float delta)
{
	for(auto& control : controllers){
		control->update(delta);
	}
}

}

