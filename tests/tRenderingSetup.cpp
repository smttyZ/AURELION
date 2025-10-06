#include <gtest/gtest.h>

// GLAD (v0.1.x) must be included before GLFW's OpenGL headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Simple RAII helpers to ensure clean teardown even if assertions fail
struct GlfwGuard {
    GlfwGuard() { ok = (glfwInit() == GLFW_TRUE); }
    ~GlfwGuard() { if (ok) glfwTerminate(); }
    bool ok = false;
};

TEST(RenderingSetup, CanCreateHiddenWindowAndLoadGL) {
    GlfwGuard glfw;
    ASSERT_TRUE(glfw.ok) << "glfwInit failed";

    // Request a modern core profile 3.3 context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
    // Create a hidden, small window for headless-ish smoke test
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(320, 240, "render_smoke", nullptr, nullptr);
    ASSERT_NE(window, nullptr) << "glfwCreateWindow failed";

    glfwMakeContextCurrent(window);

    // Load GL function pointers via GLAD (v0.1 API)
    int glad_ok = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    ASSERT_EQ(glad_ok, 1) << "gladLoadGLLoader failed";

    // Basic sanity: GL version string should be available now
    const GLubyte* ver = glGetString(GL_VERSION);
    ASSERT_NE(ver, nullptr) << "glGetString(GL_VERSION) returned nullptr";

    // Ensure we got at least GL 3.3 core through GLAD's reported availability
    ASSERT_TRUE(GLAD_GL_VERSION_3_3) << "GL 3.3 functions not reported as available by GLAD";

    // Cleanup
    glfwDestroyWindow(window);
}
