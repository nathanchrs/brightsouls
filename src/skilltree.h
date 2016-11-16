#ifndef SKILLTREE_H
#define SKILLTREE_H

#include "array.h"
#include "boolean.h"
#include "gamestate.h"
#include <stdio.h>

#define SKILLTREE_NO_PARENT -1

typedef struct {
	char *skillName;
	char *skillDescription;
	int requiredLevel;

	int parent;
	ARRAY(int) children;
	size_t leafCount;
	int depth;
} Skill;

typedef ARRAY(Skill) SkillTree;

void SkillTree_load(SkillTree *skillTree, FILE *fin);

int SkillTree_searchIndex(const SkillTree *skillTree, const char *skillName);

bool SkillTree_isSkillUnlocked(const SkillTree *skillTree, const GameState *gameState, const char *skillName);

bool SkillTree_unlockSkill(const SkillTree *skillTree, const GameState *gameState, const char *skillName);

void SkillTree_deallocate(SkillTree *skillTree);

#endif