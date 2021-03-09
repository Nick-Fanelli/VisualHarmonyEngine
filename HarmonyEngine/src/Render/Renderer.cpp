#include "Renderer.h"

#include "../Scene/Scene.h"

namespace HarmonyEngine {

    static const size_t MaxQuadCount = 20000;
    static const size_t MaxVertexCount = MaxQuadCount * 4;
    static const size_t MaxIndexCount = MaxQuadCount * 6;

    static OrthographicCamera* s_Camera = nullptr;
    static std::unique_ptr<Shader> s_Shader = nullptr;

    size_t RendererStatistics::BatchCount = 0;
    size_t RendererStatistics::CurrentBatchCount = 0;

    size_t RendererStatistics::VertexCount = 0;
    size_t RendererStatistics::CurrentVertexCount = 0;

    size_t RendererStatistics::IndexCount = 0;
    size_t RendererStatistics::CurrentIndexCount = 0;

    struct RenderBatch {

        GLuint VaoID = 0;
        GLuint VboID = 0;
        GLuint EboID = 0;

        size_t IndexCount = 0;
        size_t TextureIndex = 1;

        Vertex* Vertices = nullptr;
        Vertex* VertexPtr = nullptr;

        int* Textures = nullptr;
    };

    static RenderBatch s_Batch;

    void Renderer::OnCreate(OrthographicCamera* camera) {
        // Check to make sure that the OnCreate method wasn't already called!
        if (s_Batch.Vertices != nullptr) {
            Log::Error("Vertices array was not nullptr, exiting Renderer::OnCreate()");
            return;
        }

        s_Camera = camera; // Hold a pointer the main camera in the scene
        auto maxTextureCount = OpenGLUtils::GetGPUMaxTextureSlots(); // Get the max texture count allowed by the GPU

        // Setup the static render batch
        s_Batch = RenderBatch();
        s_Batch.Vertices = new Vertex[MaxVertexCount];
        s_Batch.VertexPtr = s_Batch.Vertices;

        s_Batch.Textures = new int[maxTextureCount];

        // Setup and create the shader with a replacement that points to the max texture count
        std::unordered_map<std::string, std::string> replacements;
        replacements["MAX_SUPPORTED_TEXTURES"] = std::to_string(maxTextureCount);
        s_Shader = std::make_unique<Shader>("assets/shaders/default.vert.glsl", "assets/shaders/default.frag.glsl",
                                            &replacements);

        // Bind the VAO
        glGenVertexArrays(1, &s_Batch.VaoID);
        glBindVertexArray(s_Batch.VaoID);

        // Bind the Verticies
        glGenBuffers(1, &s_Batch.VboID);
        glBindBuffer(GL_ARRAY_BUFFER, s_Batch.VboID); // Bind Vertex Buffer

        // Push the data
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MaxVertexCount, nullptr, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, Position));
        glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, Color));
        glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, TextureCoord));
        glVertexAttribPointer(3, 1, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, TextureID));

        glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind Buffer

        uint32_t indices[MaxIndexCount];
        uint32_t offset = 0;

        for (size_t i = 0; i < MaxIndexCount; i += 6) {
            // First Triangle
            indices[i] = offset;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            // Second Triangle
            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset;

            offset += 4;
        }

        // Bind the indices
        glGenBuffers(1, &s_Batch.EboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Batch.EboID); // Bind Indices Buffer
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind Buffer
        glBindVertexArray(0);
    }

    void Renderer::StartBatch() {
        s_Batch.IndexCount = 0;
        s_Batch.VertexPtr = s_Batch.Vertices;

#ifdef HARMONY_DEBUG_ENABLED
        RendererStatistics::CurrentBatchCount++;
#endif
    }

    void Renderer::EndBatch() {
        Renderer::UpdateBatchVertexData();
        Renderer::Render();
    }

    void Renderer::UpdateBatchVertexData() {
        GLsizeiptr size = (uint8_t*) s_Batch.VertexPtr - (uint8_t*) s_Batch.Vertices;

        glBindBuffer(GL_ARRAY_BUFFER, s_Batch.VboID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, s_Batch.Vertices);
    }

    void Renderer::Render() {

        s_Shader->Bind();
        s_Shader->AddUniformMat4("cameraViewProjectionMatrix", s_Camera->GetViewProjectionMatrix());
        s_Shader->AddUniformIntArray("uTextures", s_Batch.TextureIndex, s_Batch.Textures);

        for (int i = 0; i < s_Batch.TextureIndex; i++) {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, s_Batch.Textures[i]);
        }

        glBindVertexArray(s_Batch.VaoID);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Batch.EboID);

        glDrawElements(GL_TRIANGLES, s_Batch.IndexCount, GL_UNSIGNED_INT, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
        glBindVertexArray(0);

        s_Shader->Unbind();
    }

    void Renderer::OnDestroy() {
        if (s_Batch.Vertices == nullptr) {
            Log::Warn("Vertices array was already nullptr, exiting Renderer::OnDestroy()");
            return;
        }

        glDeleteVertexArrays(1, &s_Batch.VaoID);
        glDeleteBuffers(1, &s_Batch.VboID);
        glDeleteBuffers(1, &s_Batch.EboID);

        delete[] s_Batch.Vertices;
        delete[] s_Batch.Textures;

        // Keep track of if it is created or not
        s_Batch.Vertices = nullptr;
        s_Batch.Textures = nullptr;
    }

    static const int NullTextureValue = -1;

    const int& Renderer::AddTexture(const Texture& texture) {
        // TODO: Check to make sure that we aren't exceeding max texture amount
        if (texture.GetTextureID() == -1) {
            Log::Error("Texture : " + std::string(texture.GetFilepath()) +
                       " has not been initialized and can not be added to the render batch!");
            return NullTextureValue;
        }

        s_Batch.Textures[s_Batch.TextureIndex] = texture.GetTextureID();
        s_Batch.TextureIndex++;

        return s_Batch.Textures[s_Batch.TextureIndex - 1];
    }

    void Renderer::AllocateVertices(const int& amount) {
        uint32_t vertexCount = s_Batch.VertexPtr - s_Batch.Vertices;

#ifdef HARMONY_DEBUG_ENABLED
        RendererStatistics::CurrentVertexCount += amount;
#endif

        // If there's not enough space, start a new render batch!
        if (vertexCount + amount >= MaxVertexCount) {
            Renderer::EndBatch();
            Renderer::StartBatch();
        }
    }

    void Renderer::DrawQuad(const Quad& quad) {
        AllocateVertices(4);

        (*s_Batch.VertexPtr) = quad.V0;
        s_Batch.VertexPtr++;

        (*s_Batch.VertexPtr) = quad.V1;
        s_Batch.VertexPtr++;

        (*s_Batch.VertexPtr) = quad.V2;
        s_Batch.VertexPtr++;

        (*s_Batch.VertexPtr) = quad.V3;
        s_Batch.VertexPtr++;

        s_Batch.IndexCount += 6;
#ifdef HARMONY_DEBUG_ENABLED
        RendererStatistics::CurrentIndexCount += 6;
#endif
    }

    void Renderer::DrawQuad(const Quad& quad, const glm::vec4& color) {
        AllocateVertices(4);

        (*s_Batch.VertexPtr) = quad.V0;
        (*s_Batch.VertexPtr).Color = color;
        s_Batch.VertexPtr++;

        (*s_Batch.VertexPtr) = quad.V1;
        (*s_Batch.VertexPtr).Color = color;
        s_Batch.VertexPtr++;

        (*s_Batch.VertexPtr) = quad.V2;
        (*s_Batch.VertexPtr).Color = color;
        s_Batch.VertexPtr++;

        (*s_Batch.VertexPtr) = quad.V3;
        (*s_Batch.VertexPtr).Color = color;
        s_Batch.VertexPtr++;

        s_Batch.IndexCount += 6;
#ifdef HARMONY_DEBUG_ENABLED
        RendererStatistics::CurrentIndexCount += 6;
#endif
    }

    void Renderer::DrawQuad(const glm::vec2& positionOffset, const Quad& quad) {
        AllocateVertices(4);

        Vertex v0 = quad.V0;
        Vertex v1 = quad.V1;
        Vertex v2 = quad.V2;
        Vertex v3 = quad.V3;

        v0.Position += positionOffset;
        v1.Position += positionOffset;
        v2.Position += positionOffset;
        v3.Position += positionOffset;

        (*s_Batch.VertexPtr) = v0;
        s_Batch.VertexPtr++;

        (*s_Batch.VertexPtr) = v1;
        s_Batch.VertexPtr++;

        (*s_Batch.VertexPtr) = v2;
        s_Batch.VertexPtr++;

        (*s_Batch.VertexPtr) = v3;
        s_Batch.VertexPtr++;

        s_Batch.IndexCount += 6;
#ifdef HARMONY_DEBUG_ENABLED
        RendererStatistics::CurrentIndexCount += 6;
#endif
    }

    void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color,
                            const float& textureID) {
        AllocateVertices(4);

        Vertex v0 = Vertex();
        Vertex v1 = Vertex();
        Vertex v2 = Vertex();
        Vertex v3 = Vertex();

        v0.Position = position;
        v0.Color = color;
        v0.TextureCoord = {0, 0};
        v0.TextureID = textureID;

        v1.Position = glm::vec2(position.x, position.y + 1 * scale.y);
        v1.Color = color;
        v1.TextureCoord = {0, 1};
        v1.TextureID = textureID;

        v2.Position = glm::vec2(position.x + 1 * scale.x, position.y + 1 * scale.y);
        v2.Color = color;
        v2.TextureCoord = {1, 1};
        v2.TextureID = textureID;

        v3.Position = glm::vec2(position.x + 1 * scale.x, position.y);
        v3.Color = color;
        v3.TextureCoord = {1, 0};
        v3.TextureID = textureID;

        (*s_Batch.VertexPtr) = v0;
        s_Batch.VertexPtr++;

        (*s_Batch.VertexPtr) = v1;
        s_Batch.VertexPtr++;

        (*s_Batch.VertexPtr) = v2;
        s_Batch.VertexPtr++;

        (*s_Batch.VertexPtr) = v3;
        s_Batch.VertexPtr++;

        s_Batch.IndexCount += 6;
#ifdef HARMONY_DEBUG_ENABLED
        RendererStatistics::CurrentIndexCount += 6;
#endif
    }

    void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& scale, const std::array<glm::vec4, 4>& colorArray,
                       const float& textureID) {
        AllocateVertices(4);

        Vertex v0 = Vertex();
        Vertex v1 = Vertex();
        Vertex v2 = Vertex();
        Vertex v3 = Vertex();

        v0.Position = position;
        v0.Color = colorArray[0];
        v0.TextureCoord = {0, 0};
        v0.TextureID = textureID;

        v1.Position = glm::vec2(position.x, position.y + 1 * scale.y);
        v1.Color = colorArray[1];
        v1.TextureCoord = {0, 1};
        v1.TextureID = textureID;

        v2.Position = glm::vec2(position.x + 1 * scale.x, position.y + 1 * scale.y);
        v2.Color = colorArray[2];
        v2.TextureCoord = {1, 1};
        v2.TextureID = textureID;

        v3.Position = glm::vec2(position.x + 1 * scale.x, position.y);
        v3.Color = colorArray[3];
        v3.TextureCoord = {1, 0};
        v3.TextureID = textureID;

        (*s_Batch.VertexPtr) = v0;
        s_Batch.VertexPtr++;

        (*s_Batch.VertexPtr) = v1;
        s_Batch.VertexPtr++;

        (*s_Batch.VertexPtr) = v2;
        s_Batch.VertexPtr++;

        (*s_Batch.VertexPtr) = v3;
        s_Batch.VertexPtr++;

        s_Batch.IndexCount += 6;
#ifdef HARMONY_DEBUG_ENABLED
        RendererStatistics::CurrentIndexCount += 6;
#endif
    }
}