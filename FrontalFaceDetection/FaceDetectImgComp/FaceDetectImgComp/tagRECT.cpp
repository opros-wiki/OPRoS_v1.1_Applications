#include "stdafx.h"
#include "tagRECT.h"
/*
inline std::string typeName(RECT *p)
{
	return "RECT";
}
*/

void load_this(opros::archive::iarchive &ar, RECT &t)
{
           ar >> t.left;
		   ar >> t.top;
           ar >> t.right;
		   ar >> t.bottom;
}

 

void save_this(opros::archive::oarchive &ar, RECT &t)
{
           ar << t.left;
		   ar << t.top;
           ar << t.right;
		   ar << t.bottom;
}

void load_this(opros::archive::iarchive &ar, std::vector<RECT> &t)
{
           ar >> t;
}

 

void save_this(opros::archive::oarchive &ar, std::vector<RECT> &t)
{
           ar << t;
}