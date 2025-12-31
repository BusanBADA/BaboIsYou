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
};
static const std::unordered_map<std::string, SubjectType> SubjectMap = {
	{"Babo", SubjectType::BABO},
	{"Player", SubjectType::BABO}, 
	{"Wall", SubjectType::WALL},
	{"Flag", SubjectType::FLAG},
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
	RIGHT = 0,
	UP = 1,
	LEFT = 2,
	DOWN = 3,
	WIN = 4,
	LOSE = 5,
};
static const std::unordered_map<std::string, ObjectiveType> ObjectMap =
{
	{"Right", ObjectiveType::RIGHT},
	{"Up", ObjectiveType::UP},
	{"Left", ObjectiveType::LEFT},
	{"Down", ObjectiveType::DOWN},
	{"Win", ObjectiveType::WIN},
	{"Lose", ObjectiveType::LOSE},
};

struct Sentence
{
	class WordObject* subject = nullptr;
	class WordObject* verb = nullptr;
	class WordObject* object = nullptr;
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
