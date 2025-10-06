AURELION project guidelines (build, testing, and development)

Audience: Advanced C++ developers working inside CLion using the existing CMake profile.

Last verified on: 2025-10-06 (Debug-Visual Studio profile)

1) Build and configuration specifics for this repository

- Toolchain and language level
  - CMake minimum 3.28; project enforces C++23 (CMAKE_CXX_STANDARD 23, no compiler extensions).
  - GoogleTest is fetched at configure time via FetchContent (URL v1.15.0). Internet access is required on first configure or when clearing the build tree.

- Targets
  - AURELION (executable): main application; links against math.
  - math (static library): contains math/Vector3 implementation; public include path set to src/math.
  - math_tests (executable): unit tests for math.

- Include paths and headers
  - The math target exports src/math as PUBLIC include directory. Headers under src/math/include are therefore included from code and tests as:
    #include "include/Vector3.h"

- CLion / profile constraints
  - Use the existing CLion profile only: Debug-Visual Studio
  - Build directory: C:\Users\Admin\Documents\GitHub\AURELION\cmake-build-debug-visual-studio
  - Do not create new build directories or change the profile.

- Build commands (verified)
  - Build a specific target (preferred):
    cmake --build C:\Users\Admin\Documents\GitHub\AURELION\cmake-build-debug-visual-studio --target math_tests
  - Build everything:
    cmake --build C:\Users\Admin\Documents\GitHub\AURELION\cmake-build-debug-visual-studio

- Artifact locations (Ninja single-config under CLion)
  - math_tests.exe is produced directly in the build root:
    C:\Users\Admin\Documents\GitHub\AURELION\cmake-build-debug-visual-studio\math_tests.exe
  - AURELION.exe is likewise in the same directory.
  - Note: The README shows a bin/ layout, but with the current CLion profile the executables end up at the build root (not in bin/). Prefer discovering paths with Get-ChildItem or by inspecting the build output.

2) Testing: configuration, running, and adding tests

- Framework and CMake wiring
  - GoogleTest is integrated via FetchContent; tests are enabled with enable_testing() and gtest_discover_tests(math_tests).
  - The math_tests target currently compiles tests/tVector3.cpp only (see CMakeLists.txt add_executable(math_tests ...)).

- Running all tests (verified)
  - Option A: run the test executable directly
    C:\Users\Admin\Documents\GitHub\AURELION\cmake-build-debug-visual-studio\math_tests.exe --gtest_color=yes
  - Option B: run through CTest from the build directory (auto-discovers tests via gtest_discover_tests)
    ctest --output-on-failure -V
  - Filtering (GoogleTest):
    math_tests.exe --gtest_filter=Vector3TestFixture.*  (run only Vector3 suite)

- One-shot build + run from PowerShell (recommended while iterating)
  - Build the target and run immediately:
    cmake --build C:\Users\Admin\Documents\GitHub\AURELION\cmake-build-debug-visual-studio --target math_tests; `
    & C:\Users\Admin\Documents\GitHub\AURELION\cmake-build-debug-visual-studio\math_tests.exe --gtest_color=yes

- Adding new tests
  - Fastest path (no CMake edits): append additional TEST/TEST_F cases to tests/tVector3.cpp so they are picked up by the existing math_tests target.
  - Adding a new test source file (requires CMake edit):
    1) Create a new file under tests/, e.g. tests/tVector3_operators.cpp
    2) Add that file to the math_tests sources in CMakeLists.txt:
       add_executable(math_tests
           tests/tVector3.cpp
           tests/tVector3_operators.cpp
       )
    3) Reconfigure/rebuild the math_tests target.
  - If you need a separate test binary, create a new add_executable(<name>) and link PRIVATE math gtest_main, then call gtest_discover_tests(<name>).

- Example: minimal test snippet (can be placed into tests/tVector3.cpp)
  - This is a smoke-test pattern to validate wiring:
    TEST(Vector3Smoke, Sanity) {
        EXPECT_EQ(1, 1);
    }

- Notes about test discovery
  - gtest_discover_tests will register each TEST and TEST_F into CTest at configure/build time. If CTest does not see a new test, ensure you rebuilt the target and (in some cases) re-ran CMake reconfigure.

3) Additional development and debugging information

- Code style and conventions (summarized from CONTRIBUTING.md and current codebase)
  - Prefer small, immutable value types for math primitives with clear ownership semantics.
  - Keep headers lightweight; put implementations in .cpp files under src/ to avoid ODR and to reduce compile times.
  - Avoid extensions; use standard C++23 features. Keep exception use explicit and minimal in math code.
  - Naming aligns with existing Vector3: PascalCase for types (Vector3), snake_case for members (x, y, z public in current design), free functions only when semantically appropriate.
  - Tests: one focused assertion group per TEST where possible; use fixtures for shared setup (see Vector3TestFixture).

- Project layout invariants
  - Public headers for math live under: src/math/include
  - Library sources under: src/math/*.cpp
  - Tests under: tests/*.cpp
  - CMake controls which test sources are compiled; do not rely on globbing.

- Common pitfalls in this repo
  - Header include path: because src/math is the PUBLIC include directory, include headers as "include/Vector3.h" (not <math/Vector3.h>). Mismatching this will fail on some toolchains.
  - Executable output path differs by generator/profile. Under the current CLion Ninja profile, executables land at the build root, not in bin/. Adjust scripts accordingly.
  - First-time configure requires network access to fetch GoogleTest 1.15.0; if offline, vendor the dependency or point FetchContent to a local archive.

- Debugging tips
  - To inspect numerical stability, add EXPECT_NEAR with a local EPSILON; the codebase commonly uses 1e-6f for float comparisons.
  - Use --gtest_filter and --gtest_break_on_failure when iterating a failing case:
    math_tests.exe --gtest_break_on_failure --gtest_filter=Vector3TestFixture.Length
  - From CLion, you can run the math_tests configuration and set breakpoints in both tests and library sources (math is linked statically).

- Extending the math library
  - When adding new types (e.g., Vector2, Matrix4):
    1) Place headers in src/math/include and sources in src/math.
    2) Add new .cpp files to the math target in CMakeLists.txt.
    3) Export public headers via the existing target_include_directories(math PUBLIC src/math).
    4) Add corresponding tests under tests/ and include the new test sources in the math_tests target.

Verification performed for this document

- Built and executed existing math_tests target successfully on the Debug-Visual Studio profile.
- Confirmed executable path: C:\Users\Admin\Documents\GitHub\AURELION\cmake-build-debug-visual-studio\math_tests.exe
- Validated GoogleTest filtering works (e.g., --gtest_filter=Vector3TestFixture.*).
- Demonstrated the process of adding a test by temporarily appending a smoke test to tests/tVector3.cpp, rebuilding, and running it; then reverted the change to keep the repository clean.

Housekeeping

- Please avoid creating new build directories. Use only the CLion-provided build directory and profile.
- Keep third-party dependency versions (like googletest) in sync with CMakeLists; do not upgrade in only part of the toolchain without discussion.
