#pragma once
#include "engine/module.hpp"
#include "btBulletDynamicsCommon.h"
#include <unordered_map>

class Physics : public Module{
    public:
    void simulate(double dt);
    int addBoxShape(float width, float height, float depth);
    int addSphereShape(float radius);
    int addRigidBody(int shapeId, btVector3 position, btScalar mass);
    btRigidBody* getRigidBody(int bodyId);
    protected:
    bool initInternal();
    void cleanupInternal();
    private:
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btBroadphaseInterface* overlappingPairCache;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;
    btAlignedObjectArray<btCollisionShape*> collisionShapes;
    std::unordered_map<int, btRigidBody*> rigidBodyLookup;
};