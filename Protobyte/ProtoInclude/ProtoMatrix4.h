/*!  \brief  ProtoMatrix4.h: 4D Homogeneous Matrix implementation
 Guaranteed to not be terribly fast or efficient!
 Default order : Column Major
 Use transpose to convert to Row Major Order
 ProtoMatrix4.h
 Protobyte Library v02
 
 Created by Ira on 12/14/13.
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


#ifndef PROTO_MATRIX4_H
#define	PROTO_MATRIX4_H

#include "ProtoVector4.h"
#include <cassert>


namespace ijg {
    
    // forward declaration for non-member ops
    template <class T> class ProtoMatrix4;
    
    /*****************************************************/
    /*            Non-Member Ops & Functions             */
    /*****************************************************/
    //M4*V4
    //returns V3
    template <typename T>
    ProtoVector3<T> operator*(const ProtoMatrix4<T>& lhs, const ProtoVector4<T>& rhs);
    
    //V4*M4 (convenience funcion, still default column major order)
    //returns V3
    template <typename T>
    ProtoVector3<T> operator*(const ProtoVector4<T>& lhs, const ProtoMatrix4<T>& rhs);
    
    //M4*M4
    //returns M4
    template <typename T>
    ProtoMatrix4<T> operator*(const ProtoMatrix4<T>& lhs, const ProtoMatrix4<T>& rhs);
    
    //M4*Sclr
    //returns M4
    template <typename T>
    ProtoMatrix4<T> operator*(const ProtoMatrix4<T>& lhs, T s);
    
    //Sclr*M4
    //returns M4
    template <typename T>
    ProtoMatrix4<T> operator*(T s, const ProtoMatrix4<T>& rhs);
    
    //M4+M4
    //returns M4
    template <typename T>
    ProtoMatrix4<T> operator+(const ProtoMatrix4<T>& lhs, const ProtoMatrix4<T>& rhs);
    
    //M4-M4
    //returns M4
    template <typename T>
    ProtoMatrix4<T> operator-(const ProtoMatrix4<T>& lhs, const ProtoMatrix4<T>& rhs);
    
    //M4+Sclr
    //returns M4
    template <typename T>
    ProtoMatrix4<T> operator+(const ProtoMatrix4<T>& lhs, T s);
    
    //Sclr+M4
    //returns M4
    template <typename T>
    ProtoMatrix4<T> operator+(T s, const ProtoMatrix4<T>& rhs);
    
    //M4-Sclr
    //returns M4
    template <typename T>
    ProtoMatrix4<T> operator-(const ProtoMatrix4<T>& lhs, T s);
    
    //Sclr-M4
    //returns M4
    template <typename T>
    ProtoMatrix4<T> operator-(T s, const ProtoMatrix4<T>& rhs);
    /**********************/
    /* END non-member ops */
    /**********************/
    
    
    /*************************************************/
    /*                Class Declaration              */
    /*************************************************/
    template <class T>
    class ProtoMatrix4 {
        
    public:
        
        template <class U>
        friend std::ostream& operator<< (std::ostream& out, const ProtoMatrix4<U>& mat);
        
        enum MajorOrder {
            ROW_MAJOR,
            COLUMN_MAJOR
        };

        
        // cstrs
        // array vals should be packed: xyzwxyzw... for M*V
        // transpose if you need xxxxyyyy... for V*M.
        ProtoMatrix4<T>();
        ProtoMatrix4<T>(T m0, T m1, T m2, T m3, T m4, T m5, T m6, T m7, T m8, T m9, T m10, T m11, T m12, T m13, T m14, T m15, MajorOrder order=COLUMN_MAJOR);
        ProtoMatrix4<T>(T data[16], MajorOrder order=COLUMN_MAJOR);
        ProtoMatrix4<T>(T data[9], const ProtoVector4<T>& translation, MajorOrder order=COLUMN_MAJOR);
        ProtoMatrix4<T>(const ProtoMatrix3<T>&, const ProtoVector4<T>& translation, MajorOrder order=COLUMN_MAJOR);
        ProtoMatrix4<T>(const ProtoVector4<T>& row0, const ProtoVector4<T>& row1, const ProtoVector4<T>& row2, const ProtoVector4<T>& row3, MajorOrder order=COLUMN_MAJOR);
        ProtoMatrix4<T>(const ProtoVector4<T> rows[4], MajorOrder order=COLUMN_MAJOR);
        
        // copy cstr | assignment op
        ProtoMatrix4(const ProtoMatrix4<T>& mat);
        ProtoMatrix4<T>& operator=(const ProtoMatrix4<T>& mat);
        
        void identity();
        void transpose();
        T determinent() const;
        ProtoVector4<T> getRow(int index) const;
        ProtoVector4<T> getColumn(int index) const;
        void setRow(int index, const ProtoVector4<T>& row);
        void setColumn(int index, const ProtoVector4<T>& column);
        
        
        /*************************************************/
        /*            Member Ops & Functions             */
        /*************************************************/
        ProtoMatrix4<T>& operator*=(const ProtoMatrix4<T>& m4);
        ProtoMatrix4<T>& operator*=(T s);
        ProtoMatrix4<T>& operator/=(T s);
        ProtoMatrix4<T>& operator+=(const ProtoMatrix4<T>& m4);
        ProtoMatrix4<T>& operator-=(const ProtoMatrix4<T>& m4);
        
        T& operator[](unsigned index);
        const T& operator[](unsigned index) const;
        T& operator() ( int r, int c ) const;
        
        
    private:
        float data[16];
        MajorOrder order;
        
    };
    
    /**************************************/
    /*       END Class Declaration        */
    /**************************************/
    
    template <class T>
    inline std::ostream& operator<< (std::ostream& out, const ProtoMatrix4<T>& mat){
        out << std::setprecision( 4 ) <<
         std::fixed << std::setw(4) <<  "| " << mat.data[0] << "  " << mat.data[1] << "  " << mat.data[2] << "  " << mat.data[3] <<" | \n" <<
         std::fixed << std::setw(4) <<  "| " << mat.data[4] << "  " << mat.data[5] << "  " << mat.data[6] << "  " << mat.data[7] <<" | \n" <<
         std::fixed << std::setw(4) <<  "| " << mat.data[8] << "  " << mat.data[9] << "  " << mat.data[10] << "  " << mat.data[11] <<" | \n" <<
         std::fixed << std::setw(4) <<  "| " << mat.data[12] << "  " << mat.data[13] << "  " << mat.data[14] << "  " << mat.data[15] <<" | \n";
        return out;
    }

    
     /*************************************************/
    /*                  Constructors                  */
    /**************************************************/
    
    template <class T>
    inline ProtoMatrix4<T>::ProtoMatrix4() {
        // set default to identity
        identity();
    }
    
    template <class T>
    inline ProtoMatrix4<T>::ProtoMatrix4(T data[16], MajorOrder order):
    order(order){
        // eventually transpose data[16] if packed for row major (pre-multiplication)
        for(int i=0; i<16; ++i){
            this->data[i] = data[i]; // can I do this using default asignment op this.data = data without copying pointer or overloading =?
        }
    }
    
    template <class T>
    inline ProtoMatrix4<T>::ProtoMatrix4(T data[9], const ProtoVector4<T>& translation, MajorOrder order):
    order(order){
        // eventually transpose data[9] if packed for row major (pre-multiplication)
        // row 1
        this->data[0] = data[0];
        this->data[1] = data[1];
        this->data[2] = data[2];
        this->data[3] = translation.x;
        // row 2
        this->data[4] = data[3];
        this->data[5] = data[4];
        this->data[6] = data[5];
        this->data[7] = translation.y;
        // row 3
        this->data[8] = data[6];
        this->data[9] = data[7];
        this->data[10] = data[8];
        this->data[11] = translation.z;
        // row 4
        this->data[12] = 0;
        this->data[13] = 0;
        this->data[14] = 0;
        this->data[15] = translation.w;
    }
    
    template <class T>
    inline ProtoMatrix4<T>::ProtoMatrix4(const ProtoMatrix3<T>& mat3, const ProtoVector4<T>& translation, MajorOrder order):
    order(order) {
        // eventually transpose mat3 if packed for row major (pre-multiplication)
        // row 1
        data[0] = mat3[0];
        data[1] = mat3[1];
        data[2] = mat3[2];
        data[3] = translation.x;
        // row 2
        data[4] = mat3[3];
        data[5] = mat3[4];
        data[6] = mat3[5];
        data[7] = translation.y;
        // row 3
        data[8] = mat3[6];
        data[9] = mat3[7];
        data[10] = mat3[8];
        data[11] = translation.z;
        // row 4
        data[12] = 0;
        data[13] = 0;
        data[14] = 0;
        data[15] = translation.w;
    }
    
    template <class T>
    inline ProtoMatrix4<T>::ProtoMatrix4(const ProtoVector4<T>& row0, const ProtoVector4<T>& row1, const ProtoVector4<T>& row2, const ProtoVector4<T>& row3, MajorOrder order):
    order(order) {
        setRow(0, row0);
        setRow(1, row1);
        setRow(2, row2);
        setRow(3, row3);
    }
    
    template <class T>
    inline ProtoMatrix4<T>::ProtoMatrix4(const ProtoVector4<T> rows[4], MajorOrder order):
    order(order) {
        setRow(0, rows[0]);
        setRow(1, rows[1]);
        setRow(2, rows[2]);
        setRow(3, rows[3]);
    }
    
    template <class T>
    inline ProtoMatrix4<T>::ProtoMatrix4(T m0, T m1, T m2, T m3, T m4, T m5, T m6, T m7, T m8, T m9, T m10, T m11, T m12, T m13, T m14, T m15, MajorOrder order):
    order(order) {
        data[0]=m0;  data[1]=m1;  data[2]=m2;  data[3]=m3;
        data[4]=m4;  data[5]=m5;  data[6]=m6;  data[7]=m7;
        data[8]=m8;  data[9]=m9;  data[10]=m10;  data[11]=m11;
        data[12]=m12;  data[13]=m13;  data[14]=m14;  data[15]=m15;
    }
    
    // copy cstr
    template <class T>
    inline ProtoMatrix4<T>::ProtoMatrix4(const ProtoMatrix4<T>& mat){
        for(int i=0; i<16; ++i){
            data[i] = mat.data[i];
        }
        order = mat.order;
    }
    
    // assignment op
    template <class T>
    inline ProtoMatrix4<T>& ProtoMatrix4<T>::operator=(const ProtoMatrix4<T>& mat){
        if (this != &mat){
            for(int i=0; i<16; ++i){
                data[i] = mat.data[i];
            }
            order = mat.order;
        }
        return *this;
    }
    
    /**************************************/
    /*           END Constructors         */
    /**************************************/
    
    
    
    /*****************************************************/
    /*                  Member Functions                 */
    /*****************************************************/
    
    template <class T>
    inline void ProtoMatrix4<T>::transpose() {
        T temp[16];
        for (int i=0; i<4; ++i) {
            for (int j=0, k=0; j<4; ++j, k+=4) {
                temp[i*4+j] = data[i+k];
            }
        }
        for(int i=0; i<16; ++i){
            data[i] = temp[i];
        }
    }
    
    // Laplace expansion method
    // from http://www.mathsisfun.com/algebra/matrix-determinant.html
    template <class T>
    inline T ProtoMatrix4<T>::determinent() const {
        
        // get inner 3x3 determinents
        ProtoMatrix3<T> mat3A(data[5], data[6], data[7], data[9], data[10], data[11], data[13], data[14], data[15]);
        ProtoMatrix3<T> mat3B(data[4], data[6], data[7], data[8], data[10], data[11], data[12], data[14], data[15]);
        ProtoMatrix3<T> mat3C(data[4], data[5], data[7], data[8], data[9], data[11], data[12], data[13], data[15]);
        ProtoMatrix3<T> mat3D(data[4], data[5], data[6], data[8], data[9], data[10], data[12], data[13], data[14]);
        
           T d = data[0] * mat3A.determinent() -
                 data[1] * mat3B.determinent() +
                 data[2] * mat3C.determinent() -
                 data[3] * mat3D.determinent();
        return d;
    }
    
    template <class T>
    inline void ProtoMatrix4<T>::identity() {
        // set 1's along diagonal
        for (int i =0; i <16; i++) {
            if (i % 5 == 0) {
                data[i] = 1;
            } else {
                 data[i] = 0;
            }
        }
    }
    
    template <class T>
    inline void ProtoMatrix4<T>::setRow(int index, const ProtoVector4<T>& row) {
        data[index*4] = row.x;
        data[1+index*4] = row.y;
        data[2+index*4] = row.z;
        data[3+index*4] = row.w;
    }
    
    template <class T>
    inline void ProtoMatrix4<T>::setColumn(int index, const ProtoVector4<T>& column) {
        data[index] = column.x;
        data[4+index] = column.y;
        data[8+index] = column.z;
        data[12+index] = column.w;
    }
    
    template <class T>
    inline ProtoVector4<T> ProtoMatrix4<T>::getRow(int index) const {
        return ProtoVector4<T>(data[index*4], data[index*4+1], data[index*4+2], data[index*4+3]);
    }
    
    template <class T>
    inline ProtoVector4<T> ProtoMatrix4<T>::getColumn(int index) const {
        return ProtoVector4<T>(data[index+0], data[index+4], data[index+8], data[index+12]);
    }
    

    
    /**************************************/
    /*       END Member Functions         */
    /**************************************/
    
    
    
    /*****************************************************/
    /*              Member Ops Implementation            */
    /*****************************************************/
    
    template <typename T>
    inline ProtoMatrix4<T>& ProtoMatrix4<T>::operator*=(const ProtoMatrix4<T>& m4){
        
        T temp[16];
        temp[0] = *this[0]*m4[0] + *this[1]*m4[4] + *this[2]*m4[8] + *this[3]*m4[12];
        temp[1] = *this[0]*m4[1] + *this[1]*m4[5] + *this[2]*m4[9] + *this[3]*m4[13];
        temp[2] = *this[0]*m4[2] + *this[1]*m4[6] + *this[2]*m4[10] + *this[3]*m4[14];
        temp[3] = *this[0]*m4[3] + *this[1]*m4[7] + *this[2]*m4[11] + *this[3]*m4[15];
        
        temp[4] = *this[4]*m4[0] + *this[5]*m4[4] + *this[6]*m4[8] + *this[7]*m4[12];
        temp[5] = *this[4]*m4[1] + *this[5]*m4[5] + *this[6]*m4[9] + *this[7]*m4[13];
        temp[6] = *this[4]*m4[2] + *this[5]*m4[6] + *this[6]*m4[10] + *this[7]*m4[14];
        temp[7] = *this[4]*m4[3] + *this[5]*m4[7] + *this[6]*m4[11] + *this[7]*m4[15];
        
        temp[8] = *this[8]*m4[0] + *this[9]*m4[4] + *this[10]*m4[8] + *this[11]*m4[12];
        temp[9] = *this[8]*m4[1] + *this[9]*m4[5] + *this[10]*m4[9] + *this[11]*m4[13];
        temp[10] = *this[8]*m4[2] + *this[9]*m4[6] + *this[10]*m4[10] + *this[11]*m4[14];
        temp[11] = *this[8]*m4[3] + *this[9]*m4[7] + *this[10]*m4[11] + *this[11]*m4[15];
        
        temp[12] = *this[12]*m4[0] + *this[13]*m4[4] + *this[14]*m4[8] + *this[15]*m4[12];
        temp[13] = *this[12]*m4[1] + *this[13]*m4[5] + *this[14]*m4[9] + *this[15]*m4[13];
        temp[14] = *this[12]*m4[2] + *this[13]*m4[6] + *this[14]*m4[10] + *this[15]*m4[14];
        temp[15] = *this[12]*m4[3] + *this[13]*m4[7] + *this[14]*m4[11] + *this[15]*m4[15];
        
        for(int i=0; i<16; ++i){
            data[i] = temp[i];
        }
        return *this;
    }
    
    template <typename T>
    inline ProtoMatrix4<T>& ProtoMatrix4<T>::operator*=(T s){
        for(int i=0; i<16; ++i){
            data[i] *= s;
        }
        return *this;
    }
    

    template <typename T>
    inline ProtoMatrix4<T>& ProtoMatrix4<T>::operator/=(T s){
        for(int i=0; i<16; ++i){
            data[i] /= s;
        }
        return *this;
    }

    template <typename T>
    inline ProtoMatrix4<T>& ProtoMatrix4<T>::operator+=(const ProtoMatrix4<T>& m4){
        for(int i=0; i<16; ++i){
           data[i] += m4[i];
        }
        return *this;
    }

    template <typename T>
    inline ProtoMatrix4<T>& ProtoMatrix4<T>::operator-=(const ProtoMatrix4<T>& m4){
        for(int i=0; i<16; ++i){
            data[i] -= m4[i];
        }
        return *this;
    }

    template <typename T>
    inline T& ProtoMatrix4<T>::operator[](unsigned index){
        assert( index >= 0 && index <= 15 );
        return data[index];
    }
    
    // const template <typename T>
    template <typename T>
    inline const T& ProtoMatrix4<T>::operator[](unsigned index) const{
        assert( index >= 0 && index <= 15 );
        return data[index];
    }
    
    template <typename T>
    inline T&	ProtoMatrix4<T>::operator() ( int r, int c ) const{
        int index = r*4+c;
        assert( index >= 0 && index <= 15 );
        return *this[index];
    }
    
 
    /**************************************/
    /*          END Member OPs           */
    /**************************************/
    
    
    /*****************************************************/
    /*         Non-Member Ops Implementation        */
    /*****************************************************/
    
    // M4*V4
    // returns V3
    template <typename T>
    inline ProtoVector3<T> operator*(const ProtoMatrix4<T>& lhs, const ProtoVector4<T>& rhs){
//        T x = lhs[0]*rhs.x + lhs[1]*rhs.y + lhs[2]*rhs.z + lhs[3];
//        T y = lhs[4]*rhs.x + lhs[5]*rhs.y + lhs[6]*rhs.z + lhs[7];
//        T z = lhs[8]*rhs.x + lhs[9]*rhs.y + lhs[10]*rhs.z + lhs[11];
        
        T x = lhs[0]*rhs.x + lhs[4]*rhs.y + lhs[8]*rhs.z + lhs[3];
        T y = lhs[1]*rhs.x + lhs[5]*rhs.y + lhs[9]*rhs.z + lhs[7];
        T z = lhs[2]*rhs.x + lhs[6]*rhs.y + lhs[10]*rhs.z + lhs[11];

        return ProtoVector3<T>(x, y, z);
    }
    
    // V4*M4
    // returns V3
    template <typename T>
    inline ProtoVector3<T> operator*(const ProtoVector4<T>& lhs, const ProtoMatrix4<T>& rhs){
        return rhs*lhs;
    }
    
    // M4*M4
    // return M4
    template <typename T>
    inline ProtoMatrix4<T> operator*(const ProtoMatrix4<T>& lhs, const ProtoMatrix4<T>& rhs) {
        ProtoMatrix4<T> tempMat(T arr[16]);
        for(int i=0; i<4; ++i){
            for(int j=0; j<4; ++j){
                tempMat.arr[i*4+j] = lhs[4*i]*rhs[j] + lhs[4*i+1]*rhs[j+4] + lhs[4*i+2]*rhs[j+8] + lhs[4*i+3]*rhs[j+12];
            }
        }
        return tempMat;
    }
    
    // M4*Sclr
    // return M4
    template <typename T>
    inline ProtoMatrix4<T> operator*(const ProtoMatrix4<T>& lhs, T s) {
        ProtoMatrix4<T> tempMat(T arr[16]);
        for(int i=0; i<16; ++i){
            tempMat.arr[i] = lhs[i]*s;
        }
        return tempMat;
    }
    
    // Sclr*M4
    // return M4
    template <typename T>
    inline ProtoMatrix4<T> operator*(T s, const ProtoMatrix4<T>& rhs) {
        return rhs*s;
    }
    
    // M4+M4
    // return M4
    template <typename T>
    inline ProtoMatrix4<T> operator+(const ProtoMatrix4<T>& lhs, const ProtoMatrix4<T>& rhs){
        ProtoMatrix4<T> tempMat(T arr[16]);
        for(int i=0; i<16; ++i){
            tempMat.arr[i] = lhs[i]+rhs[i];
        }
        return tempMat;
    }
    
    // M4-M4
    // return M4
    template <typename T>
    inline ProtoMatrix4<T> operator-(const ProtoMatrix4<T>& lhs, const ProtoMatrix4<T>& rhs){
        ProtoMatrix4<T> tempMat(T arr[16]);
        for(int i=0; i<16; ++i){
            tempMat.arr[i] = lhs[i]-rhs[i];
        }
        return tempMat;
    }
    
    // M4+Sclr
    // return M4
    template <typename T>
    inline ProtoMatrix4<T> operator+(const ProtoMatrix4<T>& lhs, T s){
        ProtoMatrix4<T> tempMat(T arr[16]);
        for(int i=0; i<16; ++i){
            tempMat.arr[i] = lhs[i]+s;
        }
        return tempMat;
    }
    
    // Sclr+M4
    // return M4
    template <typename T>
    inline ProtoMatrix4<T> operator+(T s, const ProtoMatrix4<T>& rhs){
        return rhs+s;
    }
    
    // M4-Sclr
    // return M4
    template <typename T>
    inline ProtoMatrix4<T> operator-(const ProtoMatrix4<T>& lhs, T s){
        return lhs+(-s);
    }
    
    // Sclr-M4
    // return M4
    template <typename T>
    inline ProtoMatrix4<T> operator-(T s, const ProtoMatrix4<T>& rhs){
        return rhs+(-s);
    }
    
    /**********************/
    /*         END        */
    /**********************/
    
    
    
    
#define ProtoMatrix4f ProtoMatrix4<float>
#define ProtoMatrix4d ProtoMatrix4<double>
}

#endif	// PROTO_MATRIX4_H

