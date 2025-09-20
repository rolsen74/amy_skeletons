
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --
// Global Pointers

struct Library *			ApplicationBase		= NULL;
struct Library *			AslBase				= NULL;
struct Library *			ButtonBase			= NULL;
struct Library *			ChooserBase			= NULL;
struct Library *			CyberGfxBase		= NULL;
struct Library *			DOSBase				= NULL;
struct Library *			GfxBase				= NULL;
struct Library *			IntuitionBase		= NULL;
struct Library *			LabelBase			= NULL;
struct Library *			LayoutBase			= NULL;
struct Library *			NewlibBase			= NULL;
struct Library * 			SliderBase			= NULL;
struct Library *			SpaceBase			= NULL;
struct Library *			SysBase				= NULL;
struct Library *			UtilityBase			= NULL;
struct Library *			P96Base				= NULL;

Class *						ButtonClass			= NULL;
Class *						ChooserClass		= NULL;
Class *						LabelClass			= NULL;
Class *						LayoutClass			= NULL;
Class *						SliderClass			= NULL;
Class *						SpaceClass			= NULL;

struct ApplicationIFace *	IApplication 		= NULL;
struct AslIFace *			IAsl				= NULL;
struct CyberGfxIFace *		ICyberGfx			= NULL;
struct DOSIFace *			IDOS				= NULL;
struct ExecIFace *			IExec				= NULL;
struct GraphicsIFace *		IGraphics			= NULL;
struct IntuitionIFace *		IIntuition			= NULL;
struct Interface *			INewlib				= NULL;
struct LabelIFace *			ILabel				= NULL;
struct LayoutIFace *		ILayout				= NULL;
struct SliderIFace *		ISlider				= NULL;
struct SpaceIFace *			ISpace				= NULL;
struct UtilityIFace *		IUtility			= NULL;
struct P96IFace *			IP96				= NULL;
struct PrefsObjectsIFace *	IPrefsObjects 		= NULL;

// -- 

#if 0
struct Library *			ApplicationBase		= NULL;
struct Library *        	AslBase     		= NULL;
struct Library *        	ChooserBase     	= NULL;
struct Library *			CyberGfxBase		= NULL;
struct Library *        	DOSBase      		= NULL;
struct Library *        	GfxBase      		= NULL;
struct Library *        	IntuitionBase   	= NULL;
struct Library *        	P96Base     		= NULL;
struct Library *        	ScreenBlankerBase	= NULL;
struct Library *        	NewlibBase     		= NULL;
struct Library *        	UtilityBase     	= NULL;

struct ApplicationIFace *	IApplication 		= NULL;
struct AslIFace *    		IAsl         		= NULL;
struct ChooserIFace *    	IChooser        	= NULL;
struct CyberGfxIFace *		ICyberGfx			= NULL;
struct DOSIFace *    		IDOS            	= NULL;
struct ExecIFace *      	IExec           	= NULL;
struct IntuitionIFace * 	IIntuition      	= NULL;
struct P96IFace *   		IP96	        	= NULL;
struct PrefsObjectsIFace *	IPrefsObjects 		= NULL;
struct ScreenBlankerIFace *	IScreenBlanker		= NULL;
struct Interface *    		INewlib         	= NULL;
struct UtilityIFace *   	IUtility        	= NULL;

struct ScreenModeRequester *ScreenModeRequester = NULL;
unsigned int				RandomSeed;
#endif

// --

enum OpenType
{
	OT_End,
	OT_Class,
	OT_Library,
	OT_Interface,
	OT_Last
};

struct OpenStruct
{
	enum OpenType		os_Type;
	STR					os_STR;
	U32					os_VAL;
	PTR					os_PTR1;
	PTR					os_PTR2;
};

#define OS_LIB_NAME		os_STR
#define OS_LIB_VERS		os_VAL
#define OS_LIB_BASE		os_PTR2

#define OS_IFC_NAME		os_STR
#define OS_IFC_VERS		os_VAL
#define OS_IFC_BASE		os_PTR1
#define OS_IFC_IFC		os_PTR2

#define OS_CLS_NAME		os_STR
#define OS_CLS_VERS		os_VAL
#define OS_CLS_BASE		os_PTR1
#define OS_CLS_CLS		os_PTR2

// --

static struct OpenStruct OpenList[] =
{
	// -- First Newlib
	{ OT_Library,		"newlib.library",			50,			NULL,				& NewlibBase },
	{ OT_Interface,		"main",						1,			& NewlibBase,		& INewlib },

	// -- Libraries
	{ OT_Library,		"application.library",		50,			NULL,				& ApplicationBase },
	{ OT_Library,		"asl.library",				50,			NULL,				& AslBase },
	{ OT_Library,		"cybergraphics.library",	42,			NULL,				& CyberGfxBase },
	{ OT_Library,		"dos.library",				50,			NULL,				& DOSBase },
	{ OT_Library,		"graphics.library",			50,			NULL,				& GfxBase },
	{ OT_Library,		"intuition.library",		50,			NULL,				& IntuitionBase },
	{ OT_Library,		"Picasso96API.library",		50,			NULL,				& P96Base },
	{ OT_Library,		"utility.library",			50,			NULL,				& UtilityBase },

	// -- Interfaces
	{ OT_Interface,		"application",				2,			& ApplicationBase,	& IApplication },
	{ OT_Interface,		"prefsobjects",				2,			& ApplicationBase,	& IPrefsObjects },
	{ OT_Interface,		"main",						1,			& AslBase,			& IAsl },
	{ OT_Interface,		"main",						1,			& CyberGfxBase,		& ICyberGfx },
	{ OT_Interface,		"main",						1,			& DOSBase,			& IDOS },
	{ OT_Interface,		"main",						1,			& GfxBase,			& IGraphics },
	{ OT_Interface,		"main",						1,			& IntuitionBase,	& IIntuition },
	{ OT_Interface,		"main",						1,			& P96Base,			& IP96 },
	{ OT_Interface,		"main",						1,			& UtilityBase,		& IUtility },

	// -- Note: Intuition must be opened before OT classes
	{ OT_Class,			"gadgets/button.gadget",	50,			& ButtonBase,		& ButtonClass },
	{ OT_Class,			"gadgets/chooser.gadget",	50,			& ChooserBase,		& ChooserClass },
	{ OT_Class,			"gadgets/layout.gadget",	50,			& LayoutBase,		& LayoutClass },
	{ OT_Class,			"gadgets/slider.gadget",	50,			& SliderBase,		& SliderClass },
	{ OT_Class,			"gadgets/space.gadget",		50,			& SpaceBase,		& SpaceClass },
	{ OT_Class,			"images/label.image",		50,			& LabelBase,		& LabelClass },

	{ OT_End,			NULL,						0,			NULL,				NULL },
};

// --

S32 myOpenResources( void )
{
S32 retval;
S32 pos;

	MYERROR( "Blanker : myOpenResources" );

	retval = FALSE;

	for( pos=0 ; TRUE ; pos++ )
	{
		if ( OpenList[pos].os_Type == OT_End )
		{
			break;
		}

//		MYERROR( "Blanker : Processing : %s", OpenList[pos].os_STR );

		switch( OpenList[pos].os_Type )
		{
			case OT_Library:
			{
				PTR *base = OpenList[pos].OS_LIB_BASE;
				STR name = OpenList[pos].OS_LIB_NAME;
				U32 vers = OpenList[pos].OS_LIB_VERS;

				MYINFO( "Blanker : Opening library '%s' v%lu", name, vers );

				*base = OpenLibrary( name, vers );

				if ( ! *base )
				{
					MYERROR( "Blanker : Error opening library '%s' v%lu", name, vers );
					goto bailout;
				}
				break;
			}

			case OT_Interface:
			{
				PTR *base = OpenList[pos].OS_IFC_BASE;
				PTR *ifc = OpenList[pos].OS_IFC_IFC;
				STR name = OpenList[pos].OS_IFC_NAME;
				U32 vers = OpenList[pos].OS_IFC_VERS;

				MYINFO( "Blanker : Getting interface pos #%lu", pos );

				*ifc = GetInterface( *base, name, vers, NULL );

				if ( ! *ifc )
				{
					MYERROR( "Blanker : Error getting interface pos #%lu", pos );
					goto bailout;
				}
				break;
			}

			case OT_Class:
			{
				struct IClass **cls = OpenList[pos].OS_CLS_CLS;
				PTR *base = OpenList[pos].OS_CLS_BASE;
				STR name = OpenList[pos].OS_CLS_NAME;
				U32 vers = OpenList[pos].OS_CLS_VERS;

				MYINFO( "Blanker : Opening class '%s'", name );

				// Make sure you have opened Intuition first
				*base = OpenClass( name, vers, cls );

				if ( *base == NULL )
				{
					MYERROR( "Blanker : Error opening class '%s' pos #%lu", name, pos );
					goto bailout;
				}
				break;
			}

			default:
			{
				MYERROR( "Blanker : Unknown Resource type (%lu)", OpenList[pos].os_Type );
				goto bailout;
			}
		}
	}

	retval = TRUE;

bailout:

	return( retval );
}

// --

void myCloseResources( void )
{
S32 pos;

	MYERROR( "Blanker : myCloseResources" );

	// -- Find End of List
	for( pos=0 ; TRUE ; pos++ )
	{
		if ( OpenList[pos].os_Type == OT_End )
		{
			break;
		}
	}

	// -- Walk back
	// Test pos and then Subtact 1
	while( pos-- )
	{
		MYERROR( "Blanker : Processing : %s", OpenList[pos].os_STR );

		switch( OpenList[pos].os_Type )
		{
			case OT_Library:
			{
				PTR *base = OpenList[pos].OS_LIB_BASE;

				if ( *base )
				{
					CloseLibrary( *base );
					*base = NULL;
				}
				break;
			}

			case OT_Interface:
			{
				PTR *ifc = OpenList[pos].OS_IFC_IFC;

				if ( *ifc )
				{
					DropInterface( *ifc );
					*ifc = NULL;
				}
				break;
			}

			case OT_Class:
			{
				struct IClass **cls = OpenList[pos].OS_CLS_CLS;
				PTR *base = OpenList[pos].OS_CLS_BASE;

				if ( *base )
				{
					CloseClass( (PTR) *base );
					*base = NULL;
					*cls = NULL;
				}
				break;
			}

			default:
			{
				MYERROR( "Unknown Resource type (%ld)", OpenList[pos].os_Type );
				break;
			}
		}
	}
}

// --