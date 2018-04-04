#pragma once

#include <type_traits>

#include "../system/system_manager.h"
// #include "../entity/entity_manager.h"

namespace ecs {

	enum solution_state {

		/**
			The solution is broken and cannot continue
		*/
		BROKEN,

		/**
			The solution cannot continue without more input
		*/
		EXAUSTED,

		/**
			The solution has been interrupted and is no longer solving
		*/
		INTERRUPTED,

		/**
			The solution has complete
		*/
		DONE
	};

	/**
		An ecs solution implements both system_manager and entity_manager
	*/
	template<typename solutionT>
	class solution {
	public:

		static_assert(
			!std::is_base_of<solutionT, system_manager>::value,
			"ecs::solution<T> T must inherit ecs::system_manager"
		);

		virtual solution_state solve() noexcept = 0;
	};

}
