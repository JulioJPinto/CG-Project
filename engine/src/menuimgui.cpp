#include "menuimgui.hpp"

void setupMenu()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGLUT_Init();
    ImGui_ImplOpenGL3_Init();
}

void shutDownMenu()
{
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();
}

bool w = false;

void renderMenu() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    {
      ImGui::Begin("Infos", NULL, ImGuiWindowFlags_AlwaysAutoResize);

      ImGui::Text("FPS: %f", io.Framerate);

      ImGui::End();
    }
    ImGui::Render();
    glViewport(0, 0, (GLsizei) io.DisplaySize.x, (GLsizei) io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
