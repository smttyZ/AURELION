# Contributing to AURELION

First off, thank you for considering contributing to AURELION! This document provides guidelines and instructions for contributing to the project.

## 📋 Table of Contents

- [Code of Conduct](#code-of-conduct)
- [Getting Started](#getting-started)
- [Development Process](#development-process)
- [Coding Standards](#coding-standards)
- [Commit Guidelines](#commit-guidelines)
- [Pull Request Process](#pull-request-process)
- [Issue Reporting](#issue-reporting)

## Code of Conduct

Please read and follow our [Code of Conduct](CODE_OF_CONDUCT.md) to maintain a welcoming and inclusive environment.

## Getting Started

1. **Fork the repository** on GitHub
2. **Clone your fork** locally:
   ```bash
   git clone https://github.com/yourusername/AURELION.git
   cd AURELION
   ```
3. **Add upstream remote**:
   ```bash
   git remote add upstream https://github.com/originalowner/AURELION.git
   ```
4. **Create a branch** for your feature or fix:
   ```bash
   git checkout -b feature/your-feature-name
   ```

## Development Process

### 1. Before Starting Work

- Check existing issues and pull requests to avoid duplicate work
- For significant changes, open an issue first to discuss your proposal
- Ensure your fork is up to date with the main branch

### 2. During Development

- Write code following our coding standards (see below)
- Add tests for new functionality
- Update documentation as needed
- Keep commits focused and atomic

### 3. Before Submitting

- Run all tests: `ctest --verbose`
- Ensure code compiles without warnings
- Update the CHANGELOG.md if applicable
- Rebase on the latest main branch

## Coding Standards

Based on the established patterns in our codebase (see Vector3 for reference):

### C++ Style Guide

#### File Organization
```cpp
// Header files (.h)
#pragma once

#include <system_headers>
#include <alphabetically>

#include "project_headers"
#include "alphabetically"

namespace math {

/**
 * @class ClassName
 * @brief Brief description.
 *
 * Detailed description including purpose, usage, and important notes.
 *
 * Example usage:
 * @code
 * // Example code here
 * @endcode
 */
class ClassName {
public:
    // Public members (if any)
    
    // Constructors and destructor
    
    // Public methods
    
private:
    // Private members
    
    // Private methods
};

} // namespace math
```

#### Implementation Files (.cpp)
```cpp
#include "include/ClassName.h"

namespace math {

// Constructor implementations

// Method implementations (in same order as header)

} // namespace math
```

### Naming Conventions

- **Classes**: `PascalCase` (e.g., `Vector3`, `PhysicsEngine`)
- **Methods/Functions**: `camelCase` (e.g., `normalize()`, `lengthSquared()`)
- **Variables**: `camelCase` (e.g., `velocity`, `maxIterations`)
- **Constants**: `UPPER_SNAKE_CASE` (e.g., `MAX_VELOCITY`, `DEFAULT_GRAVITY`)
- **Namespaces**: `lowercase` (e.g., `math`, `physics`)
- **Files**: Match class name (e.g., `Vector3.h`, `Vector3.cpp`)

### Documentation

All public APIs must be documented using Doxygen format:

```cpp
/**
 * @brief Brief description of the function.
 *
 * Detailed description if needed.
 *
 * @param paramName Description of parameter.
 * @return Description of return value.
 *
 * @note Any important notes.
 * @warning Any warnings about usage.
 */
```

### Code Practices

1. **RAII**: Use Resource Acquisition Is Initialization
2. **Const Correctness**: Mark methods and parameters `const` when appropriate
3. **References**: Prefer references over pointers when null is not valid
4. **Smart Pointers**: Use `std::unique_ptr` and `std::shared_ptr` over raw pointers
5. **Auto**: Use `auto` for complex type declarations, but be explicit for primitives
6. **Range-based for loops**: Prefer over traditional loops when possible
7. **Early Returns**: Use guard clauses to reduce nesting

### Example Following Our Standards

```cpp
// Good example following Vector3 patterns
Vector3 Vector3::normalized() const {
    float len = length();
    if (len == 0) return {0, 0, 0};  // Guard clause
    return *this / len;               // Clean return
}

// Compound operators for efficiency
Vector3& Vector3::operator+=(const Vector3& rhs) {
    x += rhs.x; y += rhs.y; z += rhs.z;
    return *this;
}
```

## Commit Guidelines

### Commit Message Format

```
<type>: <subject>

<body>

<footer>
```

### Types
- **feat**: New feature
- **fix**: Bug fix
- **docs**: Documentation changes
- **style**: Code style changes (formatting, missing semicolons, etc.)
- **refactor**: Code refactoring
- **perf**: Performance improvements
- **test**: Adding or modifying tests
- **build**: Build system or dependency changes
- **ci**: CI/CD configuration changes
- **chore**: Other changes that don't modify src or test files

### Example
```
feat: Add quaternion multiplication operator

Implements Hamilton product for quaternion multiplication following
right-hand convention. Includes operator* and operator*= overloads.

Closes #42
```

### Commit Best Practices
- Keep commits atomic and focused
- Write clear, descriptive commit messages
- Reference issues when applicable
- Sign your commits: `git commit -s`

## Pull Request Process

### Before Submitting a PR

1. **Update your branch**:
   ```bash
   git fetch upstream
   git rebase upstream/main
   ```

2. **Run tests locally**:
   ```bash
   cd build
   cmake ..
   cmake --build .
   ctest --verbose
   ```

3. **Check for compilation warnings**:
   ```bash
   cmake -DCMAKE_CXX_FLAGS="-Wall -Wextra -Wpedantic" ..
   cmake --build .
   ```

### PR Checklist

- [ ] Code follows the project's coding standards
- [ ] All tests pass
- [ ] New features include tests
- [ ] Documentation is updated
- [ ] Commit messages follow guidelines
- [ ] PR description clearly explains changes
- [ ] No merge conflicts with main branch
- [ ] CHANGELOG.md updated (if applicable)

### PR Description Template

```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Breaking change
- [ ] Documentation update

## Testing
- [ ] Unit tests pass
- [ ] Integration tests pass
- [ ] Manual testing completed

## Related Issues
Closes #(issue number)

## Screenshots (if applicable)
```

## Issue Reporting

### Before Creating an Issue

- Search existing issues to avoid duplicates
- Check the documentation and FAQ
- Ensure you're using the latest version

### Issue Templates

We provide templates for:
- **Bug Reports**: Unexpected behavior or errors
- **Feature Requests**: New functionality proposals
- **Documentation**: Documentation improvements
- **Questions**: General questions (consider Discussions first)

### Good Issue Practices

- Use clear, descriptive titles
- Provide minimal reproducible examples for bugs
- Include system information (OS, compiler, versions)
- Add relevant labels
- Be respectful and constructive

## Testing

### Writing Tests

- Place tests in the `tests/` directory
- Name test files with `t` prefix (e.g., `tVector3.cpp`)
- Use descriptive test names
- Test edge cases and error conditions
- Aim for high code coverage

### Test Structure Example

```cpp
#include <cassert>
#include <iostream>
#include "math/include/Vector3.h"

void testNormalization() {
    math::Vector3 v(3.0f, 4.0f, 0.0f);
    v.normalize();
    assert(std::abs(v.length() - 1.0f) < 0.0001f);
    std::cout << "✓ Normalization test passed\n";
}

int main() {
    testNormalization();
    // More tests...
    std::cout << "All tests passed!\n";
    return 0;
}
```

## Code Review

All submissions require code review. During review:

- Be open to feedback and suggestions
- Respond to all review comments
- Make requested changes in new commits (don't force-push during review)
- Mark conversations as resolved when addressed
- Be patient - reviewers are volunteers

## Recognition

Contributors will be:
- Listed in the project's contributors section
- Mentioned in release notes for significant contributions
- Given credit in relevant documentation

## Questions?

If you have questions:
1. Check the documentation
2. Search existing issues
3. Ask in GitHub Discussions
4. Contact the maintainers

## License

By contributing to AURELION, you agree that your contributions will be licensed under the MIT License.

---

Thank you for helping make AURELION better! 🚀