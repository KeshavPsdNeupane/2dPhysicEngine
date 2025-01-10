#pragma once

namespace Engine{
	class State {
	public:
		State() {}
		virtual ~State() {}
	public:
		virtual void Load() = 0;
		virtual void ProcessInput() = 0;
		virtual void Update(const float& dt) = 0;
		virtual void Draw() = 0;

		virtual void Pause() {}
		virtual void Start() {}
	};

}