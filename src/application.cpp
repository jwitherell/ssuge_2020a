#include <stdafx.h>
#include <application.h>



ssuge::Application::Application() : OgreBites::ApplicationContext("ssuge 2020"), mRotationDirection(0)
{
	// Intentionally empty -- the initializers above did the real work.
}


void ssuge::Application::setup()
{
	OgreBites::ApplicationContext::setup();

	addInputListener(this);

	Ogre::Root* root = getRoot();
	mSceneManager = root->createSceneManager();

	// register our scene manager with the RTSS
	Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(mSceneManager);

	createScene();
}

void ssuge::Application::createScene()
{
	// without light we would just get a black screen    
	Ogre::Light* light = mSceneManager->createLight("MainLight");
	Ogre::SceneNode* lightNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
	lightNode->setPosition(20, 50, 50);
	lightNode->attachObject(light);
	// also need to tell where we are
	Ogre::SceneNode* camNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
	camNode->setPosition(0, 15, 30);
	camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
	// create the camera
	Ogre::Camera * cam = mSceneManager->createCamera("myCam");
	cam->setNearClipDistance(5); // specific to this sample
	cam->setAutoAspectRatio(true);
	camNode->attachObject(cam);
	// and tell it to render into the main window
	getRenderWindow()->addViewport(cam);
	// finally something to render
	Ogre::Entity * ent = mSceneManager->createEntity("Sinbad.mesh");
	Ogre::SceneNode * node = mSceneManager->getRootSceneNode()->createChildSceneNode("ogre_node");
	node->attachObject(ent);
	node->setPosition(0, 5, 0);
	// Create a ground plane
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::RGN_DEFAULT, plane, 100, 100, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* groundEntity = mSceneManager->createEntity("ground");
	mSceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setCastShadows(false);
	groundEntity->setMaterialName("Examples/Rockwall");
	// Set up shadows
	mSceneManager->setAmbientLight(Ogre::ColourValue(0, 0, 0));
	mSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	// Skybox
	mSceneManager->setSkyBox(true, "Examples/SpaceSkyBox", 300, false);
}



void ssuge::Application::shutdown() 
{
	OgreBites::ApplicationContext::shutdown();
}



bool ssuge::Application::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
		return false;
	}
	else if (evt.keysym.sym == OgreBites::SDLK_LEFT)
		mRotationDirection = 1;
	else if (evt.keysym.sym == OgreBites::SDLK_RIGHT)
		mRotationDirection = -1;
	return true;
}


bool ssuge::Application::keyReleased(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == OgreBites::SDLK_LEFT || evt.keysym.sym == OgreBites::SDLK_RIGHT)
		mRotationDirection = 0;
	return true;
}


bool ssuge::Application::frameStarted(const Ogre::FrameEvent & evt)
{
	// Important: processes input!
	OgreBites::ApplicationContext::frameStarted(evt);

	float dt = evt.timeSinceLastFrame;
	mSceneManager->getSceneNode("ogre_node")->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(90 * mRotationDirection * dt));

	return true;
}