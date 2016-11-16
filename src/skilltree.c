#include "stringutils.h"
#include "skilltree.h"

int SkillTree_calculateTreeInfo_impl(SkillTree *skillTree, int pos, int depth) {
	int i;
	size_t leafCount = 0;
	if (skillTree->items[pos].children.length > 0) {
		for (i = 0; i < skillTree->items[pos].children.length; i++) {
			leafCount += SkillTree_calculateTreeInfo_impl(skillTree, skillTree->items[pos].children.items[i], depth+1);
		}
	} else {
		leafCount = 1;
	}

	skillTree->items[pos].leafCount = leafCount;
	skillTree->items[pos].depth = depth;
	return leafCount;
}

void SkillTree_calculateTreeInfo(SkillTree *skillTree) {
	if (skillTree->length > 0) {
		SkillTree_calculateTreeInfo_impl(skillTree, 0, 0);
	}
}

void SkillTree_load(SkillTree *skillTree, FILE *fin) {
	int n, i;
	fscanf(fin, "%d", &n);
	Array_allocate(skillTree, n);
	skillTree->length = n;
	for (i = 0; i < n; i++) {
		StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);
		skillTree->items[i].skillName = StringUtils_scan(fin, STRINGUTILS_NEWLINE);
		StringUtils_discardCharacters(fin, STRINGUTILS_WHITESPACE);
		skillTree->items[i].skillDescription = StringUtils_scan(fin, STRINGUTILS_NEWLINE);
		fscanf(fin, "%d", &(skillTree->items[i].requiredLevel));
		Array_allocate(&(skillTree->items[i].children), 2);

		skillTree->items[i].depth = 0;

		// the first node is assumed to be root and don't have parent info
		if (i > 0) {
			fscanf(fin, "%d", &(skillTree->items[i].parent));
		} else {
			skillTree->items[i].parent = SKILLTREE_NO_PARENT;
		}
	}

	for (i = 1; i < n; i++) {
		if (skillTree->items[i].parent != SKILLTREE_NO_PARENT && skillTree->items[i].parent < skillTree->length) {
			Array_pushBack(&(skillTree->items[skillTree->items[i].parent].children), i);
		}
	}

	// traverse tree, calculate leaf count and depth for each node
	SkillTree_calculateTreeInfo(skillTree);
}

int SkillTree_getSkillIndex(const SkillTree *skillTree, const char *skillName) {
	int i = 0;
	bool found = false;
	while (i < skillTree->length && !found) {
		if (StringUtils_strcmpi(skillTree->items[i].skillName, skillName) == 0) {
			found = true;
		} else {
			i++;
		}
	}
	return found ? i : -1;
}

bool SkillTree_isSkillUnlocked(const SkillTree *skillTree, const GameState *gameState, const char *skillName) {
	int idx = SkillTree_getSkillIndex(skillTree, skillName);
	if (idx >= 0 && idx < gameState->isSkillUnlocked.length) {
		return gameState->isSkillUnlocked.items[idx];	
	} else {
		return false;
	}
}

bool SkillTree_unlockSkill(const SkillTree *skillTree, const GameState *gameState, const char *skillName) {
	int idx = SkillTree_getSkillIndex(skillTree, skillName);
	if (idx >= 0 && idx < gameState->isSkillUnlocked.length) {
		int parent = skillTree->items[idx].parent;
		if (parent >= 0 && parent < gameState->isSkillUnlocked.length && gameState->isSkillUnlocked.items[parent]) {

			// TODO: check and deduct skill points

			gameState->isSkillUnlocked.items[idx] = true;
			return true;
		}
	}
	return false;
}

void SkillTree_deallocate(SkillTree *skillTree) {
	int i;
	for (i = 0; i < skillTree->length; i++) {
		Array_deallocate(&(skillTree->items[i].children));
	}
	Array_deallocate(skillTree);
}
