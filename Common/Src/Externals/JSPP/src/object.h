
#include <iostream>
#include <sstream>
#include <string>
#include <functional>
#include <map>
#include <vector>


enum Types {
	JSPP_NUMBER,
	JSPP_STRING,
	JSPP_FUNCTION,
	JSPP_UNDEFINED,
	JSPP_NULL,
	JSPP_OBJECT,
	JSPP_ARRAY,
	JSPP_KEYVALUE
};

class JSPPObject;
class JSPPKeyValue;

class JSPPState
{
public:
	JSPPState() : refcount(1) {}
	int refcount;

	std::map<std::string, JSPPObject> map;
	int type;

	double n;
	std::string s;
	int f;
	JSPPObject (*f0)(JSPPObject);
	JSPPObject (*f1)(JSPPObject, JSPPObject);
	JSPPObject (*f2)(JSPPObject, JSPPObject, JSPPObject);
	JSPPObject (*f3)(JSPPObject, JSPPObject, JSPPObject, JSPPObject);
	JSPPObject (*f4)(JSPPObject, JSPPObject, JSPPObject, JSPPObject, JSPPObject);
	JSPPObject (*f5)(JSPPObject, JSPPObject, JSPPObject, JSPPObject, JSPPObject, JSPPObject);
	JSPPKeyValue* kv;
};


class JSPPObject {
public:

	~JSPPObject() {
		if (s->refcount == 1) {
			delete s;
		} else {
			s->refcount -= 1;
		}
	}

	// Constructors

	
	JSPPObject& operator= (JSPPObject o);
	JSPPObject& operator|= (JSPPObject o);
	JSPPObject(const JSPPObject& o);
	JSPPObject();
	JSPPObject(double n);
	JSPPObject(int n);
	JSPPObject(bool b);
	JSPPObject(const char* str);
	JSPPObject(std::string str);
	JSPPObject(std::vector<JSPPObject> list);
	JSPPObject(std::pair<const std::basic_string<char>, JSPPObject> it);
	JSPPObject(JSPPKeyValue& kv);
	JSPPObject(JSPPObject (*f)(JSPPObject));
	JSPPObject(JSPPObject (*f)(JSPPObject, JSPPObject));
	JSPPObject(JSPPObject (*f)(JSPPObject, JSPPObject, JSPPObject));
	JSPPObject(JSPPObject (*f)(JSPPObject, JSPPObject, JSPPObject, JSPPObject));
	JSPPObject(JSPPObject (*f)(JSPPObject, JSPPObject, JSPPObject, JSPPObject, JSPPObject));
	JSPPObject(JSPPObject (*f)(JSPPObject, JSPPObject, JSPPObject, JSPPObject, JSPPObject, JSPPObject));
	template<typename F> JSPPObject(F f);


	// Methods

	JSPPObject operator()();
	JSPPObject operator()(JSPPObject);
	JSPPObject operator()(JSPPObject, JSPPObject);
	JSPPObject operator()(JSPPObject, JSPPObject, JSPPObject);
	JSPPObject operator()(JSPPObject, JSPPObject, JSPPObject, JSPPObject);
	JSPPObject operator()(JSPPObject, JSPPObject, JSPPObject, JSPPObject, JSPPObject);
	
	std::string toString();
	JSPPObject& get_key(std::string key);
	JSPPObject& operator[](JSPPObject key);

	JSPPObject* self;
	JSPPObject* write;
	JSPPState* s;
	
	std::map<std::string, JSPPObject>::iterator begin() {
		return s->map.begin();
	}

	std::map<std::string, JSPPObject>::iterator end() {
		return s->map.end();
	}

protected:

/* Functions */
	// http://stackoverflow.com/questions/4170201/c0x-overloading-on-lambda-arity

	/* 0 param */
	template<typename F>
	void set_func(F& f, JSPPObject (F::*mf)(JSPPObject))
	{ s->f = 0; s->f0 = f; }

	/* 1 param */
	template<typename F>
	void set_func(F& f, JSPPObject (F::*mf)(JSPPObject, JSPPObject))
	{ s->f = 1; s->f1 = f; }

	/* 2 param */
	template<typename F>
	void set_func(F& f, JSPPObject (F::*mf)(JSPPObject, JSPPObject, JSPPObject))
	{ s->f = 2; s->f2 = f; }

	/* 3 param */
	template<typename F>
	void set_func(F& f, JSPPObject (F::*mf)(JSPPObject, JSPPObject, JSPPObject, JSPPObject))
	{ s->f = 3; s->f3 = f; }

	/* 4 param */
	template<typename F>
	void set_func(F& f, JSPPObject (F::*mf)(JSPPObject, JSPPObject, JSPPObject, JSPPObject, JSPPObject))
	{ s->f = 4; s->f4 = f; }

	/* 5 param */
	template<typename F>
	void set_func(F& f, JSPPObject (F::*mf)(JSPPObject, JSPPObject, JSPPObject, JSPPObject, JSPPObject, JSPPObject))
	{ s->f = 5; s->f5 = f; }
};

std::ostream& operator<<(std::ostream& stream, JSPPObject o) {
	stream << o.toString();
	return stream;
}

typedef JSPPObject var;

JSPPObject undefined;
JSPPObject global;
