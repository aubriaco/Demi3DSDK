#ifndef __DM_OBJ_LOADER_INCLUDED__
#define __DM_OBJ_LOADER_INCLUDED__
#include "DmIMLoader.h"
#include <charconv>
#include <memory>
#include <sstream>
#include <string_view>
#include <vector>

namespace demi::scene
{
	class DmOBJLoader : public IMLoader
	{
		static bool readIndex(std::string_view text, const std::vector<vector3>& values, vector3& value)
		{
			if (text.empty())
				return false;
			int index = 0;
			const auto result = std::from_chars(text.data(), text.data() + text.size(), index);
			if (result.ec != std::errc{} || result.ptr != text.data() + text.size() || index == 0)
				return false;
			const auto offset = index > 0 ? index - 1LL : static_cast<long long>(values.size()) + index;
			if (offset < 0 || static_cast<size_t>(offset) >= values.size())
				return false;
			value = values[static_cast<size_t>(offset)];
			return true;
		}

		bool isBinary() override { return false; }

		SMesh load(system::DmFileIO* file) override
		{
			SMesh mesh;
			std::unique_ptr<char[]> contents(file->readAll());
			if (!contents)
				return mesh;

			std::vector<vector3> positions, normals, coordinates;
			std::vector<std::unique_ptr<SMeshGroup>> groups;
			std::istringstream input(contents.get());
			std::string line;
			while (std::getline(input, line))
			{
				std::istringstream fields(line);
				std::string kind;
				fields >> kind;
				vector3 value;
				if (kind == "v" && fields >> value.X >> value.Y >> value.Z)
					positions.push_back(value);
				else if (kind == "vn" && fields >> value.X >> value.Y >> value.Z)
					normals.push_back(value);
				else if (kind == "vt" && fields >> value.X >> value.Y)
					coordinates.push_back(value);
				else if (kind == "g")
					groups.push_back(std::make_unique<SMeshGroup>());
				else if (kind == "f")
				{
					std::vector<vertex> face;
					std::string corner;
					bool valid = true;
					while (fields >> corner && corner.front() != '#')
					{
						const std::string_view token(corner);
						const auto first = token.find('/');
						const auto second = first == token.npos ? token.npos : token.find('/', first + 1);
						vector3 position, uv, normal;
						valid = readIndex(token.substr(0, first), positions, position);
						if (valid && first != token.npos && second != first + 1)
							valid = readIndex(token.substr(first + 1, second == token.npos ?
								token.npos : second - first - 1), coordinates, uv);
						if (valid && second != token.npos)
							valid = readIndex(token.substr(second + 1), normals, normal);
						if (!valid)
							break;
						face.emplace_back(position, uv, normal);
					}
					if (!valid || face.size() < 3)
						continue;
					if (groups.empty())
						groups.push_back(std::make_unique<SMeshGroup>());
					for (size_t i = 1; i + 1 < face.size(); ++i)
					{
						groups.back()->Vertices.add(face[0]);
						groups.back()->Vertices.add(face[i]);
						groups.back()->Vertices.add(face[i + 1]);
					}
				}
			}
			for (const auto& group : groups)
			{
				if (!group->Vertices.size())
					continue;
				group->fillArrays();
				group->UseArrays = true;
				mesh.Groups.add(group.get());
			}
			for (auto& group : groups)
				if (group->UseArrays)
					group.release();
			return mesh;
		}

		bool isLoadableFile(stringc filename) override
		{
			return filename.size() >= 4 && filename.subString(filename.size() - 4, 4) == ".obj";
		}
	};
}

#endif
