#include "entity_collection.h"
#include "entity.h"

void ecs::entity_collection::add_entity_copy
	( const ecs::entity& entity )
{
	_entities.push_back(ecs::entity(entity));
}

void ecs::entity_collection::add_entity
	( ecs::entity&& entity )
{
	_entities.push_back(std::move(entity));
}
