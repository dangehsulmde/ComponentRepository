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

#ifndef SMARTMAPPERGRIDMAP_ACE_PORTFACTORY_HH_
#define SMARTMAPPERGRIDMAP_ACE_PORTFACTORY_HH_

// include ACE/SmartSoft component implementation
#include "SmartMapperGridMapImpl.hh"

// include the main component-definition class
#include "SmartMapperGridMapPortFactoryInterface.hh"

class SmartMapperGridMapAcePortFactory: public SmartMapperGridMapPortFactoryInterface
{
private:
	SmartMapperGridMapImpl *componentImpl;
public:
	SmartMapperGridMapAcePortFactory();
	virtual ~SmartMapperGridMapAcePortFactory();

	virtual void initialize(SmartMapperGridMap *component, int argc, char* argv[]) override;
	virtual int onStartup() override;

	virtual Smart::IPushClientPattern<CommBasicObjects::CommMobileLaserScan> * createLaserServiceIn() override;
	
	virtual Smart::IQueryServerPattern<CommNavigationObjects::CommGridMapRequest, CommNavigationObjects::CommGridMap,SmartACE::QueryId> * createLtmQueryServer(const std::string &serviceName) override;
	virtual Smart::IPushServerPattern<CommNavigationObjects::CommGridMap> * createCurrMapOut(const std::string &serviceName) override;
	virtual Smart::IQueryServerPattern<CommNavigationObjects::CommGridMapRequest, CommNavigationObjects::CommGridMap,SmartACE::QueryId> * createCurrQueryServer(const std::string &serviceName) override;
	
	// get a pointer to the internal component implementation
	SmartACE::SmartComponent* getComponentImpl();

	virtual int onShutdown(const std::chrono::steady_clock::duration &timeoutTime=std::chrono::seconds(2)) override;
	virtual void destroy() override;
};

#endif /* SMARTMAPPERGRIDMAP_ACE_PORTFACTORY_HH_ */