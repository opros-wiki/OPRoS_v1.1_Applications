#include "stdafx.h"
#include "CDib.h"

/*
 *  Generated sources by OPRoS Component Generator (OCG V2.0 [Symbol])
 *  
 */
#ifndef _tagRECT_DATATYPE_H
#define _tagRECT_DATATYPE_H
#include <archive/opros_archive.h>
#include <string>


//#include <WinDef.h>
/*
** 
** 
*/
RectArray ( const RectArray &s )   { *this = s; }
RectArray& operator=( const RectArray &s )  {  return *this; }


void load_this(opros::archive::iarchive &ar, RectArray &t);
void save_this(opros::archive::oarchive &ar, RectArray &t);

inline std::string typeName(RectArray *p)
{
	return "RectArray";
}
 


#endif