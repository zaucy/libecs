#include <iostream>
#include "system.h"

ecs::_detail::system_component_definition::system_component_definition
	( const ecs::component_type& component_type
	, bool copy
	, bool optional
	, bool readonly
	)
	: component_type(component_type)
	, copy(copy)
	, optional(optional)
	, readonly(readonly)
{ }

ecs::_detail::system_component_definition::system_component_definition
	( const system_component_definition& other
	)
	: component_type(other.component_type)
	, copy(other.copy)
	, optional(other.optional)
	, readonly(other.readonly)
{ }

ecs::_detail::system_component_definition::system_component_definition
	( system_component_definition&& other
	)
	: component_type(other.component_type)
	, copy(other.copy)
	, optional(other.optional)
	, readonly(other.readonly)
{ }

ecs::_detail::system::system
	( std::vector<system_component_definition> componentDefinitions
	)
	: _componentDefinitions(componentDefinitions)
	, _lastTimePoint(std::chrono::high_resolution_clock::now())
	, _currentTimePoint(std::chrono::high_resolution_clock::now())
{
	std::cout << "System constructor" << std::endl;
}

ecs::component_types ecs::_detail::system::component_types() const {
	ecs::component_types componentTypes;

	for(auto& componentDefinition : _componentDefinitions) {
		componentTypes += componentDefinition.component_type;
	}

	return componentTypes;
}
