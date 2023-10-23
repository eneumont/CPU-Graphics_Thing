#include "World04.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"

#include <glm/glm/gtc/type_ptr.hpp>

namespace nc {
    bool World04::Initialize() {
        auto material = GET_RESOURCE(Material, "Materials/grid.mtrl");
        m_model = std::make_shared<Model>();
        m_model->SetMaterial(material);
        //m_model->Load("Models/plane.obj");
        //m_transform.position.y = -1;
        //m_model->Load("Models/bob.obj", glm::vec3{ 0 }, glm::vec3{ -90, 0, 0});
        m_model->Load("Models/buddha.obj");

        m_light.type = light_t::eType::Point;
        m_light.position = glm::vec3{ 0, 5, 0 };
        m_light.direction = glm::vec3{ 0, -1, 0 };
        m_light.color = glm::vec3{ 1, 1, 1 };
        m_light.cutoff = 30.0;

        return true;
    }

    void World04::Shutdown() {

    }

    void World04::Update(float dt) {
        ENGINE.GetSystem<Gui>()->BeginFrame();

        ImGui::Begin("Transform");
        ImGui::DragFloat3("Position", &m_transform.position[0], 0.1f);
        ImGui::DragFloat3("Rotation", &m_transform.rotation[0]);
        ImGui::DragFloat3("Scale", &m_transform.scale[0], 0.1f);
        ImGui::End();

        ImGui::Begin("Light");
        const char* types[] = {"Point", "Directional", "Spot"};
        //ImGui::Combo("Type", (int*)(&m_light.type), types, 3);
        ImGui::Combo("Type", (int*)(&m_light.type), types, 3);

        if (m_light.type != light_t::Directional) ImGui::DragFloat3("Position", &m_light.position[0], 0.1f); //may need to tweak these
        if (m_light.type != light_t::Point) ImGui::DragFloat3("Direction", &m_light.direction[0], 0.1f); //may need to tweak these
        if (m_light.type != light_t::Spot) ImGui::DragFloat("Cutoff", &m_light.cutoff, 1, 0, 90); //may need to tweak these
        ImGui::ColorEdit3("Light Color", &m_light.color[0], 0.1f);
        ImGui::ColorEdit3("Light Ambience", &m_light_amb[0], 0.1f);
        ImGui::End();
        //can do glm::value_ptr() or 

        //m_transform.rotation.z += 90 * dt;

        m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? m_speed * -dt : 0;
        m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? m_speed * dt : 0;
        m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? m_speed * -dt : 0;
        m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? m_speed * dt : 0;
        m_time += dt;

        auto material = m_model->GetMaterial();

        material->ProcessGui();
        material->Bind();
        /*m_program->SetUniform("offset", glm::vec2{ 0, 0 });
        m_program->SetUniform("tiling", glm::vec2{ 2, 2 });*/

        //model
        material->GetProgram()->SetUniform("model", m_transform.GetMatrix());

        //view
        glm::mat4 view = glm::lookAt(glm::vec3{ 0, 0, 3 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0});
        material->GetProgram()->SetUniform("view", view);

        //projection
        glm::mat4 projection = glm::perspective(glm::radians(70.0f), (float ) ENGINE.GetSystem<Renderer>()->GetWidth() / ENGINE.GetSystem<Renderer>()->GetWidth(), 0.01f, 100.0f);
        material->GetProgram()->SetUniform("projection", projection);

        //light
        material->GetProgram()->SetUniform("light.type", m_light.type);
        material->GetProgram()->SetUniform("light.position", m_light.position);
        material->GetProgram()->SetUniform("light.direction", m_light.direction);
        material->GetProgram()->SetUniform("light.color", m_light.color);
        material->GetProgram()->SetUniform("light.cutoff", glm::radians(m_light.cutoff));
        material->GetProgram()->SetUniform("ambientLight", m_light_amb);

        ENGINE.GetSystem<Gui>()->EndFrame();
    }

    void World04::Draw(Renderer& renderer) {
        // pre-render
        renderer.BeginFrame();

        // render
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        m_model->Draw(GL_TRIANGLES);
        ENGINE.GetSystem<Gui>()->Draw();

        // post-render
        renderer.EndFrame();
    }
}