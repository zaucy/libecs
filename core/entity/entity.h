#pragma once

#include <map>
#include <memory>
#include <vector>
#include <type_traits>
#include <cstdint>
#include <atomic>

#include "../component/component.h"

// Forward Declarations
namespace ecs {
	class entity_collection;
	class system_manager;
}

namespace ecs {

	using entity_id = uint32_t;
	using atomic_entity_id = std::atomic_uint32_t;

	class entity {
	public:

		entity();

		/*
			Copy constructor for entity. Each component will be copied as well.
		*/
		entity(const entity&);

		~entity();

		/*
			Getter for entity id. An entity id is unique to this entity and will never
			be reused.
		*/
		const entity_id id() const;

		/*
			Convenient method for getting all component types of this entity.
		*/
		ecs::component_types component_types() const;

		/*
			Adds component to entity. This simply constructs componentT passing in
			ctorArgsT into the constructor.

			Only 1 component of each type is allowed. If add_component is called
			again with the same type the previous type will be overwritten.
		*/
		template<typename componentT, typename... ctorArgsT>
		inline void add_component
			( ctorArgsT... ctorArgs );

	private:

		friend ecs::system_manager;
		friend ecs::entity_collection;

		const ecs::entity_id _entityId;
		ecs::component_types _componentTypes;
		std::map<ecs::component_type, ecs::component_base*> components;

		/* Internal method for adding components/ */
		void _addComponent
			( ecs::component_type  componentType
			, component_base*      componentBase
			);
	};


	template<typename componentT, typename... ctorArgsT>
	inline void entity::add_component
		( ctorArgsT... ctorArgs )
	{

		static_assert(
			std::is_base_of<component_base, componentT>::value,
			"entity::add_component<T> T must be a component type"
		);

		_addComponent(
			componentT::get_component_type(),
			new componentT{ctorArgs...}
		);
	}

}//namespace ecs
