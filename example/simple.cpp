#include <iostream>
#include <ecs/core/core.h>

/**
	SimpleGame is an ecs::solution. An ecs::solution must inherit an
	entity_manager and a system_manager. To ensure this is correct a solution
	inherits a helper template class that checks this at compile time.
*/
class SimpleGame
	: public ecs::entity_manager
	, public ecs::system_manager
	, public ecs::solution<SimpleGame>
{
public:

	virtual ecs::solution_state solve() noexcept override {

		auto entities = get_entities();

		for(auto& entity : entities) {
			process_entity(entity);
		}

		return ecs::solution_state::INTERRUPTED;
	}

};

class PositionComponent
	: public ecs::component<PositionComponent>
{
public:
	float x = 0.f;
	float y = 0.f;

	PositionComponent() = default;
	inline PositionComponent(float x, float y): x(x), y(y) {}
};

class GravitySystem
	: public ecs::system<PositionComponent&>
{
public:

	virtual void process
		( ecs::entity&        entity
		, PositionComponent&  positionComponent
		) override
	{
		positionComponent.y -= 9.81f;

		std::cout
			<< "Gravity system processing entity! "
			<< "y = " << positionComponent.y
			<< std::endl;
	}
};

int main() {
	SimpleGame game;
	int exitCode = 0;
	bool exiting = false;

	ecs::entity testEntity;
	testEntity.add_component<PositionComponent>(0.f, 10.f);

	game.add_entity_copy(testEntity);
	game.add_system<GravitySystem>();

	while(!exiting) {
		auto state = game.solve();

		switch(state) {
			case ecs::solution_state::BROKEN:
				exitCode = 1;
				exiting = true;
				break;
			case ecs::solution_state::DONE:
				exiting = true;
				break;
			default:
				std::cout << "Solution solve() state: " << state << std::endl;
		}
	}

	return exitCode;
}
