#include "stdafx.h"
#include "RectArray.h"
/*
inline std::string typeName(RectArray *p)
{
	return "RECT";
}
*/

void load_this(opros::archive::iarchive &ar, RectArray &t)

{
           ar >> t;
}

 

void save_this(opros::archive::oarchive &ar, RectArray &t)

{
           ar << t;
}