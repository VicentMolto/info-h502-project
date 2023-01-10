#include "xhl.h"

#include "src/glInit.h"
#include "src/ImportData.h"

#include "src/Shader.h"
#include "src/camera.h"
#include "src/Texture.h"
#include "src/Importer.h"

// Set camera parameters
const int w = 1680;
const int h = 1400;
Camera camera(45, 10, .1,vec3(2,3,25));


void Draw(Meshes Meshes,Shader& shader, mat4 &M, vec3 translateSize = vec3(0, 0, 0), float angle = 0, vec3 rotateAxil = vec3(0, 1, 0), vec3 scaleSize = vec3(1, 1, 1))
{
    M = mat4(1);
    M = translate(M, translateSize);
    M = rotate(M, radians(angle), rotateAxil);
    M = scale(M, scaleSize);

    shader.setMat4("M", M);

    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(Meshes.vID), GL_UNSIGNED_INT, (void*)(Meshes.vOffset * sizeof(float)));
}


int getTexID(vector<string> v, string a) {
    vector<string>::iterator it = find(v.begin(), v.end(), a);
    if (it != v.end())
        return std::distance(v.begin(), it);
    else
        return -1;
}

// mouse Pos
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    camera.mousePos(xpos, ypos);
}
// scroll
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.mouseScroll(yoffset);
}


int main()
{
    GLFWwindow* window = glInit(w, h, "OpenGL Project - solar system");
    glEnable(GL_DEPTH_TEST);

    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback); // mouse event
    glfwSetScrollCallback(window, scroll_callback); // scroll event

    


    
    Import("18.4.obj");
    ImportData vertex(vertices, indices, prop, propSize); // read the vertices
    
    
    // read all the textures
    // for (int i = 0; i < textures.size(); i++)
    // {
    //     Texture(textures[i].c_str(), i + 1, true);
    // }

    // transform matrix
    mat4 M(1);
    mat4 V(1);
    mat4 P(1);

    //Instancing starts from here:
    srand(static_cast<unsigned int>(glfwGetTime()));// initialise the random seed
    float radius = 30.0;
    int amount = 10000;
    float offset = 10;

    mat4* modelMatrices;
    modelMatrices = new mat4[amount];


    for (int i = 0; i < amount; i++)
    {
        float angle = (float)i / (float)amount * 360.0f;
        // X
        float random = (rand() % 100) / 100.0f * 2 - 1; // -1  -> 1.0 random value
        float x = sin(angle) * radius + random * offset;
        // Y
        random = (rand() % 100) / 100.0f * 2 - 1; // -1  -> 1.0 random value
        float y = random * 3;
        //Z
        random = (rand() % 100) / 100.0f; // 0.0 -1.0 random value
        float z = cos(angle) * radius + random * offset;

        // position
        vec3 pos = vec3(x, y, z);
        // rotation
        float rotate_angel = (rand() % 360);
        // scale
        float size = (rand() % 5) / 100.0f + 0.01;  // 0.05 -0.25  
        mat4 M1 = mat4(1.0f);
        M1 = translate(M1, pos);
        M1 = rotate(M1, radians(rotate_angel), vec3(0.4f, 0.6f, 0.8f));
        M1 = scale(M1, vec3(size));
        modelMatrices[i] = M1;
    }
    

    // vertex buffer
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

    unsigned int VAO = vertex.VAO;
    glBindVertexArray(VAO);

    // vertex properties
    GLsizei vec4Size = sizeof(glm::vec4);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    // glBindVertexArray(0);
    //Instancing ends here.
    




    //Initialise all shaders
    Shader basicShader("shaderFolder/basic.vs","shaderFolder/basic.fs");
    Shader shader1("shaderFolder/reflect.vs","shaderFolder/reflect.fs");
    Shader shader_skybox("shaderFolder/sky.vs", "shaderFolder/sky.fs");
    Shader shader_instancing("shaderFolder/asteroid.vs","shaderFolder/basic.fs");
    Shader shader_geometry("shaderFolder/geo.vs", "shaderFolder/geo.fs", "shaderFolder/geo.gs");
    Shader shader_grass("shaderFolder/grass.vs","shaderFolder/grass.fs");
    // create objects (meshes)
    Meshes bunny_big = Meshes_OK[0];
    Meshes cube = Meshes_OK[1];
    Meshes cube1 = Meshes_OK[2];
    Meshes cube2= Meshes_OK[3];
    Meshes cube3 = Meshes_OK[4]; //asteroid

    Meshes mars= Meshes_OK[5];
    Meshes ship = Meshes_OK[6];
    // defaut is a part of ship
    Meshes sky = Meshes_OK[8];
    Meshes grass = Meshes_OK[9];
    Meshes window_object = Meshes_OK[10];
    


    // mat4 M(1);
    // mat4 V(1);
    // mat4 P(1);


    vector<std::string> faces
    {
        "skybox/right.jpg",
        "skybox/left.jpg",
        "skybox/top.jpg",
        "skybox/bottom.jpg",
        "skybox/front.jpg",
        "skybox/back.jpg"
    };

    unsigned int cubemapTexture = loadCubemap(faces);


    // load the all the textures
    for (int i = 0; i < textures.size(); i++)
    {
        Texture(textures[i].c_str(), i+1, true);
    }
    // print all the positions : (0,0,0)
    for (int i = 0; i < pos.size(); i++)
    {
        cout << "(";
        printV3(pos[i]);
        cout << ")\n";
    }

    // to see how many objects are loaded:
    print("The number of objects in the scene:"); // Just to tell you vicent: one .obj file may contain several objects, for example a nanosuit.obj contains his arm, leg, body....
    print(Meshes_OK.size());

    float angle = 0.0f; // used for geometry shader
    while (!glfwWindowShouldClose(window)) {
        camera.processInput(window); // keyboard event should be in the loop


        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClearColor(0,0,0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        V = camera.getV();
        P = perspective(radians(camera.fov), (float)(w / h), 0.1f, 100.0f);
            





        // draw the scene 
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
        //Draw first object to third object
        basicShader.use();
        basicShader.setMat4("V", V);
        basicShader.setMat4("P", P);
        basicShader.setVec3("camPos", camera.cameraPos);

        for (int i = 0; i < 6 ; i++)
        {


            int matID = Meshes_OK[i].matID;
            int texID = getTexID(textures, mats[matID].diff);
            basicShader.setInt("t0", texID+1);
            if(i==1)
            {
                Draw(Meshes_OK[i], basicShader, M,
                    vec3(0,0,0),
                    angle, vec3(1, 0, 0),
                    vec3(.5,.5,5)
                );
            }
            else {
           
            Draw(Meshes_OK[i], basicShader, M,
                pos[i],
                -90, vec3(1, 0, 0)
            );
            }

        }
        //Draw grass
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        shader_grass.use();
        shader_grass.setMat4("V", V);
        shader_grass.setMat4("P", P);
        shader_grass.setVec3("camPos", camera.cameraPos);
        shader_grass.setInt("t0", getTexID(textures, mats[grass.matID].diff)+1);
        Draw(grass, shader_grass,M, pos[0],
                -90, vec3(10, 0, 0));

        //Draw window
        shader_grass.use();
        shader_grass.setMat4("V", V);
        shader_grass.setMat4("P", P);
        shader_grass.setVec3("camPos", camera.cameraPos);
        shader_grass.setInt("t0", getTexID(textures, mats[window_object.matID].diff)+1);
        Draw(window_object, shader_grass,M, pos[0],
                -90, vec3(20, 0, 0));



        //Draw ship
        shader1.use();
        shader1.setMat4("V", V);
        shader1.setMat4("P", P);
        shader1.setVec3("camPos", camera.cameraPos);


        int matID = ship.matID;
        int texID = getTexID(textures, mats[matID].diff);
        shader1.setInt("t0", texID+1);
        Draw(ship, shader1, M,
            pos[4],
            -90, vec3(1, 0, 0)
        );


        //Draw the normals(geometry shader) of  the cube
        shader_geometry.use();
        shader_geometry.setMat4("V", V);
        shader_geometry.setMat4("P", P);
        shader_geometry.setFloat("time", static_cast<float>(glfwGetTime()));
       
        Draw(cube, shader_geometry, M,
            vec3(0, 0, 0),
            angle, vec3(1, 0, 0),
            vec3(.5, .5, 5)
        );

        glEnable(GL_BLEND);

        // draw the skybox
        glDepthFunc(GL_LEQUAL);

        shader_skybox.use();
        V = glm::mat4(glm::mat3(camera.getV()));
        shader_skybox.setMat4("V", V);
        shader_skybox.setMat4("P", P);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        shader_skybox.setInt("t0", 0);
        Draw(sky, shader_skybox, M);

        glDepthFunc(GL_LESS);



        //draw instancing asteroids:
        glBindVertexArray(VAO);
        shader_instancing.use();
        V = camera.getV();
        P = perspective(radians(camera.fov), (float)(w / h), 0.1f, 100.0f);

        shader_instancing.setMat4("V", V);
        shader_instancing.setMat4("P", P);
        shader_instancing.setInt("t0", 4);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(Meshes_OK[8].vID), GL_UNSIGNED_INT, (void*)(cube3.vOffset * sizeof(float)), amount);


        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    // clear buffer
    glfwTerminate();
    return 0;
}

