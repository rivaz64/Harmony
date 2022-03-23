#include "Manager.h"
#include "Controller.h"
#include "Pawn.h"
#include "Controller.h"
#include "GoToPoint.h"
#include "LookTo.h"

namespace Harmony{

Manager::Manager()
{
	actions.insert({"GoToPoint",new GoToPoint});
	actions.insert({"LookTo",new LookTo});
	states.insert({"GoToPoint",new State});
	states.insert({"LookTo",new State});
	states["GoToPoint"]->m_action = actions["GoToPoint"];
	states["LookTo"]->m_action = actions["LookTo"];
}

void
Manager::addPawn(Pawn* pawn, PAWNS::E type)
{
	switch (type)
	{
	case PAWNS::GOER:
		controllers.push_back(new Controller({states["GoToPoint"]})); 
		break;

	case PAWNS::VIEW:
		controllers.push_back(new Controller({states["LookTo"]})); 
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

