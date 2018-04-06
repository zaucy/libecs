#pragma once

#include <map>
#include <iterator>
#include <cstdint>

#include "entity.h"

// Forward Declarations
namespace ecs {
	class entity;
	class component_base;
	class entity_collection;
}

namespace ecs {

	class entity_iterator
		: public std::iterator<
			std::forward_iterator_tag,
			ecs::entity,
			ecs::entity_id,
			const ecs::entity_id*,
			ecs::entity&
		>
	{
	public:
		explicit entity_iterator
			( ecs::entity_collection&  entityCollection
			, ecs::entity_id           entityId
			, std::size_t              currentIndex
			);

		entity_iterator& operator++
			(
			);

		entity_iterator operator++
			( int
			);

		bool operator==
			( entity_iterator other
			) const;

		bool operator!=
			( entity_iterator other
			) const;

		ecs::entity& operator*
			(
			) const;

	private:
		ecs::entity_collection& _entityCollection;
		ecs::entity_id _entityId;
		std::size_t _currentIndex;
	};

	class entity_collection {
	public:

		using iterator = entity_iterator;

		iterator begin();
		iterator end();

		/**
			Adds a new entity created from a copy of another entities components.
		*/
		void add_entity_copy(const ecs::entity& entity);

		/**
			Add a new entity (moved)
		*/
		void add_entity(ecs::entity&& entity);

	private:
		friend class ecs::entity_iterator;
		std::vector<ecs::entity> _entities;
	};

}
