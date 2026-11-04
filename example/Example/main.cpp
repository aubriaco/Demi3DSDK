

#define _CRT_SECURE_NO_DEPRECATE
#include <Demi3D.h>

#include <memory>
#include <exception>

using namespace demi;
using namespace demi::scene;
using namespace demi::system;
using namespace demi::material;
using namespace demi::resource;
using namespace demi::effect;
using namespace demi::shader;

int main(int argc,char **argv)
try
{
	std::unique_ptr<DmDevice> Device(createDemiDevice(640,480,16,false,"Test"));
	DmScene* Scene = Device->getScene();
	DmSystem* DSys = Device->getSystem();
	DmResource* Resource = Device->getResourceManager();
	DmEffects* Effects = Device->getEffects();
	DmMaterialManager* MMgr = Device->getMaterialManager();
	DmShaderManager* SMgr = Device->getShaderManager();

	Device->setFog(true,EFM_LINEAR,1,60,0.4f,color4(0.5f,0.5f,0.5f,0.1f));

	DmEntity* ent = Scene->addEntity();
	ent->setPosition(vector3(0,0,-50));

	DmMeshEntity* test = Scene->addMeshEntity("sphere.gem",ent);
	test->setRotation(vector3(45,45,45));

	DmMeshEntity* stuff = Scene->addMeshEntity("scene.gem",ent);
	

	DmLightEntity* light = Scene->addLightEntity(0,300);
	light->setPosition(vector3(0,0,-40));

	DmCameraEntity* camera = Scene->addCameraEntity();
	camera->setPosition(vector3(0,5,-10));
	camera->setTarget(vector3(0,0,-40));

	while(Device->isRunning())
	{
		Device->beginScene();
		if (!Device->isRunning()) break;
		Device->renderScene();
		Device->flushScene();
		test->setRotation(test->getRotation()+vector3(0,0.1f,0));
	}
	return 0;
}
catch (const std::exception& error)
{
	fprintf(stderr, "%s\n", error.what());
	return 1;
}
