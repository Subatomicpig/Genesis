#ifndef COLLISION_H
#define COLLISION_H

class Collision
{
	friend class Sprite;
	
public:
	

	Collision();
	~Collision();

	int Collision::foodCheck(Sprite *player, Sprite *opp);

	
};

Collision::Collision()
{

}
Collision::~Collision()
{
}



int Collision::foodCheck(Sprite *player, Sprite *opp)
{
		


	/** bottom of sprite 1 is above top of sprite 2 */
	if( (player->ypos + player->rect.h) < opp->getY() )
		return 0;

	/** top of sprite 1 is below bottom of sprite 2 */
	if( player->ypos > (opp->getY() + opp->getH()) )
		return 0;

	/** right of sprite 1 is less than left of sprite 2 */
	if( (player->xpos + player->rect.w) - 120  < opp->getX() )
		return 0;
	

	/** left of sprite 1 is greater than right of sprite 2 */
	if( player->xpos > (opp->getX() + opp->getW()) )
		return 0;

	

	
	return 1;
}

#endif 
