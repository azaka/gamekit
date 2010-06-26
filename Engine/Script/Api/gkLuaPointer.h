/*
-------------------------------------------------------------------------------
--                                                                           --
--  This file is part of GameKit.                                            --
--  http://gamekit.googlecode.com/                                           --
--                                                                           --
--                                                                           --
--  Released under the zlib license.                                         --
--  http://www.gzip.org/zlib/zlib_license.html                               --
--                                                                           --
--                                                                           --
-------------------------------------------------------------------------------
*/
#ifndef _gkLuaPointer_h_
#define _gkLuaPointer_h_



// Referenced counted ptr for freeing script objects with lua's gc
// adapted from gkPtrRef.h

template<class T>
class Pointer
{

public:

#ifndef SWIG

    explicit Pointer(T *p = 0)
        :   m_obj(p), m_ref(0) 
    {
        addRef();
    }

    ~Pointer()
    {
        release();
    }

    Pointer(const Pointer &obj)
        :   m_obj(obj.m_obj), m_ref(0)
    {
        addRef();
    }

    Pointer &operator = (const Pointer &obj)
    {
        if(this != &obj)
        {
            obj.addRef();
            release();
            m_obj = obj.m_obj;
            m_ref = obj.m_ref;
        }
        return *this;
    }

#endif


    bool isNull(void) const                         { return m_obj == 0; }
    bool operator ==(const Pointer &rhs) const      { return m_obj == rhs.m_obj; }
    bool operator !=(const Pointer &rhs) const      { return m_obj != rhs.m_obj; }


    T *operator->() const
    {
        GK_ASSERT(m_obj);
        return m_obj;
    }


private:

    void addRef(void) const
    {
        if (m_obj)
            ++m_ref;
    }

    void release(void) const
    {
        if(m_obj)
        {
            if (--m_ref == 0)
            {
                delete m_obj;
                m_obj = 0;
            }
        }
    }

    mutable T   *m_obj;
    mutable int  m_ref;
};

#endif//_gkLuaPointer_h_