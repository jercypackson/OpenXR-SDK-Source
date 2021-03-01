// Copyright (c) 2017-2020 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include <bitset>
#include <iostream>
#include <fstream>
#include <sstream>

#include "pch.h"
#include "common.h"
#include "geometry.h"
#include "data.h"
#include "graphicsplugin.h"
#include "Matrix_lib.h"
#include "options.h"

#include <algorithm>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#ifdef XR_USE_GRAPHICS_API_OPENGL

#include <common/gfxwrapper_opengl.h>
#include <common/xr_linear.h>


namespace {
constexpr float DarkSlateGray[] = {0.184313729f, 0.309803933f, 0.309803933f, 1.0f};

int width = 932;
int height = 1036;

//static const char* VertexShaderGlsl = R"_(
//    #version 410
//
//    in vec3 VertexPos;
//    in vec3 VertexColor;
//
//    out vec3 PSVertexColor;
//
//    uniform mat4 ModelViewProjection;
//
//    void main() {
//       gl_Position = ModelViewProjection * vec4(VertexPos, 1.0);
//       PSVertexColor = VertexColor;
//    }
//    )_";
//
//static const char* FragmentShaderGlsl = R"_(
//    #version 410
//
//    in vec3 PSVertexColor;
//    out vec4 FragColor;
//
//    void main() {
//       FragColor = vec4(PSVertexColor, 1);
//    }
//    )_";

struct OpenGLGraphicsPlugin : public IGraphicsPlugin {
    OpenGLGraphicsPlugin(const std::shared_ptr<Options>& opt, const std::shared_ptr<IPlatformPlugin> /*unused*/&) :
        options(opt) {}

    OpenGLGraphicsPlugin(const OpenGLGraphicsPlugin&) = delete;
    OpenGLGraphicsPlugin& operator=(const OpenGLGraphicsPlugin&) = delete;
    OpenGLGraphicsPlugin(OpenGLGraphicsPlugin&&) = delete;
    OpenGLGraphicsPlugin& operator=(OpenGLGraphicsPlugin&&) = delete;

    ~OpenGLGraphicsPlugin() override {
        if (m_swapchainFramebuffer != 0) {
            glDeleteFramebuffers(1, &m_swapchainFramebuffer);
        }
        if (m_program != 0) {
            glDeleteProgram(m_program);
        }
        if (m_vao_pnt != 0) {
            glDeleteVertexArrays(1, &m_vao_pnt);
        }
        if (m_vao_tess != 0) {
            glDeleteVertexArrays(1, &m_vao_tess);
        }
        if (m_pntBuffer != 0) {
            glDeleteBuffers(1, &m_pntBuffer);
        }
        if (m_cubeIndexBuffer != 0) {
            glDeleteBuffers(1, &m_cubeIndexBuffer);
        }

        for (auto& colorToDepth : m_colorToDepthMap) {
            if (colorToDepth.second != 0) {
                glDeleteTextures(1, &colorToDepth.second);
            }
        }
    }

    std::vector<std::string> GetInstanceExtensions() const override { return {XR_KHR_OPENGL_ENABLE_EXTENSION_NAME}; }

    ksGpuWindow window{};

    void DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message) {
        (void)source;
        (void)type;
        (void)id;
        (void)severity;
        Log::Write(Log::Level::Info, "GL Debug: " + std::string(message, 0, length));
    }

    void InitializeDevice(XrInstance instance, XrSystemId systemId) override {
        // Extension function must be loaded by name
        PFN_xrGetOpenGLGraphicsRequirementsKHR pfnGetOpenGLGraphicsRequirementsKHR = nullptr;
        CHECK_XRCMD(xrGetInstanceProcAddr(instance, "xrGetOpenGLGraphicsRequirementsKHR",
                                          reinterpret_cast<PFN_xrVoidFunction*>(&pfnGetOpenGLGraphicsRequirementsKHR)));

        XrGraphicsRequirementsOpenGLKHR graphicsRequirements{XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_KHR};
        CHECK_XRCMD(pfnGetOpenGLGraphicsRequirementsKHR(instance, systemId, &graphicsRequirements));

        // Initialize the gl extensions. Note we have to open a window.
        ksDriverInstance driverInstance{};
        ksGpuQueueInfo queueInfo{};
        ksGpuSurfaceColorFormat colorFormat{KS_GPU_SURFACE_COLOR_FORMAT_B8G8R8A8};
        ksGpuSurfaceDepthFormat depthFormat{KS_GPU_SURFACE_DEPTH_FORMAT_D24};
        ksGpuSampleCount sampleCount{KS_GPU_SAMPLE_COUNT_1};
        if (!ksGpuWindow_Create(&window, &driverInstance, &queueInfo, 0, colorFormat, depthFormat, sampleCount, width, height, false)) {
            THROW("Unable to create GL context");
        }

        GLint major = 0;
        GLint minor = 0;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);

        const XrVersion desiredApiVersion = XR_MAKE_VERSION(major, minor, 0);
        if (graphicsRequirements.minApiVersionSupported > desiredApiVersion) {
            THROW("Runtime does not support desired Graphics API and/or version");
        }

#ifdef XR_USE_PLATFORM_WIN32
        m_graphicsBinding.hDC = window.context.hDC;
        m_graphicsBinding.hGLRC = window.context.hGLRC;
#elif defined(XR_USE_PLATFORM_XLIB)
        m_graphicsBinding.xDisplay = window.context.xDisplay;
        m_graphicsBinding.visualid = window.context.visualid;
        m_graphicsBinding.glxFBConfig = window.context.glxFBConfig;
        m_graphicsBinding.glxDrawable = window.context.glxDrawable;
        m_graphicsBinding.glxContext = window.context.glxContext;
#elif defined(XR_USE_PLATFORM_XCB)
        // TODO: Still missing the platform adapter, and some items to make this usable.
        m_graphicsBinding.connection = window.connection;
        // m_graphicsBinding.screenNumber = window.context.screenNumber;
        // m_graphicsBinding.fbconfigid = window.context.fbconfigid;
        m_graphicsBinding.visualid = window.context.visualid;
        m_graphicsBinding.glxDrawable = window.context.glxDrawable;
        // m_graphicsBinding.glxContext = window.context.glxContext;
#elif defined(XR_USE_PLATFORM_WAYLAND)
        // TODO: Just need something other than NULL here for now (for validation).  Eventually need
        //       to correctly put in a valid pointer to an wl_display
        m_graphicsBinding.display = reinterpret_cast<wl_display*>(0xFFFFFFFF);
#endif

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(
            [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message,
               const void* userParam) {
                ((OpenGLGraphicsPlugin*)userParam)->DebugMessageCallback(source, type, id, severity, length, message);
            },
            this);

        InitializeResources();
    }


    std::string readFile(std::string filename)
    {
        //https://github.com/JoeyDeVries/LearnOpenGL/blob/95ed602bd6e2a8b796ea84b363c7b4b31e6334ca/includes/learnopengl/shader_s.h#L17

        std::string code;
        std::ifstream file;
        file.open(filename);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        code = stream.str();
        return code;
    }

    void loadData() {
        std::ifstream input("data/pca.csv");
        std::string line;
        getline(input, line);  // discard headers

        while (getline(input, line)) {
            std::vector<float> vec;

            // https://stackoverflow.com/a/14267455
            std::string delim = ",";
            auto start = 0U;
            auto end = line.find(delim);
            while (end != std::string::npos) {
                vec.push_back(std::stof(line.substr(start, end - start)));
                start = end + delim.length();
                end = line.find(delim, start);
            }
            int c = std::stoi(line.substr(start, end));

            float size = 2.f;

            Geometry::data.push_back({{vec[0] * size, vec[1] * size, vec[2] * size, vec[3] * size}, Geometry::colors.at(c)});

            if (Geometry::data.size() >= 1) {
                return;
            }
        }
    }

    void InitializeResources() {
        glGenFramebuffers(1, &m_swapchainFramebuffer);

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        auto vsString = readFile("shaders/vertex.glsl");
        auto vsCharArr = vsString.c_str();
        glShaderSource(vertexShader, 1, &vsCharArr, nullptr);
        glCompileShader(vertexShader);
        CheckShader(vertexShader);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        auto fsString = readFile("shaders/fragment.glsl");
        auto fsCharArr = fsString.c_str();
        glShaderSource(fragmentShader, 1, &fsCharArr, nullptr);
        glCompileShader(fragmentShader);
        CheckShader(fragmentShader);

        m_program = glCreateProgram();
        glAttachShader(m_program, vertexShader);
        glAttachShader(m_program, fragmentShader);
        glLinkProgram(m_program);
        CheckProgram(m_program);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        m_modelViewProjectionUniformLocation = glGetUniformLocation(m_program, "ModelViewProjection");

        m_vertexAttribCoords = glGetAttribLocation(m_program, "VertexPos");
        m_vertexAttribColor = glGetAttribLocation(m_program, "VertexColor");

        loadData();


        // auto ds = sizeof(Geometry::data);
        // auto sdf = &Geometry::data;

        // glGenBuffers(1, &m_cubeIndexBuffer);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_cubeIndexBuffer);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Geometry::c_cubeIndices), Geometry::c_cubeIndices, GL_STATIC_DRAW);


        glGenBuffers(1, &m_cubeVertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_cubeVertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Geometry::c_cubeVertices), Geometry::c_cubeVertices, GL_STATIC_DRAW);

        glGenBuffers(1, &m_cubeIndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_cubeIndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Geometry::c_cubeIndices), Geometry::c_cubeIndices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
        glEnableVertexAttribArray(m_vertexAttribCoords);
        glEnableVertexAttribArray(m_vertexAttribColor);
        glBindBuffer(GL_ARRAY_BUFFER, m_cubeVertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_cubeIndexBuffer);
        glVertexAttribPointer(m_vertexAttribCoords, 4, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), nullptr);
        glVertexAttribPointer(m_vertexAttribColor, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex),
                              reinterpret_cast<const void*>(sizeof(XrVector3f)));




        glGenBuffers(1, &m_pntBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_pntBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Geometry::data) * Geometry::data.size(), Geometry::data.data(), GL_STATIC_DRAW);

        glGenVertexArrays(1, &m_vao_pnt);
        glBindVertexArray(m_vao_pnt);
        glEnableVertexAttribArray(m_vertexAttribCoords);
        glEnableVertexAttribArray(m_vertexAttribColor);
        glBindBuffer(GL_ARRAY_BUFFER, m_pntBuffer);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_cubeIndexBuffer);
        glVertexAttribPointer(m_vertexAttribCoords, 4, GL_FLOAT, GL_FALSE, sizeof(Geometry::Iris), nullptr);
        glVertexAttribPointer(m_vertexAttribColor, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Iris),
                              reinterpret_cast<const void*>(sizeof(XrVector4f)));



        glGenBuffers(1, &m_tessBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_tessBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Geometry::tess) * Geometry::tess.size(), Geometry::tess.data(), GL_STATIC_DRAW);

        glGenVertexArrays(1, &m_vao_tess);
        glBindVertexArray(m_vao_tess);
        glEnableVertexAttribArray(m_vertexAttribCoords);
        glEnableVertexAttribArray(m_vertexAttribColor);
        glBindBuffer(GL_ARRAY_BUFFER, m_tessBuffer);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_cubeIndexBuffer);
        glVertexAttribPointer(m_vertexAttribCoords, 4, GL_FLOAT, GL_FALSE, sizeof(Geometry::Iris), nullptr);
        glVertexAttribPointer(m_vertexAttribColor, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Iris),
                              reinterpret_cast<const void*>(sizeof(XrVector4f)));

        // auto y = [](char p, int i) { return p == '0' ? Geometry::a[i] : p == '1' ? Geometry::b[i] : -1; };

        // for (int i = 0; i < 16; ++i) {

        //    auto binary = std::bitset<4>(i).to_string(); // to binary
        //    char bin[5];

        //    std::cout << binary << std::endl;
        //

        //    for (int j = 0; j < 4; ++j) {
        //        strcpy(bin, binary.c_str());

        //        Geometry::tess.push_back({{y(bin[0], 0), y(bin[1], 1), y(bin[2], 2), y(bin[3], 3)}, Geometry::grey});
        //
        //        std::string tmp = std::to_string(1 - (bin[j] - '0'));
        //        bin[j] = tmp.c_str()[0];    // I HATE CPP

        //        Geometry::tess.push_back({{y(bin[0], 0), y(bin[1], 1), y(bin[2], 2), y(bin[3], 3)}, Geometry::grey});
        //    }

        //}

        /*std::cout << binary << "\n";

        unsigned long decimal = std::bitset<8>(binary).to_ulong();
        std::cout << decimal << "\n";*/



        int width, height, nrChannels;
        unsigned char* data = stbi_load("data/atlas.png", &width, &height, &nrChannels, 0);
        if (!data) {
            std::cout << "Failed to load texture" << std::endl;
        }

        // load and create a texture
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);

        stbi_image_free(data);
    }

    void CheckShader(GLuint shader) {
        GLint r = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &r);
        if (r == GL_FALSE) {
            GLchar msg[4096] = {};
            GLsizei length;
            glGetShaderInfoLog(shader, sizeof(msg), &length, msg);
            THROW(Fmt("Compile shader failed: %s", msg));
        }
    }

    void CheckProgram(GLuint prog) {
        GLint r = 0;
        glGetProgramiv(prog, GL_LINK_STATUS, &r);
        if (r == GL_FALSE) {
            GLchar msg[4096] = {};
            GLsizei length;
            glGetProgramInfoLog(prog, sizeof(msg), &length, msg);
            THROW(Fmt("Link program failed: %s", msg));
        }
    }

    int64_t SelectColorSwapchainFormat(const std::vector<int64_t>& runtimeFormats) const override {
        // List of supported color swapchain formats.
        constexpr int64_t SupportedColorSwapchainFormats[] = {
            GL_RGB10_A2,
            GL_RGBA16F,
            // The two below should only be used as a fallback, as they are linear color formats without enough bits for color
            // depth, thus leading to banding.
            GL_RGBA8,
            GL_RGBA8_SNORM,
        };

        auto swapchainFormatIt =
            std::find_first_of(runtimeFormats.begin(), runtimeFormats.end(), std::begin(SupportedColorSwapchainFormats),
                               std::end(SupportedColorSwapchainFormats));
        if (swapchainFormatIt == runtimeFormats.end()) {
            THROW("No runtime swapchain format supported for color swapchain");
        }

        return *swapchainFormatIt;
    }

    const XrBaseInStructure* GetGraphicsBinding() const override {
        return reinterpret_cast<const XrBaseInStructure*>(&m_graphicsBinding);
    }

    std::vector<XrSwapchainImageBaseHeader*> AllocateSwapchainImageStructs(
        uint32_t capacity, const XrSwapchainCreateInfo& /*swapchainCreateInfo*/) override {
        // Allocate and initialize the buffer of image structs (must be sequential in memory for xrEnumerateSwapchainImages).
        // Return back an array of pointers to each swapchain image struct so the consumer doesn't need to know the type/size.
        std::vector<XrSwapchainImageOpenGLKHR> swapchainImageBuffer(capacity);
        std::vector<XrSwapchainImageBaseHeader*> swapchainImageBase;
        for (XrSwapchainImageOpenGLKHR& image : swapchainImageBuffer) {
            image.type = XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR;
            swapchainImageBase.push_back(reinterpret_cast<XrSwapchainImageBaseHeader*>(&image));
        }

        // Keep the buffer alive by moving it into the list of buffers.
        m_swapchainImageBuffers.push_back(std::move(swapchainImageBuffer));

        return swapchainImageBase;
    }

    uint32_t GetDepthTexture(uint32_t colorTexture) {
        // If a depth-stencil view has already been created for this back-buffer, use it.
        auto depthBufferIt = m_colorToDepthMap.find(colorTexture);
        if (depthBufferIt != m_colorToDepthMap.end()) {
            return depthBufferIt->second;
        }

        // This back-buffer has no corresponding depth-stencil texture, so create one with matching dimensions.

        GLint width;
        GLint height;
        glBindTexture(GL_TEXTURE_2D, colorTexture);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

        uint32_t depthTexture;
        glGenTextures(1, &depthTexture);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

        m_colorToDepthMap.insert(std::make_pair(colorTexture, depthTexture));

        return depthTexture;
    }

    void RenderView(const XrCompositionLayerProjectionView& layerView, const XrSwapchainImageBaseHeader* swapchainImage,
                    int64_t swapchainFormat, const std::vector<Cube>& cubes) override {
        CHECK(layerView.subImage.imageArrayIndex == 0);  // Texture arrays not supported.
        UNUSED_PARM(swapchainFormat);                    // Not used in this function for now.

        glBindFramebuffer(GL_FRAMEBUFFER, m_swapchainFramebuffer);

        const uint32_t colorTexture = reinterpret_cast<const XrSwapchainImageOpenGLKHR*>(swapchainImage)->image;

        glViewport(static_cast<GLint>(layerView.subImage.imageRect.offset.x),
                   static_cast<GLint>(layerView.subImage.imageRect.offset.y),
                   static_cast<GLsizei>(layerView.subImage.imageRect.extent.width),
                   static_cast<GLsizei>(layerView.subImage.imageRect.extent.height));

        glFrontFace(GL_CW);
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        

        const uint32_t depthTexture = GetDepthTexture(colorTexture);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

        // Clear swapchain and depth buffer.
        glClearColor(DarkSlateGray[0], DarkSlateGray[1], DarkSlateGray[2], DarkSlateGray[3]);
        glClearDepth(1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glPointSize(20.f);


        // Set shaders and uniform variables.
        glUseProgram(m_program);




        XrMatrix4x4f proj;
        XrMatrix4x4f toView;
        XrVector3f scale{1.f, 1.f, 1.f};
        XrMatrix4x4f view;
        XrMatrix4x4f vp;



        // 0 5 10 15 20
        // 1 6 11 16 21
        // 2 7 12 17 22
        // 3 8 13 18 23
        // 4 9 14 19 24

        // camera is at w = 3, tesseract at w = [-1;1]
        float n = 0.1f;
        float f = 11.f;

        // taken from glm\ext\matrix_clip_space.inl perspectiveRH_NO(...)
        float a = -(f + n) / (f - n);
        float b = -(2 * f * n) / (f - n);

        // column major
        float m5x5[] = {
        /*/
        // orthographic
            2.0f / (maxs[0] - mins[0]), 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 2.0f / (maxs[1] - mins[3]), 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 2.0f / (maxs[2] - mins[4]), 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 2.0f / (maxs[3] - mins[3]), 0.0f,
            -(maxs[0] + mins[0]) / (maxs[0] - mins[0]), -(maxs[1] + mins[3]) / (maxs[1] - mins[3]), -(maxs[2] + mins[4]) / (maxs[2] - mins[4]), -(maxs[3] + mins[3]) / (maxs[3] - mins[3]), 1.0f
        };
        /*/
        // perspective at w
            1, 0, 0, 0, 0,
            0, 1, 0, 0, 0,
            0, 0, 1, 0, 0,
            0, 0, 0, a, 1, //according to math this should be -1, but it's mirrored along the w axis then, so we use 1
            0, 0, 0, b, 0
        };

        
        /**/

        const auto& pose = layerView.pose;

        auto pos = pose.position;
        //pos.z = 2;

        XrMatrix4x4f_CreateProjectionFov(&proj, GRAPHICS_OPENGL, layerView.fov, 0.05f, 100.0f);
        XrMatrix4x4f_CreateTranslationRotationScale(&toView, &pos, &pose.orientation, &scale);
        XrMatrix4x4f_InvertRigidBody(&view, &toView);
        XrMatrix4x4f_Multiply(&vp, &proj, &view);


        glUniformMatrix4fv(m_modelViewProjectionUniformLocation, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&vp));

        glUniform1fv(glGetUniformLocation(m_program, "proj5d"), 25, m5x5);


        /**/
        options->XWRot = fmod(options->XWRot, 360.f);
        options->YWRot = fmod(options->YWRot, 360.f);
        options->ZWRot = fmod(options->ZWRot, 360.f);

        float speeee = 0.0028f * 8;
        glUniform1fv(glGetUniformLocation(m_program, "XWRot"), 25, Matrix_lib::getXWRotationMatrix(options->XWRot * speeee).data());
        glUniform1fv(glGetUniformLocation(m_program, "YWRot"), 25, Matrix_lib::getYWRotationMatrix(options->YWRot * speeee).data());
        glUniform1fv(glGetUniformLocation(m_program, "ZWRot"), 25, Matrix_lib::getZWRotationMatrix(options->ZWRot * speeee).data());

        /*/



        float toRad = 0.0174533f;


        // hyperspherical coords
        options->XWRot = fmod(options->XWRot + 360.f, 360.f);
        options->YWRot = fmod(options->YWRot + 360.f, 360.f);
        options->ZWRot = fmod(options->ZWRot + 360.f, 360.f);
        auto phi1 = options->XWRot * toRad;
        auto phi2 = options->YWRot * toRad;
        auto phi3 = options->ZWRot * toRad;
        auto sinphi1 = sin(phi1);
        auto sinphi2 = sin(phi2);
        auto x_4 = -cos(phi1);
        auto x_2 = -sinphi1 * cos(phi2);
        auto x_1 = -sinphi1 * sinphi2 * cos(phi3);
        auto x_3 = -sinphi1 * sinphi2 * sin(phi3);

        //hopf coords
        //options->XWRot = fmod(options->XWRot + 360.f, 360.f);
        //options->YWRot = std::max(std::min(options->YWRot, 179.f), 1.f);
        //options->ZWRot = fmod(options->ZWRot + 360.f, 360.f);
        //auto x_1 = cos(options->XWRot * toRad) * sin(options->YWRot * toRad);
        //auto x_2 = sin(options->XWRot * toRad) * sin(options->YWRot * toRad);
        //auto x_3 = cos(options->ZWRot * toRad) * cos(options->YWRot * toRad);
        //auto x_4 = sin(options->ZWRot * toRad) * cos(options->YWRot * toRad);

        std::vector<std::array<float, 4>> ai;
        ai = {
            {x_1, x_2, x_3, x_4},
            {0.f, 1.f, 0.f, 0.f},
            {0.f, 0.f, 1.f, 0.f},
            {0.f, 0.f, 0.f, 1.f}
        };

        auto tmp = {x_1, x_2, x_3, x_4};
        auto tmp2 = data(tmp);
        glUniform1fv(glGetUniformLocation(m_program, "campos"), 4, tmp2);

        if (options->print) {
            std::cout << x_1 << " " << x_2 << " " << x_3 << " " << x_4 << std::endl;
            options->print = false;
        }

        std::vector<std::array<float, 4>> r(4);
        std::vector<std::array<float, 4>> q(4);

        auto _pow = [](std::array<float, 4> a, float b)
        {
            float tmp = 0;
            for (float v : a) {
                tmp += pow(v, b);
            }
            return tmp;
        };

        auto _mul = [](std::array<float, 4> a, float b) {
            std::array<float, 4> tmp{};
            for (int i = 0; i < 4; ++i) {
                tmp[i] = a[i] * b;
            }
            return tmp;
        };

        auto _div = [&_mul](std::array<float, 4> a, float b)
        {
            return _mul(a, 1 / b);
        };

        auto _dot = [](std::array<float, 4> a, std::array<float, 4> b)
        {
            float tmp = 0;
            for (int i = 0; i < 4; ++i) {
                tmp += a[i] * b[i];
            }
            return tmp;
        };

        auto _sub = [](std::array<float, 4> a, std::array<float, 4> b)
        {
            std::array<float, 4> tmp{};
            for (int i = 0; i < 4; ++i) {
                tmp[i] = a[i] - b[i];
            }
            return tmp;
        };

        //https://blogs.mathworks.com/cleve/2016/07/25/compare-gram-schmidt-and-householder-orthogonalization-algorithms/

        for (int k = 0; k < 4; ++k) {

            q[k] = ai[k];

            for (int i = 0; i < k; ++i) {
                r[k][i] = _dot(q[i], q[k]);
                q[k] = _sub(q[k], _mul(q[i], r[k][i]));
            }


            r[k][k] = sqrt(_pow(q[k], 2));
            q[k] = _div(q[k], r[k][k]);
        }


        int c = 0;
        std::array<float, 25> gms_base{};

        std::cout << std::setprecision(2) << std::fixed;
        bool print = false;
        for (auto && vec : q) {
            for (auto val : vec) {
                if (print) std::cout << val << " ";
                gms_base[c] = val;
                c++;
            }
            gms_base[c] = 0;
            c++;
            if (print) std::cout << std::endl;
        }
        gms_base[24] = 1;

        glUniform1fv(glGetUniformLocation(m_program, "gms_base"), 25, gms_base.data());
        /**/


        int atlas = 0;

        glActiveTexture(GL_TEXTURE0 + atlas);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        glUniform1i(glGetUniformLocation(m_program, "atlas"), atlas);


        glUniform1i(glGetUniformLocation(m_program, "dodiscard"), 1);

        glBindVertexArray(m_vao_pnt);
        //glDrawArrays(GL_POINTS, 0, Geometry::data.size());
        //}

        glUniform1i(glGetUniformLocation(m_program, "dodiscard"), 0);

        glBindVertexArray(m_vao_tess);
        glDrawArrays(GL_LINES, 0, Geometry::tess.size());



        // Set cube primitive data.
        glBindVertexArray(m_vao);

        // Render each cube
        for (const Cube& cube : cubes) {
            // Compute the model-view-projection transform and set it..
            XrMatrix4x4f model;
            XrMatrix4x4f_CreateTranslationRotationScale(&model, &cube.Pose.position, &cube.Pose.orientation, &cube.Scale);
            XrMatrix4x4f mvp;
            XrMatrix4x4f_Multiply(&mvp, &vp, &model);
            glUniformMatrix4fv(m_modelViewProjectionUniformLocation, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(&mvp));

            // Draw the cube.
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(ArraySize(Geometry::c_cubeIndices)), GL_UNSIGNED_SHORT, nullptr);
        }




        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, m_swapchainFramebuffer);
        glBlitFramebuffer(layerView.subImage.imageRect.offset.x, layerView.subImage.imageRect.offset.y,
                          layerView.subImage.imageRect.extent.width, layerView.subImage.imageRect.extent.height, 
                          0, 0, width, height,
                          GL_COLOR_BUFFER_BIT, GL_LINEAR);

        glBindVertexArray(0);
        glUseProgram(0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Swap our window every other eye for RenderDoc
        static int everyOther = 0;
        if ((everyOther++ & 1) != 0) {
            ksGpuWindow_SwapBuffers(&window);
        }

        ksGpuWindow_ProcessEvents(&window);
    }

   private:
#ifdef XR_USE_PLATFORM_WIN32
    XrGraphicsBindingOpenGLWin32KHR m_graphicsBinding{XR_TYPE_GRAPHICS_BINDING_OPENGL_WIN32_KHR};
#elif defined(XR_USE_PLATFORM_XLIB)
    XrGraphicsBindingOpenGLXlibKHR m_graphicsBinding{XR_TYPE_GRAPHICS_BINDING_OPENGL_XLIB_KHR};
#elif defined(XR_USE_PLATFORM_XCB)
    XrGraphicsBindingOpenGLXcbKHR m_graphicsBinding{XR_TYPE_GRAPHICS_BINDING_OPENGL_XCB_KHR};
#elif defined(XR_USE_PLATFORM_WAYLAND)
    XrGraphicsBindingOpenGLWaylandKHR m_graphicsBinding{XR_TYPE_GRAPHICS_BINDING_OPENGL_WAYLAND_KHR};
#endif

    std::list<std::vector<XrSwapchainImageOpenGLKHR>> m_swapchainImageBuffers;
    GLuint m_swapchainFramebuffer{0};
    GLuint m_program{0};
    GLint m_modelViewProjectionUniformLocation{0};
    GLint m_vertexAttribCoords{0};
    GLint m_vertexAttribColor{0};
    GLuint m_vao{0};
    GLuint m_vao_pnt{0};
    GLuint m_vao_tess{0};
    GLuint m_pntBuffer{0};
    GLuint m_tessBuffer{0};
    GLuint m_cubeVertexBuffer{0};
    GLuint m_cubeIndexBuffer{0};
    GLuint m_texture{0};


    // Map color buffer to associated depth buffer. This map is populated on demand.
    std::map<uint32_t, uint32_t> m_colorToDepthMap;

    const std::shared_ptr<Options>& options;

};
}  // namespace

std::shared_ptr<IGraphicsPlugin> CreateGraphicsPlugin_OpenGL(const std::shared_ptr<Options>& options,
                                                             std::shared_ptr<IPlatformPlugin> platformPlugin) {
    return std::make_shared<OpenGLGraphicsPlugin>(options, platformPlugin);
}

#endif
