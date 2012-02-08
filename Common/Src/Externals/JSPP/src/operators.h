
#include <limits>
double NaN = std::numeric_limits<double>::quiet_NaN();

JSPPObject JSPPObject::operator()() {
		if (s->type != JSPP_FUNCTION) { throw _("JSPPObject is not a function"); }
		if (s->f == 0) return s->f0(*self);
		if (s->f == 1) return s->f1(*self, undefined);
		if (s->f == 2) return s->f2(*self, undefined, undefined);
		if (s->f == 3) return s->f3(*self, undefined, undefined, undefined);
		if (s->f == 4) return s->f4(*self, undefined, undefined, undefined, undefined);
		if (s->f == 5) return s->f5(*self, undefined, undefined, undefined, undefined, undefined);
		throw _("Too many arguments");
	}

JSPPObject JSPPObject::operator()(JSPPObject a) {
		if (s->type != JSPP_FUNCTION) { throw _("JSPPObject is not a function"); }
		if (s->f == 0) return s->f0(*self);
		if (s->f == 1) return s->f1(*self, a);
		if (s->f == 2) return s->f2(*self, a, undefined);
		if (s->f == 3) return s->f3(*self, a, undefined, undefined);
		if (s->f == 4) return s->f4(*self, a, undefined, undefined, undefined);
		if (s->f == 5) return s->f5(*self, a, undefined, undefined, undefined, undefined);
		throw _("Too many arguments");
	}

JSPPObject JSPPObject::operator()(JSPPObject a, JSPPObject b) {
		if (s->type != JSPP_FUNCTION) { throw _("JSPPObject is not a function"); }
		if (s->f == 0) return s->f0(*self);
		if (s->f == 1) return s->f1(*self, a);
		if (s->f == 2) return s->f2(*self, a, b);
		if (s->f == 3) return s->f3(*self, a, b, undefined);
		if (s->f == 4) return s->f4(*self, a, b, undefined, undefined);
		if (s->f == 5) return s->f5(*self, a, b, undefined, undefined, undefined);
		throw _("Too many arguments");
	}

JSPPObject JSPPObject::operator()(JSPPObject a, JSPPObject b, JSPPObject c) {
		if (s->type != JSPP_FUNCTION) { throw _("JSPPObject is not a function"); }
		if (s->f == 0) return s->f0(*self);
		if (s->f == 1) return s->f1(*self, a);
		if (s->f == 2) return s->f2(*self, a, b);
		if (s->f == 3) return s->f3(*self, a, b, c);
		if (s->f == 4) return s->f4(*self, a, b, c, undefined);
		if (s->f == 5) return s->f5(*self, a, b, c, undefined, undefined);
		throw _("Too many arguments");
	}

JSPPObject JSPPObject::operator()(JSPPObject a, JSPPObject b, JSPPObject c, JSPPObject d) {
		if (s->type != JSPP_FUNCTION) { throw _("JSPPObject is not a function"); }
		if (s->f == 0) return s->f0(*self);
		if (s->f == 1) return s->f1(*self, a);
		if (s->f == 2) return s->f2(*self, a, b);
		if (s->f == 3) return s->f3(*self, a, b, c);
		if (s->f == 4) return s->f4(*self, a, b, c, d);
		if (s->f == 5) return s->f5(*self, a, b, c, d, undefined);
		throw _("Too many arguments");
	}

JSPPObject JSPPObject::operator()(JSPPObject a, JSPPObject b, JSPPObject c, JSPPObject d, JSPPObject e) {
		if (s->type != JSPP_FUNCTION) { throw _("JSPPObject is not a function"); }
		if (s->f == 0) return s->f0(*self);
		if (s->f == 1) return s->f1(*self, a);
		if (s->f == 2) return s->f2(*self, a, b);
		if (s->f == 3) return s->f3(*self, a, b, c);
		if (s->f == 4) return s->f4(*self, a, b, c, d);
		if (s->f == 5) return s->f5(*self, a, b, c, d, e);
		throw _("Too many arguments");
	}


JSPPObject operator >>(JSPPObject a, JSPPObject b) {
	if (a.s->type == JSPP_NUMBER && b.s->type == JSPP_NUMBER) {
		return (int)a.s->n >> (int)b.s->n;
	}
	throw JSPPObject("Unfinished operator>>");
}


JSPPObject operator +(JSPPObject a, JSPPObject b) {
	if (a.s->type == JSPP_NUMBER && b.s->type == JSPP_NUMBER) {
		return a.s->n + b.s->n;
	}
	return a.toString() + b.toString();
}

JSPPObject operator -(JSPPObject a, JSPPObject b) {
	if (a.s->type == JSPP_NUMBER && b.s->type == JSPP_NUMBER) {
		return a.s->n - b.s->n;
	}
	return NaN;
}

bool operator ==(JSPPObject a, JSPPObject b) {
	if (a.s->type == JSPP_UNDEFINED && b.s->type == JSPP_UNDEFINED) {
		return true;
	}
	if (a.s->type == JSPP_NUMBER && b.s->type == JSPP_NUMBER) {
		return a.s->n == b.s->n;
	}
	if (a.s->type == JSPP_STRING && b.s->type == JSPP_STRING) {
		return a.s->s == b.s->s;
	}
	return a.s == b.s;
}

bool operator !=(JSPPObject a, JSPPObject b) {
	return !(a == b);
}

JSPPObject operator *(JSPPObject a, JSPPObject b) {
	if (a.s->type == JSPP_NUMBER && b.s->type == JSPP_NUMBER) {
		return a.s->n * a.s->n;
	}
	return NaN;
}

JSPPObject operator /(JSPPObject a, JSPPObject b) {
	if (a.s->type == JSPP_NUMBER && b.s->type == JSPP_NUMBER) {
		return a.s->n / a.s->n;
	}
	return NaN;
}

JSPPObject& operator -=(JSPPObject& a, JSPPObject b) {
	a = a - b;
	return a;
}

JSPPObject& operator +=(JSPPObject& a, JSPPObject b) {
	a = a + b;
	return a;
}

JSPPObject& operator /=(JSPPObject& a, JSPPObject b) {
	a = a / b;
	return a;
}

JSPPObject& operator *=(JSPPObject& a, JSPPObject b) {
	a = a * b;
	return a;
}

JSPPObject& operator ++(JSPPObject& a) {
	a += 1;
	return a;
}

JSPPObject& operator --(JSPPObject& a) {
	a -= 1;
	return a;
}

JSPPObject& operator --(JSPPObject& a, int) {
	a -= 1;
	return a;
}

JSPPObject& operator ++(JSPPObject& a, int) {
	a += 1;
	return a;
}
/*
bool operator !(JSPPObject a) {
	if (a.s->type == JSPP_NUMBER) {
		return a.s->n == 0;
	}
	return a.toString() == "";
}
*/

bool operator <(JSPPObject a, JSPPObject b) {
	if (a.s->type == JSPP_NUMBER && b.s->type == JSPP_NUMBER) {
		return a.s->n < b.s->n;
	}
	return a.toString() < b.toString();
}

bool operator <=(JSPPObject a, JSPPObject b) {
	if (a.s->type == JSPP_NUMBER && b.s->type == JSPP_NUMBER) {
		return a.s->n <= b.s->n;
	}
	return a.toString() <= b.toString();
}

bool operator >(JSPPObject a, JSPPObject b) {
	return !(a <= b);
}

bool operator >=(JSPPObject a, JSPPObject b) {
	return !(a < b);
}


std::string JSPPObject::toString() {
	if (s->type == JSPP_STRING) {
		return s->s;
	}

	if (s->type == JSPP_NUMBER) {
		std::ostringstream stream;
		stream << s->n;
		return stream.str();
	}

	if (s->type == JSPP_UNDEFINED) {
		return "undefined";
	}

	if (s->type == JSPP_NULL) {
		return "null";
	}

	if (s->type == JSPP_FUNCTION) {
		std::ostringstream stream;
		stream << "<function " << s << ">";
		return stream.str();
	}

	if (s->type == JSPP_OBJECT) {
		std::ostringstream stream;
		stream << "{";

		/*
		bool first = true;
		for (auto it = this->s->map.begin(); it != this->s->map.end(); ++it) {
			if (it->second != undefined) {
				if (!first) {
					stream << ", ";
				}
				first = false;
				stream << it->first << ": " << it->second;
			}
		}
		 */

		stream << "}";
		return stream.str();
	}

	if (s->type == JSPP_ARRAY) {
		var length = (*this)["length"];
		std::ostringstream stream;
		stream << "[";

		for (var i = 0; i < length; ++i) {
			stream << (*this)[i];
			if (i != length - 1) {
				stream << ", ";
			}
		}

		stream << "]";
		return stream.str();
	}


	throw _("Unknown type");
}


JSPPObject& JSPPObject::get_key(std::string key) {
	JSPPObject& ret = s->map[key];
	if (ret == undefined && s->map["__proto__"] != undefined) {
		return s->map["__proto__"].get_key(key);
	}
	return ret;
}

JSPPObject& JSPPObject::operator[](JSPPObject key) {
	std::string key_str = key.toString();
	JSPPObject& ret = get_key(key_str);
	ret.self = this;
	ret.write = &s->map[key_str];
	return ret;
}

