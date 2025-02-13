#include "physics.hpp"
#include "btLinearMathAll.cpp"

void Physics::simulate(double dt)
{
    dynamicsWorld->stepSimulation(dt, 10, dt);
    // for(int i = 0; i < dynamicsWorld->getNumCollisionObjects(); i++){
    //     auto obj = dynamicsWorld->getCollisionObjectArray()[i];
    //     auto rb = btRigidBody::upcast(obj);
    //     auto pos = rb->getCenterOfMassPosition();
    //     printf("box %i: x: %f, y: %f, z: %f\n", i, pos.x(), pos.y(), pos.z());
    // }
}

int Physics::addBoxShape(float width, float height, float depth)
{
    int idx = collisionShapes.size();
    btCollisionShape* shape = new btBoxShape(btVector3(width, height, depth));
    collisionShapes.push_back(shape);
    return idx;
}

int Physics::addSphereShape(float radius)
{
    int idx = collisionShapes.size();
    btCollisionShape* shape = new btSphereShape(radius);
    collisionShapes.push_back(shape);
    return idx;
}

int Physics::addStaticMeshShape(std::vector<float> vertices)
{
    int idx = collisionShapes.size();
    printf("TODO: not implemented\n");
    // int triangleIndexBase;
    // auto b = new btTriangleIndexVertexArray(vertices.size()/3, &triangleIndexBase, );
    // auto m = btIndexedMesh();
    // b->addIndexedMesh(m);
    // btCollisionShape* shape = new btBvhTriangleMeshShape(b, false);
    // collisionShapes.push_back(shape);
    return idx;
}

int Physics::addRigidBody(int shapeId, btVector3 position, btScalar mass)
{
    //create a dynamic rigidbody
    // Get shape
    // TODO: bounds checking
    auto shape = collisionShapes[shapeId];

    // Create Dynamic Objects
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(position);

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (mass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        shape->calculateLocalInertia(mass, localInertia);


    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
    btRigidBody* body = new btRigidBody(rbInfo);
    // int id = dynamicsWorld->getNumCollisionObjects();
    dynamicsWorld->addRigidBody(body);
    // rigidBodyLookup.insert(std::make_pair(id, body));
    return rigidBodyLookup.add(body);
}

btRigidBody *Physics::getRigidBody(int bodyId)
{
    // TODO: bounds checking
    return rigidBodyLookup.get(bodyId);
}

bool Physics::initInternal()
{
    ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, 10, 0));
    return true;
}

void Physics::cleanupInternal()
{
    //remove the rigidbodies from the dynamics world and delete them
    for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject(obj);
	}
    rigidBodyLookup.clear();
    //delete collision shapes
	for (int j = 0; j < collisionShapes.size(); j++)
	{
		btCollisionShape* shape = collisionShapes[j];
		collisionShapes[j] = 0;
		delete shape;
	}
	//delete dynamics world
	delete dynamicsWorld;

	//delete solver
	delete solver;

	//delete broadphase
	delete overlappingPairCache;

	//delete dispatcher
	delete dispatcher;

	delete collisionConfiguration;

	//next line is optional: it will be cleared by the destructor when the array goes out of scope
	collisionShapes.clear();
}
