#pragma once
#include <vector>

namespace BBG
{

	struct GamePacket
	{
		GW::MATH::GMATRIXF matrix;
		int objectID;
		std::string name;

		GamePacket() { matrix = GW::MATH::GMATRIXF(); objectID = -1; name = ""; }

		GamePacket(GW::MATH::GMATRIXF mat, int id, std::string eman)
		{
			matrix = mat;
			objectID = id;
			name = eman;
		}

		GamePacket(GW::MATH::GMATRIXF mat, int id)
		{
			matrix = mat;
			objectID = id;
			name = "N/A";
		}
	};

	class Packets 
	{
	public:
		std::vector<GamePacket> startPacket;
		std::vector<GamePacket> gamePacket;

		Packets() { startPacket = std::vector<GamePacket>(); gamePacket = std::vector<GamePacket>(); }
	};
	

}
/*
* Level is loaded in renderer. in renderer store name, id, and matrix. push out.
*/
