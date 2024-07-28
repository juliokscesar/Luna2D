#include "Renderer.hpp"

#include "Texture2D.hpp"

namespace Luna::Renderer
{
    static ViewportSpecifications g_viewportSpecs;

    void Init(const ViewportSpecifications &viewportSpecs)
    {
        g_viewportSpecs = viewportSpecs;

        glViewport(0, 0, (GLsizei)viewportSpecs.Width, (GLsizei)viewportSpecs.Height);

	glEnable(GL_DEPTH_TEST);
    }

    void UpdateViewport(uint32_t newWidth, uint32_t newHeight)
    {
        g_viewportSpecs.Width = newWidth;
        g_viewportSpecs.Height = newHeight;
        g_viewportSpecs.AspectRatio = static_cast<float>(newWidth) / static_cast<float>(newHeight);

        glViewport(0, 0, (GLsizei)g_viewportSpecs.Width, (GLsizei)g_viewportSpecs.Height);
    }

    static ShaderLibrary g_shaderLib;
    std::string AddToShaderLib(const Shader &shader)
    {
	g_shaderLib.Add(shader);
	return shader.GetName();
    }

    Ref<Shader> GetFromShaderLib(const std::string& name)
    {
	return g_shaderLib.Get(name);
    }

    void RenderSprite(Ref<Sprite> sprite)
    {
	glBindVertexArray(sprite->GetVAO());

	if (sprite->IsUsingTexture())
	    sprite->GetTexture().Use();
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void RenderEntity(Scene* scene, Ref<Entity> entity, Ref<Shader> shader)
    {
	shader->Use();
	shader->SetUniformMat4("u_projection", scene->GetProjection().Matrix);
	shader->SetUniformMat4("u_worldT", scene->GetWorldTransform());
	shader->SetUniformMat4("u_model", entity->Transform.GetTransformMatrix());
	shader->SetUniformMat4("u_view", scene->GetCamera()->GetViewMatrix());

	if (entity->GetSprite()->IsUsingTexture())
	    shader->SetUniformUInt("u_texUnit", entity->GetSprite()->GetTexture().GetTextureUnit());

	RenderSprite(entity->GetSprite());
    }
    
    void RenderScene(Scene* scene, const std::string& baseShaderName)
    {
	auto baseShader = g_shaderLib.Get(baseShaderName);
	baseShader->Use();
	for (auto& entity : scene->GetAllEntities())
	{
	    RenderEntity(scene, entity, baseShader);
	}
    }

    void ClearColor(float r, float g, float b, float a)
    {
        // TODO: test if glClear can be in NewFrame function
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void EndFrame(GLFWwindow *window)
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
