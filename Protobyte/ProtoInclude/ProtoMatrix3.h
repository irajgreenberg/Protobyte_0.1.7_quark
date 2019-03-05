/*!  \brief  ProtoMatrix3.h: 3D Matrix implementation
 Guaranteed to not be terribly fast or efficient!
 Default order : Column Major
 Use transpose to convert to Row Major Order
 ProtoMatrix3.h
 Protobyte Library v02
 
 Created by Ira on 12/16/13.
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


#ifndef PROTO_MATRIX3_H
#define	PROTO_MATRIX3_H

#include "ProtoVector3.h"
#include <iomanip>
#include <cassert>


namespace ijg {
    
    
    // forward declaration for non-member ops
    template <class T> class ProtoMatrix3;
    
    typedef ProtoMatrix3<float> Mat3f;
    typedef ProtoMatrix3<float> Mat3; // most common form
    
    /*****************************************************/
    /*            Non-Member Ops & Functions             */
    /*****************************************************/
    //M3*V3
    //returns V3
    template <typename T>
    ProtoVector3<T> operator*(const ProtoMatrix3<T>& lhs, const ProtoVector3<T>& rhs);
    
    //V3*M3 (convenience function, still default column major order)
    //returns V3
    template <typename T>
    ProtoVector3<T> operator*(const ProtoVector3<T>& lhs, const ProtoMatrix3<T>& rhs);
    
    //M3*M3
    //returns M3
    template <typename T>
    ProtoMatrix3<T> operator*(const ProtoMatrix3<T>& lhs, const ProtoMatrix3<T>& rhs);
    
    //M3*Sclr
    //returns M3
    template <typename T>
    ProtoMatrix3<T> operator*(const ProtoMatrix3<T>& lhs, T s);
    
    //Sclr*M3
    //returns M3
    template <typename T>
    ProtoMatrix3<T> operator*(T s, const ProtoMatrix3<T>& rhs);
    
    //M3+M3
    //returns M3
    template <typename T>
    ProtoMatrix3<T> operator+(const ProtoMatrix3<T>& lhs, const ProtoMatrix3<T>& rhs);
    
    //M3-M3
    //returns M3
    template <typename T>
    ProtoMatrix3<T> operator-(const ProtoMatrix3<T>& lhs, const ProtoMatrix3<T>& rhs);
    
    //M3+Sclr
    //returns M3
    template <typename T>
    ProtoMatrix3<T> operator+(const ProtoMatrix3<T>& lhs, T s);
    
    //Sclr+M3
    //returns M3
    template <typename T>
    ProtoMatrix3<T> operator+(T s, const ProtoMatrix3<T>& rhs);
    
    //M3-Sclr
    //returns M3
    template <typename T>
    ProtoMatrix3<T> operator-(const ProtoMatrix3<T>& lhs, T s);
    
    //Sclr-M3
    //returns M3
    template <typename T>
    ProtoMatrix3<T> operator-(T s, const ProtoMatrix3<T>& rhs);
    /**********************/
    /* END non-member ops */
    /**********************/
    
    
    /*************************************************/
    /*                Class Declaration              */
    /*************************************************/
    template <class T>
    class ProtoMatrix3 {
        
    public:
        template <class U>
        friend std::ostream& operator<< (std::ostream& out, const ProtoMatrix3<U>& mat);
        
        enum MajorOrder {
            ROW_MAJOR,
            COLUMN_MAJOR
        };
        
        // cstrs
        // array vals should be packed: xyzwxyzw... for M*V
        // transpose if you need xxxxyyyy... for V*M.
        ProtoMatrix3<T>();
        ProtoMatrix3<T>(T d0, T d1, T d2, T d3, T d4, T d5, T d6, T d7, T d8, MajorOrder order=COLUMN_MAJOR);
        ProtoMatrix3<T>(T data[9], MajorOrder order=COLUMN_MAJOR);
        ProtoMatrix3<T>(const ProtoVector3<T>& row0, const ProtoVector3<T>& row1, const ProtoVector3<T>& row2, MajorOrder order=COLUMN_MAJOR);
        ProtoMatrix3<T>(const ProtoVector3<T> rows[3], MajorOrder order=COLUMN_MAJOR);
       
        
        // copy cstr | assignment op
        ProtoMatrix3<T>(const ProtoMatrix3<T>& mat);
        ProtoMatrix3<T>& operator=(const ProtoMatrix3<T>& mat);
        
        // gen matrix functions
        void identity();
        void transpose();
        T determinent() const;
        ProtoVector3<T> getRow(int index) const;
        ProtoVector3<T> getColumn(int index) const;
        void setRow(int index, const ProtoVector3<T>& row);
        void setColumn(int index, const ProtoVector3<T>& column);
        
        // transfomations
        ProtoVector3<T> getRotate(float theta, const ProtoVector3<T>& axis, const ProtoVector3<T>& vec);
    
        
        /*************************************************/
        /*            Member Ops & Functions             */
        /*************************************************/
        ProtoMatrix3<T>& operator*=(const ProtoMatrix3<T>& m3);
        ProtoMatrix3<T>& operator*=(T s);
        ProtoMatrix3<T>& operator/=(T s);
        ProtoMatrix3<T>& operator+=(const ProtoMatrix3<T>& m3);
        ProtoMatrix3<T>& operator-=(const ProtoMatrix3<T>& m3);
        
        T& operator[](unsigned index);
        const T& operator[](unsigned index) const;
        T&	operator() ( int r, int c );
        
        
    private:
        float data[9];
        MajorOrder order;
        
    };
    
    /**************************************/
    /*       END Class Declaration        */
    /**************************************/
    
    
    template <class T>
    inline std::ostream& operator<< (std::ostream& out, const ProtoMatrix3<T>& mat){
    
        out << std::setprecision( 4 ) <<
                  std::fixed << std::setw(4) << "| " << mat.data[0] << "  " << mat.data[1] << "  " << mat.data[2] <<" | \n" <<
                  std::fixed << std::setw(4) << "| " << mat.data[3] << "  " << mat.data[4] << "  " << mat.data[5] <<" | \n" <<
                  std::fixed << std::setw(4) << "| " << mat.data[6] << "  " << mat.data[7] << "  " << mat.data[8] <<" | \n";
        return out;
    }
    
    
    /*************************************************/
    /*                  Constructors                  */
    /**************************************************/
    
    template <class T>
    inline ProtoMatrix3<T>::ProtoMatrix3() {
        // set default to identity
        identity();
    }
    
    template <class T>
    inline ProtoMatrix3<T>::ProtoMatrix3(T data[9], MajorOrder order):
    order(order){
        // eventually transpose data[16] if packed for row major (pre-multiplication)
        for(int i=0; i<9; ++i){
            this->data[i] = data[i]; // can I do this using default asignment op this.data = data without copying pointer or overloading =?
        }
    }
    
    template <class T>
    inline ProtoMatrix3<T>::ProtoMatrix3(const ProtoVector3<T>& row0, const ProtoVector3<T>& row1, const ProtoVector3<T>& row2, MajorOrder order):
    order(order) {
        setRow(0, row0);
        setRow(1, row1);
        setRow(2, row2);
    }
    
    template <class T>
    inline ProtoMatrix3<T>::ProtoMatrix3(const ProtoVector3<T> rows[3], MajorOrder order):
    order(order) {
        setRow(0, rows[0]);
        setRow(1, rows[1]);
        setRow(2, rows[2]);
    }
    
    template <class T>
    inline ProtoMatrix3<T>::ProtoMatrix3(T d0, T d1, T d2, T d3, T d4, T d5, T d6, T d7, T d8, MajorOrder order):
    order(order) {
        data[0]=d0;  data[1]=d1;  data[2]=d2;
        data[3]=d3;  data[4]=d4;  data[5]=d5;
        data[6]=d6;  data[7]=d7;  data[8]=d8;
    }
    
    // copy cstr
    template <class T>
    inline ProtoMatrix3<T>::ProtoMatrix3(const ProtoMatrix3<T>& mat){
        for(int i=0; i<9; ++i){
            data[i] = mat.data[i];
        }
        order = mat.order;
    }
    
    // assignment op
    template <class T>
    inline ProtoMatrix3<T>& ProtoMatrix3<T>::operator=(const ProtoMatrix3<T>& mat){
        if (this != &mat){
            for(int i=0; i<9; ++i){
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
    inline void ProtoMatrix3<T>::transpose() {
        T temp[9];
        for (int i=0; i<3; ++i) {
            for (int j=0, k=0; j<3; ++j, k+=3) {
                temp[i*3+j] = data[i+k];
            }
        }
        for(int i=0; i<9; ++i){
            data[i] = temp[i];
        }
    }
    
    // Laplace expansion method
    // from http://www.mathsisfun.com/algebra/matrix-determinant.html
    template <class T>
    inline T ProtoMatrix3<T>::determinent() const {
        T d = data[0]*(data[4]*data[8]-data[5]*data[7]) - data[1]*(data[3]*data[8]-data[5]*data[6]) + data[2]*(data[3]*data[7]-data[4]*data[6]);
        return d;
    }
    
    template <class T>
    inline void ProtoMatrix3<T>::identity() {
        // set 1's along diagonal
        for (int i =0; i <9; i++) {
            if (i % 4 == 0) {
                data[i] = 1;
            } else {
                data[i] = 0;
            }
        }
    }
   
    template <class T>
    inline void ProtoMatrix3<T>::setRow(int index, const ProtoVector3<T>& row) {
        data[index*3] = row.x;
        data[1+index*3] = row.y;
        data[2+index*3] = row.z;
    }
    
    template <class T>
    inline void ProtoMatrix3<T>::setColumn(int index, const ProtoVector3<T>& column) {
        data[index] = column.x;
        data[3+index] = column.y;
        data[6+index] = column.z;
    }
    
    template <class T>
    inline ProtoVector3<T> ProtoMatrix3<T>::getRow(int index) const {
        return ProtoVector3<T>(data[index*3+0], data[index*3+1], data[index*3+2]);
    }
    
    template <class T>
    inline ProtoVector3<T> ProtoMatrix3<T>::getColumn(int index) const {
        return ProtoVector3<T>(data[index+0], data[index+3], data[index+6]);
    }

    
    template <class T>
    inline ProtoVector3<T> ProtoMatrix3<T>::getRotate(float theta, const ProtoVector3<T>& axis, const ProtoVector3<T>& vec) {
        //std::cout << "vec in getRotate = " << vec << std::endl;
        float c = cos(theta);
        float s = sin(theta);
        // row 1
        data[0] = c + (axis.x * axis.x) * (1 - c);
        data[1] = axis.x * axis.y * (1 - c) - s * axis.z;
        data[2] = axis.z * axis.x * (1 - c) + s * axis.y;
        //row 2
        data[3] = axis.x * axis.y * (1 - c) + s * axis.z;
        data[4] = c + (axis.y * axis.y) * (1 - c);
        data[5] = axis.z * axis.y * (1 - c) - s * axis.x;
        //row 3
        data[6] = axis.x * axis.z * (1 - c) - s * axis.y;
        data[7] = axis.y * axis.z * (1 - c) + s * axis.x;
        data[8] = c + (axis.z * axis.z) * (1 - c);
        
        Vec3f temp;
        temp.x = vec.x * data[0] + vec.y * data[1] + vec.z * data[2];
        temp.y = vec.x * data[3] + vec.y * data[4] + vec.z * data[5];
        temp.z = vec.x * data[6] + vec.y * data[7] + vec.z * data[8];
        
        return temp;
    }

    
    /**************************************/
    /*       END Member Functions         */
    /**************************************/
    
    
    
    /*****************************************************/
    /*              Member Ops Implementation            */
    /*****************************************************/
    
    //FIX
    template <typename T>
    ProtoMatrix3<T>& ProtoMatrix3<T>::operator*=(const ProtoMatrix3<T>& m3){
        
        T temp[9];
        temp[0] = *this[0]*m3[0] + *this[1]*m3[3] + *this[2]*m3[6];
        temp[1] = *this[0]*m3[1] + *this[1]*m3[4] + *this[2]*m3[7];
        temp[2] = *this[0]*m3[2] + *this[1]*m3[5] + *this[2]*m3[8];
        
        temp[3] = *this[3]*m3[0] + *this[4]*m3[3] + *this[5]*m3[6];
        temp[4] = *this[3]*m3[1] + *this[4]*m3[4] + *this[5]*m3[7];
        temp[5] = *this[3]*m3[2] + *this[4]*m3[5] + *this[5]*m3[8];
        
        temp[6] = *this[6]*m3[0] + *this[7]*m3[3] + *this[8]*m3[6];
        temp[7] = *this[6]*m3[1] + *this[7]*m3[4] + *this[8]*m3[7];
        temp[8] = *this[6]*m3[2] + *this[7]*m3[5] + *this[8]*m3[8];
        
        for(int i=0; i<9; ++i){
            data[i] = temp[i];
        }
        return *this;
    }
    
    template <typename T>
    ProtoMatrix3<T>& ProtoMatrix3<T>::operator*=(T s){
        for(int i=0; i<9; ++i){
            data[i] *= s;
        }
        return *this;
    }
    
    
    template <typename T>
    ProtoMatrix3<T>& ProtoMatrix3<T>::operator/=(T s){
        for(int i=0; i<9; ++i){
            data[i] /= s;
        }
        return *this;
    }
    
    template <typename T>
    ProtoMatrix3<T>& ProtoMatrix3<T>::operator+=(const ProtoMatrix3<T>& m3){
        for(int i=0; i<9; ++i){
            data[i] += m3[i];
        }
        return *this;
    }
    
    template <typename T>
    ProtoMatrix3<T>& ProtoMatrix3<T>::operator-=(const ProtoMatrix3<T>& m3){
        for(int i=0; i<9; ++i){
            data[i] -= m3[i];
        }
        return *this;
    }
    
    template <typename T>
    inline T& ProtoMatrix3<T>::operator[](unsigned index){
        assert( index >= 0 && index <= 8 );
        return data[index];
    }
    
    // const
    template <typename T>
    inline const T& ProtoMatrix3<T>::operator[](unsigned index) const{
        assert( index >= 0 && index <= 8 );
        return data[index];
    }
    
    // expects two ints between 0-2
    template <typename T>
    T&	ProtoMatrix3<T>::operator() ( int r, int c ){
        assert( r >= 0 && r <= 2  && c >= 0 && c <= 2 );
        int index = r*3+c;
        assert( index >= 0 && index <= 8 );
        return *this[index];
    }
    
    /**************************************/
    /*          END Member OPs           */
    /**************************************/
    
    
    /*****************************************************/
    /*         Non-Member Ops Implementation        */
    /*****************************************************/
    
    // M3*V3
    // returns V3
    template <typename T>
    inline ProtoVector3<T> operator*(const ProtoMatrix3<T>& lhs, const ProtoVector3<T>& rhs){
        T x = lhs[0]*rhs.x + lhs[1]*rhs.y + lhs[2]*rhs.z;
        T y = lhs[3]*rhs.x + lhs[4]*rhs.y + lhs[5]*rhs.z;
        T z = lhs[6]*rhs.x + lhs[7]*rhs.y + lhs[8]*rhs.z;
        return ProtoVector3<T>(x, y, z);
    }
    
    // V3*M3
    // returns V3
    template <typename T>
    inline ProtoVector3<T> operator*(const ProtoVector3<T>& lhs, const ProtoMatrix3<T>& rhs){
        return rhs*lhs;
    }
    
    // M3*M3
    // return M4
    template <typename T>
    inline ProtoMatrix3<T> operator*(const ProtoMatrix3<T>& lhs, const ProtoMatrix3<T>& rhs) {
        ProtoMatrix3<T> tempMat3();
        int index = 0;
        for(int i=0; i<3; ++i){
            for(int j=0; j<3; ++j){
                index = i*3+j;
               tempMat3.data[index] = lhs[3*i]*rhs[j] + lhs[3*i+1]*rhs[j+3] + lhs[3*i+2]*rhs[j+6];
            }
        }
        return tempMat3;
    }
    
    // M4*Sclr
    // return M4
    template <typename T>
    inline ProtoMatrix3<T> operator*(const ProtoMatrix3<T>& lhs, T s) {
        ProtoMatrix3<T> tempMat();
        for(int i=0; i<9; ++i){
            tempMat.data[i] = lhs[i]*s;
        }
        return tempMat;
    }
    
    // Sclr*M4
    // return M4
    template <typename T>
    inline ProtoMatrix3<T> operator*(T s, const ProtoMatrix3<T>& rhs) {
        return rhs*s;
    }
    
    // M4+M4
    // return M4
    template <typename T>
    inline ProtoMatrix3<T> operator+(const ProtoMatrix3<T>& lhs, const ProtoMatrix3<T>& rhs){
        ProtoMatrix3<T> tempMat();
        for(int i=0; i<9; ++i){
            tempMat.data[i] = lhs[i]+rhs[i];
        }
        return tempMat;
    }
    
    // M4-M4
    // return M4
    template <typename T>
    inline ProtoMatrix3<T> operator-(const ProtoMatrix3<T>& lhs, const ProtoMatrix3<T>& rhs){
        ProtoMatrix3<T> tempMat();
        for(int i=0; i<9; ++i){
            tempMat.data[i] = lhs[i]-rhs[i];
        }
        return tempMat;
    }
    
    // M4+Sclr
    // return M4
    template <typename T>
    inline ProtoMatrix3<T> operator+(const ProtoMatrix3<T>& lhs, T s){
        ProtoMatrix3<T> tempMat();
        for(int i=0; i<9; ++i){
            tempMat.data[i] = lhs[i]+s;
        }
        return tempMat;
    }
    
    // Sclr+M4
    // return M4
    template <typename T>
    inline ProtoMatrix3<T> operator+(T s, const ProtoMatrix3<T>& rhs){
        return rhs+s;
    }
    
    // M4-Sclr
    // return M4
    template <typename T>
    inline ProtoMatrix3<T> operator-(const ProtoMatrix3<T>& lhs, T s){
        return lhs+(-s);
    }
    
    // Sclr-M4
    // return M4
    template <typename T>
    inline ProtoMatrix3<T> operator-(T s, const ProtoMatrix3<T>& rhs){
        return rhs+(-s);
    }
    
    /**********************/
    /*         END        */
    /**********************/
    
    
    
#define ProtoMatrix3f ProtoMatrix3<float>
#define ProtoMatrix3d ProtoMatrix3<double>
}

#endif	// PROTO_MATRIX3_H

