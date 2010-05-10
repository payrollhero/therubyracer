#ifndef _THE_RUBY_RACER_
#define _THE_RUBY_RACER_ 

#include <ruby.h>

#define rr_define_method(klass, name, impl, argc) rb_define_method(klass, name, (VALUE(*)(...))impl, argc)
#define rr_define_singleton_method(object, name, impl, argc) rb_define_singleton_method(object, name, (VALUE(*)(...))impl, argc)

VALUE rr_define_class(const char *name, VALUE superclass = rb_cObject);
VALUE rr_str_to_perl_case(VALUE str);
VALUE rr_str_to_camel_case(VALUE str);

#endif