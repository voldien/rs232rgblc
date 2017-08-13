/**
    rs232 RGB LED controller library interface.
    Copyright (C) 2017  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _R232LCDEF_H_
#define _RS232LCDEF_H_ 1
#include<stdint.h>

/**
 *    Compiler
 */
#ifdef _MSC_VER 	/*	Visual Studio C++ Compiler.	*/
	#define R232LC_VC
	#define R232LC_COMPILER 1
	#if _MSC_VER >= 1900
		#define R232LC_V13 _MSC_VER
	#elif _MSC_VER >= 1800
		#define R232LC_V12 _MSC_VER
	#elif _MSC_VER >= 1700
		#define R232LC_VC11 _MSC_VER
	#elif _MSC_VER >= 1600
		#define R232LC_VC10 _MSC_VER
	#elif _MSC_VER >= 1500
		#define R232LC_VC9 _MSC_VER
	#elif _MSC_VER >= 1400
		#define R232LC_VC8 _MSC_VER
	#elif _MSC_VER >= 1300
		#define R232LC_VC7 _MSC_VER
	#else
		#define R232LC_VC6 _MSC_VER
	#endif
    	#pragma warning(disable : 4201)
	#define R232LC_COMPILER_NAME "Visual Studio C++/C"

#elif defined(__clang__)  || defined(__llvm__)           /*  LLVM, clang   */
    #define R232LC_LLVM 1
	#define R232LC_CLANG 1
	#define R232LC_COMPILER 5
	#define R232LC_COMPILER_NAME "LLVM/CLANG"
	#define R232LC_COMPILER_MAJOR_VERSION __clang_major__
	#define R232LC_COMPILER_MINOR_VERSION __clang_minor__

#elif defined(__GNUC__) || defined(__SNC__) || defined( __GNUC_MINOR__)	/*  GNU C Compiler*/
	#define R232LC_GNUC 1
	#define R232LC_COMPILER 2
	#define R232LC_COMPILER_NAME "GNU C"
	#define R232LC_COMPILER_MAJOR_VERSION __clang_major__
	#define R232LC_COMPILER_MINOR_VERSION __clang_minor__

#elif defined(__GNUG__) /*  GNU C++ Compiler*/
	#define R232LC_GNUC 2

#elif defined(__ghs__)		/* GHS	*/
	#define R232LC_GHS 1
	#define R232LC_COMPILER 3

#elif defined(__HP_cc) || defined(__HP_aCC)			/*	*/

#elif defined(__PGI)			/*	*/

#elif defined(__ICC) || defined(__INTEL_COMPILER) /*  Intel Compiler  */
	#define R232LC_INTEL
	#define R232LC_COMPILER 4
	#define R232LC_COMPILER_NAME "Intel C++"

#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)

#else
	#error Unsupported Compiler.
#endif


#if defined(__GNUC__) && defined(__ARM_NEON__)
     /* GCC-compatible compiler, targeting ARM with NEON */
     #include <arm_neon.h>
#endif	/**/


/**
 *	Platform define
 *	Architecture!
 */
#ifdef R232LC_VC
	#if defined(_M_IX86) || defined(_WIN32)
		#define R232LC_X86                          /**/
		#define R232LC_X32                          /**/
		#define R232LC_WIN32                        /**/
		#define R232LC_WINDOWS                      /**/
	#elif defined(_M_X64) || defined(_WIN64)
		#define R232LC_X64                          /**/
		#define R232LC_WIN64                        /**/
		#define R232LC_WINDOWS                      /**/
	#elif defined(_M_PPC)
		#define R232LC_PPC                          /**/
		#define R232LC_X360                         /**/
		#define R232LC_VMX                          /**/
	#elif defined(_M_ARM)
		#define R232LC_ARM                          /**/
		#define R232LC_ARM_NEON                     /**/
	#endif
#elif defined(R232LC_GNUC) || defined(R232LC_CLANG)
	#ifdef __CELLOS_LV2__   /**/
        #define R232LC_PS3                          /*	playstation 3*/
	#elif defined(__arm__)	/**/
		#define R232LC_ARM
        #define R232LC_PSP2                         /*	playstation portable 2*/
        #define R232LC_RAS_PI                       /*	rasberry pi	*/
	#endif
	#if defined(_WIN32) /**  Window*/
		#define R232LC_X86
		#define R232LC_WINDOWS                      /**/
	#endif
	#if ( defined(__linux__) || defined(__linux) || defined(linux) ) && (!(__ANDROID__) || !(ANDROID))/* Linux */
		#define R232LC_LINUX 1                       /**/
		#if defined(__amd64) || defined(__x86_64__) || defined(__i386__)
            #define R232LC_X86 1
		#endif
		#if defined(__arm__)
              #define EX_ARM 1
        #endif

	#elif defined (ANDROID) || defined(__ANDROID__) || __ANDROID_API__ > 9  /** Android */
        #include<jni.h>
		#define R232LC_ANDROID 1
		/*  android Architecture*/
        #if defined(__arm__)
			#define R232LC_ARM 1
		  #if defined(__ARM_ARCH_7A__)
			#if defined(__ARM_NEON__)
			  #if defined(__ARM_PCS_VFP)
				#define ABI "armeabi-v7a/NEON (hard-float)"
			  #else
				#define ABI "armeabi-v7a/NEON"
			  #endif
			#else
			  #if defined(__ARM_PCS_VFP)
				#define ABI "armeabi-v7a (hard-float)"
			  #else
				#define ABI "armeabi-v7a"
			  #endif
			#endif
		  #else
		   #define ABI "armeabi"
		  #endif
		#elif defined(__i386__)
		   #define ABI "x86"
		#elif defined(__x86_64__)
		   #define ABI "x86_64"
		#elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
		   #define ABI "mips64"
		#elif defined(__mips__)
		   #define ABI "mips"
		#elif defined(__aarch64__)
		   #define ABI "arm64-v8a"
		#else
		   #define ABI "unknown"
		#endif

	#elif defined (__APPLE__)   /*  Apple product   */
		#define R232LC_APPLE 1
		#if defined(__arm__)
			#define R232LC_APPLE_IOS    /*  Apple iphone/ipad OS    */
		#elif defined(MACOSX) || defined(macintosh) || defined(Macintosh)
			#define EX_MAC 1
		#endif
	#elif defined(__CYGWIN) 	/**/
		#define R232LC_CYGWIN 1
		#define R232LC_LINUX 1
	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)   /*  BSD*/
		#define R232LC_BSD
    	#elif defined(__llvm__) || defined(__clang__)   	/*  llvm    */
        	#define R232LC_LLVM 1
	#endif

#elif defined(__ICC) || defined(__INTEL_COMPILER)


#else
	#error  Unsupported architecture!   /*  No architecture support implicitly. remove this line to compile anyway*/
#endif

#if defined(__native_client__)	/*	nacl google	*/
	#define R232LC_NACL 1
#endif
#if defined(__pnacl__)          /* portable nacl google */
	#define R232LC_PNACL 1
#endif
#if defined(__unix__) || defined(__unix) || defined(unix)	/*  Unix    */
	#   define R232LC_UNIX 1
#endif

/**
 *	Calling function convention.
 */
#ifdef R232LC_WINDOWS	        /** Windows Calling Convention.*/
	#define R232LCAPIENTRY     __cdecl
	#define R232LCAPIFASTENTRY __fastcall
	#define R232LCAPITHISENTRY __thiscall
	#define R232LCAPISTDENTRY  __stdcall
#elif defined(R232LC_ANDROID)   /** Android Calling Convention	*/
    #define R232LCAPIENTRY JNICALL
    #define R232LCAPIFASTENTRY JNICALL
    #define R232LCAPITHISENTRY JNICALL
    #define R232LCAPISTDENTRY JNICALL
#else
#   if !defined(__cdecl) && ( defined(R232LC_GNUC)  || defined(R232LC_CLANG) )
        #define __cdecl  __attribute__ ((__cdecl__))
        #define __stdcall  __attribute__ ((stdcall))
		#define __fastcall __attribute__((fastcall))
#   endif
	#define R232LCAPIENTRY     __cdecl
	#define R232LCAPISTDENTRY  __stdcall
	#define R232LCAPIFASTENTRY __fastcall
#endif

/**
 *	library declaration.
 */
#if defined(R232LC_GNUC) || defined(R232LC_LLVM)
	#if defined(R232LC_UNIX)
		#define R232LCDS	 __attribute__((__visibility__ ("default")))
	#else
		#define R232LCDS
	#endif
#elif defined(R232LC_VC)
	#if R232LC_INTERNAL
		#define R232LCDS __declspec(dllexport)
	#else
		#define R232LCDS __declspec(dllimport)
	#endif
#endif

#endif
