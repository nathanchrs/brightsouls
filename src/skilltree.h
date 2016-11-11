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

void SkillTree_load(Skill *skillTree, FILE *fin);

void SkillTree_save(const Skill *skillTree, FILE *fout);

void SkillTree_deallocate(Skill *skillTree);

#endif