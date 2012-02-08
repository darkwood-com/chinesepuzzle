// Initialize with a dummy value first or it'll go into an infinite loop
global["Function"] = "Function";
global["Function"] = function(var s) {
	throw _("Cannot eval in C++ sorry :(");
};
global["Function"]["prototype"] = {};
global["Function"]["prototype"]["call"] = function (var self, var a, var b, var c, var d) {
	This.self = &self;
	return This(a, b, c, d);
};
var Function = global["Function"];

global["typeof"] = function (JSPPObject o) {
	if (o.s->type == JSPP_NUMBER) {
		return "number";
	}
	if (o.s->type == JSPP_STRING) {
		return "string";
	}
	if (o.s->type == JSPP_UNDEFINED) {
		return "undefined";
	}
	if (o.s->type == JSPP_NULL) {
		return "null";
	}
	if (o.s->type == JSPP_OBJECT) {
		return "object";
	}
	return undefined;
};
var Typeof = global["typeof"];

global["Array"] = function () {
	return {};
};
var Array = global["Array"];
