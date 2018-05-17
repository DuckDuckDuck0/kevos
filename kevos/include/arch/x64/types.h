
/*x64架构下的数值类型
*/

#ifndef _KEVOS_ARCH_X64_TYPES_H_
#define _KEVOS_ARCH_X64_TYPES_H_

#include <sys/portable.h>


#ifndef _INT8_T
#define _INT8_T
using int8_t __mode__(__QI__)	=	char;
#endif

#ifndef _UINT8_T
#define _UINT8_T
using uint8_t __mode__(__QI__)	=	unsigned char;
#endif

#ifndef _INT16_T
#define _INT16_T
using int16_t __mode__(__HI__)	=	short;
#endif

#ifndef _UINT16_T
#define _UINT16_T
using uint16_t __mode__(__HI__)	=	unsigned short;
#endif

#ifndef _INT32_T
#define _INT32_T
using int32_t __mode__(__SI__)	=	int;
#endif

#ifndef _UINT32_T
#define _UINT32_T
using uint32_t	__mode__(__SI__) =	unsigned int;
#endif

#ifndef _INT64_T
#define _INT64_T
using int64_t __mode__(__DI__)	=	long;
#endif

#ifndef _UINT64_T
#define _UINT64_T
using uint64_t __mode__(__DI__)  =	unsigned long;
#endif

#ifndef _FLOAT32_T
#define _FLOAT32_T
using float32_t	=	float;
#endif

#ifndef _FLOAT64_T
#define _FLOAT64_T
using float64_t	=	double;
#endif

#ifndef _SIZE_T
#define _SIZE_T
using size_t    =	uint64_t;
#endif

#ifndef _SSIZE_T
#define _SSIZE_T
using ssize_t  	=	int64_t;
#endif

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
using ptrdiff_t	=	int64_t;
#endif


#endif