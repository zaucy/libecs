#pragma once

#include <vector>

// Forward Declarations
namespace ecs {
	class entity;
	class component_base;
}

namespace ecs {

	class entity_manager {
	public:

		/**
			Adds a new entity created from a copy of another entities components.
		*/
		void add_entity_copy(const ecs::entity& entity);

		/**
			Add a new entity (moved)
		*/
		void add_entity(ecs::entity&& entity);

		/**
			@NOTE: This will be deprecated soon in favour of an entity iterator that
			       can be extended.
		*/
		std::vector<ecs::entity>& get_entities();

	private:

		std::vector<ecs::entity> _entities;
	};

}
