#ifndef PERHAPS_PCH
#define PERHAPS_PCH

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Vendor/stb/stb_image.h"
#include "entt/entt.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"

#include "mono/jit/jit.h"
#include "mono/metadata/assembly.h"
#include "mono/metadata/debug-helpers.h"
#include "mono/metadata/mono-debug.h"
#include "mono/metadata/threads.h"

#include <thread>
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
#include <array>
#include <unordered_set>

#define conlog(x) std::cout << x << "\n";
typedef glm::vec4 Color;

#define PAPI extern "C" __declspec(dllexport)

void __M_Assert(const char* expr_str, bool expr, const char* file, int line, const char* msg);
#ifndef NDEBUG
#   define passert(Expr, Msg) \
    __M_Assert(#Expr, Expr, __FILE__, __LINE__, Msg)
#else
#   define passert(Expr, Msg) ;
#endif



#endif