#include "Graphics\window.h"
#include "Camera\camera.h"
#include "Shaders\shader.h"
#include "Model Loading\mesh.h"
#include "Model Loading\texture.h"
#include "Model Loading\meshLoaderObj.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <list>
#include "Bounding.h"
#include "BigHouse.h"
#include "MiniHouse.h"
#include "Tree.h"
#include "LRock.h"


void processKeyboardInput();
void GameOver();
void testViewY();
void manageEvents();
void genJail();
void rain();

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

Window window("Game Engine", 800, 800);

//Starting Position
glm::vec3 strartingPoint = glm::vec3(1360, 2, 166);

Camera camera = Camera::Camera(strartingPoint);

glm::vec3 lightColor = glm::vec3(1.0f);
glm::vec3 lightPos = glm::vec3(-180.0f, 100.0f, -200.0f);


//Collisions
std::list<Bounding> Boundaries;
float xBorder1 = 50, xBorder2 = 1500, zBorder1 = 0, zBorder2 = 1000;

//Houses
std::list<BigHouse> BHList;
std::list<MiniHouse> MHList;

//Trees
std::list<Tree> TreeList;

//Rocks
std::list<LRock> LRockList;

//Events
int taskn=0;
bool dialogue1 = true, dialogue2 = false, dialogue3 = false, lookup = false, dialoguend = true, controls = true;
bool dialogue4 = true, dead = false, dialogue5 = false, dialogue6 = false, dialogue7 = false, dialogue8 = false;
Bounding bTask0 = Bounding::Bounding(20, 20, 303, 912);
Bounding bTask1 = Bounding::Bounding(5, 5, 303, 857);
Bounding bTask2_1 = Bounding::Bounding(5, 5, 227, 639);
Bounding bTask2_2 = Bounding::Bounding(20, 20, 348, 587);
Bounding bTask3 = Bounding::Bounding(5, 5, 350, 623);
Bounding bTask4 = Bounding::Bounding(10, 10, 1177, 918);
Bounding bTask5 = Bounding::Bounding(20, 20, 1213, 918);
Bounding bTask7 = Bounding::Bounding(100, 100, 1360, 166);

int main()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//UI
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);

	ImGui_ImplOpenGL3_Init("#version 130");

	//building and compiling shader program
	Shader shader("Shaders/vertex_shader.glsl", "Shaders/fragment_shader.glsl");
	Shader sunShader("Shaders/sun_vertex_shader.glsl", "Shaders/sun_fragment_shader.glsl");
	Shader terrainShader("Shaders/terrain_vertex_shader.glsl", "Shaders/terrain_fragment_shader.glsl");

	//Textures
	GLuint s1 = loadBMP("Resources/Textures/sky1.bmp");
	GLuint s2 = loadBMP("Resources/Textures/sky2.bmp");
	GLuint s3 = loadBMP("Resources/Textures/sky3.bmp");
	GLuint s4 = loadBMP("Resources/Textures/sky4.bmp");
	GLuint s5 = loadBMP("Resources/Textures/sky5.bmp");
	GLuint v = loadBMP("Resources/Textures/volcano.bmp");
	GLuint g = loadBMP("Resources/Textures/grass.bmp");
	GLuint p = loadBMP("Resources/Textures/planks.bmp");
	GLuint bp = loadBMP("Resources/Textures/bplanks.bmp");
	GLuint t = loadBMP("Resources/Textures/tree.bmp");
	GLuint l = loadBMP("Resources/Textures/Lava_Rock.bmp");
	GLuint w = loadBMP("Resources/Textures/white_color.bmp");
	GLuint e = loadBMP("Resources/Textures/entrance.bmp");

	glEnable(GL_DEPTH_TEST);


	std::vector<Texture> skyt1;
	skyt1.push_back(Texture());
	skyt1[0].id = s1;
	skyt1[0].type = "texture_diffuse";

	std::vector<Texture> skyt2;
	skyt2.push_back(Texture());
	skyt2[0].id = s2;
	skyt2[0].type = "texture_diffuse";

	std::vector<Texture> skyt3;
	skyt3.push_back(Texture());
	skyt3[0].id = s3;
	skyt3[0].type = "texture_diffuse";

	std::vector<Texture> skyt4;
	skyt4.push_back(Texture());
	skyt4[0].id = s4;
	skyt4[0].type = "texture_diffuse";

	std::vector<Texture> skyt5;
	skyt5.push_back(Texture());
	skyt5[0].id = s5;
	skyt5[0].type = "texture_diffuse";

	std::vector<Texture> voltext;
	voltext.push_back(Texture());
	voltext[0].id = v;
	voltext[0].type = "texture_diffuse";

	std::vector<Texture> grasstext;
	grasstext.push_back(Texture());
	grasstext[0].id = g;
	grasstext[0].type = "texture_diffuse";

	std::vector<Texture> plankstext;
	plankstext.push_back(Texture());
	plankstext[0].id = p;
	plankstext[0].type = "texture_diffuse";

	std::vector<Texture> treetext;
	treetext.push_back(Texture());
	treetext[0].id = t;
	treetext[0].type = "texture_diffuse";

	std::vector<Texture> lrocktext;
	lrocktext.push_back(Texture());
	lrocktext[0].id = l;
	lrocktext[0].type = "texture_diffuse";

	std::vector<Texture> bplankstext;
	bplankstext.push_back(Texture());
	bplankstext[0].id = bp;
	bplankstext[0].type = "texture_diffuse";

	std::vector<Texture> whitetext;
	whitetext.push_back(Texture());
	whitetext[0].id = w;
	whitetext[0].type = "texture_diffuse";

	std::vector<Texture> gatetext;
	gatetext.push_back(Texture());
	gatetext[0].id = e;
	gatetext[0].type = "texture_diffuse";


	// Create Obj files - easier :)
	// we can add here our textures :)
	MeshLoaderObj loader;
	Mesh terrain = loader.loadObj("Resources/Models/plane1.obj", voltext);
	Mesh plane = loader.loadObj("Resources/Models/plane.obj", grasstext);
	Mesh skybox1 = loader.loadObj("Resources/Models/skyrendertest.obj", skyt1);
	Mesh skybox2 = loader.loadObj("Resources/Models/skyrendertest.obj", skyt2);
	Mesh skybox3 = loader.loadObj("Resources/Models/skyrendertest.obj", skyt3);
	Mesh skybox4 = loader.loadObj("Resources/Models/skyrendertest.obj", skyt4);
	Mesh skybox5 = loader.loadObj("Resources/Models/skyrendertest.obj", skyt5);
	Mesh volcano = loader.loadObj("Resources/Models/volcano.obj", voltext);
	Mesh bigHouse = loader.loadObj("Resources/Models/bigHouse.obj", plankstext);
	Mesh miniHouse = loader.loadObj("Resources/Models/miniHouse.obj", plankstext);
	Mesh Treem = loader.loadObj("Resources/Models/Tree.obj", treetext);
	Mesh lRock = loader.loadObj("Resources/Models/lava_rock.obj", lrocktext);
	Mesh table = loader.loadObj("Resources/Models/table.obj", bplankstext);
	Mesh paper = loader.loadObj("Resources/Models/plane.obj", whitetext);
	Mesh wall = loader.loadObj("Resources/Models/wall.obj", gatetext);

	//Objects

	BigHouse bhouse = BigHouse::BigHouse(glm::vec3(300.0f, 15.0f, 950.0f), 180);

	BHList.push_back(bhouse);
	for (Bounding b : bhouse.getBoundaries())
		Boundaries.push_back(b);

	bhouse = BigHouse::BigHouse(glm::vec3(1300.0f, 15.0f, 500.0f), 270);

	BHList.push_back(bhouse);
	for (Bounding b : bhouse.getBoundaries())
		Boundaries.push_back(b);

	bhouse = BigHouse::BigHouse(glm::vec3(700.0f, 15.0f, 500.0f), 0);

	BHList.push_back(bhouse);
	for (Bounding b : bhouse.getBoundaries())
		Boundaries.push_back(b);

	bhouse = BigHouse::BigHouse(glm::vec3(233.0f, 15.0f, 536.0f), 0);

	BHList.push_back(bhouse);
	for (Bounding b : bhouse.getBoundaries())
		Boundaries.push_back(b);

	MiniHouse mhouse = MiniHouse::MiniHouse(glm::vec3(380.0f, 15.0f, 600.0f), 270);

	MHList.push_back(mhouse);
	for (Bounding m : mhouse.getBoundaries())
		Boundaries.push_back(m);

	mhouse = MiniHouse::MiniHouse(glm::vec3(700.0f, 15.0f, 950.0f), 90);

	MHList.push_back(mhouse);
	for (Bounding m : mhouse.getBoundaries())
		Boundaries.push_back(m);

	mhouse = MiniHouse::MiniHouse(glm::vec3(1200.0f, 15.0f, 950.0f), 180);

	MHList.push_back(mhouse);
	for (Bounding m : mhouse.getBoundaries())
		Boundaries.push_back(m);

	mhouse = MiniHouse::MiniHouse(glm::vec3(1200.0f, 15.0f, 700.0f), 180);

	MHList.push_back(mhouse);
	for (Bounding m : mhouse.getBoundaries())
		Boundaries.push_back(m);

	Tree tree = Tree::Tree(glm::vec3(300, -10, 300));

	TreeList.push_back(tree);
	Boundaries.push_back(tree.getBoundaries());


	tree = Tree::Tree(glm::vec3(1240, -10, 577));

	TreeList.push_back(tree);
	Boundaries.push_back(tree.getBoundaries());

	tree = Tree::Tree(glm::vec3(766, -10, 482));

	TreeList.push_back(tree);
	Boundaries.push_back(tree.getBoundaries());

	tree = Tree::Tree(glm::vec3(211, -10, 868));

	TreeList.push_back(tree);
	Boundaries.push_back(tree.getBoundaries());

	tree = Tree::Tree(glm::vec3(863, -10, 1064));

	TreeList.push_back(tree);
	Boundaries.push_back(tree.getBoundaries());

	tree = Tree::Tree(glm::vec3(1201, -10, 16));

	TreeList.push_back(tree);
	Boundaries.push_back(tree.getBoundaries());

	tree = Tree::Tree(glm::vec3(1052, -10, 1023));

	TreeList.push_back(tree);
	Boundaries.push_back(tree.getBoundaries());


	//Table

	Boundaries.push_back(Bounding::Bounding(3, 8, 1213, 918));

	//Walls
	
	Boundaries.push_back(Bounding::Bounding(10,60,1378, 118));
	Boundaries.push_back(Bounding::Bounding(10, 60, 1378, 270));


	//check if we close the window or press the escape button
	while (!window.isPressed(GLFW_KEY_ESCAPE) &&
		glfwWindowShouldClose(window.getWindow()) == 0)
	{


		//UI
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Tasks");
		ImGui::Text("Go to your house");
		if (taskn >= 2) ImGui::Text("Check inside one house");
		if (taskn >= 4) ImGui::Text("Check the rest of the houses");
		if (taskn >= 5) ImGui::Text("Read the note");
		if (taskn >= 7) ImGui::Text("Exit the village");

		if(lookup) ImGui::Text("Look up");
		ImGui::End();

		manageEvents();

		if (controls) {
			ImGui::Begin("Controls", &controls);
			ImGui::Text("Movement: W A S D");
			ImGui::Text("Camera movement: Arrows");
			ImGui::Text("Run: Shift");
			if (ImGui::Button("Close"))
				controls = false;
			ImGui::End();
		}

		window.clear();
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processKeyboardInput();
		


		 //// Code for the light ////


		glm::mat4 ProjectionMatrix = glm::perspective(90.0f, window.getWidth() * 1.0f / window.getHeight(), 0.1f, 100000.0f);
		glm::mat4 ViewMatrix = glm::lookAt(camera.getCameraPosition(), camera.getCameraPosition() + camera.getCameraViewDirection(), camera.getCameraUp());


		///// Test plane Obj file //////

		terrainShader.use();

		GLuint MatrixID2 = glGetUniformLocation(shader.getId(), "MVP");
		GLuint ModelMatrixID = glGetUniformLocation(shader.getId(), "model");

		glm::mat4 ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(20.0f, 1.0f, 20.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -200.0f, 0.0f));
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniform3f(glGetUniformLocation(terrainShader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(terrainShader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(terrainShader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		terrain.draw(terrainShader);

		shader.use();

		//Plane

		for (int j = 0; j < 9; j++) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-183.3f, -10.0f, j * 147.3f));
			for (int i = 0; i < 9; i++) {
				ModelMatrix = glm::translate(ModelMatrix, glm::vec3(183.3f, 0.0f, 0.0f));
				MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
				glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
				glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

				plane.draw(shader);
			}
		}

		//Volcano

		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-2000.0f, 0.0f, 1000.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(100.0f, 100.0f, 100.0f));

		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

		volcano.draw(shader);

		//Skybox

		if (taskn < 6) {
			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -2000.0f, 9150.0f));
			ModelMatrix = glm::rotate(ModelMatrix, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(145.0f, 1.0f, 145.0f));

			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			skybox1.draw(shader);

			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::rotate(ModelMatrix, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -2000.0f, 9150.0f));
			ModelMatrix = glm::rotate(ModelMatrix, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(145.0f, 1.0f, 145.0f));

			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			skybox2.draw(shader);

			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 7300.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(145.0f, 1.0f, 145.0f));

			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			skybox3.draw(shader);

			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::rotate(ModelMatrix, 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -2000.0f, 9150.0f));
			ModelMatrix = glm::rotate(ModelMatrix, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(145.0f, 1.0f, 145.0f));

			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			skybox4.draw(shader);

			ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::rotate(ModelMatrix, -90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -2000.0f, 9200.0f));
			ModelMatrix = glm::rotate(ModelMatrix, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(145.0f, 1.0f, 145.0f));

			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			skybox5.draw(shader);
		}
		//Skybox 2
		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 0.0f, -100.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2000.0f, 2000.0f, 2000.0f));

		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

		lRock.draw(shader);

		//Houses

		for (BigHouse bh : BHList) {

			ModelMatrix = bh.getTransform();


			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
			glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
			glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

			bigHouse.draw(shader);
		}

		for (MiniHouse mh : MHList) {

			ModelMatrix = mh.getTransform();


			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			glUniform3f(glGetUniformLocation(shader.getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
			glUniform3f(glGetUniformLocation(shader.getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
			glUniform3f(glGetUniformLocation(shader.getId(), "viewPos"), camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

			miniHouse.draw(shader);
		}

		for (Tree t : TreeList) {

			ModelMatrix = t.getTransform();

			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			Treem.draw(shader);
		}

		//Rocks

		for (LRock& r : LRockList) {
			if (r.Fall(deltaTime)) {
				if (r.getBoundaries().Collide(camera.getCameraPosition())) GameOver();
				Boundaries.push_back(r.getBoundaries());
			}
			ModelMatrix = r.getTransform();

			MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
			glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			lRock.draw(shader);
		}
		//Table 

		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(1213.0f, -7.0f, 918.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.1f, 0.1f, 0.1f));
		ModelMatrix = glm::rotate(ModelMatrix, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

		table.draw(shader);

		//Paper


		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(1213.0f, -4.4f, 918.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.02f, 0.01f, 0.01f));
		ModelMatrix = glm::rotate(ModelMatrix, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

		paper.draw(shader);

		//Gates
		ModelMatrix = glm::mat4(1.0);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(1378, -10, 118));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.15f, 0.15f, 0.3f));


		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

		wall.draw(shader);

		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0, 0, 500));

		MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

		wall.draw(shader);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.update();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();


}

void GameOver() {
	while (!window.isPressed(GLFW_KEY_ESCAPE) &&
		glfwWindowShouldClose(window.getWindow()) == 0) {
		window.clear();
		window.update();
	}
}

bool OutOfMap(glm::vec3 newPos) {

	if (newPos.x < xBorder1 || newPos.x > xBorder2 || newPos.z < zBorder1 || newPos.z > zBorder2) return true;
	else return false;
}

bool CanMove(glm::vec3 newPos) {

	for (Bounding b : Boundaries)
		if (b.Collide(newPos)) return false;

	if (OutOfMap(newPos)) return false;

	return true;

}

void processKeyboardInput()
{
	float cameraSpeed = 30 * deltaTime, rotationSpeed = 100 * deltaTime;

	//translation
	if (window.isPressed(GLFW_KEY_LEFT_SHIFT)) cameraSpeed *= 2;
	if (window.isPressed(GLFW_KEY_W) && CanMove(camera.TestMoveFront(cameraSpeed)))
		camera.keyboardMoveFront(cameraSpeed);
	if (window.isPressed(GLFW_KEY_S) && CanMove(camera.TestMoveBack(cameraSpeed)))
		camera.keyboardMoveBack(cameraSpeed);
	if (window.isPressed(GLFW_KEY_A) && CanMove(camera.TestMoveLeft(cameraSpeed)))
		camera.keyboardMoveLeft(cameraSpeed);
	if (window.isPressed(GLFW_KEY_D) && CanMove(camera.TestMoveRight(cameraSpeed)))
		camera.keyboardMoveRight(cameraSpeed);


	//rotation
	if (window.isPressed(GLFW_KEY_LEFT))
		camera.rotateOy(rotationSpeed);
	if (window.isPressed(GLFW_KEY_RIGHT))
		camera.rotateOy(-rotationSpeed);
	if (window.isPressed(GLFW_KEY_UP))
		camera.rotateOx(rotationSpeed);
	if (window.isPressed(GLFW_KEY_DOWN))
		camera.rotateOx(-rotationSpeed);

}

bool testViewY(float y){
	if (y < 0) {
		if (camera.getCameraViewDirection().y < y) return true;
		else return false;
	}
	else {
		if (camera.getCameraViewDirection().y > y) return true;
		else return false;
	}
}

void manageEvents() {

	switch (taskn) {
	case 0:
		if (dialogue1) {
		ImGui::Begin("Dialogue", &dialogue1);   
		ImGui::Text("After a long day of work the only thing");
		ImGui::Text("i want is to go back home.");
		ImGui::Text("(The house at the other corner of the village)");
		if (ImGui::Button("Close"))
			dialogue1 = false;
		ImGui::End();
		}
		if (bTask0.Collide(camera.getCameraPosition())) {
			taskn++;
			dialogue2 = true;
			controls = false;
		}
		break;
	case 1:
		if (dialogue2) {
			ImGui::Begin("Dialogue", &dialogue2);
			ImGui::Text("It seems that nobody is home.");
			ImGui::Text("Maybe i should ask my neighbors across the");
			ImGui::Text("street if they know where all my family is.");
			if (ImGui::Button("Close"))
				dialogue2 = false;
			ImGui::End();
		}
		if (bTask1.Collide(camera.getCameraPosition())) {
			dialogue2 = false;
			dialogue3 = true;
			taskn++;
		}
		
		break;
	case 2:
		if (dialogue3) {
			ImGui::Begin("Dialogue", &dialogue3);
			ImGui::Text("Which house should i check first?");
			ImGui::Text("(Something tells you that you should choose right)");
			if (ImGui::Button("Close"))
				dialogue3 = false;
			ImGui::End();
		}
		if (bTask2_1.Collide(camera.getCameraPosition()) && !dead) {
			dialogue3 = false;
			genJail();
			lookup = true;
			dead = true;
		}
		if (bTask2_2.Collide(camera.getCameraPosition())) {
			dialogue3 = false;
			dialogue4 = true;
			taskn++;
			LRockList.push_back(LRock::LRock(glm::vec3(227, 10, 639)));
		}
		break;
	case 3:
		if (dialogue4) {
			ImGui::Begin("Dialogue", &dialogue4);
			ImGui::Text("It seems like nobody is home.");
			ImGui::Text("I should check the other house.");
			if (ImGui::Button("Close"))
				dialogue4 = false;
			ImGui::End();
		}
		if (bTask3.Collide(camera.getCameraPosition())) {
			dialogue4 = false;
			dialogue5 = true;
			taskn++;
		}
		
		break;
	case 4:
		if (dialogue5) {
			ImGui::Begin("Dialogue", &dialogue5);
			ImGui::Text("Mmm, was that rock there before?");
			ImGui::Text("Maybe I should check the rest");
			ImGui::Text("of the houses.");
			if (ImGui::Button("Close"))
				dialogue5 = false;
			ImGui::End();
		}
		if (bTask4.Collide(camera.getCameraPosition())) {
			dialogue5 = false;
			dialogue6 = true;
			taskn++;
		}
		break;
	case 5:
		if (dialogue6) {
			ImGui::Begin("Dialogue", &dialogue6);
			ImGui::Text("That looks like a note");
			if (ImGui::Button("Close"))
				dialogue6 = false;
			ImGui::End();
		}
		if (bTask5.Collide(camera.getCameraPosition()) && testViewY(-0.7)) {
			dialogue6 = false;
			dialogue7 = true;
			taskn++;
		}
		break;
	case 6:
		if (dialogue7) {
			ImGui::Begin("Dialogue", &dialogue7);
			ImGui::Text("Lets see...");
			ImGui::Text("Ajam...");
			ImGui::Text("Hmmm");
			ImGui::Text("Ohhh");
			ImGui::Text("(More reading sounds)");
			ImGui::Text("It says they abandoned the village due to ");
			ImGui::Text("the volcan erupting and rocks falling ");
			ImGui::Text("everywhere, but i dont see any...");
			if (ImGui::Button("Close"))
				dialogue7 = false;
			ImGui::End();
		}
		if (bTask4.Collide(camera.getCameraPosition())) {
			dialogue7 = false;
			dialogue8 = true;
			taskn++;
			rain();
		}
		break;
	case 7:
		if (dialogue8) {
			ImGui::Begin("Dialogue", &dialogue8);
			ImGui::Text("Oh my god.");
			ImGui::Text("I should escape, NOW.");
			if (ImGui::Button("Close"))
				dialogue8 = false;
			ImGui::End();
		}
		if (bTask7.Collide(camera.getCameraPosition()) && !dead) {
			dialogue8 = false;
			genJail();
			lookup = true;
			dead = true;
		}
		
		break;
	}

	if (lookup) {
		if (dialoguend) {
			ImGui::Begin("Dialogue");
			ImGui::Text("Hmm?");
			ImGui::Text("You feel something above you.");

			ImGui::End();

			if (testViewY(0.7)) {
				dialoguend = false;
				LRockList.push_back(LRock::LRock(glm::vec3(camera.getCameraPosition().x, 500, camera.getCameraPosition().z)));
				
			}
		}
	}
}
void genJail() {
	Boundaries.push_back(Bounding::Bounding(5, 5, camera.getCameraPosition().x, camera.getCameraPosition().z));

}
void rain() {
	float height = 500;
	LRockList.push_back(LRock::LRock(glm::vec3(829, height,977 )));
	height += 500;
	LRockList.push_back(LRock::LRock(glm::vec3(604, height++,631 )));
	height += 500;
	LRockList.push_back(LRock::LRock(glm::vec3(737, height++,264 )));
	height += 500;
	LRockList.push_back(LRock::LRock(glm::vec3(1171, height++,576 )));
	height += 500;
	LRockList.push_back(LRock::LRock(glm::vec3(797, height++,539 )));
	height += 500;
	LRockList.push_back(LRock::LRock(glm::vec3(967, height++, 729)));
	height += 500;
	LRockList.push_back(LRock::LRock(glm::vec3(120, height++,442 )));
	height += 500;
	LRockList.push_back(LRock::LRock(glm::vec3(1354, height++,75 )));
	height += 500;
	LRockList.push_back(LRock::LRock(glm::vec3(193, height++,917 )));
	height += 500;
	LRockList.push_back(LRock::LRock(glm::vec3(1160, height++,895 )));
	height += 500;
	LRockList.push_back(LRock::LRock(glm::vec3(1197, height++, 228)));
	height += 500;

}





