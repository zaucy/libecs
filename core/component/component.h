#pragma once

#include <iostream>

#include <set>
#include <string>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <cstdint>
#include <functional>
#include <utility>

#include "_detail/hashCombine.h"

// Forward Declarations
namespace ecs {
	struct component_types;
	class component_base;
}

namespace ecs {

	/*
		A component_type holds the runtime type information as well as functors
		for making a copy of a component of the component represented by the
		runtime type information.

		This is mostly used internally and you shouldn't need to use this class.
	*/
	struct component_type {
		using copy_fn_type = std::function<component_base*(const component_base*)>;

		component_type() = delete;
		component_type(const component_type&);
		component_type(component_type&&);
		component_type
			( const std::type_info&  typeInfo
			, const std::size_t      typeSize
			, copy_fn_type           copyFn
			);

		component_type& operator=(component_type) = delete;
		component_type& operator=(component_type&&) = delete;
		component_type& operator=(const component_type&) = delete;

		const std::size_t component_type_hash_code;
		const std::size_t component_type_size;
		const copy_fn_type component_copy_fn;

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
			static const ecs::component_type componentType{
				typeid(T), sizeof(T), [](const component_base* c) -> component_base* {
					return new T{*reinterpret_cast<const T*>(c)};
				}
			};

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
