/*!  \brief  ProtoCore.h: Core Universal Functionality
 ProtoCore.h
 Protobyte Library v02
 
 Created by Ira on 12/21/13.
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

#ifndef Protobyte_dev_ProtoCore_h
#define Protobyte_dev_ProtoCore_h

#include <iostream>


namespace ijg {

    
    template <typename T>
    void print(T t){
        std::cout << t;
    }
    
    template <typename T, typename U>
    void print(T t, U u){
        std::cout << t << u;
    }
    
    template <typename T, typename U, typename V>
    void print(T t, U u, V v){
        std::cout << t << u << v;
    }
    
    template <typename T, typename U, typename V, typename W>
    void print(T t, U u, V v, W w){
        std::cout << t << u << v << w;
    }
    
   template <typename T, typename U, typename V, typename W, typename X>
    void print(T t, U u, V v, W w, X x){
        std::cout << t << u << v << w << x;
    }
    
    template <typename T, typename U, typename V, typename W, typename X, typename Y>
    void print(T t, U u, V v, W w, X x, Y y){
        std::cout << t << u << v << w << x << y;
    }
    
    template <typename T, typename U, typename V, typename W, typename X, typename Y, typename Z>
    void print(T t, U u, V v, W w, X x, Y y, Z z){
        std::cout << t << u << v << w << x << y << z;
    }
    
    //// with line returns
    //template <typename T>
    //void println(T t){
    //    std::cout << t << std::endl;
    //}
    //
    //template <typename T, typename U>
    //void println(T t, U u){
    //    std::cout << t << u << std::endl;
    //}
    //
    //template <typename T, typename U, typename V>
    //void println(T t, U u, V v){
    //    std::cout << t << u << v << std::endl;
    //}
    //
    //template <typename T, typename U, typename V, typename W>
    //void println(T t, U u, V v, W w){
    //    std::cout << t << u << v << w << std::endl;
    //}
    //
    //template <typename T, typename U, typename V, typename W, typename X>
    //void println(T t, U u, V v, W w, X x){
    //    std::cout << t << u << v << w << x << std::endl;
    //}
    //
    //template <typename T, typename U, typename V, typename W, typename X, typename Y>
    //void println(T t, U u, V v, W w, X x, Y y){
    //    std::cout << t << u << v << w << x << y << std::endl;
    //}
    //
    //template <typename T, typename U, typename V, typename W, typename X, typename Y, typename Z>
    //void println(T t, U u, V v, W w, X x, Y y, Z z){
    //    std::cout << t << u << v << w << x << y << z << std::endl;
    //}

	// variadic template approach
	// thanks to http://www.devx.com/cplus/Article/41533/0/page/2

	template<typename T>
	void println(T value)
	{
		std::cout << value << std::endl;
	}

	template<typename First, typename ... Rest>
	void println(First first, Rest ... rest)
	{
		std::cout << first << " ";
		println(rest...);
	}
    // the fun ends here
    
    
}

// homage to Macromedia
#define trace println

#endif // Protobyte_dev_ProtoCore_h
