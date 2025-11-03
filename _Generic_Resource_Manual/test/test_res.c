
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/test_resource.h>

#include <stdio.h>

// --

struct Library *			Test_ResourceBase	= NULL;
struct Test_ResourceIFace *	ITest_Resource		= NULL;

// --

static int myInit( void );
static void myFree( void );

// --

int main( void )
{
uint32_t val;

	if ( ! myInit())
	{
		goto bailout;
	}

	val = ITest_Resource->TESTRes_GetVal();

	if ( val != 0xacdc )
	{
		printf( "Invalid Value : $%08lx != $%08lx\n", val, 0xacdc );
	}
	else
	{
		printf( "Got Value : $%08lx\n", val );
	}

	printf( "Test Resource Okay\n" );

bailout:

	myFree();

	return( 0 );
}


// -- 

static int myInit( void )
{
int retval;
APTR res;

	retval = FALSE;

	// Load and Start Resource, will always return NULL
	res = IExec->OpenLibrary( "test_resource.resource", 0 );

//	if ( res )
	{
		printf( "Test_Res : OpenLibrary %p\n", res );
	}

	// Now get Base pointer, if it got loaded
	Test_ResourceBase = IExec->OpenResource( "test_resource.resource" );

	if ( ! Test_ResourceBase )
	{
		printf( "Error opening Test_Resource resource\n" );
		goto bailout;
	}

	ITest_Resource = (APTR) IExec->GetInterface( Test_ResourceBase, "main", 1, NULL );

	if ( ! ITest_Resource )
	{
		printf( "Error opening Test_Resource interface v1\n" );
		goto bailout;
	}

	retval = TRUE;

bailout:

	return( retval );
}

// -- 

static void myFree( void )
{
	if ( ITest_Resource )
	{
		IExec->DropInterface( (APTR) ITest_Resource );
	}

	if ( Test_ResourceBase )
	{
		// There are no CloseResource()
	}
}

// --