#include "GUI.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui_internal.h"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <string>

namespace Luna::GUI
{
    void InitContext(GLFWwindow* glfwWindow)
    {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// setup imgui style
	ImGui::StyleColorsDark();

	// setup backends
	ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330");
    }

    void NewFrame()
    {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
    }

    void Render()
    {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Terminate()
    {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::Shutdown();
	ImGui::DestroyContext();
    }

    void FrameStatsWindow(float deltaTime)
    {
	ImGui::Begin("Frame stats");

	ImGui::Text("Time per frame: %f ms", deltaTime * 1000.0f);
	ImGui::Text("FPS: %f", 1.0f / deltaTime);

	ImGui::End();
    }

    void EntityPropertiesManager(Scene* scene)
    {
	if (!scene)
	    return;

	ImGui::Begin("Entity properties");

	auto& sceneEntities = scene->GetAllEntities();
	static Entity* selectedEntity = nullptr;
	static uint32_t selectedId = 0;
	for (size_t id = 0; id < sceneEntities.size(); id++)
	{
	    const std::string btnLabel = sceneEntities[id]->Name + "##" + std::to_string(id);

	    if (ImGui::Button(btnLabel.c_str()))
	    {
		selectedEntity = sceneEntities[id].get();
		selectedId = (uint32_t)id;
	    }
	    ImGui::SameLine();
	}
	ImGui::NewLine();
	if (selectedEntity)
	{
	    const std::string labelId = "##" + std::to_string(selectedId);
	    glm::vec3 position = selectedEntity->Transform.GetPosition();
	    glm::vec3 rotation = selectedEntity->Transform.GetRotation();
	    glm::vec3 scale = selectedEntity->Transform.GetScale();

	    ImGui::Text("Properties");

	    ImGui::Text("Position"); ImGui::SameLine();
	    ImGui::InputFloat3((labelId+"p").c_str(), glm::value_ptr(position));

	    ImGui::Text("Rotation"); ImGui::SameLine();
	    ImGui::InputFloat3((labelId+"r").c_str(), glm::value_ptr(rotation));

	    ImGui::Text("Scale   "); ImGui::SameLine();
	    ImGui::InputFloat3((labelId+"s").c_str(), glm::value_ptr(scale));

	    selectedEntity->Transform.SetPosition(position);
	    selectedEntity->Transform.SetRotation(rotation);
	    selectedEntity->Transform.SetScale(scale);

	    
	    bool visible = selectedEntity->IsVisible();
	    ImGui::Text("Visible"); ImGui::SameLine();
	    ImGui::Checkbox((labelId+"v").c_str(), &visible);
	    selectedEntity->SetVisible(visible);
	}

	ImGui::End();
    }
}

