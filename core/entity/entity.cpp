#include "entity.h"
#include "../component/component.h"

namespace {
	// Storage of the next entity id that will be used on construction.
	ecs::atomic_entity_id nextEntityId{0};
}

ecs::entity::entity()
	// Simply increment entity id every time we create an entity
	: _entityId(++nextEntityId)
{

}

ecs::entity::entity(const entity& other)
	// Make sure to call the empty entity constructor so we get a brand new
	// entity id.
	: entity()
{

	// Copy all the components from the other entity
	for(auto entry : other.components) {
		_addComponent(
			entry.first,

			// This is the copy functor created from the component_type
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
