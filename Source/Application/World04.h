#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include <vector>

namespace nc {
	class World04 : public World {
	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_time;
		float m_speed = 5;

		Transform m_transform;
		
		res_t<Material> m_material;
		res_t<Model> m_model;

		glm::vec3 m_light_pos = { 0.0f, 0.8f, 0.0f };
		glm::vec3 m_light_col{ 0.5f, 0.5f, 0.5f };
		glm::vec3 m_light_amb { 1.0f, 1.0f, 1.0f };
	};
}