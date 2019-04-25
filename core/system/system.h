#ifndef ECS_SYSTEM_SYSTEM_HPP
#define ECS_SYSTEM_SYSTEM_HPP

#include <type_traits>
#include <iostream>

#include "_detail/system.h"
#include "../component/component.h"

// Forward declarations
namespace ecs {
	class entity;
}

namespace ecs {

	template<typename T>
	struct system_component_defintion
		: _detail::system_component_definition
	{

		using component_type = typename std::remove_reference<typename std::remove_cv<T>::type>::type;

		static_assert(
			std::is_base_of<component_base, typename std::remove_reference<typename std::remove_cv<T>::type>::type>::value,
			"system_component_defintion<T> T must be a component type"
		);

		system_component_defintion(const system_component_defintion&) = delete;
		system_component_defintion(system_component_defintion&&) = delete;

		inline system_component_defintion()
			: _detail::system_component_definition
				( component_type::get_component_type()
				, std::is_reference<T>::value
				, std::is_pointer<T>::value
				, std::is_const<T>::value
				)
		{ }
	};

	template<typename... componentsT>
	class system : public _detail::system {
	public:

		inline system();

		template<class Rep, class Period = std::ratio<1>>
		std::chrono::duration<Rep, Period> delta() const;

		inline void pre_process() override {}

		virtual void process
			( ecs::entity&    entity
			, componentsT...  components
			) = 0;

		inline void post_process() override {}

	private:

		using _detail::system::_currentTimePoint;
		using _detail::system::_lastTimePoint;

		virtual void _process
			( ecs::entity&                  entity
			, std::vector<component_base*>  components
			) final;

	};

	template<typename... componentsT>
	inline system<componentsT...>::system()
		: _detail::system({
			system_component_defintion<componentsT>{}...
		})
	{

	}

	template<typename... componentsT>
	template<class Rep, class Period>
	inline std::chrono::duration<Rep, Period> system<componentsT...>::delta
		(
		) const
	{
		using std::chrono::duration;

		if(_lastTimePoint == _currentTimePoint) {
			std::cout << "Last time point is same as current time point!" << std::endl;
		}

		return duration<Rep, Period>(
			_currentTimePoint - _lastTimePoint
		);
	}

	template<typename... componentsT>
	inline void system<componentsT...>::_process
		( ecs::entity&                  entity
		, std::vector<component_base*>  components
		)
	{
		auto popBackGet = [&](auto dummyParam) {
			auto comp = components.back();
			components.pop_back();

			return comp;
		};

		process(
			entity,
			*reinterpret_cast<
				typename std::remove_reference<typename std::remove_cv<componentsT>::type>::type*
			>(popBackGet(components))...
		);
	}

}

#endif//ECS_SYSTEM_SYSTEM_HPP
