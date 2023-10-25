#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include <vector>

namespace nc {
	class World05 : public World {
		struct light_t {
			enum eType {
				Point,
				Directional,
				Spot
			};

			int type;
			glm::vec3 position;
			glm::vec3 direction;
			glm::vec3 color;
			float intensity;
			float range;
			float innerAngle;
			float outerAngle;
		};

	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_time;
		float m_speed = 5;

		glm::vec3 m_light_amb { 0.2f };
	};
}