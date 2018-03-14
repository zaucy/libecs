#include "entity.h"
#include "../component/component.h"

void ecs::entity::_addComponent
	( ecs::component_type  componentType
	, component_base*      componentBase
	)
{
	auto findIt = components.find(componentType);

	if(findIt != components.end()) {
		delete findIt->second;
	} else {
		_componentTypes += componentType;
	}

	components.insert_or_assign(componentType, componentBase);
}

ecs::component_types ecs::entity::component_types() const {
	return _componentTypes;
}
