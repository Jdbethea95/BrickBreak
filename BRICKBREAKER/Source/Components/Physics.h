// define all ECS components related to movement & collision
#ifndef PHYSICS_H
#define PHYSICS_H

// BBG (avoid name collisions)
namespace BBG 
{
	// ECS component types should be *strongly* typed for proper queries
	// typedef is tempting but it does not help templates/functions resolve type
	struct Position { GW::MATH2D::GVECTOR2F value; };
	struct PlayerPos { GW::MATH2D::GVECTOR2F value; };
	struct Velocity { GW::MATH2D::GVECTOR2F value; float speed; };
	struct Orientation { GW::MATH2D::GMATRIX2F value; };
	struct Acceleration { GW::MATH2D::GVECTOR2F value; };

	struct WorldMatrix { GW::MATH::GMATRIXF value; };
	struct ObjectID { int value; };

	struct BoxCollider { GW::MATH2D::GRECTANGLE2F value; };
	struct BallColliders {
		GW::MATH2D::GRECTANGLE2F top;
		GW::MATH2D::GRECTANGLE2F bottom;
		GW::MATH2D::GRECTANGLE2F left;
		GW::MATH2D::GRECTANGLE2F right;

		bool colliderChecks[4];
	};

	// Individual TAGs
	struct Collidable {}; 
	
	// ECS Relationship tags
	struct CollidedWith {};
};

#endif