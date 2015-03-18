
/*
 *  Generated sources by OPRoS Component Generator (OCG V2.0 [Symbol])
 *  
 */
#ifndef _tagRECT_DATATYPE_H
#define _tagRECT_DATATYPE_H
#include <archive/opros_archive.h>


#include "Long.h"
       
#include "Long.h"
       
#include "Long.h"
       
#include "Long.h"
       

/*
** 
** 
*/
class tagRECT
{
protected:
	friend class opros::archive::access;
	Long m_left;
	Long m_top;
	Long m_right;
	Long m_bottom;
	
public:
	void save(opros::archive::oarchive &ar, const unsigned int) 
	{
		ar << m_left;
		ar << m_top;
		ar << m_right;
		ar << m_bottom;
		

	}

	void load(opros::archive::iarchive &ar, const unsigned int)
	{
		ar >> m_left;
		ar >> m_top;
		ar >> m_right;
		ar >> m_bottom;
		

	}
public:
	tagRECT()
	{
	}

	tagRECT(const Long& in_left,const Long& in_top,const Long& in_right,const Long& in_bottom)
	{
		m_left = in_left;
		m_top = in_top;
		m_right = in_right;
		m_bottom = in_bottom;
		
	}

	Long& getLeft()
	{
		return m_left;
	}

	void setLeft(const Long& in_left)
	{
		m_left = in_left;
	}

	Long& getTop()
	{
		return m_top;
	}

	void setTop(const Long& in_top)
	{
		m_top = in_top;
	}

	Long& getRight()
	{
		return m_right;
	}

	void setRight(const Long& in_right)
	{
		m_right = in_right;
	}

	Long& getBottom()
	{
		return m_bottom;
	}

	void setBottom(const Long& in_bottom)
	{
		m_bottom = in_bottom;
	}

	

};

inline std::string typeName(tagRECT *p)
{
	return "tagRECT";
}
#endif
