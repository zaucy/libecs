#include "entity_manager.h"
#include "entity.h"

void ecs::entity_manager::add_entity_copy
	( const ecs::entity& entity )
{
	_entities.push_back(ecs::entity(entity));
}

void ecs::entity_manager::add_entity
	( ecs::entity&& entity )
{
	_entities.push_back(std::move(entity));
}

std::vector<ecs::entity>& ecs::entity_manager::get_entities() {
	return _entities;
}
