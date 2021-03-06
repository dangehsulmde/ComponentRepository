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
// This file is generated once. Modify this file to your needs. 
// If you want the toolchain to re-generate this file, please 
// delete it before running the code generator.
//--------------------------------------------------------------------------
// --------------------------------------------------------------------------
//
//  Copyright (C) 2010-2012 Christian Schlegel, Andreas Steck
//				  2015 Dennis Stampfer
//
//        (ZAFH) Servicerobotik Ulm
//        University of Applied Sciences
//        Prittwitzstr. 10
//        D-89075 Ulm
//        Germany
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// --------------------------------------------------------------------------
#include "SymbolicPannerQueryHandler.hh"
#include "ComponentSymbolicPlanner.hh"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#if defined (__GNUC__) && defined(__unix__)
	#include <unistd.h>
#elif defined(WIN32) || defined(WIN64)
	#define snprintf _snprintf
	#define vsnprintf _vsnprintf
	#define strcasecmp _stricmp
	#define strncasecmp _strnicmp
#endif

SymbolicPannerQueryHandler::SymbolicPannerQueryHandler(Smart::IQueryServerPattern<DomainSymbolicPlanner::CommSymbolicPlannerRequest, DomainSymbolicPlanner::CommSymbolicPlannerPlan, SmartACE::QueryId>* server)
:	SymbolicPannerQueryHandlerCore(server)
{
	
}

SymbolicPannerQueryHandler::~SymbolicPannerQueryHandler()
{
	
}


void SymbolicPannerQueryHandler::handleQuery(const SmartACE::QueryId &id, const DomainSymbolicPlanner::CommSymbolicPlannerRequest& request) 
{
	DomainSymbolicPlanner::CommSymbolicPlannerPlan answer;


		std::string plannerType, domainDescription, factDescription, plan;
		std::string systemcall;




		//request.getPlannerType(plannerType);
		//request.getDomainDescription(domainDescription);
		//request.getFactDescription(factDescription);

		// save domain description to domain file (domain.pddl)
		std::ofstream domainFile ( "domain.pddl" , std::ios::out | std::ios::binary);
		domainFile << domainDescription;
		domainFile.close();

		// save fact description to fact file (fact.pddl)
		std::ofstream factFile ( "fact.pddl" , std::ios::out | std::ios::binary);
		factFile << factDescription;
		factFile.close();

		std::cout << "start Symbolic Planner: " << plannerType << "\n";


		if(strcasecmp(plannerType.c_str(), "FF")==0)
		{
			//systemcall = "{ sleep 20; echo \"pid: $$ end\"; kill $$ & }& exec ff -o domain.pddl -f fact.pddl -l result.pddl";
			systemcall = "ff -o domain.pddl -f fact.pddl -l result.pddl";
		}
		else if(strcasecmp(plannerType.c_str(), "METRIC-FF")==0)
		{
			//systemcall = "{ sleep 20; echo \"pid: $$ end\"; kill $$ & }& exec metric-ff -E -O -g 99 -o domain.pddl -f fact.pddl -l result.pddl";


			// search for path:
			std::string environment_metricff_call;
			char* sr;
			sr = getenv("SMART_ROOT_ACE");
			if(sr!=NULL) {
				environment_metricff_call = sr;
				environment_metricff_call += "/bin/metric-ff";
			} else {
				std::cout<<"Warning: Could not get environment viariable $SMART_ROOT_ACE."<<std::endl;
			}

			if (!access("./metric-ff", X_OK)) {
				// ./metric-ff is executable (deployed with toolchain)
				systemcall = "./metric-ff";
			} else if(!access(environment_metricff_call.c_str(), X_OK)) { // is executable?
						// $SMART_ROOT_ACE/bin/metric-ff or /bin/metric-ff is executable
						systemcall = environment_metricff_call;
			} else {
				// give it a last try system wide...
				systemcall = "metric-ff";
			}


			systemcall += " -E -O -g 99 -o domain.pddl -f fact.pddl -l result.pddl";
		}
		else if(strcasecmp(plannerType.c_str(), "LAMA")==0)
		{
			//systemcall = "{ sleep 20; echo \"pid: $$ end\"; kill $$ & }& exec lama-runner domain.pddl fact.pddl result.pddl";
			char* sr;
	      		sr = getenv("SMART_ROOT");
			if(sr!=NULL)
			{
				std::string lamaPath("/src/utility/seq-sat-lama/");
				lamaPath.insert(0,std::string(sr));
				//std::cout<<"lamaPath: "<<lamaPath<<std::endl;
		                chdir(lamaPath.c_str());
			}
			else
			{
				std::cout<<"COULD NOT CHANGE TO LAMA WORKING DIR!"<<std::endl;
				plan = "";
				answer.set_plan(plan);

				this->server->answer(id, answer);
				return;
			}
			systemcall = "./plan domain.pddl fact.pddl result.pddl";
		}
		else
		{
			std::cout << "UNSUPPORTED PLANNER\n\n";
		}

		std::cout << "  CALL : " << systemcall << "\n";
		if(system(systemcall.c_str()) == 0)
		{
			std::cout << "Symbolic Planner successfully finished!\n\n";
			if((strcasecmp(plannerType.c_str(), "LAMA")==0))
			{
				// read plan from result.pddl
				//TODO in case of more then one result the first is taken
				std::ifstream resultFile ("result.pddl.1", std::ios::in | std::ios::binary);
				//resultFile >> plan; //won't work --> reads only till first blank!
				std::string line;
				while(getline(resultFile,line))
					plan.append(line);
				std::string lama_pre ("((result ok)(plan (");
				std::string lama_post (")))");
	 			plan.insert(0,lama_pre);
	 			plan.append(lama_post);
				std::cout<<"LAMA PLAN: "<<plan<<std::endl;
				resultFile.close();


			}
			else
			{
				// read plan from result.pddl
				std::ifstream resultFile ("result.pddl", std::ios::in | std::ios::binary);
				//resultFile >> plan; //won't work --> reads only till first blank!
				getline (resultFile,plan);
				resultFile.close();
			}
		}
		else
		{
			std::cout << "Symbolic Planner failed --> empyt plan!\n\n";
			plan = "";
		}

		answer.set_plan(plan);



	
	
	this->server->answer(id, answer);
}
