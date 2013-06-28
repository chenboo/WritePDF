/*
 * << Haru Free PDF Library 2.0.0 >> -- font_demo.cpp
 *
 * Copyright (c) 1999-2006 Takeshi Kanno <takeshi_kanno@est.hi-ho.ne.jp>
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.
 * It is provided "as is" without express or implied warranty.
 *
 */
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <exception>
#include "./include/hpdf.h"
#include "algorithm"

int max(int x, int y)
{
	return x > y ? x : y;
}
#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif
error_handler (HPDF_STATUS   error_no,
               HPDF_STATUS   detail_no,
               void         *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%u\n",
      (HPDF_UINT)error_no, (HPDF_UINT)detail_no);

    throw std::exception ();
}

const char *font_list[] = {
    "Courier",
    "Courier-Bold",
    "Courier-Oblique",
    "Courier-BoldOblique",
    "Helvetica",
    "Helvetica-Bold",
    "Helvetica-Oblique",
    "Helvetica-BoldOblique",
    "Times-Roman",
    "Times-Bold",
    "Times-Italic",
    "Times-BoldItalic",
    "Symbol",
    "ZapfDingbats",
    NULL
};
#define  __WIN32__
void
print_grid  (HPDF_Doc     pdf,
			 HPDF_Page    page)
{
	HPDF_REAL height = HPDF_Page_GetHeight (page);
	HPDF_REAL width = HPDF_Page_GetWidth (page);
	HPDF_Font font = HPDF_GetFont (pdf, "Helvetica", NULL);
	HPDF_UINT x, y;

	HPDF_Page_SetFontAndSize (page, font, 5);
	HPDF_Page_SetGrayFill (page, 0.5);
	HPDF_Page_SetGrayStroke (page, 0.8);

	/* Draw horizontal lines */
	y = 0;
	while (y < height) {
		if (y % 10 == 0)
			HPDF_Page_SetLineWidth (page, 0.5);
		else {
			if (HPDF_Page_GetLineWidth (page) != 0.25)
				HPDF_Page_SetLineWidth (page, 0.25);
		}

		HPDF_Page_MoveTo (page, 0, y);
		HPDF_Page_LineTo (page, width, y);
		HPDF_Page_Stroke (page);

		if (y % 10 == 0 && y > 0) {
			HPDF_Page_SetGrayStroke (page, 0.5);

			HPDF_Page_MoveTo (page, 0, y);
			HPDF_Page_LineTo (page, 5, y);
			HPDF_Page_Stroke (page);

			HPDF_Page_SetGrayStroke (page, 0.8);
		}

		y += 5;
	}


	/* Draw virtical lines */
	x = 0;
	while (x < width) {
		if (x % 10 == 0)
			HPDF_Page_SetLineWidth (page, 0.5);
		else {
			if (HPDF_Page_GetLineWidth (page) != 0.25)
				HPDF_Page_SetLineWidth (page, 0.25);
		}

		HPDF_Page_MoveTo (page, x, 0);
		HPDF_Page_LineTo (page, x, height);
		HPDF_Page_Stroke (page);

		if (x % 50 == 0 && x > 0) {
			HPDF_Page_SetGrayStroke (page, 0.5);

			HPDF_Page_MoveTo (page, x, 0);
			HPDF_Page_LineTo (page, x, 5);
			HPDF_Page_Stroke (page);

			HPDF_Page_MoveTo (page, x, height);
			HPDF_Page_LineTo (page, x, height - 5);
			HPDF_Page_Stroke (page);

			HPDF_Page_SetGrayStroke (page, 0.8);
		}

		x += 5;
	}

	/* Draw horizontal text */
	y = 0;
	while (y < height) {
		if (y % 10 == 0 && y > 0) {
			char buf[12];

			HPDF_Page_BeginText (page);
			HPDF_Page_MoveTextPos (page, 5, y - 2);
#ifdef __WIN32__
			_snprintf (buf, 12, "%u", y);
#else
			snprintf (buf, 12, "%u", y);
#endif
			HPDF_Page_ShowText (page, buf);
			HPDF_Page_EndText (page);
		}

		y += 5;
	}


	/* Draw virtical text */
	x = 0;
	while (x < width) {
		if (x % 50 == 0 && x > 0) {
			char buf[12];

			HPDF_Page_BeginText (page);
			HPDF_Page_MoveTextPos (page, x, 5);
#ifdef __WIN32__
			_snprintf (buf, 12, "%u", x);
#else
			snprintf (buf, "%u", x);
#endif
			HPDF_Page_ShowText (page, buf);
			HPDF_Page_EndText (page);

			HPDF_Page_BeginText (page);
			HPDF_Page_MoveTextPos (page, x, height - 10);
			HPDF_Page_ShowText (page, buf);
			HPDF_Page_EndText (page);
		}

		x += 5;
	}

	HPDF_Page_SetGrayFill (page, 0);
	HPDF_Page_SetGrayStroke (page, 0);
}

void DrawTable(int x, int y, int width, int height)
{

}

void DrawString(HPDF_Page page, int x, int y, int width, const char* szInfo, HPDF_TextAlignment align)
{
	HPDF_Rect rect;
	rect.left = x;
	rect.top = y;
	rect.right = rect.left + width;
	rect.bottom = rect.top + 20;

	HPDF_Page_BeginText (page);
	HPDF_Page_TextRect (page, rect.left, rect.top, rect.right, rect.bottom,
		szInfo, align, NULL);
	HPDF_Page_EndText (page);
}

void DrawString(HPDF_Page page, int x, int y, const char* szInfo, HPDF_TextAlignment align)
{
	int nStrWidth = HPDF_Page_TextWidth (page, szInfo);

	HPDF_Rect rect;
	rect.left = x;
	rect.top = y;
	rect.right = rect.left + nStrWidth + 10;
	rect.bottom = rect.top + 20;

	HPDF_Page_BeginText (page);
	HPDF_Page_TextRect (page, rect.left, rect.top, rect.right, rect.bottom,
		szInfo, align, NULL);
	HPDF_Page_EndText (page);
}

void DrawString(HPDF_Page page, HPDF_Rect rect, const char* szInfo, HPDF_TextAlignment align)
{
	HPDF_Page_BeginText (page);
	HPDF_Page_TextRect (page, rect.left, rect.top, rect.right, rect.bottom,
		szInfo, align, NULL);
	HPDF_Page_EndText (page);
}


int main (int argc, char **argv)
{
	const char *page_title = "哎呦 我去!@#$@#%$^%&\n*^*^&x%%x。";
    HPDF_Doc  pdf;
	char fname[256] = "test";
    HPDF_Page page;
    HPDF_Font def_font;
    HPDF_REAL tw;
    HPDF_REAL nPageHeight;
    HPDF_REAL nPageWidth;
    HPDF_UINT i;

    //strcpy (fname, argv[0]);
    strcat (fname, ".pdf");

    pdf = HPDF_New (error_handler, NULL);
    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    }

    try {
        /* Add a new page object. */
        page = HPDF_AddPage (pdf);

		HPDF_Page_SetWidth(page, 800);
		HPDF_Page_SetHeight(page, 1200);

        nPageHeight = HPDF_Page_GetHeight (page);
        nPageWidth = HPDF_Page_GetWidth (page);

        /* Print the lines of the page. */
        //HPDF_Page_SetLineWidth (page, 1);
        //HPDF_Page_Rectangle (page, 50, 50, width - 100, height - 110);
        //HPDF_Page_Stroke (page);

		HPDF_UseCNSFonts(pdf);
		HPDF_UseCNSEncodings(pdf);

        ///* Print the title of the page (with positioning center). */
        def_font = HPDF_GetFont (pdf, "SimSun", "GBK-EUC-H");
        HPDF_Page_SetFontAndSize (page, def_font, 10);

		char* szLable1 = "学生名:";
		char* szLable2 = "考试名称:";
		char* szLable3 = "班级名称:";
		char* szLable4 = "考试日期:";
		char* szLable5 = "考试时间:";

		char* szInfo1 = "chenbo";
		char* szInfo2 = "quiz 1";
		char* szInfo3 = "class mode 1";
		char* szInfo4 = "18:00 2012-06-27";
		char* szInfo5 = "120 min";

		int nLable1Width = HPDF_Page_TextWidth(page, szLable1);
		int nLable2Width = HPDF_Page_TextWidth(page, szLable2);
		int nLable3Width = HPDF_Page_TextWidth(page, szLable3);
		int nLable4Width = HPDF_Page_TextWidth(page, szLable4);
		int nLable5Width = HPDF_Page_TextWidth(page, szLable5);

		int nInfo1Width = HPDF_Page_TextWidth(page, szInfo1);
		int nInfo2Width = HPDF_Page_TextWidth(page, szInfo2);
		int nInfo3Width = HPDF_Page_TextWidth(page, szInfo3);
		int nInfo4Width = HPDF_Page_TextWidth(page, szInfo4);
		int nInfo5Width = HPDF_Page_TextWidth(page, szInfo5);

		int nLableMaxWidth = max(max(max(nLable1Width, nLable2Width), max(nLable3Width, nLable4Width)), nLable5Width);
		int nInfoMaxWidth = max(max(max(nInfo1Width, nInfo2Width), max(nInfo3Width, nInfo4Width)), nInfo5Width);

		HPDF_Rect rectLable;
		rectLable.left = (nPageWidth - nInfoMaxWidth - nLableMaxWidth - 20) / 2;
		rectLable.top = nPageHeight - 20;
		rectLable.right = rectLable.left + nLableMaxWidth;
		rectLable.bottom = rectLable.top - 20;
	
		DrawString(page, rectLable, szLable1, HPDF_TALIGN_RIGHT);

		rectLable.top -= 15;
		rectLable.bottom -= 15;
		DrawString(page, rectLable, szLable2, HPDF_TALIGN_RIGHT);

		rectLable.top -= 15;
		rectLable.bottom -= 15;
		DrawString(page, rectLable, szLable3, HPDF_TALIGN_RIGHT);
		
		rectLable.top -= 15;
		rectLable.bottom -= 15;
		DrawString(page, rectLable, szLable4, HPDF_TALIGN_RIGHT);
		
		rectLable.top -= 15;
		rectLable.bottom -= 15;
		DrawString(page, rectLable, szLable5, HPDF_TALIGN_RIGHT);

		HPDF_Page_SetFontAndSize (page, def_font, 9);

		HPDF_Rect rectInfo;
		rectInfo.left = rectLable.right + 10;
		rectInfo.top = nPageHeight - 20;
		rectInfo.right = rectInfo.left + nInfoMaxWidth;
		rectInfo.bottom = rectInfo.top - 20;

		DrawString(page, rectInfo, szInfo1, HPDF_TALIGN_LEFT);

		rectInfo.top -= 15;
		rectInfo.bottom -= 15;
		DrawString(page, rectInfo, szInfo2, HPDF_TALIGN_LEFT);

		rectInfo.top -= 15;
		rectInfo.bottom -= 15;
		DrawString(page, rectInfo, szInfo3, HPDF_TALIGN_LEFT);

		rectInfo.top -= 15;
		rectInfo.bottom -= 15;
		DrawString(page, rectInfo, szInfo4, HPDF_TALIGN_LEFT);

		rectInfo.top -= 15;
		rectInfo.bottom -= 15;
		DrawString(page, rectInfo, szInfo5, HPDF_TALIGN_LEFT);
		
		
		print_grid(pdf,page);
//////////////////////////////////////////////////////////////////////////////////////
		HPDF_Rect rectTable;
		rectTable.left = 100;
		rectTable.top = rectInfo.bottom - 40;
		rectTable.right = nPageWidth - 100;
		rectTable.bottom = rectTable.top - 20 * 3;

		HPDF_Page_Rectangle (page, rectTable.left, rectTable.top, rectTable.right - rectTable.left,
			rectTable.bottom - rectTable.top);
		HPDF_Page_Stroke (page);

		//line
		HPDF_Page_MoveTo (page, rectTable.left, rectTable.top - 20);
		HPDF_Page_LineTo (page, rectTable.right, rectTable.top - 20);
		HPDF_Page_Stroke (page);
		
		HPDF_Page_MoveTo (page, rectTable.left, rectTable.top - 40);
		HPDF_Page_LineTo (page, rectTable.right, rectTable.top - 40);
		HPDF_Page_Stroke (page);
		
		HPDF_Page_MoveTo (page, rectTable.left, rectTable.top - 60);
		HPDF_Page_LineTo (page, rectTable.right, rectTable.top - 60);
		HPDF_Page_Stroke (page);

		//column
		HPDF_Page_MoveTo (page, rectTable.left + (rectTable.right - rectTable.left) / 3, rectTable.top);
		HPDF_Page_LineTo (page, rectTable.left + (rectTable.right - rectTable.left) / 3, rectTable.bottom);
		HPDF_Page_Stroke (page);

		//HPDF_Page_MoveTo (page, rectTable.left, rectTable.top - 40);
		//HPDF_Page_LineTo (page, rectTable.right, rectTable.top - 40);
		//HPDF_Page_Stroke (page);

		//HPDF_Page_MoveTo (page, rectTable.left, rectTable.top - 60);
		//HPDF_Page_LineTo (page, rectTable.right, rectTable.top - 60);
		//HPDF_Page_Stroke (page);


		






















        HPDF_SaveToFile (pdf, fname);

    } catch (...) {
        HPDF_Free (pdf);
        return 1;
    }

    /* clean up */
    HPDF_Free (pdf);

    return 0;
}
