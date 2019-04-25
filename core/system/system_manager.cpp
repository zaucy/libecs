#include <iostream>
#include <chrono>

#include "system_manager.h"
#include "system.h"
#include "../entity/entity.h"
#include "../entity/entity_collection.h"

ecs::system_manager_entity_processor::system_manager_entity_processor
	( ecs::system_manager& systemManager
	)
	: _systemManager(systemManager)
{

	auto now = std::chrono::high_resolution_clock::now();

	for(auto system : _systemManager.systemsList) {
		system->_currentTimePoint = now;
		system->pre_process();
	}
}

ecs::system_manager_entity_processor::~system_manager_entity_processor() {
	// std::cout << "Set current time point to the last time point" << std::endl;

	auto now = std::chrono::high_resolution_clock::now();

	for(auto system : _systemManager.systemsList) {
		system->post_process();
		system->_lastTimePoint = system->_currentTimePoint;
	}
}

ecs::system_manager::system_manager() {

}

ecs::system_manager::~system_manager() {
	for(auto system : systemsList) {
		delete system;
	}
}

void ecs::system_manager::_addSystem(ecs::_detail::system* system) {

	auto foundSystemIt = std::find(
		systemsList.begin(),
		systemsList.end(),
		system
	);

	if(foundSystemIt == systemsList.end()) {
		auto systemComponentTypes = system->component_types();
		auto indiciesSize = systemComponentTypes.component_type_indices.size();
		auto indicies = std::vector<size_t>(
			systemComponentTypes.component_type_indices.begin(),
			systemComponentTypes.component_type_indices.end()
		);

		systemsList.push_back(system);

		auto componentTypePermutations = systemComponentTypes.permutations();

		for(const auto& componentTypes : componentTypePermutations) {
			auto it = systemsListMap.find(systemComponentTypes);
			if(it == systemsListMap.end()) {
				it = systemsListMap.insert(
					systemsListMap.end(),
					std::make_pair(systemComponentTypes, systems_list_type{})
				);
			}

			it->second.push_back(system);
		}
	}
}

ecs::system_manager::systems_list_type ecs::system_manager::_matchSystems
	( const ecs::component_types& componentTypes
	)
{
	systems_list_type list;
	auto it = systemsListMap.find(componentTypes);
	if(it != systemsListMap.end()) {
		list = systems_list_type(it->second.begin(), it->second.end());
	}

	return list;
}

void ecs::system_manager_entity_processor::process_entity
	( ecs::entity& entity
	)
{

	auto entityComponentTypes = entity.component_types();

	for(auto system : _systemManager.systemsList) {
		std::vector<ecs::component_base*> componentList;
		const auto& systemComponentDefs = system->_componentDefinitions;

		for(auto systemComponentDef : systemComponentDefs) {
			bool foundSystemComponent = false;

			for(auto& pair : entity.components) {
				if(pair.first == systemComponentDef.component_type) {
					componentList.push_back(pair.second);
					foundSystemComponent = true;
					break;
				}
			}

			if(!foundSystemComponent) {
				break;
			}
		}

		if(systemComponentDefs.size() == componentList.size()) {
			system->_process(entity, componentList);
		}
	}

	// auto systems = _systemManager._matchSystems(entity.component_types());

	// for(auto* system : systems) {
	// 	std::vector<ecs::component_base*> componentList;

	// 	for(auto entityComponentPair : entity.components) {
	// 		componentList.push_back(entityComponentPair.second);
	// 	}

	// 	system->_process(entity, componentList);
	// }
}

void ecs::system_manager_entity_processor::process_entities
	( ecs::entity_collection& entities
	)
{
	for(auto& entity : entities) {
		// @TODO: Optimize multiple entities
		process_entity(entity);
	}
}
