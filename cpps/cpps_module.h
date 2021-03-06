#ifndef CPPS_MODULE_CPPS_HEAD_
#define CPPS_MODULE_CPPS_HEAD_

//===================================
//@Author		:	Johnson
//@Email		:	jiang_4177@163.com
//@Date			:	2015/11/20 (yy/mm/dd)
//@Module		:	CPPS_MODULE
//@Description	:	Cpp注册到Cpps接口
//@website		:	http://cpps.wiki
//==================================


namespace cpps
{
	struct cpps_reg_class
	{
		cpps_reg* f;
	};

	struct RegxModule
	{

		RegxModule(cpps_reg_class c)
			:f(c.f)
		{
			f->isneedC = false;
		}
		RegxModule( cpps_regfunction* f,bool b )
			:f(f)
		{
			f->isneedC = b;
		}
		RegxModule 	operator ,(RegxModule c)
		{
			if (!f->next)
			{
				f->next = c.f;
			}
			else
			{
				cpps_reg* next = f->next;
				while (next->next)
					next = next->next;
			
				next->next = c.f;
			}
			return *this;
		}
		cpps_reg* f;
	};

	template< class C>
	struct _class : public cpps_reg_class
	{
		_class(std::string name)
		{
			_cls = new cpps_class<C>(name,NULL, cpps_domain_type_class);
			f = new cpps_regclass_template<C>(name, _cls);
			cpps_class_singleton<C*>::getSingletonPtr()->setsls(_cls);
		}
		template<class F>
		_class<C>& 	def(std::string func, F _f)
		{
			cpps_reg* r = make_regfunction(func, _f);
			r->isneedC = false;
			_cls->regFunc( r );
			return *this;
		}
		template<class F>
		_class<C>& 	def_inside(std::string func, F _f)
		{
			cpps_reg* r = make_regfunction(func, _f);
			r->isneedC = true;
			_cls->regFunc(r);
			return *this;
		}

		RegxModule 	operator ,(RegxModule c)
		{
			RegxModule(*this).operator,(c);
			return *this;
		}
		cpps_class<C> *_cls;
	};

	template<class F>
	RegxModule def(std::string func, F f)
	{
		return RegxModule(make_regfunction(func, f),false);
	}

	template<class F>
	RegxModule def_inside(std::string func, F f)
	{
		return RegxModule(make_regfunction(func, f), true);
	}
	


	struct cpps_module
	{
		cpps_module(C* c,std::string _domain) //默认注册给_G
		{
			cState = c;
			domain = cState->_G;//默认是根节点
			if (!_domain.empty())//如果定义名字了 那就是自己的一个。。。
			{
				cpps_regvar * v = domain->getVar(_domain);
				if (!v)
				{
					cpps_domain *temp_domain = new cpps_domain(NULL, cpps_domain_type_root,"root");//创建根节点域


					v = new cpps_regvar();//_G 为根节点
					v->setVarName(_domain);
					v->setValue(cpps_value(temp_domain)); //域列表会copy进去
					domain->regVar(v); //将自己注册成_G..
				}
				domain = v->getValue().value.domain;
			}
		}

		void	operator [](RegxModule m)
		{
			domain->regFunc(m.f);
		}

	public:
		C					*cState;
		cpps_domain			*domain;	//根节点
	};


	static cpps_module module(C *c, std::string _domain = "")
	{
		return cpps_module(c, _domain);
	}

}

#endif // CPPS_MODULE_CPPS_HEAD_