#ifndef SKILLTREE_H
#define SKILLTREE_H

#include "array.h"

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

int SkillTree_searchIndex(SkillTree *skillTree, const char *skillName);

void SkillTree_deallocate(SkillTree *skillTree);

#endif