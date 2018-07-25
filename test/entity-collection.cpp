#include <string>
#include <cassert>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <ecs/core/core.h>
#include "gtest/gtest.h"

auto testRandNum() {
	std::srand(std::time(nullptr));
	return std::rand();
}

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

class TestSystem : public ecs::system<TestComponent&> {
public:
	virtual void process
		( ecs::entity&    entity
		, TestComponent&  testComponent
		)
	{

	}
};

TEST(Entities, EntityCollectionIteration) {
	ecs::entity_collection entities;
	ecs::entity testEntity;
	testEntity.add_component<TestComponent>("test", 42.f);

	auto expectedCount = testRandNum();

	for(auto i=0; expectedCount > i; ++i) {
		entities.add_entity_copy(testEntity);
	}

	auto entityCount = 0;
	for(auto& entity : entities) {
		++entityCount;
	}

	ASSERT_EQ(entityCount, expectedCount);
}

TEST(Entities, EntityCopy) {
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

	for(auto& entity : entities) {
		auto foundSelf = false;
		for(auto& otherEntity : entities) {
			if(!foundSelf && entity.id() == otherEntity.id()) {
				foundSelf = true;
				continue;
			}


			ASSERT_NE(entity.id(), otherEntity.id());
		}
	}
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
