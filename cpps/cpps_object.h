#ifndef CPPS_OBJECT_CPPS_HEAD_
#define CPPS_OBJECT_CPPS_HEAD_

//===================================
//@Author		:	Johnson
//@Email		:	jiang_4177@163.com
//@Date			:	2015/11/24 (yy/mm/dd)
//@Module		:	CPPS_OBJECT
//@Description	:	Cpps转C++
//@website		:	http://cpps.wiki
//==================================


namespace cpps
{
	struct cpps_domain;
	struct object
	{
		object()
		{
			
		}
		
		object(cpps_value v)
		{
			value = v;
		}


		template<class Type>
		object(Type v)
		{
			if (!cpps_cpp_to_cpps_converter<Type>::match(NULL,v))
			{
				throw("转换失败。。。。");
			}

			value = cpps_cpp_to_cpps_converter<Type>::apply(NULL,v);
		}
	
		object		operator [] (std::string k)
		{
			cpps_value ret;
			if (value.tt == CPPS_TCLASSVAR || value.tt == CPPS_TDOMAIN)
			{
				cpps_regvar* var = value.value.domain->getVar(k);
				if (var)
				{
					ret = var->getValue();
				}
			}
			return static_cast<object>(ret);
		}
		//array可以用
		object		operator [] (int32 k)
		{

		}

		cpps_value	value;
	};

	static int32		type(object& o)
	{
		return o.value.tt;
	}
	static std::string type_s(object &o)
	{
		switch (type(o))
		{
		case CPPS_TNIL:
			return "nil";
		case CPPS_TINTEGER:
			return "integer";
		case CPPS_TNUMBER:
			return "number";
		case CPPS_TBOOLEAN:
			return "boolean";
		case CPPS_TSTRING:
			return "string";
		case CPPS_TCLASSVAR:
			return "userdata";
		case CPPS_TFUNCTION:
			return "function";
		}
		return "unknow";
	}

}

#endif // CPPS_OBJECT_CPPS_HEAD_