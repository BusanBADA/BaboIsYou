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
	std::optional<SubjectType> GetSubjectType() const { return subjectType; }
	std::optional<VerbType> GetVerbType() const { return verbType; }
	std::optional<ObjectiveType> GetObjectiveType() const { return objectiveType; }
private:
	WordType type;
	WordState state = WordState::Pool;

	std::optional<SubjectType> subjectType;
	std::optional<VerbType> verbType;
	std::optional<ObjectiveType> objectiveType;

	void ResolveWordType(const std::string& text);
public:
	std::optional<SubjectType> GetSubjectType() const { return subjectType; }
	std::optional<VerbType> GetVerbType() const { return verbType; }
	std::optional<ObjectiveType> GetObjectType() const { return objectiveType; }
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
	void CheckCompletedSentences(const EngineContext& engineContext);
	void ExecuteSentenceAction(const Sentence& sentence, const EngineContext& engineContext);
	void ApplyIsRule(SubjectType subject,ObjectiveType object,const EngineContext& engineContext);
	void ApplyYouRule(SubjectType subject, const EngineContext& engineContext);
	void ApplyRightRule(SubjectType subject, const EngineContext& engineContext);
	void ApplyUpRule(SubjectType subject, const EngineContext& engineContext);
	void ApplyLeftRule(SubjectType subject, const EngineContext& engineContext);
	void ApplyDownRule(SubjectType subject, const EngineContext& engineContext);
	void ApplyWinRule(SubjectType subject, const EngineContext& engineContext);
	void ApplyDefeatRule(SubjectType subject, const EngineContext& engineContext);
	void ApplyPushRule(SubjectType subject, const EngineContext& engineContext);
	void ApplyStopRule(SubjectType subject, const EngineContext& engineContext);
	void ApplyFixedRule(SubjectType subject, const EngineContext& engineContext);
	void ApplyLoseRule(SubjectType subject, const EngineContext& engineContext);
	bool MatchesSubject(Object* obj, SubjectType subject);
	Sentence* FindSentenceForWord(WordObject* word);
	std::vector<WordObject*> Poolwords;
	std::vector<Sentence> Sentences;
	std::unique_ptr<GameObject> background;
	BackgroundObject* poolBackground = nullptr;
	BackgroundObject* sentenceBackground = nullptr;
};