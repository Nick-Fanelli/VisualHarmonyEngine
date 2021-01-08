package test;

import com.harmonygames.harmonyengine.Log;
import com.harmonygames.harmonyengine.mesh.Mesh;
import com.harmonygames.harmonyengine.mesh.MeshLoader;
import com.harmonygames.harmonyengine.scene.Scene;
import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL20;
import org.lwjgl.opengl.GL30;

public class TestScene extends Scene {

    String vertexShader = "#version 400 core\n" +
            "\n" +
            "out vec4 vertexColor;\n" +
            "\n" +
            "void main() {\n" +
            "    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n" +
            "}";

    String fragmentShader = "#version 400 core\n" +
            "\n" +
            "out vec4 out_Color;\n" +
            "\n" +
            "in vec4 vertexColor;\n" +
            "\n" +
            "void main() {\n" +
            "    out_Color = vertexColor;\n" +
            "}";

    float[] vertices = {-0.5f,-0.5f,0f,
            0.5f, -0.5f, 0f,
            0f,0.5f,0f};
    int[] indices = {0,1,2};

    int vaoID, vboID;
    int programID;

    Mesh mesh;

    @Override
    public void onCreate() {
        super.onCreate();

        // Create the shaders
        int vertexID, fragmentID;

        vertexID = GL20.glCreateShader(GL20.GL_VERTEX_SHADER);
        GL20.glShaderSource(vertexID, vertexShader);
        GL20.glCompileShader(vertexID);

        // Check for errors in compilation
        int success = GL20.glGetShaderi(vertexID, GL20.GL_COMPILE_STATUS);
        if(success == GL20.GL_FALSE) {
            int length = GL20.glGetShaderi(vertexID, GL20.GL_INFO_LOG_LENGTH);
            Log.error("Vertex shader compilation failed!");
            Log.fatalError(GL20.glGetShaderInfoLog(vertexID, length));
        }

        fragmentID = GL20.glCreateShader(GL20.GL_FRAGMENT_SHADER);
        GL20.glShaderSource(fragmentID, fragmentShader);
        GL20.glCompileShader(fragmentID);

        // Check for errors in compilation
        success = GL20.glGetShaderi(fragmentID, GL20.GL_COMPILE_STATUS);
        if(success == GL20.GL_FALSE) {
            int length = GL20.glGetShaderi(fragmentID, GL20.GL_INFO_LOG_LENGTH);
            Log.error("Fragment shader compilation failed!");
            Log.fatalError(GL20.glGetShaderInfoLog(fragmentID, length));
        }

        programID = GL20.glCreateProgram();
        GL20.glAttachShader(programID, vertexID);
        GL20.glAttachShader(programID, fragmentID);

        GL20.glLinkProgram(programID);
        success = GL20.glGetProgrami(programID, GL20.GL_LINK_STATUS);
        if(success == GL20.GL_FALSE) {
            int length = GL20.glGetProgrami(programID, GL20.GL_INFO_LOG_LENGTH);
            Log.error("Shader programing linking failed!");
            Log.fatalError(GL20.glGetProgramInfoLog(programID, length));
        }

        mesh = MeshLoader.createMesh(vertices, indices);

//        // Create the elements
//        vaoID = GL30.glGenVertexArrays();
//        GL30.glBindVertexArray(vaoID);
//
//        vboID = GL30.glGenBuffers();
//        GL30.glBindBuffer(GL30.GL_ARRAY_BUFFER, vboID);
//        GL30.glBufferData(GL30.GL_ARRAY_BUFFER, vertices.length * Float.BYTES, GL30.GL_DYNAMIC_DRAW);
//
//        int eboID = GL30.glGenBuffers();
//        GL30.glBindBuffer(GL30.GL_ELEMENT_ARRAY_BUFFER, eboID);
//        GL30.glBufferData(GL30.GL_ELEMENT_ARRAY_BUFFER, indices, GL30.GL_STATIC_DRAW);
//
//        GL30.glVertexAttribPointer(0, 2, GL30.GL_FLOAT, false, 9 * Float.BYTES, 0);
//        GL30.glEnableVertexAttribArray(0);
    }

    @Override
    public void update(float deltaTime) {
        GL30.glUseProgram(programID);

        GL30.glBindVertexArray(mesh.getVaoID());
        GL20.glEnableVertexAttribArray(0);
        GL11.glDrawElements(GL11.GL_TRIANGLES, mesh.getVertexCount(), GL11.GL_UNSIGNED_INT, 0);
        GL20.glDisableVertexAttribArray(0);
        GL30.glBindVertexArray(0);

        GL30.glUseProgram(0);
    }

}