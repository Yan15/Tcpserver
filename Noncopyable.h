#ifndef __MY_NONCOPYABLE_H_
#define __MY_NONCOPYABLE_H_

namespace st
{
class Noncopyable
{
protected:
	Noncopyable(){}
private:
	Noncopyable(const Noncopyable &rhs);
	Noncopyable & operator=(const Noncopyable &rhs);
};
}
#endif
