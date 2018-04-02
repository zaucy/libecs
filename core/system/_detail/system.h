#pragma once

#include <vector>
#include <string>

#include "../../component/component.h"

// Forward Declarations
namespace ecs {
	class system_manager;
	class entity;
}


namespace ecs { namespace _detail {

	/**

	*/
	struct system_component_definition {
		const ecs::component_type& component_type;
		const bool copy;
		const bool optional;
		const bool readonly;

		system_component_definition() = delete;

		system_component_definition
			( const ecs::component_type& component_type
			, bool copy
			, bool optional
			, bool readonly
			);

		system_component_definition
			( const system_component_definition& other
			);

		system_component_definition
			( system_component_definition&& other
			);
	};

	class system {
	public:

		ecs::component_types component_types() const;

	protected:

		friend ecs::system_manager;

		system
			( std::vector<system_component_definition> componentDefinitions
			);

		virtual void _process
			( ecs::entity&                  entity
			, std::vector<component_base*>  components
			) = 0;

	private:

		std::vector<system_component_definition> _componentDefinitions;

	};

}}// namespace ecs::_detail
