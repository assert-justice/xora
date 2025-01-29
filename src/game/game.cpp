#include "game.hpp"
#include <iostream>
#include "utils/fs.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "btLinearMathAll.cpp"
#include "globals.hpp"

float quad[] = {
    1.0f, 1.0f, 0.0f,     1.0f, 1.0f, // top right
    1.0f, 0.0f, 0.0f,     1.0f, 0.0f, // bottom right
    0.0f, 1.0f, 0.0f,     0.0f, 1.0f, // top left

    1.0f, 0.0f, 0.0f,     1.0f, 0.0f, // bottom right
    0.0f, 1.0f, 0.0f,     0.0f, 1.0f, // top left
    0.0f, 0.0f, 0.0f,     0.0f, 0.0f, // bottom left
};

float cube[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

// static void addBox(btDiscreteDynamicsWorld* dynamicsWorld, btCollisionShape* shape, float x, float y, float z){
//     //create a dynamic rigidbody

//     /// Create Dynamic Objects
//     btTransform startTransform;
//     startTransform.setIdentity();

//     btScalar mass(1.f);

//     //rigidbody is dynamic if and only if mass is non zero, otherwise static
//     bool isDynamic = (mass != 0.f);

//     btVector3 localInertia(0, 0, 0);
//     if (isDynamic)
//         shape->calculateLocalInertia(mass, localInertia);

//     startTransform.setOrigin(btVector3(x, y, z));

//     //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
//     btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
//     btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
//     btRigidBody* body = new btRigidBody(rbInfo);

//     dynamicsWorld->addRigidBody(body);
// }

Game::Game(){}
void Game::run(){
    // Do setup stuff
    // auto collisionConfiguration = new btDefaultCollisionConfiguration();
    // auto dispatcher = new btCollisionDispatcher(collisionConfiguration);
    // auto overlappingPairCache = new btDbvtBroadphase();
    // auto solver = new btSequentialImpulseConstraintSolver;
    // dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
    // dynamicsWorld->setGravity(btVector3(0, -10, 0));
    // //the ground is a cube of side 100 at position y = -56.
	// //the sphere will hit it at y = -6, with center at -5
	// {
	// 	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));

	// 	collisionShapes.push_back(groundShape);

	// 	btTransform groundTransform;
	// 	groundTransform.setIdentity();
	// 	groundTransform.setOrigin(btVector3(0, -56, 0));

	// 	btScalar mass(0.);

	// 	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	// 	bool isDynamic = (mass != 0.f);

	// 	btVector3 localInertia(0, 0, 0);
	// 	if (isDynamic)
	// 		groundShape->calculateLocalInertia(mass, localInertia);

	// 	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	// 	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	// 	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
	// 	btRigidBody* body = new btRigidBody(rbInfo);

	// 	//add the body to the dynamics world
	// 	dynamicsWorld->addRigidBody(body);
	// }

	// {
	// 	//create a dynamic rigidbody

	// 	btCollisionShape* colShape = new btBoxShape(btVector3(0.5f,0.5f,0.5f));
	// 	collisionShapes.push_back(colShape);
    //     addBox(dynamicsWorld, colShape, 2, 10, 0);
    //     addBox(dynamicsWorld, colShape, 1.5f, 11, 0);
    //     addBox(dynamicsWorld, colShape, 1, 12, 0);
	// }

    if(!engine.init(this)){
        std::cout << "Engine failed to initialize" << std::endl;
        return;
    }

    // //remove the rigidbodies from the dynamics world and delete them
    // for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	// {
	// 	btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
	// 	btRigidBody* body = btRigidBody::upcast(obj);
	// 	if (body && body->getMotionState())
	// 	{
	// 		delete body->getMotionState();
	// 	}
	// 	dynamicsWorld->removeCollisionObject(obj);
	// 	delete obj;
	// }
    // //delete collision shapes
	// for (int j = 0; j < collisionShapes.size(); j++)
	// {
	// 	btCollisionShape* shape = collisionShapes[j];
	// 	collisionShapes[j] = 0;
	// 	delete shape;
	// }
    // collisionShapes.clear();
    // delete dynamicsWorld;
    // delete solver;
    // delete overlappingPairCache;
    // delete dispatcher;
    // delete collisionConfiguration;
    // delete crate;
    // delete floor;
    engine.cleanup();
    // Do shutdown stuff
    std::cout << "Thanks for playing!" << std::endl;
}
void Game::init(){
    std::vector<float> quadData(quad, quad + sizeof quad / sizeof quad[0]);
    std::vector<float> cubeData(cube, cube + sizeof(cube)/4);
    auto quadMesh = engine.graphics.newMesh(cubeData, {3, 2});
    bool hasError = false;
    auto vertSrc = readFile(&hasError, "shaders/ball_vert.glsl");
    auto fragSrc = readFile(&hasError, "shaders/ball_frag.glsl");
    shader = engine.graphics.newShader(vertSrc, fragSrc);
    auto crateTexture = engine.graphics.loadImage("textures/container.jpg");
    auto floorTexture = engine.graphics.loadImage("textures/wall.jpg");
    globals.camera.position = glm::vec3(0, 5, -5);
    auto sh = engine.graphics.getShader(shader);
    sh->use();
    sh->setUniform("perspective", globals.camera.getView());
    // crate = new Box(
    //     engine.graphics.getTexture(crateTexture), 
    //     sh, 
    //     engine.graphics.getMesh(quadMesh)
    // );
    floor = new Box(
        engine.graphics.getTexture(floorTexture), 
        sh, 
        engine.graphics.getMesh(quadMesh)
    );
    engine.input.setMouseEnabled(false);
    globals.init();
}
void Game::update(double dt){
    if(globals.inputHandler.pause->isPressed()){
        engine.quit();
    }
    // globals.camera.rotation.x += globals.inputHandler.look->getAxisY()->getValue() * dt;
    // globals.camera.rotation.y += globals.inputHandler.look->getAxisX()->getValue() * dt;
    globals.camera.rotation.x += engine.input.getMouseDY() * dt * 0.01f;
    globals.camera.rotation.y += engine.input.getMouseDX() * dt * 0.01f;
    float theta = globals.camera.rotation.y;
    float mx = -globals.inputHandler.move->getAxisX()->getValue() * dt;
    float mz = globals.inputHandler.move->getAxisY()->getValue() * dt;
    float dx = 0;
    float dz = 0;
    dx += mx * cos(theta);
    dz += mx * sin(theta);
    dx += mz * cos(theta+90);
    dz += mz * sin(theta+90);
    globals.camera.position.x += dx;
    globals.camera.position.z += dz;
    globals.camera.position.y -= globals.inputHandler.hover->getValue() * dt;

    auto sh = engine.graphics.getShader(shader);
    sh->use();
    sh->setUniform("perspective", globals.camera.getView());
    // dynamicsWorld->stepSimulation((float)dt, 10);
}
void Game::draw(){
    // for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
    // {
    //     btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
    //     btRigidBody* body = btRigidBody::upcast(obj);
    //     btTransform trans;
    //     if (body && body->getMotionState())
    //     {
    //         body->getMotionState()->getWorldTransform(trans);
    //     }
    //     else
    //     {
    //         trans = obj->getWorldTransform();
    //     }
    //     glm::mat4 matrix;
    //     auto matData = glm::value_ptr(matrix);
    //     trans.getOpenGLMatrix(matData);
    //     crate->draw(matrix);
    // }
    floor->draw(glm::vec3(0, -56, 0), glm::vec3(100, 100, 100));
}