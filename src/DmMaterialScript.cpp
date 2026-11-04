
#include "DmMaterialScript.h"
#include "DmGLExtensions.h"
#include <memory>
#include <sstream>

namespace demi
{
namespace material
{
	namespace func
	{
		void enable(aPtr args)
		{
			glEnable(args.Integer[0]);
		}
		void disable(aPtr args)
		{
			glDisable(args.Integer[0]);
		}

		void set_active_texture(aPtr args)
		{
			glActiveTextureARB(GL_TEXTURE0_ARB+args.Integer[0]);
		}

		void set_texture(aPtr args)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,args.Integer[0]);
		}
	}

	DmMaterialScript::DmMaterialScript(system::DmFileIO* file, resource::DmResource* resource)
		: Resource(resource)
	{
		std::unique_ptr<char[]> buf(file->readAll());
		Script = buf ? buf.get() : "";
		build();
	}

	DmMaterialScript::~DmMaterialScript()
	{
		list<fPtr>::iterator it;
		for(it = Module.begin();it != Module.end();++it)
			(*it).Args.destroy();
		Module.clear();
	}

	void DmMaterialScript::setSection(stringc name)
	{
		Section = name;
	}

	void DmMaterialScript::build()
	{
		std::istringstream input(Script.c_str());
		stringc section;
		std::string line;
		while (std::getline(input, line))
		{
			const auto start = line.find_first_not_of(" \t\r");
			if (start == std::string::npos)
				continue;
			if (line[start] == ':')
			{
				section = line.substr(start + 1, line.find_last_not_of(" \t\r") - start).c_str();
				continue;
			}
			std::istringstream command(line);
			std::string name, argument;
			if (!(command >> name >> argument))
				continue;
			if(name == "enable")
			{
				aPtr args;
				args.Integer = new int[1];
				args.Integer[0] = atoi(argument.c_str());
				FUNCTION(func::enable,&args,1,section);
			}
			if(name == "disable")
			{
				aPtr args;
				args.Integer = new int[1];
				args.Integer[0] = atoi(argument.c_str());
				FUNCTION(func::disable,&args,1,section);
			}
			if(name == "set_active_texture")
			{
				aPtr args;
				args.Integer = new int[1];
				args.Integer[0] = atoi(argument.c_str());
				FUNCTION(func::set_active_texture,&args,1,section);
			}
			if(name == "set_texture")
			{
				aPtr args;
				args.Integer = new int[1];
				resource::DmTexture* tex = Resource->loadTexture(argument.c_str());
				if (!tex)
				{
					args.destroy();
					continue;
				}
				args.Integer[0] = tex->getTexture();
				FUNCTION(func::set_texture,&args,1,section);
			}
		}
	}

	void DmMaterialScript::addToModule(TFUNCTION func, aPtr* arg, unsigned int argCount,
		stringc section)
	{
		fPtr ptr;
		ptr.Func = func;
		ptr.Args = *arg;
		ptr.Section = section;
		Module.push_back(ptr);
	}

	void DmMaterialScript::set()
	{
		list<fPtr>::iterator it;
		for(it = Module.begin();it != Module.end();++it)
		{
			if((*it).Section == Section || (*it).Section.size() == 0)
				(*it).Func((*it).Args);
		}
	}

	void DmMaterialScript::unset()
	{

	}

}
}
