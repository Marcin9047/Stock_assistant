#include "src/interface/imgui/imgui.h"
#include "src/interface/backends/imgui_impl_glfw.h"
#include "src/interface/backends/imgui_impl_opengl3.h"
#include "src/interface/implot/implot_candlestick.h"
#include "src/interface/code/windows.h"
#include <stdio.h>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include "src/interface/implot/implot.h"
#include "src/interface/implot/implot_internal.h"
#include <string>
#include <iostream>
#include <vector>



static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// Main code
int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
    
    // Get the primary monitor's video mode
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
    int screenWidth = videoMode->width;
    int screenHeight = videoMode->height;
    
    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Stock assistant", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);



    // Our state

    show_login_window = true;
    show_profile_data = false;
    show_registration = false;
    show_login_error_window = false;
    ImVec4 clear_color = ImVec4(0.10f, 0.50f, 0.50f, 1.00f);

    // Main loop
#ifdef __EMSCRIPTEN__
    
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    login_window log_wnd;
    profile_window prof_wnd;
    registration_window register_wnd;
    login_error_window error_wnd;

    while (!glfwWindowShouldClose(window))
#endif
    {
        
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        
        if (show_login_window) {

            log_wnd.show(width, height);
        }

        
        if (show_profile_data) {
            prof_wnd.show(width, height);
        }

        if (show_registration) {
            register_wnd.show(width, height);
        }

        if (show_login_error_window) {
            error_wnd.show(width, height);
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
