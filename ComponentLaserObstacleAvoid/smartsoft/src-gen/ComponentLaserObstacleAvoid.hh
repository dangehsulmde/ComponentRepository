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
#ifndef _COMPONENTLASEROBSTACLEAVOID_HH
#define _COMPONENTLASEROBSTACLEAVOID_HH
	
#include <iostream>
#include "aceSmartSoft.hh"
#include "smartQueryServerTaskTrigger_T.h"
#include "ComponentLaserObstacleAvoidCore.hh"
#include "ComponentLaserObstacleAvoidImpl.hh"

// include communication objects
#include <CommBasicObjects/CommMobileLaserScan.hh>
#include <CommBasicObjects/CommMobileLaserScanACE.hh>
#include <CommBasicObjects/CommNavigationVelocity.hh>
#include <CommBasicObjects/CommNavigationVelocityACE.hh>

// include tasks
#include "RobotTask.hh"
// include UpcallManagers
#include "LaserServiceInUpcallManager.hh"

// include input-handler
// include input-handler


// include handler
#include "CompHandler.hh"


#include "SmartStateChangeHandler.hh"

#define COMP ComponentLaserObstacleAvoid::instance()

class ComponentLaserObstacleAvoid : public ComponentLaserObstacleAvoidCore {
private:
	static ComponentLaserObstacleAvoid _componentLaserObstacleAvoid;
	
	// constructor
	ComponentLaserObstacleAvoid();
	
	// copy-constructor
	ComponentLaserObstacleAvoid(const ComponentLaserObstacleAvoid& cc);
	
	// destructor
	~ComponentLaserObstacleAvoid() { };
	
	// load parameter from ini file
	void loadParameter(int argc, char* argv[]);
	
	// instantiate comp-handler
	CompHandler compHandler;
	
	Smart::TaskTriggerSubject* getInputTaskTriggerFromString(const std::string &client);
	
public:
	// component
	ComponentLaserObstacleAvoidImpl *component;
	
	
	// define tasks
	Smart::TaskTriggerSubject* robotTaskTrigger;
	RobotTask *robotTask;
	
	// define input-ports
	// InputPort LaserServiceIn
	Smart::IPushClientPattern<CommBasicObjects::CommMobileLaserScan> *laserServiceIn;
	Smart::InputTaskTrigger<CommBasicObjects::CommMobileLaserScan> *laserServiceInInputTaskTrigger;
	LaserServiceInUpcallManager *laserServiceInUpcallManager;
	
	// define request-ports
	
	// define input-handler
	
	// define output-ports
	Smart::ISendClientPattern<CommBasicObjects::CommNavigationVelocity> *navigationVelocityServiceOut;
	
	// define answer-ports
	
	// define request-handlers
	
	
	// define default slave ports
	SmartACE::StateSlave *stateSlave;
	SmartStateChangeHandler *stateChangeHandler;
	SmartACE::WiringSlave *wiringSlave;
	
	
	void init(int argc, char *argv[]);
	void run();
	
	void setStartupFinished();
	Smart::StatusCode connectAndStartAllServices();
	void startAllTasks();
	void startAllTimers();
	
	Smart::StatusCode connectLaserServiceIn(const std::string &serverName, const std::string &serviceName);
	Smart::StatusCode connectNavigationVelocityServiceOut(const std::string &serverName, const std::string &serviceName);

	// return singleton instance
	static ComponentLaserObstacleAvoid* instance()
	{
		return (ComponentLaserObstacleAvoid*)&_componentLaserObstacleAvoid;
	}
	
	// connections parameter
	struct connections_struct
	{
		// component struct
		struct component_struct
		{
			// the name of the component
			std::string name;
			std::string initialComponentMode;
			std::string defaultScheduler;
			bool useLogger;
		} component;
		
		//--- task parameter ---
		struct RobotTask_struct {
			double minActFreq;
			double maxActFreq;
			std::string trigger;
			// only one of the following two params is 
			// actually used at run-time according 
			// to the system config model
			double periodicActFreq;
			// or
			std::string inPortRef;
			int prescale;
			// scheduling parameters
			std::string scheduler;
			int priority;
			int cpuAffinity;
		} robotTask;
		
		//--- upcall parameter ---
		
		//--- server port parameter ---
	
		//--- client port parameter ---
		struct LaserServiceIn_struct {
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
		} laserServiceIn;
		struct NavigationVelocityServiceOut_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
		} navigationVelocityServiceOut;
		
	} connections;
};
#endif
