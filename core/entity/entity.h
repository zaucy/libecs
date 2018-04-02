#pragma once

#include <map>
#include <memory>
#include <vector>
#include <type_traits>

#include "../component/component.h"

// Forward Declarations
namespace ecs {
	class entity_manager;
	class system_manager;
}

namespace ecs {

	class entity {
	public:

		ecs::component_types component_types() const;

		template<typename componentT, typename... ctorArgsT>
		inline void add_component
			( ctorArgsT... ctorArgs );

	private:

		friend ecs::system_manager;
		friend ecs::entity_manager;

		ecs::component_types _componentTypes;
		std::map<ecs::component_type, ecs::component_base*> components;

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
