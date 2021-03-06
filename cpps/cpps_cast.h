#ifndef CPPS_CAST_CPPS_HEAD_
#define CPPS_CAST_CPPS_HEAD_

//===================================
//@Author		:	Johnson
//@Email		:	jiang_4177@163.com
//@Date			:	2015/11/24 (yy/mm/dd)
//@Module		:	CPPS_CAST
//@Description	:	Cpps ת���� C++
//@website		:	http://cpps.wiki
//==================================

namespace cpps
{
	template<class T>
	static T object_cast(object& o)
	{
		typedef cpps_converter<T> converter;

		if (!converter::match((o.value)))
		{
			throw("object_castʧ�ܡ�����");
		}

		return converter::apply((o.value));
	}
}
#endif // CPPS_CAST_CPPS_HEAD_