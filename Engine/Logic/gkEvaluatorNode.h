/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2010 Nestor Silveira.

    Contributor(s): none yet.
-------------------------------------------------------------------------------
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#ifndef _gkEvaluatorNode_h_
#define _gkEvaluatorNode_h_

#include "gkLogicNode.h"

template<gkLogicSocket::SocketType type>
class gkEqualNode  : public gkLogicNode
{
public:

	enum
	{
		A,
		B,
		TRUE_VALUE,
		FALSE_VALUE,
		MAX_SOCKETS
	};

    gkEqualNode(gkLogicTree *parent, size_t id)
		: gkLogicNode(parent, id)
	{
		ADD_ISOCK(*getA(), this, type);
		ADD_ISOCK(*getB(), this, type);
		ADD_OSOCK(*getTrue(), this, gkLogicSocket::ST_BOOL);
		ADD_OSOCK(*getFalse(), this, gkLogicSocket::ST_BOOL);
	}

	~gkEqualNode() {}

	bool evaluate(gkScalar tick)
	{
		bool isTrue = getA()->getValueString() == getB()->getValueString();

		getTrue()->setValue(isTrue);
		
		getFalse()->setValue(!isTrue);

		return false;
	}

    GK_INLINE gkLogicSocket* getA() {return &m_sockets[A];}
    GK_INLINE gkLogicSocket* getB() {return &m_sockets[B];}
	GK_INLINE gkLogicSocket* getTrue() {return &m_sockets[TRUE_VALUE];}
	GK_INLINE gkLogicSocket* getFalse() {return &m_sockets[FALSE_VALUE];}

private:
	gkLogicSocket m_sockets[MAX_SOCKETS];
};

typedef gkEqualNode<gkLogicSocket::ST_STRING> gkStringEqualNode;
typedef gkEqualNode<gkLogicSocket::ST_INT> gkIntEqualNode;

#endif//_gkEvaluatorNode_h_