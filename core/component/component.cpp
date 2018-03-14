#include "component.h"

ecs::component_type::component_type
	( const ecs::component_type& other
	)
	: component_type_hash_code(other.component_type_hash_code)
{ }

ecs::component_type::component_type
	( ecs::component_type&& other
	)
	: component_type_hash_code(other.component_type_hash_code)
{ }

ecs::component_type::component_type
	( const std::type_info& typeInfo
	)
	: component_type_hash_code(typeInfo.hash_code())
{ }

ecs::component_types ecs::component_type::operator+
	( const ecs::component_type& componentType
	)
{
	return ecs::component_types{} + componentType;
}

ecs::component_types ecs::component_type::operator+
	( const ecs::component_types& componentTypes
	)
{
	return ecs::component_types{} + componentTypes;
}

bool ecs::component_type::operator<
	( const component_type& other
	) const
{
	return component_type_hash_code < other.component_type_hash_code;
}

ecs::component_types ecs::component_types::operator+
	( const ecs::component_type& componentType
	)
{
	ecs::component_types componentTypesCopy;

	componentTypesCopy += componentType;

	return componentTypesCopy;
}

ecs::component_types ecs::component_types::operator+
	( const ecs::component_types& componentTypes
	)
{
	ecs::component_types componentTypesCopy;

	componentTypesCopy += componentTypes;

	return componentTypesCopy;
}

ecs::component_types& ecs::component_types::operator+=
	( const ecs::component_type& componentType
	)
{
	component_type_indices.insert(
		componentType.component_type_hash_code
	);

	return *this;
}

ecs::component_types& ecs::component_types::operator+=
	( const ecs::component_types& componentTypes
	)
{
	component_type_indices.insert(
		componentTypes.component_type_indices.begin(),
		componentTypes.component_type_indices.end()
	);

	return *this;
}

bool ecs::component_types::operator==
	( const component_types& other
	) const
{
	if(component_type_indices.size() != other.component_type_indices.size()) {
		return false;
	}

	auto size = component_type_indices.size();
	auto componentTypeIndexIt = component_type_indices.begin();
	auto otherComponentTypeIndexIt = other.component_type_indices.begin();

	for(auto i=0; size > i; ++i) {
		auto componentTypeIndex = *componentTypeIndexIt;
		auto otherComponentTypeIndex = *otherComponentTypeIndexIt;

		if(componentTypeIndex != otherComponentTypeIndex) {
			return false;
		}

		++componentTypeIndexIt;
		++otherComponentTypeIndexIt;
	}

	return true;
}

bool ecs::component_types::operator!=
	( const component_types& other
	) const
{
	if(component_type_indices.size() != other.component_type_indices.size()) {
		return true;
	}

	auto size = component_type_indices.size();
	auto componentTypeIndexIt = component_type_indices.begin();
	auto otherComponentTypeIndexIt = other.component_type_indices.begin();

	for(auto i=0; size > i; ++i) {
		auto componentTypeIndex = *componentTypeIndexIt;
		auto otherComponentTypeIndex = *otherComponentTypeIndexIt;

		if(componentTypeIndex != otherComponentTypeIndex) {
			return true;
		}

		++componentTypeIndexIt;
		++otherComponentTypeIndexIt;
	}

	return false;
}
