
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/intuition.h>

#include <proto/layout.h>
#include <proto/test_gadget.h>
#include <proto/window.h>

#include <classes/window.h>
#include <gadgets/layout.h>

#include <stdio.h>

// --

struct Library *			IntuitionBase		= NULL;
struct IntuitionIFace *		IIntuition			= NULL;

struct ClassLibrary *		Test_GadgetBase		= NULL;
Class *						Test_GadgetClass	= NULL;

struct Window *				winadr				= NULL;
Object *					winobj				= NULL;
uint32						winmask				= 0;

// --

static int myInit( void );
static void myFree( void );

// --

int main( void )
{
uint32 running;
uint32 result;
uint32 mask;
uint16 code;

	if ( ! myInit())
	{
		goto bailout;
	}

	running = TRUE;

	while( running )
	{
		mask = IExec->Wait( winmask | SIGBREAKF_CTRL_C );

		if ( mask & SIGBREAKF_CTRL_C )
		{
			running = FALSE;
			break;
		}

		if ( mask & winmask )
		{
			while( TRUE )
			{
				result = IIntuition->IDoMethod( winobj, WM_HANDLEINPUT, & code );

				if ( result == WMHI_LASTMSG )
				{
					break;
				}

				switch( result & WMHI_CLASSMASK )
				{
					case WMHI_CLOSEWINDOW:
					{
						running = FALSE;
						break;
					}

					default:
					{
						break;
					}
				}
			}
		}
	}

	printf( "Test Gadget Okay\n" );

bailout:

	myFree();

	return( 0 );
}


// -- 

static int myInit( void )
{
int retval;

	retval = FALSE;

	IntuitionBase = IExec->OpenLibrary( "intuition.library", 50 );

	if ( ! IntuitionBase )
	{
		printf( "Error opening Intuition library v50\n" );
		goto bailout;
	}

	IIntuition = (APTR) IExec->GetInterface( IntuitionBase, "main", 1, NULL );

	if ( ! IIntuition )
	{
		printf( "Error opening Intuition interface v1\n" );
		goto bailout;
	}

	Test_GadgetBase = IIntuition->OpenClass( "gadgets/test_gadget.gadget", 1, & Test_GadgetClass );

	if ( ! Test_GadgetBase )
	{
		printf( "Error opening Test_Gadget\n" );
		goto bailout;
	}

	winobj = IIntuition->NewObject( NULL, "window.class",
		WA_Title, "Test Gadget",
		WA_DragBar, TRUE,
		WA_CloseGadget, TRUE,
		WINDOW_Layout, IIntuition->NewObject( NULL, "layout.gadget",
			LAYOUT_AddChild, IIntuition->NewObject( NULL, "test_gadget.gadget",
				TEST_GADGET_Needed, 123,
			TAG_END	),
		TAG_END	),
	TAG_END );

	if ( ! winobj )
	{
		printf( "Failed to create Window Object\n" );
		goto bailout;
	}

	winadr = (APTR) IIntuition->IDoMethod( winobj, WM_OPEN );

	if ( ! winadr )
	{
		printf( "Failed to open Window\n" );
		goto bailout;
	}

	IIntuition->GetAttrs( winobj,
		WINDOW_SigMask, & winmask,
		TAG_END
	);

	retval = TRUE;

bailout:

	return( retval );
}

// -- 

static void myFree( void )
{
	if ( winobj )
	{
		IIntuition->DisposeObject( winobj );
	}

	if ( Test_GadgetBase )
	{
		IIntuition->CloseClass( Test_GadgetBase );
	}

	if ( IIntuition )
	{
		IExec->DropInterface( (APTR) IIntuition );
	}

	if ( IntuitionBase )
	{
		IExec->CloseLibrary( IntuitionBase );
	}
}

// --