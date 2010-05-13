#include "v8_obj.h"
#include "v8_ref.h"
#include "v8_value.h"
#include "converters.h"

using namespace v8;

#include <cstdio>

VALUE rr_cV8_C_Object;

void rr_init_obj() {
  rr_cV8_C_Object = rr_define_class("Object", rr_cV8_C_Value);
  rr_define_singleton_method(rr_cV8_C_Object, "new", v8_Object_New, 0);
  rr_define_method(rr_cV8_C_Object, "Get", v8_Object_Get, 1);
  rr_define_method(rr_cV8_C_Object, "Set", v8_Object_Set, 2);
  rr_define_method(rr_cV8_C_Object, "GetPropertyNames", v8_Object_GetPropertyNames, 0);
  rr_define_method(rr_cV8_C_Object, "ToString", v8_Object_ToString, 0);
  rr_define_method(rr_cV8_C_Object, "context", v8_Object_context, 0);  
}

VALUE rr_reflect_v8_object(Handle<Value> value) {
  Local<Object> o = Object::Cast(*value);
  return V8_Ref_Create(rr_cV8_C_Object, o);
}

namespace {
  Local<Object> unwrap(VALUE robj) {
    return V8_Ref_Get<Object>(robj);
  }
}

VALUE v8_Object_New(VALUE clazz) {
  HandleScope handles;
  return V8_Ref_Create(clazz, Object::New());
}

VALUE v8_Object_Get(VALUE self, VALUE key) {
  HandleScope handles;  
  Local<Object> obj = unwrap(self);
  VALUE keystr = rb_str_to_str(key);
  Local<Value> value = obj->Get(RB2V8(keystr));
  return V82RB(value);
}

VALUE v8_Object_Set(VALUE self, VALUE key, VALUE value) {
  HandleScope handles;
  Local<Object> obj = unwrap(self);

  VALUE keystr = rb_funcall(key, rb_intern("to_s"), 0);
  obj->Set(RB2V8(keystr), RB2V8(value));
  return Qnil;
}

VALUE v8_Object_GetPropertyNames(VALUE self) {
  HandleScope handles;
  Local<Object> object = unwrap(self);  
  Local<Value> names = object->GetPropertyNames();
  return V82RB(names);
}

VALUE v8_Object_context(VALUE self) {
  HandleScope handles;
  Local<Object> object = unwrap(self);
  Local<Value> cxt = object->GetHiddenValue(String::New("TheRubyRacer::Context"));
  return cxt.IsEmpty() ? Qnil : (VALUE)External::Unwrap(cxt);
}

VALUE v8_Object_ToString(VALUE self) {
  HandleScope handles;
  Local<Object> object = unwrap(self);
  Local<Value> string = object->ToString();
  return V82RB(string);
}