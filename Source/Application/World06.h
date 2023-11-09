#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include <vector>

namespace nc {
	class World06 : public World {
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
		const uint32_t INVERT_MASK = (1 << 0);
		const uint32_t GRAYSCALE_MASK = (1 << 1);
		const uint32_t COLORTINT_MASK = (1 << 2);

		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_time;
		float m_speed = 5;
		float m_blend = 1;

		uint32_t m_params{ 0 };

		float m_refraction{ 1.0f };
		glm::vec3 m_light_amb { 0.2f };
	};
}