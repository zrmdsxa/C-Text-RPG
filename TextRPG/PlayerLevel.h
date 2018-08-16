//Class that holds stat values for a certain level

#ifndef PLAYERLEVEL_H
#define PLAYERLEVEL_H


class PlayerLevel
{
public:

	PlayerLevel(int lvl, int expReq, int atk, int def, int spd, int hp);
	const int level;
	const int expReq;
	const int attack;
	const int defense;
	const int speed;
	const int health;
};

#endif