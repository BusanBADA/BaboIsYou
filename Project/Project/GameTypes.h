#pragma once
#include <unordered_map>

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
	BLANK = 3,
	FLOOR = 4,
	BOX = 5,
	DEADZONE = 6,
	STAR = 7,
};
static const std::unordered_map<std::string, SubjectType> SubjectMap =
{
	{"Babo", SubjectType::BABO},
	{"Wall", SubjectType::WALL},
	{"Flag", SubjectType::FLAG},
	{"Blank", SubjectType::BLANK},
	{"Floor", SubjectType::FLOOR},
	{"Box", SubjectType::BOX},
	{"Deadzone", SubjectType::DEADZONE},
	{"Star", SubjectType::STAR},
};
enum class VerbType
{
	IS = 0,
	ADD = 1,
	MOVE = 2,
};
static const std::unordered_map<std::string, VerbType> VerbMap =
{
	{"Is", VerbType::IS},
	{"Add", VerbType::ADD},
	{"Move", VerbType::MOVE},
};
enum class ObjectiveType
{
	YOU = 0,
	RIGHT = 1,
	UP = 2,
	LEFT = 3,
	DOWN = 4,
	WIN = 5,
	DEFEAT = 6,
	PUSH = 7,
	STOP = 8,
	FIXED = 9,
};
static const std::unordered_map<std::string, ObjectiveType> ObjectMap =
{
	{"You", ObjectiveType::YOU},
	{"Right", ObjectiveType::RIGHT},
	{"Up", ObjectiveType::UP},
	{"Left", ObjectiveType::LEFT},
	{"Down", ObjectiveType::DOWN},
	{"Win", ObjectiveType::WIN},
	{"Defeat", ObjectiveType::DEFEAT},
	{"Push", ObjectiveType::PUSH},
	{"Stop", ObjectiveType::STOP},
	{"Fixed", ObjectiveType::FIXED},
};

struct Sentence
{
	class WordObject* subject = nullptr;
	class WordObject* verb = nullptr;
	class WordObject* object = nullptr;
	bool IsComplete() const
	{
		return subject && verb && object;
	}
};

struct WordDictionary
{
	static bool IsSubject(const std::string& text)
	{
		return SubjectMap.find(text) != SubjectMap.end();
	}
	static bool IsVerb(const std::string& text)
	{
		return VerbMap.find(text) != VerbMap.end();
	}
	static bool IsObject(const std::string& text)
	{
		return ObjectMap.find(text) != ObjectMap.end();
	}
	static SubjectType ToSubject(const std::string& text)
	{
		return SubjectMap.at(text);
	}
	static VerbType ToVerb(const std::string& text)
	{
		return VerbMap.at(text);
	}
	static ObjectiveType ToObject(const std::string& text)
	{
		return ObjectMap.at(text);
	}
};
