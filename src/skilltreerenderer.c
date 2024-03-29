#include "skilltreerenderer.h"
#include "array.h"
#include "point.h"
#include "boolean.h"
#include "stringutils.h"

#define SKILLTREE_RENDER_BORDER 2
#define SKILL_HORIZONTAL_PADDING 5

void SkillTreeRenderer_render(FrameBuffer *fb, const GameState *gameState, const SkillTree *st) {
	int i;
	char *reqExp;
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

	// draw skills and locked edges
	for (i = 0; i<st->length; i++) {
		int skillR = verticalPos.items[i] * (drawHeight/depthChildLeafCount.items[st->items[i].depth]);
		skillR += (drawHeight/rootLeafCount)*st->items[i].leafCount / 2 + SKILLTREE_RENDER_BORDER;
		int skillC1 = st->items[i].depth * (drawWidth/depthChildLeafCount.length) + SKILLTREE_RENDER_BORDER + 1;
		int skillC2 = skillC1 + (drawWidth/depthChildLeafCount.length) - SKILL_HORIZONTAL_PADDING - 2;

		if (st->items[i].parent != SKILLTREE_NO_PARENT) {
			if (i >= gameState->isSkillUnlocked.length || !gameState->isSkillUnlocked.items[i]) {
				int parentR = verticalPos.items[st->items[i].parent] * (drawHeight/depthChildLeafCount.items[st->items[st->items[i].parent].depth]);
				parentR += (drawHeight/rootLeafCount)*st->items[st->items[i].parent].leafCount / 2 + SKILLTREE_RENDER_BORDER;
				int parentLeft = st->items[st->items[i].parent].depth * (drawWidth/depthChildLeafCount.length) + SKILLTREE_RENDER_BORDER;
				int parentEdgeC = parentLeft + (drawWidth/depthChildLeafCount.length) - SKILL_HORIZONTAL_PADDING-1;

				FrameBuffer_drawHorizontalLine(fb, Point_make(parentR, parentEdgeC+1), Point_make(parentR, parentEdgeC+SKILL_HORIZONTAL_PADDING/2), '*', GRAY, TRANSPARENT);
				FrameBuffer_drawVerticalLine(fb, Point_make(parentR, parentEdgeC+SKILL_HORIZONTAL_PADDING/2+1), Point_make(skillR, parentEdgeC+SKILL_HORIZONTAL_PADDING/2+1), '*', GRAY, TRANSPARENT);
				FrameBuffer_drawHorizontalLine(fb, Point_make(skillR, parentEdgeC+SKILL_HORIZONTAL_PADDING/2+2), Point_make(skillR, parentEdgeC+SKILL_HORIZONTAL_PADDING), '*', GRAY, TRANSPARENT);
			}
		}

		if (i < gameState->isSkillUnlocked.length && gameState->isSkillUnlocked.items[i]) {
			FrameBuffer_drawRectangle(fb, Point_make(skillR, skillC1), Point_make(skillR, skillC2), BLANK, TRANSPARENT, WHITE, WHITE);
			FrameBuffer_drawTextBox(fb, Point_make(skillR, skillC1), Point_make(skillR, skillC2), "[U]", WHITE, GREEN);
			FrameBuffer_drawTextBox(fb, Point_make(skillR, skillC1+4), Point_make(skillR, skillC2), st->items[i].skillName, BLACK, TRANSPARENT);
		} else if (st->items[i].parent < gameState->isSkillUnlocked.length && gameState->isSkillUnlocked.items[st->items[i].parent]) {
			reqExp = StringUtils_fromInt(st->items[i].requiredExp, "%02d");
			FrameBuffer_drawRectangle(fb, Point_make(skillR, skillC1), Point_make(skillR, skillC2), BLANK, TRANSPARENT, WHITE, WHITE);
			FrameBuffer_drawTextBox(fb, Point_make(skillR, skillC1), Point_make(skillR, skillC2), "[L]", WHITE, BROWN);
			FrameBuffer_drawTextBox(fb, Point_make(skillR, skillC1+4), Point_make(skillR, skillC2), st->items[i].skillName, BLACK, TRANSPARENT);
			FrameBuffer_drawTextBox(fb, Point_make(skillR, skillC2-6), Point_make(skillR, skillC2-4), reqExp, BLACK, TRANSPARENT);
			StringUtils_deallocate(reqExp);
			FrameBuffer_drawTextBox(fb, Point_make(skillR, skillC2-3), Point_make(skillR, skillC2), "EXP", BLACK, TRANSPARENT);
		} else {
			reqExp = StringUtils_fromInt(st->items[i].requiredExp, "%02d");
			FrameBuffer_drawRectangle(fb, Point_make(skillR, skillC1), Point_make(skillR, skillC2), BLANK, TRANSPARENT, BLACK, BLACK);
			FrameBuffer_drawTextBox(fb, Point_make(skillR, skillC1), Point_make(skillR, skillC2), "N/A", MAROON, TRANSPARENT);
			FrameBuffer_drawTextBox(fb, Point_make(skillR, skillC1+4), Point_make(skillR, skillC2), st->items[i].skillName, GRAY, TRANSPARENT);
			FrameBuffer_drawTextBox(fb, Point_make(skillR, skillC2-6), Point_make(skillR, skillC2-4), reqExp, GRAY, TRANSPARENT);
			StringUtils_deallocate(reqExp);
			FrameBuffer_drawTextBox(fb, Point_make(skillR, skillC2-3), Point_make(skillR, skillC2), "EXP", GRAY, TRANSPARENT);
		}
	}

	// draw unlocked edges
	for (i = 0; i<st->length; i++) {
		int skillR = verticalPos.items[i] * (drawHeight/depthChildLeafCount.items[st->items[i].depth]);
		skillR += (drawHeight/rootLeafCount)*st->items[i].leafCount / 2 + SKILLTREE_RENDER_BORDER;

		if (st->items[i].parent != SKILLTREE_NO_PARENT) {
			if (i < gameState->isSkillUnlocked.length && gameState->isSkillUnlocked.items[i]) {
				int parentR = verticalPos.items[st->items[i].parent] * (drawHeight/depthChildLeafCount.items[st->items[st->items[i].parent].depth]);
				parentR += (drawHeight/rootLeafCount)*st->items[st->items[i].parent].leafCount / 2 + SKILLTREE_RENDER_BORDER;
				int parentLeft = st->items[st->items[i].parent].depth * (drawWidth/depthChildLeafCount.length) + SKILLTREE_RENDER_BORDER;
				int parentEdgeC = parentLeft + (drawWidth/depthChildLeafCount.length) - SKILL_HORIZONTAL_PADDING-1;

				FrameBuffer_drawHorizontalLine(fb, Point_make(parentR, parentEdgeC+1), Point_make(parentR, parentEdgeC+SKILL_HORIZONTAL_PADDING/2), '*', GREEN, TRANSPARENT);
				FrameBuffer_drawVerticalLine(fb, Point_make(parentR, parentEdgeC+SKILL_HORIZONTAL_PADDING/2+1), Point_make(skillR, parentEdgeC+SKILL_HORIZONTAL_PADDING/2+1), '*', GREEN, TRANSPARENT);
				FrameBuffer_drawHorizontalLine(fb, Point_make(skillR, parentEdgeC+SKILL_HORIZONTAL_PADDING/2+2), Point_make(skillR, parentEdgeC+SKILL_HORIZONTAL_PADDING), '*', GREEN, TRANSPARENT);
			}
		}
	}

	// draw title
	FrameBuffer_drawRectangle(fb, Point_make(2,2), Point_make(4,15), '=', TEAL, BLACK, BLACK);
	FrameBuffer_drawTextBox(fb, Point_make(3,4), Point_make(3, 13), "SKILL TREE", WHITE, TRANSPARENT);

	// draw EXP counter
	FrameBuffer_drawTextBox(fb, Point_make(27, 1), Point_make(27, 5), "[ EXP", YELLOW, TRANSPARENT);
    FrameBuffer_drawMeter(fb, Point_make(27, 7), 26, gameState->player.exp, gameState->player.maxExp);
    FrameBuffer_drawTextBox(fb, Point_make(27, 34), Point_make(27, 34), "]", YELLOW, TRANSPARENT);

	FrameBuffer_drawTextBox(fb, Point_make(fb->height-1,0), Point_make(fb->height-1, fb->width-1), gameState->message, WHITE, TRANSPARENT);
	FrameBuffer_setInputPrompt(fb, "Select skill to unlock [<skill name>/back/pause] >> ");

	Array_deallocate(&verticalPos);
	Array_deallocate(&depthChildLeafCount);
}
