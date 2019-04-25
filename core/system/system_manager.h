#pragma once

#include <unordered_map>
#include <vector>
#include <type_traits>

#include "_detail/system.h"
#include "../component/component.h"

// Forward Declarations
namespace ecs {
	class entity;
	class entity_collection;
	class system_manager;
}

namespace ecs {

	class system_manager_entity_processor {
	private:
		system_manager& _systemManager;

		friend system_manager;
	public:
		system_manager_entity_processor
			( system_manager&
			);
		system_manager_entity_processor
			( const system_manager_entity_processor&
			) = delete;
		system_manager_entity_processor
			( system_manager_entity_processor&&
			) = delete;
		~system_manager_entity_processor();

		/**
			Run process on all systems managed by this system manager for a single
			entity.
		*/
		void process_entity
			( entity& entity );

		void process_entities
			( entity_collection& entities );
	};

	class system_manager {
	public:

		friend system_manager_entity_processor;

		system_manager();
		system_manager(const system_manager&) = delete;
		system_manager(system_manager&&) = delete;
		~system_manager();

		/*
			Add system system manager. add_system simply constructs systemT passing in
			ctorArgsT into the constructor.
		*/
		template<typename systemT, typename... ctorArgsT>
		inline void add_system(ctorArgsT&&... ctorArgs) {

			static_assert(
				std::is_base_of<_detail::system, systemT>::value,
				"system_manager.add_system<systemT>() systemT must be base of ecs::system"
			);

			_addSystem(new systemT(std::forward<ctorArgsT>(ctorArgs)...));
		}

	private:
		using systems_list_type = std::vector<_detail::system*>;

		void _addSystem(_detail::system* system);

		systems_list_type _matchSystems(const ecs::component_types&);

		systems_list_type systemsList;
		std::unordered_map<ecs::component_types, systems_list_type> systemsListMap;
	};

}// namespace ecs
