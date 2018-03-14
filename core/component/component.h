#pragma once

#include <iostream>

#include <set>
#include <string>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <type_traits>

#include "_detail/hashCombine.h"

// Forward Declarations
namespace ecs {
	struct component_types;
}

namespace ecs {

	struct component_type {
		component_type() = delete;
		component_type(const component_type&);
		component_type(component_type&&);
		component_type(const std::type_info& typeInfo);

		component_type& operator=(component_type) = delete;
		component_type& operator=(component_type&&) = delete;
		component_type& operator=(const component_type&) = delete;

		const std::size_t component_type_hash_code;

		component_types operator+(const component_type&);
		component_types operator+(const component_types&);

		bool operator<
			( const component_type& other
			) const;

		// operator bool
		// 	(
		// 	) const;
	};

	struct component_types {
		component_types operator+(const component_type&);
		component_types operator+(const component_types&);

		component_types& operator+=(const component_type&);
		component_types& operator+=(const component_types&);

		bool operator==
			( const component_types& other
			) const;

		bool operator!=
			( const component_types& other
			) const;

		std::set<std::size_t> component_type_indices;
	};

	class component_base {};

	template<typename T>
	class component : public component_base {
	public:

		static const component_type& get_component_type() {
			static const ecs::component_type componentType{typeid(T)};

			return componentType;
		};
	};

}

namespace std {
	template<>
	struct hash<ecs::component_types> {
		using argument_type = ecs::component_types;
		using result_type = std::size_t;

		result_type operator()
			( argument_type const& componentTypes
			) const noexcept
		{
			std::size_t hashValue = 0;

			for(auto componentTypeIndex : componentTypes.component_type_indices) {
				ecs::_detail::hashCombine(hashValue, componentTypeIndex);
			}

			return hashValue;
		}
	};
}
