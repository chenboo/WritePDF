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

int main (int argc, char **argv)
{
	const char *page_title = "∞•ﬂœ Œ“»•!@#$@#%$^%&\n*^*^&x%%x°£";
    HPDF_Doc  pdf;
	char fname[256] = "test";
    HPDF_Page page;
    HPDF_Font def_font;
    HPDF_REAL tw;
    HPDF_REAL height;
    HPDF_REAL width;
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

        height = HPDF_Page_GetHeight (page);
        width = HPDF_Page_GetWidth (page);

        /* Print the lines of the page. */
        HPDF_Page_SetLineWidth (page, 1);
        HPDF_Page_Rectangle (page, 50, 50, width - 100, height - 110);
        HPDF_Page_Stroke (page);

		HPDF_UseCNSFonts(pdf);
		HPDF_UseCNSEncodings(pdf);

        ///* Print the title of the page (with positioning center). */
        def_font = HPDF_GetFont (pdf, "SimSun", "GBK-EUC-H");
        HPDF_Page_SetFontAndSize (page, def_font, 10);


		print_grid(pdf, page);

        tw = HPDF_Page_TextWidth (page, page_title);
        HPDF_Page_BeginText (page);
        HPDF_Page_MoveTextPos (page, (width - tw) / 2, height - 50);
        HPDF_Page_ShowText (page, page_title);
        HPDF_Page_EndText (page);

        /* output subtitle. */
        HPDF_Page_BeginText (page);
        HPDF_Page_MoveTextPos (page, (width - tw) / 2, height - 70);
        HPDF_Page_SetFontAndSize (page, def_font, 10);
        HPDF_Page_ShowText (page, "∞•ﬂœ ∞•ﬂœ");
        HPDF_Page_EndText (page);

        //HPDF_Page_BeginText (page);
        //HPDF_Page_MoveTextPos (page, 60, height - 105);

        //i = 0;
        //while (font_list[i]) {
        //    const char* samp_text = "abcdefgABCDEFG12345!#$%&+-@?";
        //    HPDF_Font font = HPDF_GetFont (pdf, font_list[i], NULL);

        //    /* print a label of text */
        //    HPDF_Page_SetFontAndSize (page, def_font, 9);
        //    HPDF_Page_ShowText (page, font_list[i]);
        //    HPDF_Page_MoveTextPos (page, 0, -18);

        //    /* print a sample text. */
        //    HPDF_Page_SetFontAndSize (page, font, 20);
        //    HPDF_Page_ShowText (page, samp_text);
        //    HPDF_Page_MoveTextPos (page, 0, -20);

        //    i++;
        //}

        //HPDF_Page_EndText (page);

        HPDF_SaveToFile (pdf, fname);

    } catch (...) {
        HPDF_Free (pdf);
        return 1;
    }

    /* clean up */
    HPDF_Free (pdf);

    return 0;
}
