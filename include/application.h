#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <stdafx.h>


/// S.S.U.G.E (SSU Game Engine) is a simple, but functional game engine.  
namespace ssuge
{
	// Forward declaration to camera component
	class CameraComponent;

	/// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
	/// The Application class is our central hub.  It initializes all of our managers,       
	/// Has access to the ogre objects, etc. and contains the main loop.  Most of the *real* 
	/// work is delegated to the various managers (ScriptManager, InputManager, etc.)         
	/// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
	class Application : public OgreBites::ApplicationContext, public OgreBites::InputListener
	{
	// ****** ATTRIBUTES ****** //
	protected:
		/// The scene manager
		Ogre::SceneManager* mSceneManager;

		/// [temporary] rotation direction
		int mRotationDirection;

	// ****** CONSTRUCTORS / DESTUCTOR ******
	public:
		/// Default constructor -- calls the initialize method.
		Application();

		/// The destructor -- does nothing.  The shutdown method will be called by ApplicationContext.
		~Application() {  }

	// ***** OVERRIDES (from inherited classes) *****
	protected:
		/// Our callback used to set up everything (all managers, the scene, etc.)
		void setup() override;

		/// Our callback used to shut down everything (de-allocate everything)
		void shutdown() override;

		/// Our callback used to update the scene (called before rendering) -- we update all our managers and stats panel here.
		bool frameStarted(const Ogre::FrameEvent & evt) override;

		/// Called by Ogre(Bites) when a Key goes down -- we'll likely deconstruct this when we get to our own "InputManager"
		bool keyPressed(const OgreBites::KeyboardEvent& evt) override;

		/// Called by Ogre(Bites) when a Key comes up -- we'll likely deconstruct this when we get to our own "InputManager"
		bool keyReleased(const OgreBites::KeyboardEvent& evt) override;
	
		
	// ***** GETTERS / SETTERS ***** 
	public:
		/// Tells ogre to start its loop
		void run() { mRoot->startRendering(); }

	// ***** OTHER METHODS ******
	protected:
		/// Sets up the scene (and possibly the viewport)
		void createScene();

	public:
	};
}

#endif
