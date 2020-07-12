#ifndef PERHAPS_PCH
#define PERHAPS_PCH
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "../Vendor/stb/stb_image.h"

#include "mono/jit/jit.h"
#include "mono/metadata/assembly.h"
#include "mono/metadata/debug-helpers.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <functional>
#include <unordered_map>
#include <map>
#include <filesystem>
#include <exception>

#define conlog(x) std::cout << x << "\n";
typedef glm::vec4 Color;

#define PAPI extern "C" __declspec(dllexport)

#endif