#pragma once

enum class WordType
{
	Subject,
	Verb,
	Object,
};

enum class WordState
{
	Fixed,
	Pool,
	Use,
};

enum class SubjectType
{
	BABO = 0,
	WALL = 1,
	FLAG = 2,
};

enum class VerbType
{
	IS = 0,
	ADD = 1,
	MOVE = 2,
};

enum class ObjectType
{
	RIGHT = 0,
	UP = 1,
	LEFT = 2,
	DOWN = 3,
	WIN = 4,
	LOSE = 5,
};
