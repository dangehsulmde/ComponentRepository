//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain
// The SmartSoft Toolchain has been developed by:
//  
// Service Robotics Research Center
// University of Applied Sciences Ulm
// Prittwitzstr. 10
// 89075 Ulm (Germany)
//
// Information about the SmartSoft MDSD Toolchain is available at:
// www.servicerobotik-ulm.de
//
// Please do not modify this file. It will be re-generated
// running the code generator.
//--------------------------------------------------------------------------
#ifndef _NAVIGATIONVELOCITYHANDLER_CORE_HH
#define _NAVIGATIONVELOCITYHANDLER_CORE_HH

#include <aceSmartSoft.hh>
#include "NavigationVelocityServiceInUpcallInterface.hh"

class NavigationVelocityHandlerCore
:	public Smart::IInputHandler<CommBasicObjects::CommNavigationVelocity>
,	public Smart::TaskInteractionSubject
,	public NavigationVelocityServiceInUpcallInterface
{
private:
	Smart::StatusCode updateStatus;
	CommBasicObjects::CommNavigationVelocity lastUpdate;
	
	// internal input handling method
	virtual void handle_input(const CommBasicObjects::CommNavigationVelocity& input) {
		// inform all associated tasks about a new update
		this->notify_all_tasks();
		// call the input handler method (which is optionally implemented in derived classes)
		this->on_NavigationVelocityServiceIn(input);
	}
	
public:
	NavigationVelocityHandlerCore(
		Smart::InputSubject<CommBasicObjects::CommNavigationVelocity> *subject,
		const int &prescaleFactor=1);
	virtual ~NavigationVelocityHandlerCore();
};
#endif