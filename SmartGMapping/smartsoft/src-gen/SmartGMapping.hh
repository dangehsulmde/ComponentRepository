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
#ifndef _SMARTGMAPPING_HH
#define _SMARTGMAPPING_HH

#include <map>
#include <iostream>
#include "aceSmartSoft.hh"
#include "smartQueryServerTaskTrigger_T.h"
#include "SmartGMappingCore.hh"

#include "SmartGMappingPortFactoryInterface.hh"
#include "SmartGMappingExtension.hh"

// forward declarations
class SmartGMappingPortFactoryInterface;
class SmartGMappingExtension;

// includes for PlainOpcUaSmartGMappingExtension
// include plain OPC UA device clients
// include plain OPC UA status servers


// include communication objects
#include <CommBasicObjects/CommBasePositionUpdate.hh>
#include <CommBasicObjects/CommBasePositionUpdateACE.hh>
#include <CommNavigationObjects/CommGridMap.hh>
#include <CommNavigationObjects/CommGridMapACE.hh>
#include <CommBasicObjects/CommMobileLaserScan.hh>
#include <CommBasicObjects/CommMobileLaserScanACE.hh>

// include tasks
#include "GMappingTask.hh"
// include UpcallManagers
#include "LaserServiceInUpcallManager.hh"

// include input-handler
// include input-handler

// include handler
#include "CompHandler.hh"

#include "ParameterStateStruct.hh"
#include "ParameterUpdateHandler.hh"

#include "SmartStateChangeHandler.hh"

#define COMP SmartGMapping::instance()

class SmartGMapping : public SmartGMappingCore {
private:
	static SmartGMapping *_smartGMapping;
	
	// constructor
	SmartGMapping();
	
	// copy-constructor
	SmartGMapping(const SmartGMapping& cc);
	
	// destructor
	~SmartGMapping() { };
	
	// load parameter from ini file
	void loadParameter(int argc, char* argv[]);
	
	// instantiate comp-handler
	CompHandler compHandler;
	
	// helper method that maps a string-name to an according TaskTriggerSubject
	Smart::TaskTriggerSubject* getInputTaskTriggerFromString(const std::string &client);
	
	// internal map storing the different port-creation factories (that internally map to specific middleware implementations)
	std::map<std::string, SmartGMappingPortFactoryInterface*> portFactoryRegistry;
	
	// internal map storing various extensions of this component class
	std::map<std::string, SmartGMappingExtension*> componentExtensionRegistry;
	
public:
	ParameterStateStruct getGlobalState() const
	{
		return paramHandler.getGlobalState();
	}
	
	// define tasks
	Smart::TaskTriggerSubject* gMappingTaskTrigger;
	GMappingTask *gMappingTask;
	
	// define input-ports
	// InputPort LaserServiceIn
	Smart::IPushClientPattern<CommBasicObjects::CommMobileLaserScan> *laserServiceIn;
	Smart::InputTaskTrigger<CommBasicObjects::CommMobileLaserScan> *laserServiceInInputTaskTrigger;
	LaserServiceInUpcallManager *laserServiceInUpcallManager;
	
	// define request-ports
	
	// define input-handler
	
	// define output-ports
	Smart::IPushServerPattern<CommNavigationObjects::CommGridMap> *currGridMapPushServiceOut;
	Smart::ISendClientPattern<CommBasicObjects::CommBasePositionUpdate> *localizationUpdateServiceOut;
	
	// define answer-ports
	
	// define request-handlers
	
	// definitions of PlainOpcUaSmartGMappingExtension
	
	
	// define default slave ports
	SmartACE::StateSlave *stateSlave;
	SmartStateChangeHandler *stateChangeHandler;
	SmartACE::WiringSlave *wiringSlave;
	ParamUpdateHandler paramHandler;
	SmartACE::ParameterSlave *param;
	
	
	/// this method is used to register different PortFactory classes (one for each supported middleware framework)
	void addPortFactory(const std::string &name, SmartGMappingPortFactoryInterface *portFactory);
	
	/// this method is used to register different component-extension classes
	void addExtension(SmartGMappingExtension *extension);
	
	/// this method allows to access the registered component-extensions (automatically converting to the actuall implementation type)
	template <typename T>
	T* getExtension(const std::string &name) {
		auto it = componentExtensionRegistry.find(name);
		if(it != componentExtensionRegistry.end()) {
			return dynamic_cast<T*>(it->second);
		}
		return 0;
	}
	
	/// initialize component's internal members
	void init(int argc, char *argv[]);
	
	/// execute the component's infrastructure
	void run();
	
	/// clean-up component's resources
	void fini();
	
	/// call this method to set the overall component into the Alive state (i.e. component is then ready to operate)
	void setStartupFinished();
	
	/// connect all component's client ports
	Smart::StatusCode connectAndStartAllServices();
	
	/// start all assocuated Activities
	void startAllTasks();
	
	/// start all associated timers
	void startAllTimers();
	
	Smart::StatusCode connectLaserServiceIn(const std::string &serverName, const std::string &serviceName);
	Smart::StatusCode connectLocalizationUpdateServiceOut(const std::string &serverName, const std::string &serviceName);

	// return singleton instance
	static SmartGMapping* instance()
	{
		if(_smartGMapping == 0) {
			_smartGMapping = new SmartGMapping();
		}
		return _smartGMapping;
	}
	
	static void deleteInstance() {
		if(_smartGMapping != 0) {
			delete _smartGMapping;
		}
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
		struct GMappingTask_struct {
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
		} gMappingTask;
		
		//--- upcall parameter ---
		
		//--- server port parameter ---
		struct CurrGridMapPushServiceOut_struct {
				std::string serviceName;
				std::string roboticMiddleware;
		} currGridMapPushServiceOut;
	
		//--- client port parameter ---
		struct LaserServiceIn_struct {
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} laserServiceIn;
		struct LocalizationUpdateServiceOut_struct {
			bool initialConnect;
			std::string serverName;
			std::string serviceName;
			std::string wiringName;
			long interval;
			std::string roboticMiddleware;
		} localizationUpdateServiceOut;
		
		// -- parameters for PlainOpcUaSmartGMappingExtension
		
	} connections;
};
#endif
