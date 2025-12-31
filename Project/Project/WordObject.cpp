#include "WordObject.h"
#include "Engine.h"
#include "GameState.h"
#include <fstream>
#include <unordered_map>
#include "TileManager.h"
WordObject::WordObject(Font* font, const std::string& text) : Button(font, text)
{
	ResolveWordType(text);
}
void WordObject::Update(float dt, const EngineContext& engineContext)
{
	if (GetWordState() == WordState::Fixed)
	{
		normalColor = { 0.8f, 0.8f, 0.4f, 1.f };
		hoverColor = normalColor;
		//JIN_ERR("TextScale: " << GetWorldScale().x << ", " << GetWorldScale().y);
	}
	//JIN_LOG("TextScale: " << GetWorldScale().x << ", " << GetWorldScale().y);

	Button::Update(dt, engineContext);
}
void WordObject::ResolveWordType(const std::string& text)
{
	if (auto it = SubjectMap.find(text); it != SubjectMap.end())
	{
		type = WordType::Subject;
		subjectType = it->second;
		return;
	}

	if (auto it = VerbMap.find(text); it != VerbMap.end())
	{
		type = WordType::Verb;
		verbType = it->second;
		return;
	}

	if (auto it = ObjectMap.find(text); it != ObjectMap.end())
	{
		type = WordType::Object;
		objectiveType = it->second;
		return;
	}

	JIN_LOG("[WordObject] Unknown word: " << text);
}
void WordManager::Init(const EngineContext& engineContext)
{
	RenderManager* rm = engineContext.renderManager;
	if (rm)
	{
		if (rm->GetMaterialByTag("[Material]Pool"))
		{
			rm->RegisterTexture("[Texture]Pool", "Textures/PoolBG.png", TextureSettings{ TextureMinFilter::Linear, TextureMagFilter::Linear, TextureWrap::ClampToEdge, TextureWrap::ClampToEdge, true });
			rm->RegisterMaterial("[Material]Pool", "[EngineShader]default_texture", { {"u_Texture","[Texture]Pool"} });
		}
		if (rm->GetMaterialByTag("[Material]Centences"))
		{
			rm->RegisterTexture("[Texture]Centences", "Textures/CentencesBG.png", TextureSettings{ TextureMinFilter::Linear, TextureMagFilter::Linear, TextureWrap::ClampToEdge, TextureWrap::ClampToEdge, true });
			rm->RegisterMaterial("[Material]Centences", "[EngineShader]default_texture", { {"u_Texture","[Texture]Centences"} });
		}
		SetRenderLayer("[Layer]UIText");
	}
	poolBackground = static_cast<BackgroundObject*>(engineContext.stateManager->GetCurrentState()->GetObjectManager().AddObject(std::make_unique<GameObject>(), "[UI]PoolBG"));

	poolBackground->SetMesh(engineContext, "[EngineMesh]default"); // Quad
	poolBackground->SetMaterial(engineContext, "[Material]Pool");
	poolBackground->SetRenderLayer("[Layer]UI");
	poolBackground->GetTransform2D().SetPosition({ -engineContext.windowManager->GetWidth() / 4.f, -engineContext.windowManager->GetHeight() / 4.f });
	poolBackground->GetTransform2D().SetScale({ engineContext.windowManager->GetWidth()/2.f, engineContext.windowManager->GetHeight() / 2.f });
	// ===== Sentence Background =====
	sentenceBackground = static_cast<BackgroundObject*>(engineContext.stateManager->GetCurrentState()->GetObjectManager().AddObject(std::make_unique<GameObject>(), "[UI]SentenceBG"));

	sentenceBackground->SetMesh(engineContext, "[EngineMesh]default");
	sentenceBackground->SetMaterial(engineContext, "[Material]Centences");
	sentenceBackground->SetRenderLayer("[Layer]UI");
	sentenceBackground->GetTransform2D().SetPosition({ -engineContext.windowManager->GetWidth() / 4.f, engineContext.windowManager->GetHeight() / 4.f });
	sentenceBackground->GetTransform2D().SetScale({ engineContext.windowManager->GetWidth() / 2.f, engineContext.windowManager->GetHeight() / 2.f });
}
void WordManager::Update(float dt, const EngineContext& engineContext)
{
	LayoutPoolWords(engineContext);
	LayoutSentences(engineContext);
}

void WordManager::ReadFile(const EngineContext& engineContext, const int& InStage)
{
	std::string PoolFilePath = "Data/PoolWord" + std::to_string(InStage) + ".txt";
	std::ifstream PoolFile(PoolFilePath);

	if (!PoolFile.is_open())
	{
		std::cerr << "파일 열기 실패\n";
		return;
	}
	std::string line;
	std::vector<std::string> PoolWords;
	while (std::getline(PoolFile, line))
	{
		PoolWords.push_back(line);
	}
	PoolFile.close();

	std::string FixedFilePath = "Data/FixedSentences" + std::to_string(InStage) + ".txt";
	std::ifstream FixedFile(FixedFilePath);
	if (!FixedFile.is_open())
	{
		std::cerr << "파일 열기 실패\n";
		return;
	}
	std::vector<std::vector<std::string>> FixedSentences;
	std::string temp = line;
	size_t pos = 0;
	const std::string delimiter = ", ";

	while (std::getline(FixedFile, line))
	{
		if (line.empty())
			continue;

		std::vector<std::string> sentence;
		std::string temp = line;
		size_t pos = 0;
		const std::string delimiter = ", ";

		while ((pos = temp.find(delimiter)) != std::string::npos)
		{
			std::string word = temp.substr(0, pos);
			sentence.push_back(word);
			temp.erase(0, pos + delimiter.length());
		}

		if (!temp.empty())
			sentence.push_back(temp);

		FixedSentences.push_back(sentence);
	}
	FixedFile.close();
	InitWordList(engineContext, PoolWords, FixedSentences);
}

void WordManager::InitWordList(const EngineContext& engineContext, const std::vector<std::string>& InPoolWords, const std::vector<std::vector<std::string>>& InFixedSentences)
{
	// --- Pool Words ---
	for (const std::string& word : InPoolWords)
	{
		WordObject* newWord = static_cast<WordObject*>(engineContext.stateManager->GetCurrentState()->GetObjectManager().AddObject(std::make_unique<WordObject>(engineContext.renderManager->GetFontByTag("[Font]default"),word),"[Object]WordObject"));

		newWord->SetWordState(WordState::Pool);
		newWord->SetOnClick([this, newWord]() { OnButtonClicked(newWord); });

		Poolwords.push_back(newWord);
	}

	// --- Fixed Sentences ---
	for (const std::vector<std::string>& sentence : InFixedSentences)
	{
		Sentence s;

		for (size_t i = 0; i < sentence.size() && i < 3; ++i)
		{
			WordObject* newWord =static_cast<WordObject*>(engineContext.stateManager->GetCurrentState()->GetObjectManager().AddObject(std::make_unique<WordObject>(engineContext.renderManager->GetFontByTag("[Font]default"),sentence[i]),"[Object]WordObject"));
			newWord->SetWordState(WordState::Fixed);

			if (i == 0)      s.subject = newWord;
			else if (i == 1) s.verb = newWord;
			else if (i == 2) s.object = newWord;
		}

		Sentences.push_back(s);
	}
}

void WordManager::OnButtonClicked(WordObject* InObject)
{
	if (!InObject)
		return;

	switch (InObject->GetWordState())
	{
		case WordState::Fixed:
			return;

		case WordState::Pool:
		{
			InObject->SetWordState(WordState::Use);

			Poolwords.erase(std::remove(Poolwords.begin(), Poolwords.end(), InObject),Poolwords.end());

			Sentence* target = FindSentenceForWord(InObject);

			if (!target)
			{
				Sentences.push_back({});
				target = &Sentences.back();
			}

			switch (InObject->GetWordType())
			{
			case WordType::Subject:
				target->subject = InObject;
				break;

			case WordType::Verb:
				target->verb = InObject;
				break;

			case WordType::Object:
				target->object = InObject;
				break;
			}

			break;
		}
		case WordState::Use:
		{
			InObject->SetWordState(WordState::Pool);

			for (auto& sentence : Sentences)
			{
				if (sentence.subject == InObject) sentence.subject = nullptr;
				if (sentence.verb == InObject) sentence.verb = nullptr;
				if (sentence.object == InObject) sentence.object = nullptr;
			}

			Poolwords.push_back(InObject);
			break;
		}
	}
}
void WordManager::LayoutPoolWords(const EngineContext& engineContext)
{
	const float startX = -engineContext.windowManager->GetWidth() / 2.f + 50.f;
	const float startY = -40.f;

	const float rowGap = 60.f;
	const float wordGap = 30.f;
	const float maxWidth = engineContext.windowManager->GetWidth() / 2.f - 100.f;

	float x = startX;
	float y = startY;

	for (WordObject* word : Poolwords)
	{
		glm::vec2 size = word->GetWorldScale();

		if (x + size.x > startX + maxWidth)
		{
			x = startX;
			y -= rowGap;
		}

		word->GetTransform2D().SetPosition({x + size.x * 0.5f,y});

		x += size.x + wordGap;
	}
}

void WordManager::LayoutSentences(const EngineContext& engineContext)
{
	const float startY = engineContext.windowManager->GetHeight() / 2.f - 50.f;
	const float startX = -engineContext.windowManager->GetWidth() / 2.f + 50.f;

	const float lineSpacing = 60.f;
	const float wordGap = 30.f;

	for (size_t i = 0; i < Sentences.size(); ++i)
	{
		float y = startY - i * lineSpacing;
		float x = startX;

		auto& s = Sentences[i];

		auto placeWord = [&](WordObject* word)
			{
				if (!word) return;

				glm::vec2 size = word->GetWorldScale();

				x += size.x * 0.5f;
				word->GetTransform2D().SetPosition({ x, y });

				x += size.x * 0.5f + wordGap;
			};

		placeWord(s.subject);
		placeWord(s.verb);
		placeWord(s.object);
	}
}

void WordManager::CheckCompletedSentences(const EngineContext& engineContext)
{
	for (auto& sentence : Sentences)
	{
		if (!sentence.IsComplete())
			continue;

		ExecuteSentenceAction(sentence, engineContext);
	}
}

void WordManager::ExecuteSentenceAction(const Sentence& sentence, const EngineContext& engineContext)
{
	auto subject = sentence.subject->GetSubjectType();
	auto verb = sentence.verb->GetVerbType();
	auto object = sentence.object->GetObjectiveType();

	if (!subject || !verb || !object)
		return;

	if (*verb == VerbType::IS)
	{
		ApplyIsRule(*subject, *object, engineContext);
	}
	if (*verb == VerbType::MOVE)
	{
		if (*object == ObjectiveType::RIGHT)
		{
			ApplyRightRule(*subject, engineContext);
		}
		else if (*object == ObjectiveType::LEFT)
		{
			ApplyLeftRule(*subject, engineContext);
		}
		else if (*object == ObjectiveType::UP)
		{
			ApplyUpRule(*subject, engineContext);
		}
		else if (*object == ObjectiveType::DOWN)
		{
			ApplyDownRule(*subject, engineContext);
		}
	}
}



void WordManager::ApplyIsRule(SubjectType subject, ObjectiveType object, const EngineContext& engineContext)
{
	switch (object)
	{
	case ObjectiveType::YOU:
		ApplyYouRule(subject, engineContext);
		break;
	case ObjectiveType::WIN:
		ApplyWinRule(subject, engineContext);
		break;

	case ObjectiveType::DEFEAT:
		ApplyLoseRule(subject, engineContext);
		break;
	case ObjectiveType::PUSH:
		ApplyPushRule(subject, engineContext);
		break;
	case ObjectiveType::STOP:
		ApplyStopRule(subject, engineContext);
		break;
	case ObjectiveType::FIXED:
		ApplyFixedRule(subject, engineContext);
		break;
	

	default:
		break;
	}
}
void WordManager::ApplyYouRule(SubjectType subject, const EngineContext& engineContext)
{
	auto objects = engineContext.stateManager->GetCurrentState()->GetObjectManager().GetAllRawPtrObjects();
	TileManager& TM = TileManager::instance();
	for (auto* obj : objects)
	{
		if (!obj) continue;

		if (MatchesSubject(obj, subject))
		{
			obj->SetTag("You");
		}
	}
}
void WordManager::ApplyRightRule(SubjectType subject, const EngineContext& engineContext)
{
	auto objects = engineContext.stateManager->GetCurrentState()->GetObjectManager().GetAllRawPtrObjects();
	TileManager& TM = TileManager::instance();
	for (auto* obj : objects)
	{
		if (!obj) continue;

		if (MatchesSubject(obj, subject))
		{
			TM.TileMove(static_cast<TileObject&>(*obj), ObjectiveType::RIGHT);
		}
	}
}

void WordManager::ApplyUpRule(SubjectType subject, const EngineContext& engineContext)
{
	auto objects = engineContext.stateManager->GetCurrentState()->GetObjectManager().GetAllRawPtrObjects();
	TileManager& TM = TileManager::instance();
	for (auto* obj : objects)
	{
		if (!obj) continue;

		if (MatchesSubject(obj, subject))
		{
			TM.TileMove(static_cast<TileObject&>(*obj), ObjectiveType::UP);
		}
	}
}

void WordManager::ApplyLeftRule(SubjectType subject, const EngineContext& engineContext)
{
	auto objects = engineContext.stateManager->GetCurrentState()->GetObjectManager().GetAllRawPtrObjects();
	TileManager& TM = TileManager::instance();
	for (auto* obj : objects)
	{
		if (!obj) continue;

		if (MatchesSubject(obj, subject))
		{
			TM.TileMove(static_cast<TileObject&>(*obj), ObjectiveType::LEFT);
		}
	}
}

void WordManager::ApplyDownRule(SubjectType subject, const EngineContext& engineContext)
{
	auto objects = engineContext.stateManager->GetCurrentState()->GetObjectManager().GetAllRawPtrObjects();
	TileManager& TM = TileManager::instance();
	for (auto* obj : objects)
	{
		if (!obj) continue;

		if (MatchesSubject(obj, subject))
		{
			TM.TileMove(static_cast<TileObject&>(*obj), ObjectiveType::DOWN);
		}
	}
}

void WordManager::ApplyWinRule(SubjectType subject, const EngineContext& engineContext)
{
	auto objects = engineContext.stateManager->GetCurrentState()->GetObjectManager().GetAllRawPtrObjects();

	for (auto* obj : objects)
	{
		if (!obj) continue;

		if (MatchesSubject(obj, subject))
		{
			obj->SetTag("Win");
		}
	}
}

void WordManager::ApplyDefeatRule(SubjectType subject, const EngineContext& engineContext)
{
	auto objects = engineContext.stateManager->GetCurrentState()->GetObjectManager().GetAllRawPtrObjects();

	for (auto* obj : objects)
	{
		if (!obj) continue;

		if (MatchesSubject(obj, subject))
		{
			obj->SetTag("Defeat");
		}
	}
}

void WordManager::ApplyPushRule(SubjectType subject, const EngineContext& engineContext)
{
	auto objects = engineContext.stateManager->GetCurrentState()->GetObjectManager().GetAllRawPtrObjects();

	for (auto* obj : objects)
	{
		if (!obj) continue;

		if (MatchesSubject(obj, subject))
		{
			obj->SetTag("Push");
		}
	}
}

void WordManager::ApplyStopRule(SubjectType subject, const EngineContext& engineContext)
{
	auto objects = engineContext.stateManager->GetCurrentState()->GetObjectManager().GetAllRawPtrObjects();

	for (auto* obj : objects)
	{
		if (!obj) continue;

		if (MatchesSubject(obj, subject))
		{
			obj->SetTag("Stop");
		}
	}
}

void WordManager::ApplyFixedRule(SubjectType subject, const EngineContext& engineContext)
{
	auto objects = engineContext.stateManager->GetCurrentState()->GetObjectManager().GetAllRawPtrObjects();

	for (auto* obj : objects)
	{
		if (!obj) continue;

		if (MatchesSubject(obj, subject))
		{
			obj->SetTag("Fixed");
		}
	}
}

void WordManager::ApplyLoseRule(SubjectType subject, const EngineContext& engineContext)
{
	auto objects = engineContext.stateManager->GetCurrentState()->GetObjectManager().GetAllRawPtrObjects();

	for (auto* obj : objects)
	{
		if (!obj) continue;

		if (MatchesSubject(obj, subject))
		{
		}
	}
}

bool  WordManager::MatchesSubject(Object* obj, SubjectType subject)
{
	TileObject* tileObj = dynamic_cast<TileObject*>(obj);
	if (!tileObj)
		return false;

	switch (subject)
	{
	case SubjectType::BABO: return tileObj->GetTileType() == TileObject::TileType::BABO;
	case SubjectType::WALL: return tileObj->GetTileType() == TileObject::TileType::WALL;
	case SubjectType::FLAG: return tileObj->GetTileType() == TileObject::TileType::STAR;
	}
	return false;
}

Sentence* WordManager::FindSentenceForWord(WordObject* word)
{
	WordType type = word->GetWordType();

	for (auto& sentence : Sentences)
	{
		if (type == WordType::Subject && sentence.subject == nullptr)
			return &sentence;

		if (type == WordType::Verb && sentence.verb == nullptr)
			return &sentence;

		if (type == WordType::Object && sentence.object == nullptr)
			return &sentence;
	}

	return nullptr;
}


