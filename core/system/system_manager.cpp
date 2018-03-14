#include <iostream>

#include "system_manager.h"
#include "system.h"
#include "../entity/entity.h"

void ecs::system_manager::_addSystem(ecs::_detail::system* system) {
	auto systemComponentTypes = system->component_types();

	auto systemsIt = systems.find(systemComponentTypes);
	if(systemsIt == systems.end()) {
		systemsIt = systems.insert(
			systems.end(),
			std::make_pair(systemComponentTypes, systems_list_type{})
		);
	}


	systemsIt->second.push_back(system);
}

void ecs::system_manager::process_entity
	( ecs::entity& entity )
{
	auto entityComponentTypes = entity.component_types();
	auto systemsIt = systems.find(entityComponentTypes);

	if(systemsIt != systems.end()) {
		for(auto* system : systemsIt->second) {
			std::vector<ecs::component_base*> componentList;

			for(auto entityComponentPair : entity.components) {
				componentList.push_back(entityComponentPair.second);
			}

			system->_process(componentList);
		}
	}
}
