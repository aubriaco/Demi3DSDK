
#include <Demi3D.h>			// You only need to include this file for Demi3D.
#include <memory>
#include <exception>

using namespace demi;		// Lets keep it simple and open the main namespace to avoid confusion.

int main(int argc, char *argv[])	// You should know what this does, else hit 'Back'
try
{
	std::unique_ptr<DmDevice> device(createDemiDevice(640, 480, 16, false, "Tutorial"));
	/*
		640: This is the width of the window and resolution to create.
		480: The height of the window and resolution.
		16: Legacy color-depth argument. SDL selects the color format.
		false: Toggle fullscreen. (true = fullscreen)
		"Tutorial": The caption of the window we are creating.
	*/
	
	scene::DmScene* scene = device->getScene();			// We grab a pointer to the Scene Manager
	
	scene::DmMeshEntity* entity = scene->addMeshEntity("sphere.gem",0);		// We load/add the mesh to the scene.
	/*
		"sphere.gem": The mesh which we will be loading.
		0: The parent, 0 means the Scene Manager itself will be the parent
	*/
	
	scene::DmCameraEntity* camera = scene->addCameraEntity();	// We add a camera to the scene.
	
	camera->setTarget(vector3(0,0,-10));	// We point the camera to look towards the front.
	/*
		vector3(0,0,-10): vector3(x,y,z)
	*/
	
	entity->setPosition(vector3(0,0,-40));	// We move the entity to the front of the camera.
	
	while(device->isRunning())		// The render loop.
	{
		device->beginScene();
		if (!device->isRunning()) break;	// We get ready for drawing the scene.
		device->renderScene();	// We render the scene.
		device->flushScene();	// We output the buffer.
	}
	return 0;
}
catch (const std::exception& error)
{
	fprintf(stderr, "%s\n", error.what());
	return 1;
}
