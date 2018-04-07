#include "entity.h"
#include "../component/component.h"

namespace {
	ecs::atomic_entity_id nextEntityId{0};
}

ecs::entity::entity()
	: _entityId(++nextEntityId)
{

}

ecs::entity::entity(const entity& other)
	: entity()
{
	for(auto entry : other.components) {
		_addComponent(
			entry.first,
			entry.first.component_copy_fn(entry.second)
		);
	}
}

ecs::entity::~entity() {
	for(auto entry : components) {
		delete entry.second;
	}
}

const ecs::entity_id ecs::entity::id() const {
	return _entityId;
}

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
