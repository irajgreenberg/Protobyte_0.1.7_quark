/*!  \brief  ProtoDimension.h: 2D dimension class with w,h fields
 ProtoDimension2.h
 Protobyte Library v02
 
 Created by Ira on 11/7/13.
 Copyright (c) 2013 Ira Greenberg. All rights reserved.
 
 Library Usage:
 This work is licensed under the Creative Commons
 Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 To view a copy of this license, visit
 http://creativecommons.org/licenses/by-nc-sa/3.0/
 or send a letter to Creative Commons,
 444 Castro Street, Suite 900,
 Mountain View, California, 94041, USA.
 
 This notice must be retained any source distribution.
 
 \ingroup common
 This class is part of the group common (update)
 \sa NO LINK
 */

#ifndef PROTO_DIMENSION2
#define PROTO_DIMENSION2

#include <iostream>

namespace ijg {
    
    /*****************************************************/
    /*            Non-Member Overloaded Ops              */
    /*****************************************************/
    template <class T> class ProtoDimension2; // forward declaration
    
    template <class T>
    ProtoDimension2<T> operator+(const ProtoDimension2<T>& lhs, const ProtoDimension2<T>& rhs) {
        return ProtoDimension2<T > (lhs.w + rhs.w, lhs.h + rhs.h);
    }
    
    template <class T>
    ProtoDimension2<T> operator-(const ProtoDimension2<T>& lhs, const ProtoDimension2<T>& rhs) {
        return ProtoDimension2<T > (lhs.w - rhs.w, lhs.h - rhs.h);
    }
    
    template <class T>
    ProtoDimension2<T> operator*(const ProtoDimension2<T>& lhs, const ProtoDimension2<T>& rhs) {
        return ProtoDimension2<T > (lhs.w * rhs.w, lhs.h * rhs.h);
    }
    
    template <class T>
    ProtoDimension2<T> operator/(const ProtoDimension2<T>& lhs, const ProtoDimension2<T>& rhs) {
        return ProtoDimension2<T > (lhs.w / rhs.w, lhs.h / rhs.h);
    }
    
    
    // templated Dimension class
    
    template <class T>
    class ProtoDimension2 {
    private:
        //T w, h, ;
        
    public:
        
        T w, h;
        
        template <class U>
        friend std::ostream& operator<<(std::ostream& output, const ProtoDimension2<U>& dim);
        
        ProtoDimension2();
        ProtoDimension2(T w, T h);
		ProtoDimension2(T sz);
        
        void setW(T w);
        void setH(T h);
        T getW(T w) const;
        T getH(T h) const;
        
        ProtoDimension2<T>& operator+=(const ProtoDimension2<T>& s);
        ProtoDimension2<T>& operator+=(double f);
        ProtoDimension2<T>& operator-=(const ProtoDimension2<T>& s);
        ProtoDimension2<T>& operator-=(double f);
        ProtoDimension2<T>& operator*=(const ProtoDimension2<T>& s);
        ProtoDimension2<T>& operator*=(double f);
        ProtoDimension2<T>& operator/=(const ProtoDimension2<T>& s);
        ProtoDimension2<T>& operator/=(double f);
        ProtoDimension2<T>& operator++();
        ProtoDimension2<T>& operator++(int);
        ProtoDimension2<T>& operator--();
        ProtoDimension2<T>& operator--(int);
        
        double operator[](int index);
        bool operator==(const ProtoDimension2<T>& v) const;
        
    };
    
    // constructors
    
    template <class T>
    inline ProtoDimension2<T>::ProtoDimension2() :
    w(1), h(1) {
    }
    
    template <class T>
    inline ProtoDimension2<T>::ProtoDimension2(T w, T h) :
    w(w), h(h) {
    }

	template <class T>
	inline ProtoDimension2<T>::ProtoDimension2(T sz) :
		w(sz), h(sz) {
	}
    
    // setters/getters
    
    template <class T>
    inline T ProtoDimension2<T>::getW(T w) const {
        return w;
    }
    
    template <class T>
    inline T ProtoDimension2<T>::getH(T h) const {
        return h;
    }
    
    template <class T>
    inline void ProtoDimension2<T>::setW(T w) {
        this->w = w;
    }
    
    template <class T>
    inline void ProtoDimension2<T>::setH(T h) {
        this->h = h;
    }
    
    // overloaded ops
    
    template <class T>
    inline ProtoDimension2<T>& ProtoDimension2<T>::operator+=(const ProtoDimension2<T>& s) {
        w += s.w;
        h += s.h;
        return *this;
    }
    
    template <class T>
    inline ProtoDimension2<T>& ProtoDimension2<T>::operator+=(double f) {
        w += f;
        h += f;
        return *this;
    }
    
    template <class T>
    inline ProtoDimension2<T>& ProtoDimension2<T>::operator-=(const ProtoDimension2<T>& s) {
        w -= s.w;
        h -= s.h;
        return *this;
    }
    
    template <class T>
    inline ProtoDimension2<T>& ProtoDimension2<T>::operator-=(double f) {
        w -= f;
        h -= f;
        return *this;
    }
    
    template <class T>
    inline ProtoDimension2<T>& ProtoDimension2<T>::operator*=(const ProtoDimension2<T>& s) {
        w *= s.w;
        h *= s.h;
        return *this;
    }
    
    template <class T>
    inline ProtoDimension2<T>& ProtoDimension2<T>::operator*=(double f) {
        w *= f;
        h *= f;
        return *this;
    }
    
    template <class T>
    inline ProtoDimension2<T>& ProtoDimension2<T>::operator/=(const ProtoDimension2<T>& s) {
        w /= s.w;
        h /= s.h;
        return *this;
    }
    
    template <class T>
    inline ProtoDimension2<T>& ProtoDimension2<T>::operator/=(double f) {
        w /= f;
        h /= f;
        return *this;
    }
    
    template <class T>
    ProtoDimension2<T>& ProtoDimension2<T>::operator++() {
        ++w;
        ++h;
        return *this;
    }
    
    template <class T>
    inline ProtoDimension2<T>& ProtoDimension2<T>::operator++(int) {
        w++;
        h++;
        return *this;
    }
    
    template <class T>
    inline ProtoDimension2<T>& ProtoDimension2<T>::operator--() {
        --w;
        --h;
        return *this;
    }
    
    template <class T>
    inline ProtoDimension2<T>& ProtoDimension2<T>::operator--(int) {
        w--;
        h--;
        return *this;
    }
    
    template <class T>
    std::ostream& operator<<(std::ostream& output, const ProtoDimension2<T>& dim) {
        output << "(" << dim.w << ", " << dim.h << ")";
        return output;
    }
    
    // most common usages
#define ProtoDimension2f ProtoDimension2<float>
#define ProtoDimension2d ProtoDimension2<double>
#define ProtoDimension2i ProtoDimension2<int>
    
#define Dim2f ProtoDimension2<float>
#define Dim2d ProtoDimension2<double>
#define Dim2i ProtoDimension2<int>
    
}
#endif /* defined(PROTO_DIMENSION2) */
