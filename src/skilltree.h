#ifndef SKILLTREE_H
#define SKILLTREE_H

#include "array.h"
#include "boolean.h"
#include "gamestate.h"
#include "io.h"

#define SKILLTREE_NO_PARENT -1

typedef struct {
	char *skillName;
	char *skillDescription;
	int requiredExp;

	int parent;
	ARRAY(int) children;
	size_t leafCount;
	int depth;
} Skill;

typedef ARRAY(Skill) SkillTree;

void SkillTree_load(SkillTree *skillTree, FILE *fin);

int SkillTree_searchIndex(const SkillTree *skillTree, const char *skillName);

bool SkillTree_isSkillUnlocked(const SkillTree *skillTree, const GameState *gameState, const char *skillName);

bool SkillTree_unlockSkill(const SkillTree *skillTree, GameState *gameState, const char *skillName);

void SkillTree_addStats(const SkillTree *skillTree, GameState *gameState, int idx);

void SkillTree_deallocate(SkillTree *skillTree);

#endif