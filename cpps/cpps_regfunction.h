#ifndef CPPS_REG_FUNCTION_CPPS_HEAD_
#define CPPS_REG_FUNCTION_CPPS_HEAD_

//===================================
//@Author		:	Johnson
//@Email		:	jiang_4177@163.com
//@Date			:	2015/11/20 (yy/mm/dd)
//@Module		:	CPPS_CALL_FUNCTION
//@Description	:	ע�ắ��
//@website		:	http://cpps.wiki
//==================================

namespace cpps
{
	template<typename p1>
	class dofunc;
	template<class retType, typename context, typename F, typename IsVoid>
	retType call_function(cpps_value &ret, cpps_domain *domain, Node*o, context &c, F &f, IsVoid&);
	template<class T>
	class cpps_is_void;
	template <class C>
	struct cpps_class;
	struct cpps_cppsclass;
#define cpps_def_regfunction	1
#define cpps_def_regclass		2


	struct cpps_function
	{
		virtual void	callfunction(C *c, cpps_value *ret, cpps_domain *domain, std::vector<cpps_value> *o, cpps_stack *stack = NULL,bool isCheckGen1 = false)
		{}
		void			setfuncname(std::string name){
			funcname = name;
		}
		std::string		getfuncname(){
			return funcname;
		}

		void setIsNeesC(bool b)
		{
			isNeesC = b;
		}
		bool getIsNeedC()
		{
			return isNeesC;
		}

		bool			isNeesC;
		std::string		funcname;
	};


	struct cpps_reg
	{
		cpps_reg()
		{
			next = NULL;
			type = 0;
			isneedC = false;
		}
		cpps_reg* next;
		int8	type;
		std::string varname;
		bool		isneedC;
	};

	struct cpps_regfunction : public cpps_reg
	{
		cpps_regfunction(std::string f,cpps_function* func)
		:func(func)
		{
			type = cpps_def_regfunction;
			varname = f;
			func->setfuncname(f);
		}
		cpps_function* func;
	};
	struct cpps_regclass : public cpps_reg
	{
		cpps_regclass(std::string name, cpps_cppsclass *c)
		:cls(c)
		{
			type = cpps_def_regclass;
			varname = name;
		}
		cpps_cppsclass* cls;
	};

	template<class C>
	struct cpps_regclass_template : public cpps_regclass
	{
		cpps_regclass_template(std::string name, cpps_class<C> *c)
		:cpps_regclass(name,c)
		{

		}
	};


	
	template<class R>
	struct cpps_function1 : public cpps_function
	{
		cpps_function1( R(*f)())
		:f(f)
		{
			param = make_vector(f);
		}

		void  callfunction(C *c, cpps_value *ret, cpps_domain *domain, std::vector<cpps_value> *o, cpps_stack *stack = NULL, bool isCheckGen1 = false)
		{
			dofunc< vector1<R> > func = make_function(param);

			call_function<R>(c,*ret,domain, *o, func, f, cpps_is_void<R>());
		}
		R(*f)();
		vector1<R> param;
	};

	template<class R>
	cpps_regfunction* make_regfunction(std::string func, R(*f)())
	{
		return new cpps_regfunction(func, new cpps_function1<R>(f));
	}

	template<class R, class CLS>
	struct cpps_cpp_function1 : public cpps_function
	{
		cpps_cpp_function1(R(CLS::*f)())
		:f(f)
		{
			param = make_vector(f);
		}

		void  callfunction(C *c, cpps_value *ret, cpps_domain *domain, std::vector<cpps_value> *o, cpps_stack *stack = NULL, bool isCheckGen1 = false)
		{
			dofunc< vector1<R> > func = make_function(param);

			call_function< R>(c,*ret,domain, *o, func, f, cpps_is_void<R>());
		}
		R(CLS::*f)();
		vector1<R> param;
	};

	template<class R, class C>
	cpps_regfunction* make_regfunction(std::string func, R(C::*f)())
	{
		return new cpps_regfunction(func, new cpps_cpp_function1<R,C>(f));
	}
}


#define CPPS_MAKE_REGFUNCTION_ITER_C 1
#include "cpps_regfunction.h"
#undef  CPPS_MAKE_REGFUNCTION_ITER_C



#define CPPS_MAKE_REGFUNCTION_ITER_C 2
#include "cpps_regfunction.h"
#undef  CPPS_MAKE_REGFUNCTION_ITER_C



#define CPPS_MAKE_REGFUNCTION_ITER_C 3
#include "cpps_regfunction.h"
#undef  CPPS_MAKE_REGFUNCTION_ITER_C



#define CPPS_MAKE_REGFUNCTION_ITER_C 4
#include "cpps_regfunction.h"
#undef  CPPS_MAKE_REGFUNCTION_ITER_C



#define CPPS_MAKE_REGFUNCTION_ITER_C 5
#include "cpps_regfunction.h"
#undef  CPPS_MAKE_REGFUNCTION_ITER_C

#define CPPS_MAKE_REGFUNCTION_ITER_C 6
#include "cpps_regfunction.h"
#undef  CPPS_MAKE_REGFUNCTION_ITER_C

#endif //CPPS_REG_FUNCTION_CPPS_HEAD_

#ifdef CPPS_MAKE_REGFUNCTION_ITER_C

namespace cpps
{
	template<class R, CPPS_PP_ENUM_PARAMS(CPPS_MAKE_REGFUNCTION_ITER_C, class A) >
	CPPS_PP_CAT(struct cpps_function, CPPS_PP_CAT(VECTOR_I_, CPPS_MAKE_REGFUNCTION_ITER_C)) : public cpps_function
	{
		CPPS_PP_CAT(cpps_function, CPPS_PP_CAT(VECTOR_I_, CPPS_MAKE_REGFUNCTION_ITER_C))( R(*f)(CPPS_PP_ENUM_PARAMS(CPPS_MAKE_REGFUNCTION_ITER_C, A)))
		: f(f)
		{
			param = make_vector(f);
		}

		void  callfunction(C *c, cpps_value *ret, cpps_domain *domain, std::vector<cpps_value> *o, cpps_stack *stack = NULL, bool isCheckGen1 = false)
		{
			dofunc<CPPS_PP_CAT(cpps::vector, CPPS_PP_CAT(VECTOR_I_, CPPS_MAKE_REGFUNCTION_ITER_C)) < R, CPPS_PP_ENUM_PARAMS(CPPS_MAKE_REGFUNCTION_ITER_C, A) > > func = make_function(param);

			call_function<R>(c,*ret,domain, *o, func, f, cpps_is_void<R>());
		}
		R(*f)(CPPS_PP_ENUM_PARAMS(CPPS_MAKE_REGFUNCTION_ITER_C, A));
		CPPS_PP_CAT(cpps::vector, CPPS_PP_CAT(VECTOR_I_, CPPS_MAKE_REGFUNCTION_ITER_C)) < R, CPPS_PP_ENUM_PARAMS(CPPS_MAKE_REGFUNCTION_ITER_C, A) > param;
	};
	template<class R, CPPS_PP_ENUM_PARAMS(CPPS_MAKE_REGFUNCTION_ITER_C, class A) >
	cpps_regfunction* make_regfunction(std::string func, R(*f)(CPPS_PP_ENUM_PARAMS(CPPS_MAKE_REGFUNCTION_ITER_C, A)))
	{
		return new cpps_regfunction(func, new CPPS_PP_CAT(cpps_function, CPPS_PP_CAT(VECTOR_I_, CPPS_MAKE_REGFUNCTION_ITER_C))<R, CPPS_PP_ENUM_PARAMS(CPPS_MAKE_REGFUNCTION_ITER_C, A)>(f));
	}


	template<class R, class CLS, CPPS_PP_ENUM_PARAMS(CPPS_MAKE_REGFUNCTION_ITER_C, class A) >
	CPPS_PP_CAT(struct cpps_cpp_function, CPPS_PP_CAT(VECTOR_I_, CPPS_MAKE_REGFUNCTION_ITER_C)) : public cpps_function
	{
		CPPS_PP_CAT(cpps_cpp_function, CPPS_PP_CAT(VECTOR_I_, CPPS_MAKE_REGFUNCTION_ITER_C))(R(CLS::*f)(CPPS_PP_ENUM_PARAMS(CPPS_MAKE_REGFUNCTION_ITER_C, A)))
		: f(f)
		{
			param = make_vector(f);
		}

		void  callfunction(C *c, cpps_value *ret, cpps_domain *domain, std::vector<cpps_value> *o, cpps_stack *stack = NULL, bool isCheckGen1 = false)
		{
			dofunc<CPPS_PP_CAT(cpps::vector, CPPS_PP_CAT(VECTOR_I_, CPPS_MAKE_REGFUNCTION_ITER_C)) < R, CPPS_PP_ENUM_PARAMS(CPPS_MAKE_REGFUNCTION_ITER_C, A) > > func = make_function(param);

			call_function<R>(c,*ret, domain, *o, func, f, cpps_is_void<R>());
		}
		R(CLS::*f)(CPPS_PP_ENUM_PARAMS(CPPS_MAKE_REGFUNCTION_ITER_C, A));
		CPPS_PP_CAT(cpps::vector, CPPS_PP_CAT(VECTOR_I_, CPPS_MAKE_REGFUNCTION_ITER_C)) < R, CPPS_PP_ENUM_PARAMS(CPPS_MAKE_REGFUNCTION_ITER_C, A) > param;
	};
	template<class R, class C, CPPS_PP_ENUM_PARAMS(CPPS_MAKE_REGFUNCTION_ITER_C, class A) >
	cpps_regfunction* make_regfunction(std::string func, R(C::*f)(CPPS_PP_ENUM_PARAMS(CPPS_MAKE_REGFUNCTION_ITER_C, A)))
	{
		return new cpps_regfunction(func, new CPPS_PP_CAT(cpps_cpp_function, CPPS_PP_CAT(VECTOR_I_, CPPS_MAKE_REGFUNCTION_ITER_C))<R, C, CPPS_PP_ENUM_PARAMS(CPPS_MAKE_REGFUNCTION_ITER_C, A)>(f));
	}



}
#endif