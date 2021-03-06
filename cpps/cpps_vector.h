#ifndef CPPS_VECTOR_CPPS_HEAD_
#define CPPS_VECTOR_CPPS_HEAD_

//===================================
//@Author		:	Johnson
//@Email		:	jiang_4177@163.com
//@Date			:	2015/11/20 (yy/mm/dd)
//@Module		:	CPPS_VECTOR
//@Description	:	函数参数列表
//@website		:	http://cpps.wiki
//==================================

template<typename ret>
class vector1
{
public:
	typedef ret rettype;
	vector1()
	{

	}
	size_t		getparamcount()
	{
		return 0;
	}
public:
};


#define VECTOR_I_1 2
#define VECTOR_I_2 3
#define VECTOR_I_3 4
#define VECTOR_I_4 5
#define VECTOR_I_5 6
#define VECTOR_I_6 7

#define VECTORCLASS(c) 

#define  CPPS_VECTOR_ITER_C() 1
#include "cpps_vector.h"
#undef CPPS_VECTOR_ITER_C


#define  CPPS_VECTOR_ITER_C() 2
#include "cpps_vector.h"
#undef CPPS_VECTOR_ITER_C


#define  CPPS_VECTOR_ITER_C() 3
#include "cpps_vector.h"
#undef CPPS_VECTOR_ITER_C


#define  CPPS_VECTOR_ITER_C() 4
#include "cpps_vector.h"
#undef CPPS_VECTOR_ITER_C



#define  CPPS_VECTOR_ITER_C() 5
#include "cpps_vector.h"
#undef CPPS_VECTOR_ITER_C


#define  CPPS_VECTOR_ITER_C() 6
#include "cpps_vector.h"
#undef CPPS_VECTOR_ITER_C

#endif // CPPS_VECTOR_CPPS_HEAD_

#ifdef CPPS_VECTOR_ITER_C


namespace cpps
{

	template<typename ret, CPPS_PP_ENUM_PARAMS(CPPS_VECTOR_ITER_C(), class p) >
	CPPS_PP_CAT(class vector, CPPS_PP_CAT(VECTOR_I_, CPPS_VECTOR_ITER_C()))
	{
	public:
		typedef ret rettype;

		size_t		getparamcount()
		{
			return CPPS_VECTOR_ITER_C();
		}
	public:
		CPPS_PP_ENUM_VARS(CPPS_VECTOR_ITER_C(), p, param);
	};
}


#endif