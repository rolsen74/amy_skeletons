
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

U32 _m_OM_New( Class *cl, Object *obj, struct opSet *msg )
{
// struct libBase *libBase;
struct GadData *data;
struct TagItem *tags;
struct TagItem *tag;
// struct Gadget *gad;
PTR needed_data;
S32 got_needed;
S32 error;

	MYINFO( "Gadget : _m_OM_New" );

//	If you need too passe data, can get it this way
//	Set in Resources_Init/MakeClass
//	libBase = (PTR) cl->cl_UserData;

	error = TRUE;
	got_needed = FALSE;
	needed_data = NULL;

	// -- Check and Retrive NEEDED Tags data

	tags = msg->ops_AttrList;

	while(( tag = NextTagItem( &tags )))
	{
		switch ( tag->ti_Tag )
		{
			case TEST_GADGET_Needed:
			{
				needed_data = (PTR) tag->ti_Data;
				got_needed = TRUE;
				break;
			}

			default:
			{
				break;
			}
		}
	}

	// Check for Needed/Missing Attributes

	if (( ! got_needed ) || ( ! needed_data ))
	{
		MYERROR( "Gadget : Missing Attribute" );
		obj = NULL;
		goto bailout;
	}

	// We passed let SuperMethod create our Object

	obj = (Object *) IDoSuperMethodA( cl, obj, (PTR) msg );

	if ( ! obj )
	{
		goto bailout;
	}

	// We got created lets Init our Data Area

//	Sometime you need too peek into The Gadget structure
// 	gad = (struct Gadget *) obj;

	data = INST_DATA( cl, obj );

	memset( data, 0, sizeof( struct GadData ));

	data->needed_data = needed_data;

	// Default Settings

	data->Optional = FALSE;

	// -- Check for optional Tags

	tags = msg->ops_AttrList;

	while(( tag = NextTagItem( &tags )))
	{
		switch ( tag->ti_Tag )
		{
			case TEST_GADGET_Optional:
			{
				data->Optional = ( tag->ti_Data ) ? TRUE : FALSE ;
				break;
			}

			default:
			{
				break;
			}
		}
	}

	// --
	// Collect gadget data 

	if ( data->Optional )
	{
		data->SomeData = AllocVecTags( 1024,
			AVT_ClearWithValue, 0,
			TAG_END
		);

		if ( ! data->SomeData )
		{
			MYERROR( "Gadget : Error allocating memory" );
			goto bailout;
		}
	}

	// --

	data->Region		= NewRegion();
	data->Region_Installed	= FALSE;

	if ( ! data->Region )
	{
		MYERROR( "Gadget : Error creating New Region" );
		goto bailout;
	}

	error = FALSE;

bailout:

	if (( error ) && ( obj ))
	{
		ICoerceMethod( cl, obj, OM_DISPOSE );
		obj = NULL;
	}

	return( (U32) obj );
}
