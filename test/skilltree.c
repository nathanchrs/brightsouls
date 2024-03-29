#include <assert.h>
#include <stdio.h>
#include "../src/skilltree.h"

void testSkillTree(const char *executableDirectory) {

	printf("  Testing SkillTree...\n");

	SkillTree skillTree;
	FILE *fin = IO_openFile(executableDirectory, "../test/skilltree.in");
	assert(fin != NULL);
	SkillTree_load(&skillTree, fin);
	IO_closeFile(fin);

	assert(skillTree.length == 5);
	int i;
	for (i = 0; i < skillTree.length; i++) {
		assert(skillTree.items[i].requiredExp == (i+1)*11);
	}
	assert(skillTree.items[0].children.length == 2);
	assert(skillTree.items[0].depth == 0);
	assert(skillTree.items[0].leafCount == 3);

	assert(skillTree.items[1].parent == 0);
	assert(skillTree.items[1].children.length == 2);
	assert(skillTree.items[1].depth == 1);
	assert(skillTree.items[1].leafCount == 2);

	assert(skillTree.items[2].parent == 0);
	assert(skillTree.items[2].children.length == 0);
	assert(skillTree.items[2].depth == 1);
	assert(skillTree.items[2].leafCount == 1);

	assert(skillTree.items[3].parent == 1);
	assert(skillTree.items[3].children.length == 0);
	assert(skillTree.items[3].leafCount == 1);
	assert(skillTree.items[3].depth == 2);
	
	assert(skillTree.items[4].parent == 1);
	assert(skillTree.items[4].children.length == 0);
	assert(skillTree.items[4].depth == 2);
	assert(skillTree.items[4].leafCount == 1);

	SkillTree_deallocate(&skillTree);
	printf("  SkillTree tested.\n");
}