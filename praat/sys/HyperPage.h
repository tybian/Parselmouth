#ifndef _HyperPage_h_
#define _HyperPage_h_
/* HyperPage.h
 *
 * Copyright (C) 1992-2011,2012,2014,2015 Paul Boersma
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "Editor.h"
#include "Collection.h"
#include "Graphics.h"

Thing_define (HyperLink, Daata) {
	double x1DC, x2DC, y1DC, y2DC;
};

autoHyperLink HyperLink_create (const char32 *name, double x1, double x2, double y1, double y2);

Thing_define (HyperPage, Editor) {
	GuiDrawingArea drawingArea;
	GuiScrollBar verticalScrollBar;
	bool d_hasExtraRowOfTools;
	autoGraphics graphics;
	Graphics ps;
	double d_x, d_y, rightMargin, previousBottomSpacing;
	long d_printingPageNumber;
	CollectionOf<structHyperLink> links;
	bool printing;
	int top, mirror;
	char32 *insideHeader, *middleHeader, *outsideHeader;
	char32 *insideFooter, *middleFooter, *outsideFooter;
	char32 *entryHint; double entryPosition;
	struct { char32 *page; int top; } history [20];
	int historyPointer;
	char32 *currentPageTitle;
	GuiMenuItem fontSizeButton_10, fontSizeButton_12, fontSizeButton_14, fontSizeButton_18, fontSizeButton_24;
	void *praatApplication, *praatObjects, *praatPicture;
	bool scriptErrorHasBeenNotified;
	structMelderDir rootDirectory;

	void v_destroy ()
		override;
	bool v_editable ()
		override { return false; }
	void v_createMenus ()
		override;
	void v_createChildren ()
		override;
	void v_dataChanged ()
		override;

	virtual void v_draw () { }
	virtual long v_getNumberOfPages () { return 0; }
	virtual long v_getCurrentPageNumber () { return 0; }
	virtual int v_goToPage (const char32 * /* title */) { return 0; }
	virtual void v_goToPage_i (long /* pageNumber */) { }
	virtual void v_defaultHeaders (EditorCommand /* cmd */) { }
	virtual bool v_hasHistory () { return false; }
	virtual bool v_isOrdered () { return false; }

	#include "HyperPage_prefs.h"
};

void HyperPage_clear (HyperPage me);

/* "Methods" */
#define HyperPage_ADD_BORDER  1
#define HyperPage_USE_ENTRY_HINT  2

int HyperPage_any (HyperPage me, const char32 *text, enum kGraphics_font font, int size, int style, double minFooterDistance,
	double x, double secondIndent, double topSpacing, double bottomSpacing, unsigned long method);
int HyperPage_pageTitle (HyperPage me, const char32 *title);
int HyperPage_intro (HyperPage me, const char32 *text);
int HyperPage_entry (HyperPage me, const char32 *title);
int HyperPage_paragraph (HyperPage me, const char32 *text);
int HyperPage_listItem (HyperPage me, const char32 *text);
int HyperPage_listItem1 (HyperPage me, const char32 *text);
int HyperPage_listItem2 (HyperPage me, const char32 *text);
int HyperPage_listItem3 (HyperPage me, const char32 *text);
int HyperPage_listTag (HyperPage me, const char32 *text);
int HyperPage_listTag1 (HyperPage me, const char32 *text);
int HyperPage_listTag2 (HyperPage me, const char32 *text);
int HyperPage_listTag3 (HyperPage me, const char32 *text);
int HyperPage_definition (HyperPage me, const char32 *text);
int HyperPage_definition1 (HyperPage me, const char32 *text);
int HyperPage_definition2 (HyperPage me, const char32 *text);
int HyperPage_definition3 (HyperPage me, const char32 *text);
int HyperPage_code (HyperPage me, const char32 *text);
int HyperPage_code1 (HyperPage me, const char32 *text);
int HyperPage_code2 (HyperPage me, const char32 *text);
int HyperPage_code3 (HyperPage me, const char32 *text);
int HyperPage_code4 (HyperPage me, const char32 *text);
int HyperPage_code5 (HyperPage me, const char32 *text);
int HyperPage_prototype (HyperPage me, const char32 *text);
int HyperPage_formula (HyperPage me, const char32 *formula);
int HyperPage_picture (HyperPage me, double width_inches, double height_inches, void (*draw) (Graphics g));
int HyperPage_script (HyperPage me, double width_inches, double height_inches, const char32 *script);

int HyperPage_goToPage (HyperPage me, const char32 *title);
void HyperPage_goToPage_i (HyperPage me, long i);

void HyperPage_init (HyperPage me, const char32 *title, Daata data);

void HyperPage_setEntryHint (HyperPage me, const char32 *entry);
void HyperPage_initSheetOfPaper (HyperPage me);

/* End of file HyperPage.h */
#endif
