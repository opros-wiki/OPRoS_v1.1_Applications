#include "stdafx.h"
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


void load_this(opros::archive::iarchive &ar, RECT &t);
void save_this(opros::archive::oarchive &ar, RECT &t);

inline std::string typeName(RECT *p)
{
	return "RECT";
}
 

void load_this(opros::archive::iarchive &ar, std::vector<RECT> &t);
void save_this(opros::archive::oarchive &ar, std::vector<RECT> &t);

inline std::string typeName(std::vector<RECT> *p)
{
	return "std::vector<RECT>";
}


#endif