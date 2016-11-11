#ifndef SKILLTREE_H
#define SKILLTREE_H

#include <stdio.h>
#include "boolean.h"

typedef struct {
	int skillId;
	char *skillName;
	char *skillDescription;
	int requiredLevel;

	int *childSkills;
	size_t leafCount;
	int depth;
} Skill;

void SkillTree_load(SkillTree *skillTree, FILE *fin);

void SkillTree_save(const SkillTree *skillTree, FILE *fout);

void SkillTree_deallocate(SkillTree *skillTree);

#endif