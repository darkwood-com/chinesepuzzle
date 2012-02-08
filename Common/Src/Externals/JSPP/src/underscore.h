
struct JSPPKeyValue {
	JSPPKeyValue(std::string k) : key(k) {
	}

	JSPPKeyValue& operator=(JSPPObject v) {
		this->value = v;
		return *this;
	}

	JSPPObject key;
	JSPPObject value;
};

class Underscore {
public:
	JSPPObject operator() (JSPPObject a) {
		return a;
	}
	JSPPKeyValue& operator[] (JSPPObject key) {
		JSPPKeyValue* kv = new JSPPKeyValue(key.toString());
		return *kv;
	}

	JSPPObject operator= (JSPPObject a) {
		return a;
	}
};
Underscore _;

