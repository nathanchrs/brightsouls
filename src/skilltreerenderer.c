#include "skilltreerenderer.h"
#include "array.h"
#include "point.h"
#include "boolean.h"

#define SKILLTREE_RENDER_BORDER 2
#define SKILL_HORIZONTAL_PADDING 5

void SkillTreeRenderer_render(FrameBuffer *fb, const GameState *gameState, const SkillTree *st) {
	int i;

	// calculate maxDepth
	int maxDepth = -1;
	for (i = 0; i<st->length; i++) {
		if (st->items[i].depth > maxDepth) maxDepth = st->items[i].depth;
	}

	ARRAY(int) verticalPos;
	ARRAY(int) depthChildLeafCount;
	Array_allocate(&verticalPos, st->length);
	Array_allocate(&depthChildLeafCount, maxDepth+1);
	verticalPos.length = st->length;
	depthChildLeafCount.length = maxDepth+1;

	// initialize depthChildLeafCount
	for (i = 0; i<=maxDepth; i++) depthChildLeafCount.items[i] = 0;

	// calculate verticalPos for each node and depthChildLeafCount
	for (i = 0; i<st->length; i++) {
		verticalPos.items[i] = depthChildLeafCount.items[st->items[i].depth];
		depthChildLeafCount.items[st->items[i].depth] += st->items[i].leafCount;
	}

	// set constants (assumes SkillTree root at 0)
	int drawHeight = fb->height - 2*SKILLTREE_RENDER_BORDER;
	int drawWidth = fb->width - 2*SKILLTREE_RENDER_BORDER;
	int rootLeafCount = st->length > 0 ? st->items[0].leafCount : 0;

	// draw skills
	for (i = 0; i<st->length; i++) {
		int skillR = verticalPos.items[i] * (drawHeight/depthChildLeafCount.items[st->items[i].depth]);
		skillR += (drawHeight/rootLeafCount)*st->items[i].leafCount / 2 + SKILLTREE_RENDER_BORDER;
		int skillC1 = st->items[i].depth * (drawWidth/depthChildLeafCount.length) + SKILLTREE_RENDER_BORDER + 1;
		int skillC2 = skillC1 + (drawWidth/depthChildLeafCount.length) - SKILL_HORIZONTAL_PADDING - 2;

		if (st->items[i].parent != SKILLTREE_NO_PARENT) {
			int parentR = verticalPos.items[st->items[i].parent] * (drawHeight/depthChildLeafCount.items[st->items[st->items[i].parent].depth]);
			parentR += (drawHeight/rootLeafCount)*st->items[st->items[i].parent].leafCount / 2 + SKILLTREE_RENDER_BORDER;
			int parentLeft = st->items[st->items[i].parent].depth * (drawWidth/depthChildLeafCount.length) + SKILLTREE_RENDER_BORDER;
			int parentEdgeC = parentLeft + (drawWidth/depthChildLeafCount.length) - SKILL_HORIZONTAL_PADDING-1;

			FrameBuffer_drawHorizontalLine(fb, Point_make(parentR, parentEdgeC+1), Point_make(parentR, parentEdgeC+SKILL_HORIZONTAL_PADDING/2), '*', GRAY, TRANSPARENT);
			FrameBuffer_drawVerticalLine(fb, Point_make(parentR, parentEdgeC+SKILL_HORIZONTAL_PADDING/2+1), Point_make(skillR, parentEdgeC+SKILL_HORIZONTAL_PADDING/2+1), '*', GRAY, TRANSPARENT);
			FrameBuffer_drawHorizontalLine(fb, Point_make(skillR, parentEdgeC+SKILL_HORIZONTAL_PADDING/2+2), Point_make(skillR, parentEdgeC+SKILL_HORIZONTAL_PADDING), '*', GRAY, TRANSPARENT);
		}

		FrameBuffer_drawRectangle(fb, Point_make(skillR, skillC1), Point_make(skillR, skillC2), BLANK, TRANSPARENT, WHITE, WHITE);
		FrameBuffer_drawTextBox(fb, Point_make(skillR, skillC1), Point_make(skillR, skillC2), st->items[i].skillName, BLACK, TRANSPARENT);
	}

	Array_deallocate(&verticalPos);
	Array_deallocate(&depthChildLeafCount);
}