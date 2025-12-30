#pragma once
#include "Button.h"
#include <string>
#include <vector>
#include "GameTypes.h"
#include "BackgroundObject.h"

class WordObject : public Button
{
public:
	WordObject(Font* font, const std::string& text);
	inline WordType GetWordType() const { return type; }
	inline void SetWordType(WordType InType) { type = InType; }
	inline WordState GetWordState() const { return state; }
	inline void SetWordState(WordState InState) { state = InState; }
	virtual void Update(float dt, const EngineContext& engineContext) override;
private:
	WordType type;
	WordState state = WordState::Pool;

	std::optional<SubjectType> subjectType;
	std::optional<VerbType> verbType;
	std::optional<ObjectiveType> objectiveType;

	void ResolveWordType(const std::string& text);
};

class WordManager : public GameObject
{
public: 
	virtual void Init(const EngineContext& engineContext) override;
	virtual void Update(float dt, const EngineContext& engineContext) override;

	void ReadFile(const EngineContext& engineContext, const int& InStage);
	void InitWordList(const EngineContext& engineContext, const std::vector<std::string>& InPoolWords, const std::vector<std::vector<std::string>>& InFixedSentences);
	void OnButtonClicked(WordObject* InObject);
	void LayoutPoolWords(const EngineContext& engineContext);
	void LayoutSentences(const EngineContext& engineContext);
	Sentence* FindSentenceForWord(WordObject* word);
	std::vector<WordObject*> Poolwords;
	std::vector<Sentence> Sentences;
	std::unique_ptr<GameObject> background;
	BackgroundObject* poolBackground = nullptr;
	BackgroundObject* sentenceBackground = nullptr;
};