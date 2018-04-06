#include <string>
#include <cassert>
#include <ecs/core/core.h>

class TestComponent : public ecs::component<TestComponent> {
public:
	std::string some_string;
	float some_float;

	inline TestComponent()
		: some_string("")
		, some_float(0.f)
	{ }

	inline TestComponent(std::string someString, float someFloat)
		: some_string(someString)
		, some_float(someFloat)
	{ }
};

int main() {

	ecs::entity_collection entities;
	{
		ecs::entity testEntity;
		testEntity.add_component<TestComponent>("test", 42.f);

		entities.add_entity_copy(testEntity);
		entities.add_entity_copy(testEntity);
		entities.add_entity_copy(testEntity);
		entities.add_entity_copy(testEntity);
		entities.add_entity_copy(testEntity);
	}

	return 0;
}
