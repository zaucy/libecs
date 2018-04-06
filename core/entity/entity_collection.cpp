#include <limits>

#include "entity_collection.h"
#include "entity.h"

ecs::entity_iterator::entity_iterator
	( ecs::entity_collection&  entityCollection
	, ecs::entity_id           entityId
	, std::size_t              currentIndex
	)
	: _entityCollection(entityCollection)
	, _entityId(entityId)
	, _currentIndex(currentIndex)
{ }

ecs::entity_iterator& ecs::entity_iterator::operator++
	(
	)
{
	_currentIndex += 1;
	auto it = _entityCollection._entities.begin() + _currentIndex;

	if(it != _entityCollection._entities.end()) {
		_entityId = it->id();
	} else {
		_entityId = 0;
		_currentIndex = std::numeric_limits<std::size_t>::max();
	}

	return *this;
}

ecs::entity_iterator ecs::entity_iterator::operator++
	( int
	)
{
	ecs::entity_iterator it{_entityCollection, _entityId, _currentIndex};
	return ++it;
}

bool ecs::entity_iterator::operator==
	( ecs::entity_iterator other
	) const
{
	return _entityId == other._entityId;
}

bool ecs::entity_iterator::operator!=
	( ecs::entity_iterator other
	) const
{
	return _entityId != other._entityId;
}

ecs::entity& ecs::entity_iterator::operator*
	(
	) const
{
	auto it = _entityCollection._entities.begin() + _currentIndex;
	return *it;
}

ecs::entity_collection::iterator ecs::entity_collection::begin() {
	auto internalBeginIt = _entities.begin();

	if(internalBeginIt == _entities.end()) {
		return end();
	} else {
		return iterator{*this, _entities[0].id(), 0};
	}
}

ecs::entity_collection::iterator ecs::entity_collection::end() {
	return iterator{*this, 0, std::numeric_limits<std::size_t>::max()};
}

void ecs::entity_collection::add_entity_copy
	( const ecs::entity& entity
	)
{
	_entities.push_back(ecs::entity(entity));
}

void ecs::entity_collection::add_entity
	( ecs::entity&& entity
	)
{
	_entities.push_back(std::move(entity));
}
