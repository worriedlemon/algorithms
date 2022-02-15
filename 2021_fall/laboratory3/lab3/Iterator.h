#ifndef IITERATOR_H
#define IITERATOR_H
class IIterator
{
public:
	virtual int next() = 0;
	virtual bool has_next() = 0;
};
#endif