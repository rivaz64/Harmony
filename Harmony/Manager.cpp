#include "Manager.h"
#include "Controller.h"
#include "Pawn.h"
#include "Controller.h"
#include "GoToPoint.h"
#include "LookTo.h"
#include "flags.h"
#include "Reaction.h"
#include "AIController.h"
namespace Harmony{



Manager::Manager()
{
	states.insert({"GoToPoint",new GoToPoint});
	states.insert({"LookTo",new LookTo});
}

void
Manager::addPawn(Pawn* pawn, PAWNS::E type)
{
	AIController* newControl = nullptr;
	switch (type)
	{
	case PAWNS::GOER:
		newControl = new AIController({states["GoToPoint"]}); 
		break;

	case PAWNS::VIEW:
		newControl = new AIController({states["LookTo"]}); 
		break;

	case PAWNS::CHANGER:
		newControl = new AIController({states["GoToPoint"],states["LookTo"]});
		newControl->init({
		{0,
		(uint)Messages::OnFinish,
		Transition((uint)STATES::LookTo,newControl)}}
		,{}); 

		break;

	case PAWNS::WANDERER:

		newControl = new AIController({states["GoToPoint"]});
		newControl->init({
		{0,
		(uint)Messages::OnFinish,
		Delegate<>::create<Reaction,AIController,&AIController::newRandomPointToGo>(newControl)}}
		,{}); 

	default:
		break;
	}
	controllers.push_back(newControl);
  pawn->m_controller = newControl;controllers[controllers.size()-1];
	newControl->m_pawn = pawn;
}

void 
Manager::update(float delta)
{
	for(auto& control : controllers){
		control->update(delta);
	}
}

}

