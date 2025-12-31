#pragma once
#include "WordObject.h"
#include "GameTypes.h"

namespace BABO::Logic {
    class RuleManager {
    public:
        void UpdateRulesFromUI(const WordManager& wordManager) {
            uiRules.clear();
            for (const auto& sentence : wordManager.Sentences) {

                if (sentence.subject && sentence.verb && sentence.object) {
                    ActiveRule rule;
                    rule.subject = sentence.subject->GetSubjectType().value_or(SubjectType::BABO);
                    rule.verb = sentence.verb->GetVerbType().value_or(VerbType::IS);
                    rule.object = sentence.object->GetObjectType().value_or(ObjectiveType::WIN);
                    uiRules.push_back(rule);
                }
            }
        }

        bool HasProperty(SubjectType sub, ObjectiveType prop) const {
    
            for (const auto& rule : uiRules) {
                if (rule.subject == sub && rule.verb == VerbType::IS && rule.object == prop) return true;
            }
      
            return false;
        }

    private:
        struct ActiveRule { SubjectType subject; VerbType verb; ObjectiveType object; };
        std::vector<ActiveRule> uiRules;
    };
}