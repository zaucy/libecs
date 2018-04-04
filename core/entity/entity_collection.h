#pragma once

#include <vector>
#include <iterator>

// Forward Declarations
namespace ecs {
	class entity;
	class component_base;
}

namespace ecs {

	class entity_iterator
		: public std::iterator<std::forward_iterator_tag, ecs::entity&>
	{
	public:
		entity_iterator
			( ecs::entity* );
	};

	class entity_collection {
	public:

		using iterator = entity_iterator;
		using const_iterator = const entity_iterator;

		iterator begin();
		iterator end();

		const_iterator begin() const;
		const_iterator end() const;

		/**
			Adds a new entity created from a copy of another entities components.
		*/
		void add_entity_copy(const ecs::entity& entity);

		/**
			Add a new entity (moved)
		*/
		void add_entity(ecs::entity&& entity);

	private:

		std::vector<ecs::entity> _entities;
	};

}
