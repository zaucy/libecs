#pragma once

namespace ecs { namespace _detail {

	// boost::hash_combine
	template <class T>
	inline void hashCombine
		( std::size_t& seed
		, const T& v
		)
	{
		std::hash<T> hasher;
		seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
	}

}}//namespace ecs::_detail
