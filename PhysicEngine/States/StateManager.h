#pragma once
#include<stack>
#include<memory>
#include"State.h"

namespace Engine {
	class StateManager {
	private:
		std::stack<std::unique_ptr<Engine::State>> states;
		std::unique_ptr<Engine::State> newState;
		bool isAdd;
		bool isReplace;
		bool isRemove;
	public:
		StateManager();
		~StateManager();

	public:
		void AddState(std::unique_ptr<State> state, bool isReplacing = true);
		void RemoveState();
		void ProcessStateChanges();
		std::unique_ptr<State>& GetActiveState();
	};

}
