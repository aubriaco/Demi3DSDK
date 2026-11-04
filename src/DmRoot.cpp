
#include "../include/DmRoot.h"

namespace demi
{
	array<DmRoot*> arr_pObjects;

	void ExecutePreEvents()
	{
		for(int n = 0;n < arr_pObjects.size();n++)
			if(arr_pObjects[n])
				arr_pObjects[n]->PreEvents();
	}
	void ExecutePostEvents()
	{
		for(int n = 0;n < arr_pObjects.size();n++)
			if(arr_pObjects[n])
				arr_pObjects[n]->PostEvents();
	}
	void ExecuteRender()
	{
		for(int n = 0;n < arr_pObjects.size();n++)
			if(arr_pObjects[n])
				arr_pObjects[n]->Render();
	}
	
	DmRoot::DmRoot()
	{
		arr_pObjects.add(this);
	}

	DmRoot::~DmRoot()
	{
		for(int n = 0;n < arr_pObjects.size();n++)
			if(this == arr_pObjects[n])
				arr_pObjects.remove(n);
	}

	void DmRoot::log(stringc str)
	{
		printf("%s\n",str.c_str());
	}
}
