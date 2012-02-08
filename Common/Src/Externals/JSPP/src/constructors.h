
	
JSPPObject& JSPPObject::operator= (JSPPObject o) {
	write->s = o.s;
	write->s->refcount += 1;
	return *write;
}
	
JSPPObject& JSPPObject::operator|= (JSPPObject o) {
	write->s->refcount += 1;
	
	write->s->type = o.s->type;
	write->s->s = o.s->s;
	write->s->n = o.s->n;
	write->s->map = o.s->map;
	write->s->kv = o.s->kv;

	write->s->f = o.s->f;
	write->s->f0 = o.s->f0;
	write->s->f1 = o.s->f1;
	write->s->f2 = o.s->f2;
	write->s->f3 = o.s->f3;
	write->s->f4 = o.s->f4;
	write->s->f5 = o.s->f5;

	return *write;
}

JSPPObject::JSPPObject(const JSPPObject& o) : self(o.self), write(this), s(o.s) {
	s->refcount += 1;
}

JSPPObject::JSPPObject() : self(&undefined), write(this), s(new JSPPState) {
	s->type = JSPP_UNDEFINED;
}
	
JSPPObject::JSPPObject(double n) : self(&undefined), write(this), s(new JSPPState)  {
	s->n = n;
	s->type = JSPP_NUMBER;
}

JSPPObject::JSPPObject(int n) : self(&undefined), write(this), s(new JSPPState)  {
	s->n = n;
	s->type = JSPP_NUMBER;
}
	
JSPPObject::JSPPObject(bool b) : self(&undefined), write(this), s(new JSPPState)  {
	s->n = b ? 1 : 0;
	s->type = JSPP_NUMBER;
}
	
JSPPObject::JSPPObject(const char* str) : self(&undefined), write(this), s(new JSPPState)  {
	s->s = str;
	s->type = JSPP_STRING;
}

JSPPObject::JSPPObject(std::string str) : self(&undefined), write(this), s(new JSPPState)  {
	s->s = str;
	s->type = JSPP_STRING;
}

JSPPObject::JSPPObject(JSPPObject (*f)(JSPPObject)) : self(&undefined), write(this), s(new JSPPState) 
{
	s->f = 0; s->f0 = f;
	s->type = JSPP_FUNCTION;
	s->map["prototype"] = global["Function"];
}

JSPPObject::JSPPObject(JSPPObject (*f)(JSPPObject, JSPPObject)) : self(&undefined), write(this), s(new JSPPState) 
{
	s->f = 1; s->f1 = f;
	s->type = JSPP_FUNCTION;
	s->map["prototype"] = global["Function"];
}

JSPPObject::JSPPObject(JSPPObject (*f)(JSPPObject, JSPPObject, JSPPObject)) : self(&undefined), write(this), s(new JSPPState) 
{
	s->f = 2; s->f2 = f;
	s->type = JSPP_FUNCTION;
	s->map["prototype"] = global["Function"];
}

JSPPObject::JSPPObject(JSPPObject (*f)(JSPPObject, JSPPObject, JSPPObject, JSPPObject)) : self(&undefined), write(this), s(new JSPPState) 
{
	s->f = 3; s->f3 = f;
	s->type = JSPP_FUNCTION;
	s->map["prototype"] = global["Function"];
}

JSPPObject::JSPPObject(JSPPObject (*f)(JSPPObject, JSPPObject, JSPPObject, JSPPObject, JSPPObject)) : self(&undefined), write(this), s(new JSPPState) 
{
	s->f = 4; s->f4 = f;
	s->type = JSPP_FUNCTION;
	s->map["prototype"] = global["Function"];
}

JSPPObject::JSPPObject(JSPPObject (*f)(JSPPObject, JSPPObject, JSPPObject, JSPPObject, JSPPObject, JSPPObject)) : self(&undefined), write(this), s(new JSPPState) 
{
	s->f = 5; s->f5 = f;
	s->type = JSPP_FUNCTION;
	s->map["prototype"] = global["Function"];
}



template<typename F> // Function
JSPPObject::JSPPObject(F f) : self(&undefined), write(this), s(new JSPPState) 
{
	set_func(f, &F::operator());
	s->type = JSPP_FUNCTION;
	s->map["prototype"] = global["Function"];
}


JSPPObject::JSPPObject(std::pair<const std::basic_string<char>, JSPPObject> it) : self(&undefined), write(this), s(new JSPPState) {
	s->s = it.first;
	s->type = JSPP_STRING;
}


JSPPObject::JSPPObject(std::vector<JSPPObject> list) : self(&undefined), write(this), s(new JSPPState) {
	int length = 0;

	for (std::vector<JSPPObject>::const_iterator elem = list.begin(); elem != list.end(); ++elem)
	{
		if (elem->s->type == JSPP_KEYVALUE) {
			(*this)[elem->s->kv->key] = elem->s->kv->value;
		} else {
			(*this)[length++] = *elem;
		}
	}

	if (length > 0) {
		(*this)["length"] = length;
		s->type = JSPP_ARRAY;
	} else {
		s->type = JSPP_OBJECT;
	}
}

JSPPObject::JSPPObject(JSPPKeyValue& kv) : self(&undefined), write(this), s(new JSPPState) {
	s->type = JSPP_KEYVALUE;
	s->kv = &kv;
}

JSPPObject New(JSPPObject o) {
	JSPPObject n;

	n.s->type = JSPP_FUNCTION;
	n.s->f = o.s->f;
	n.s->f0 = o.s->f0;
	n.s->f1 = o.s->f1;
	n.s->f2 = o.s->f2;
	n.s->f3 = o.s->f3;
	n.s->f4 = o.s->f4;
	n.s->f5 = o.s->f5;

	n.self = &n;
	n["__proto__"] = o["prototype"];

	return n;
}
