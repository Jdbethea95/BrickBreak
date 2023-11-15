// define all ECS components related to drawing
#ifndef VISUALS_H
#define VISUALS_H

// BBG (avoid name collisions)
namespace BBG
{
	struct Color { GW::MATH2D::GVECTOR3F value; };

	struct Material { Color diffuse = { 1, 1, 1 }; };

	/*struct WorldMatrix { GW::MATH::GMATRIXF value; };

	struct ObjectID { int value; };*/
};

#endif