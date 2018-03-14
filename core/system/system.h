#ifndef ECS_SYSTEM_SYSTEM_HPP
#define ECS_SYSTEM_SYSTEM_HPP

#include <type_traits>
#include <iostream>

#include "_detail/system.h"
#include "../component/component.h"

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
				( typename component_type::get_component_type()
				, std::is_reference<T>::value
				, std::is_pointer<T>::value
				, std::is_const<T>::value
				)
		{
			auto componentType = typename component_type::get_component_type();

			std::cout
				<< "Creating system component defintion from template: "
				<< std::to_string(componentType.component_type_hash_code)
				<< std::endl;
		}
	};

	template<typename... componentsT>
	class system : public _detail::system {
	public:

		inline system();

		virtual void process
			( componentsT... components
			) = 0;

	private:

		virtual void _process
			( std::vector<component_base*> components
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
	inline void system<componentsT...>::_process
		( std::vector<component_base*> components
		)
	{

		auto popBackGet = [&](auto dummyParam) {
			auto comp = components.back();
			components.pop_back();

			return comp;
		};

		process(
			*reinterpret_cast<
				std::remove_reference<std::remove_cv<componentsT>::type>::type*
			>(popBackGet(components))...
		);
	}

}

#endif//ECS_SYSTEM_SYSTEM_HPP
