# TODO: Display a 3D plane in a window (next checkpoint)

Audience: Advanced C++ devs using CLion with the existing Debug-Visual Studio CMake profile.

Goal: Run AURELION.exe and see a simple shaded 3D plane rendered in a resizable window with a basic camera. Keep changes minimal and incremental.

Status: Planning document only. No code added yet.

---

## High-level plan

1) Choose the rendering stack (recommendation)
- Use OpenGL 3.3 Core via GLFW (window/input/context) + GLAD (loader).
  - Rationale: Lightweight, easy to bring up cross-platform, minimal boilerplate, good for learning. Alternative stacks (Direct3D 11/12 or Vulkan) are heavier.

2) Add third-party deps via CMake FetchContent
- Add GLFW and GLAD in the top-level CMakeLists.txt guarded by an option like AURELION_WITH_RENDERING (default ON once ready).
- Link only the AURELION executable to these libs; keep math library independent.

3) Introduce a tiny render module
- Create src/render/ with these initial components:
  - Window.h/.cpp: wraps GLFW window creation, swap, events, vsync toggle.
  - GlContext.h/.cpp: loads GL via gladLoadGL, owns GL state init (viewport, clear color)
  - Shader.h/.cpp: compile/link small vertex/fragment shaders; set uniforms (mat4, vec3)
  - Mesh.h/.cpp: create VBO/VAO/EBO from raw arrays; draw()
  - Camera.h/.cpp: simple look-at camera; provides view/projection (use existing math: mat4, MatrixTransform::lookAt/perspective).
- Wire these internally without leaking OpenGL into main() except for start/stop.

4) Render a unit plane
- Geometry: two triangles spanning XZ plane centered at origin, e.g. positions and normals:
  - Positions: (-0.5, 0, -0.5), (0.5, 0, -0.5), (0.5, 0, 0.5), (-0.5, 0, 0.5)
  - Indices: (0,1,2), (0,2,3)
  - Normals: (0,1,0) for all vertices.
- Shader: 
  - Vertex: outputs position in clip space via MVP.
  - Fragment: simple directional Lambert shading.

5) Minimal changes to main()
- Replace Hello World with: init Window + GL, create plane mesh + shader, set up Camera, run loop (clear -> set uniforms -> draw -> swap/poll), then cleanup.

6) Math module integration
- Reuse existing math types: Vector3 (vec3), mat4 (Mat4.h), MatrixTransform.h helpers (perspective, lookAt).
- If needed, add small helpers:
  - Convert to column-major float[16] for glUniformMatrix4fv (row/column-major consistency).
  - A simple mat4 translation/rotation/scale builder (optional if MVP can be composed already).
- Do NOT add GL includes to math; keep math pure.

7) Testing and validation
- Build only the AURELION target to test rendering (no unit tests for GL at this stage).
- Keep math unit tests intact. Add math-only tests if you extend mat4.

---

## Step-by-step tasks (actionable)

- [ ] CMake: Add options and FetchContent for GLFW + GLAD
  - [ ] In top-level CMakeLists.txt, add an option AURELION_WITH_RENDERING (default ON).
  - [ ] Use FetchContent to pull GLFW 3.3+ and GLAD (OpenGL core profile). Example snippet:
        include(FetchContent)
        # GLFW
        FetchContent_Declare(
          glfw
          GIT_REPOSITORY https://github.com/glfw/glfw.git
          GIT_TAG 3.3.9
        )
        FetchContent_MakeAvailable(glfw)
        # GLAD (generated repo for OpenGL 3.3 core)
        FetchContent_Declare(
          glad
          GIT_REPOSITORY https://github.com/Dav1dde/glad.git
          GIT_TAG v0.1.36
        )
        FetchContent_MakeAvailable(glad)
  - [ ] Link target AURELION PRIVATE glfw glad
  - [ ] On Windows, link system libs if needed (e.g., opengl32)

- [ ] Source layout: create render module files
  - [ ] src/render/Window.h, Window.cpp
      - Initialize GLFW, set hints for OpenGL 3.3 core, create window, make context current
      - Set swap interval (vsync), provide pollEvents(), shouldClose(), swapBuffers()
  - [ ] src/render/GlContext.h, GlContext.cpp
      - Call gladLoadGL(); set glViewport() on framebuffer resize callback
      - Set glEnable(GL_DEPTH_TEST)
  - [ ] src/render/Shader.h, Shader.cpp
      - Compile and link shaders from in-memory strings for now
      - Uniform setters: setMat4(const char*, const mat4&), setVec3(const char*, const Vector3&)
  - [ ] src/render/Mesh.h, Mesh.cpp
      - Create VAO/VBO/EBO; interleaved position (3) + normal (3)
      - draw(): glBindVertexArray + glDrawElements
  - [ ] src/render/Camera.h, Camera.cpp
      - Fields: position (Vector3), target (Vector3), up (Vector3)
      - Methods: view(), projection(aspect, fov=60deg, near=0.1, far=100)

- [ ] Shaders (inline C-strings inside Shader.cpp for now)
  - [ ] Vertex shader: takes vec3 aPos, vec3 aNormal; uniform mat4 uMVP; gl_Position = uMVP * vec4(aPos,1)
  - [ ] Fragment shader: simple directional light with fixed color

- [ ] Plane mesh setup in main()
  - [ ] Define plane vertices and indices
  - [ ] Create Mesh and Shader instances
  - [ ] Create Camera at eye=(0,1,2), center=(0,0,0), up=(0,1,0)
  - [ ] Each frame: compute MVP = projection * view * model; upload uniforms; draw plane

- [ ] Update src/main.cpp
  - [ ] Replace Hello World with window + render loop
  - [ ] Handle ESC to close window
  - [ ] Clear with glClearColor(0.1,0.1,0.15,1) + GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT

- [ ] Math interop details
  - [ ] Ensure mat4 storage order is consistent with glUniformMatrix4fv (use GL_TRUE/GL_FALSE transpose flag appropriately)
  - [ ] Implement MatrixTransform::perspective and ::lookAt if not implemented yet
  - [ ] If needed: add a helper to flatten mat4 to float[16]

- [ ] Build and run using existing CLion profile
  - [ ] Build the app:
        cmake --build C:\Users\Admin\Documents\GitHub\AURELION\cmake-build-debug-visual-studio --target AURELION
  - [ ] Run the exe (path is the build root under current profile):
        C:\Users\Admin\Documents\GitHub\AURELION\cmake-build-debug-visual-studio\AURELION.exe

- [ ] Nice-to-have (later)
  - [ ] Basic camera orbit controls (mouse drag + scroll)
  - [ ] Grid material and axis gizmo
  - [ ] Resize-aware projection update
  - [ ] Error handling, logs, and GL debug output
  - [ ] Extract shaders to files under assets/shaders

---

## Risks and notes

- Internet is required on first configure for GLFW/GLAD via FetchContent.
- Windows/OpenGL nuances: ensure opengl32.lib is linked; GLAD must be initialized after making a context current.
- Keep math test target (math_tests) unchanged; rendering is not covered by unit tests.
- Coordinate convention assumed: right-handed, Y up, camera looking -Z in view space.

