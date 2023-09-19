#pragma once
enum class GameState
{
	Menu,
	Intruction,
	Settting,
	Run,
	Gameover,
	Gamewin,
	Exit,
	Entry,
};

enum class EntityType
{
	Player			= 1 << 1,
	Enemy			= 1 << 2,
	Bullet_Player	= 1 << 3,
	Bullet_Enemy	= 1 << 4,
};