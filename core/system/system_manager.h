#pragma once

#include <unordered_map>
#include <vector>
#include <type_traits>

#include "_detail/system.h"
#include "../component/component.h"

// Forward Declarations
namespace ecs {
	class entity;
}

namespace ecs {

	class system_manager {
	public:

		/*
			Add system system manager. add_system simply constructs systemT passing in
			ctorArgsT into the constructor.
		*/
		template<typename systemT, typename... ctorArgsT>
		inline void add_system(ctorArgsT... ctorArgs) {

			static_assert(
				std::is_base_of<_detail::system, systemT>::value,
				"system_manager.add_system<systemT>() systemT must be base of ecs::system"
			);

			_addSystem(new systemT(ctorArgs...));
		}

		/**
			Run process on all systems managed by this system manager for a single
			entity.
		*/
		void process_entity
			( entity& entity );

	private:
		void _addSystem(_detail::system* system);

		using systems_list_type = std::vector<_detail::system*>;
		std::unordered_map<ecs::component_types, systems_list_type> systems;
	};

}// namespace ecs
