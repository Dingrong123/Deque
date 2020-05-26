#include<iostream>

class Integer {
private:
	int data;
public:
	Integer(const int &value) : data(value) {}
	Integer(const Integer &other) : data(other.data) {}
	bool operator==(const Integer &t)
	{
	    if(t.data)
		return data ==t.data;
	}
	friend  std::ostream& operator<<(std::ostream &os,  Integer &r)
	{
		os << r.data;
		return os;
	}
};
