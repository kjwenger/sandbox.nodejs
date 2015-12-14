#ifndef V8_CPPWRAPPER_H_
#define V8_CPPWRAPPER_H_

#include "v8.h"

namespace v8 {

/**
 * A helperclass to easy use a C++ classe in JavaScript.
 *
 * The following example shows how to use a CppWrapper.
 *
 * We will use the C++ class Point for this example:
 *
 * \code
 * struct Point
* {
*    Point() : x_(0), y_(0) {}
*    Point(int x, int y) : x_(x), y_(y) {}
*
*    int getX() const { return x_; }
*    int getY() const { return y_; }
*    void setX(int value) { x_ = value; }
*    void setY(int value) { y_ = value; }
*    bool isNull() const { return x_ == 0 && y_ == 0; }
*
*    int x_, y_;
* };
 * \endcode
 *
 * First the Javascript functions must be mapped to the C++ functions:
 *
 * \code
  * v8::CppWrapper<Point> point_wrapper;
 * point_wrapper.SetAccessor<int>("x", &Point::getX, &Point::setX);
 * point_wrapper.SetAccessor<int>("y", &Point::getY, &Point::setY);
 * point_wrapper.SetFunction<bool>("isNull", &Point::isNull);
 * \endcode
 *
 * To create new instaces with JavaScript, the global ObjectTemplate
 * has to map it to the wrapper. It is also possible to add instaces to global.
 *
 * \code
  * global->Set(String::New("Point"), point_wrapper.NewFunctionTemplate());
 *
 * Point *p = new Point(10, 20);
 * context->Global()->Set(String::New("p"), point_wrapper.NewInstance(p));
 * \endcode
 */
template <class T> class CppWrapper
{
 class InvokeableBase
 {
 public:
  virtual Handle<Value> Call(T *cpp_object, const Arguments &args) = 0;

 protected:
  template <class S, int index>
  static inline S GetArgument(const Arguments &args)
  {
   return FromV8Value<S>(args[index]);
  }
 };

 class GetAccessorBase
 {
 public:
  virtual Handle<Value> Get(T *cpp_object) const = 0;
 };

 class SetAccessorBase
 {
 public:
  virtual void Set(T *cpp_object, Local<Value> value) const = 0;
 };


 class GetSetAccessors
 {
 public:
  GetSetAccessors(GetAccessorBase *getter, SetAccessorBase *setter)
   : get_accessor(getter), set_accessor(setter) {};

  inline Handle<Value> Get(T *cpp_object) const
  {
   return get_accessor->Get(cpp_object);
  }

  inline void Set(T *cpp_object, Local<Value> value) const
  {
   return set_accessor->Set(cpp_object, value);
  }

 private:
  GetAccessorBase *get_accessor;
  SetAccessorBase *set_accessor;
 };


 template <class S>
 class Getter1 : public GetAccessorBase
 {
 public:
  typedef S (T::*Signature)(void);

  Getter1(Signature getter) : getter_(getter) {}

  virtual Handle<Value> Get(T *cpp_object) const
  {
   return ToV8Value<S>((cpp_object->*getter_)());
  }

 private:
  Signature getter_;
 };

 template <class S>
 class Getter2 : public GetAccessorBase
 {
 public:
  typedef S (T::*Signature)(void) const;

  Getter2(Signature getter) : getter_(getter) {}

  virtual Handle<Value> Get(T *cpp_object) const
  {
   return ToV8Value<S>((cpp_object->*getter_)());
  }

 private:
  Signature getter_;
 };


 template <class S>
 class Setter1 : public SetAccessorBase
 {
 public:
  typedef void (T::*Signature)(S);

  Setter1(Signature setter) : setter_(setter) {}

  virtual void Set(T *cpp_object, Local<Value> value) const
  {
   (cpp_object->*setter_)(FromV8Value<S>(value));
  }

 private:
  Signature setter_;
 };

 template <class S>
 class Setter2 : public SetAccessorBase
 {
 public:
  typedef void (T::*Signature)(const S&);

  Setter2(Signature setter) : setter_(setter) {}

  virtual void Set(T *cpp_object, Local<Value> vale) const
  {
   (cpp_object->*setter_)(FromV8Value<S>(vale));
  }

 private:
  Signature setter_;
 };


 template<class R,
  class S1 = void,
  class S2 = void,
  class S3 = void,
  class S4 = void,
  class S5 = void,
  class S6 = void,
  class S7 = void,
  class S8 = void,
  class S9 = void,
  class S10 = void,
  class S11 = void,
  class S12 = void,
  class S13 = void,
  class S14 = void,
  class S15 = void>
 class Invokeable
 {
  template<class S>
  class Caller : public InvokeableBase
  {
  public:
   Caller(S callback) : callback_(callback) {};

   virtual Handle<Value> Call(T *cpp_object, const Arguments &args)
   {
    return CallCallback<R>(cpp_object, args);
   }

  private:
   template <class R>
   inline Handle<Value> CallCallback(T *cpp_object, const Arguments &args)
   {
    return ToV8Value<R>((cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args),
     GetArgument<S6, 5>(args),
     GetArgument<S7, 6>(args),
     GetArgument<S8, 7>(args),
     GetArgument<S9, 8>(args),
     GetArgument<S10, 9>(args),
     GetArgument<S11, 10>(args),
     GetArgument<S12, 11>(args),
     GetArgument<S13, 12>(args),
     GetArgument<S14, 13>(args),
     GetArgument<S15, 14>(args)));
   }

   template < >
   inline Handle<Value> CallCallback<void>(T *cpp_object, const Arguments &args)
   {
    (cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args),
     GetArgument<S6, 5>(args),
     GetArgument<S7, 6>(args),
     GetArgument<S8, 7>(args),
     GetArgument<S9, 8>(args),
     GetArgument<S10, 9>(args),
     GetArgument<S11, 10>(args),
     GetArgument<S12, 11>(args),
     GetArgument<S13, 12>(args),
     GetArgument<S14, 13>(args),
     GetArgument<S15, 14>(args));
    return Undefined();
   }

   S callback_;
  };

 public:
  typedef R (T::*Signature1)(S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15);
  typedef R (T::*Signature2)(S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15) const;

  template <class S>
  static InvokeableBase *NewInvokeable(S callback)
  {
   return new Caller<S>(callback);
  }
 };


 template<class R,
  class S1,
  class S2,
  class S3,
  class S4,
  class S5,
  class S6,
  class S7,
  class S8,
  class S9,
  class S10,
  class S11,
  class S12,
  class S13,
  class S14>
 class Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14>
 {
  template<class S>
  class Caller : public InvokeableBase
  {
  public:
   Caller(S callback) : callback_(callback) {};

   virtual Handle<Value> Call(T *cpp_object, const Arguments &args)
   {
    return CallCallback<R>(cpp_object, args);
   }

  private:
   template <class R>
   inline Handle<Value> CallCallback(T *cpp_object, const Arguments &args)
   {
    return ToV8Value<R>((cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args),
     GetArgument<S6, 5>(args),
     GetArgument<S7, 6>(args),
     GetArgument<S8, 7>(args),
     GetArgument<S9, 8>(args),
     GetArgument<S10, 9>(args),
     GetArgument<S11, 10>(args),
     GetArgument<S12, 11>(args),
     GetArgument<S13, 12>(args),
     GetArgument<S14, 13>(args)));
   }

   template < >
   inline Handle<Value> CallCallback<void>(T *cpp_object, const Arguments &args)
   {
    (cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args),
     GetArgument<S6, 5>(args),
     GetArgument<S7, 6>(args),
     GetArgument<S8, 7>(args),
     GetArgument<S9, 8>(args),
     GetArgument<S10, 9>(args),
     GetArgument<S11, 10>(args),
     GetArgument<S12, 11>(args),
     GetArgument<S13, 12>(args),
     GetArgument<S14, 13>(args));
    return Undefined();
   }

   S callback_;
  };

 public:
  typedef R (T::*Signature1)(S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14);
  typedef R (T::*Signature2)(S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14) const;

  template <class S>
  static InvokeableBase *NewInvokeable(S callback)
  {
   return new Caller<S>(callback);
  }
 };


 template<class R,
  class S1,
  class S2,
  class S3,
  class S4,
  class S5,
  class S6,
  class S7,
  class S8,
  class S9,
  class S10,
  class S11,
  class S12,
  class S13>
 class Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13>
 {
  template<class S>
  class Caller : public InvokeableBase
  {
  public:
   Caller(S callback) : callback_(callback) {};

   virtual Handle<Value> Call(T *cpp_object, const Arguments &args)
   {
    return CallCallback<R>(cpp_object, args);
   }

  private:
   template <class R>
   inline Handle<Value> CallCallback(T *cpp_object, const Arguments &args)
   {
    return ToV8Value<R>((cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args),
     GetArgument<S6, 5>(args),
     GetArgument<S7, 6>(args),
     GetArgument<S8, 7>(args),
     GetArgument<S9, 8>(args),
     GetArgument<S10, 9>(args),
     GetArgument<S11, 10>(args),
     GetArgument<S12, 11>(args),
     GetArgument<S13, 12>(args)));
   }

   template < >
   inline Handle<Value> CallCallback<void>(T *cpp_object, const Arguments &args)
   {
    (cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args),
     GetArgument<S6, 5>(args),
     GetArgument<S7, 6>(args),
     GetArgument<S8, 7>(args),
     GetArgument<S9, 8>(args),
     GetArgument<S10, 9>(args),
     GetArgument<S11, 10>(args),
     GetArgument<S12, 11>(args),
     GetArgument<S13, 12>(args));
    return Undefined();
   }

   S callback_;
  };

 public:
  typedef R (T::*Signature1)(S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13);
  typedef R (T::*Signature2)(S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13) const;

  template <class S>
  static InvokeableBase *NewInvokeable(S callback)
  {
   return new Caller<S>(callback);
  }
 };


 template<class R,
  class S1,
  class S2,
  class S3,
  class S4,
  class S5,
  class S6,
  class S7,
  class S8,
  class S9,
  class S10,
  class S11,
  class S12>
 class Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12>
 {
  template<class S>
  class Caller : public InvokeableBase
  {
  public:
   Caller(S callback) : callback_(callback) {};

   virtual Handle<Value> Call(T *cpp_object, const Arguments &args)
   {
    return CallCallback<R>(cpp_object, args);
   }

  private:
   template <class R>
   inline Handle<Value> CallCallback(T *cpp_object, const Arguments &args)
   {
    return ToV8Value<R>((cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args),
     GetArgument<S6, 5>(args),
     GetArgument<S7, 6>(args),
     GetArgument<S8, 7>(args),
     GetArgument<S9, 8>(args),
     GetArgument<S10, 9>(args),
     GetArgument<S11, 10>(args),
     GetArgument<S12, 11>(args)));
   }

   template < >
   inline Handle<Value> CallCallback<void>(T *cpp_object, const Arguments &args)
   {
    (cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args),
     GetArgument<S6, 5>(args),
     GetArgument<S7, 6>(args),
     GetArgument<S8, 7>(args),
     GetArgument<S9, 8>(args),
     GetArgument<S10, 9>(args),
     GetArgument<S11, 10>(args),
     GetArgument<S12, 11>(args));
    return Undefined();
   }

   S callback_;
  };

 public:
  typedef R (T::*Signature1)(S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12);
  typedef R (T::*Signature2)(S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12) const;

  template <class S>
  static InvokeableBase *NewInvokeable(S callback)
  {
   return new Caller<S>(callback);
  }
 };


 template<class R,
  class S1,
  class S2,
  class S3,
  class S4,
  class S5,
  class S6,
  class S7,
  class S8,
  class S9,
  class S10,
  class S11>
 class Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11>
 {
  template<class S>
  class Caller : public InvokeableBase
  {
  public:
   Caller(S callback) : callback_(callback) {};

   virtual Handle<Value> Call(T *cpp_object, const Arguments &args)
   {
    return CallCallback<R>(cpp_object, args);
   }

  private:
   template <class R>
   inline Handle<Value> CallCallback(T *cpp_object, const Arguments &args)
   {
    return ToV8Value<R>((cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args),
     GetArgument<S6, 5>(args),
     GetArgument<S7, 6>(args),
     GetArgument<S8, 7>(args),
     GetArgument<S9, 8>(args),
     GetArgument<S10, 9>(args),
     GetArgument<S11, 10>(args)));
   }

   template < >
   inline Handle<Value> CallCallback<void>(T *cpp_object, const Arguments &args)
   {
    (cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args),
     GetArgument<S6, 5>(args),
     GetArgument<S7, 6>(args),
     GetArgument<S8, 7>(args),
     GetArgument<S9, 8>(args),
     GetArgument<S10, 9>(args),
     GetArgument<S11, 10>(args));
    return Undefined();
   }

   S callback_;
  };

 public:
  typedef R (T::*Signature1)(S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11);
  typedef R (T::*Signature2)(S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11) const;

  template <class S>
  static InvokeableBase *NewInvokeable(S callback)
  {
   return new Caller<S>(callback);
  }
 };


 template<class R,
  class S1,
  class S2,
  class S3,
  class S4,
  class S5,
  class S6,
  class S7,
  class S8,
  class S9,
  class S10>
 class Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10>
 {
  template<class S>
  class Caller : public InvokeableBase
  {
  public:
   Caller(S callback) : callback_(callback) {};

   virtual Handle<Value> Call(T *cpp_object, const Arguments &args)
   {
    return CallCallback<R>(cpp_object, args);
   }

  private:
   template <class R>
   inline Handle<Value> CallCallback(T *cpp_object, const Arguments &args)
   {
    return ToV8Value<R>((cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args),
     GetArgument<S6, 5>(args),
     GetArgument<S7, 6>(args),
     GetArgument<S8, 7>(args),
     GetArgument<S9, 8>(args),
     GetArgument<S10, 9>(args)));
   }

   template < >
   inline Handle<Value> CallCallback<void>(T *cpp_object, const Arguments &args)
   {
    (cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args),
     GetArgument<S6, 5>(args),
     GetArgument<S7, 6>(args),
     GetArgument<S8, 7>(args),
     GetArgument<S9, 8>(args),
     GetArgument<S10, 9>(args));
    return Undefined();
   }

   S callback_;
  };

 public:
  typedef R (T::*Signature1)(S1, S2, S3, S4, S5, S6, S7, S8, S9, S10);
  typedef R (T::*Signature2)(S1, S2, S3, S4, S5, S6, S7, S8, S9, S10) const;

  template <class S>
  static InvokeableBase *NewInvokeable(S callback)
  {
   return new Caller<S>(callback);
  }
 };


 template<class R,
  class S1,
  class S2,
  class S3,
  class S4,
  class S5,
  class S6,
  class S7,
  class S8,
  class S9>
 class Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9>
 {
  template<class S>
  class Caller : public InvokeableBase
  {
  public:
   Caller(S callback) : callback_(callback) {};

   virtual Handle<Value> Call(T *cpp_object, const Arguments &args)
   {
    return CallCallback<R>(cpp_object, args);
   }

  private:
   template <class R>
   inline Handle<Value> CallCallback(T *cpp_object, const Arguments &args)
   {
    return ToV8Value<R>((cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args),
     GetArgument<S6, 5>(args),
     GetArgument<S7, 6>(args),
     GetArgument<S8, 7>(args),
     GetArgument<S9, 8>(args)));
   }

   template < >
   inline Handle<Value> CallCallback<void>(T *cpp_object, const Arguments &args)
   {
    (cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args),
     GetArgument<S6, 5>(args),
     GetArgument<S7, 6>(args),
     GetArgument<S8, 7>(args),
     GetArgument<S9, 8>(args));
    return Undefined();
   }

   S callback_;
  };

 public:
  typedef R (T::*Signature1)(S1, S2, S3, S4, S5, S6, S7, S8, S9);
  typedef R (T::*Signature2)(S1, S2, S3, S4, S5, S6, S7, S8, S9) const;

  template <class S>
  static InvokeableBase *NewInvokeable(S callback)
  {
   return new Caller<S>(callback);
  }
 };


 template<class R,
  class S1,
  class S2,
  class S3,
  class S4,
  class S5,
  class S6,
  class S7,
  class S8>
 class Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8>
 {
  template<class S>
  class Caller : public InvokeableBase
  {
  public:
   Caller(S callback) : callback_(callback) {};

   virtual Handle<Value> Call(T *cpp_object, const Arguments &args)
   {
    return CallCallback<R>(cpp_object, args);
   }

  private:
   template <class R>
   inline Handle<Value> CallCallback(T *cpp_object, const Arguments &args)
   {
    return ToV8Value<R>((cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args),
     GetArgument<S6, 5>(args),
     GetArgument<S7, 6>(args),
     GetArgument<S8, 7>(args)));
   }

   template < >
   inline Handle<Value> CallCallback<void>(T *cpp_object, const Arguments &args)
   {
    (cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args),
     GetArgument<S6, 5>(args),
     GetArgument<S7, 6>(args),
     GetArgument<S8, 7>(args));
    return Undefined();
   }

   S callback_;
  };

 public:
  typedef R (T::*Signature1)(S1, S2, S3, S4, S5, S6, S7, S8);
  typedef R (T::*Signature2)(S1, S2, S3, S4, S5, S6, S7, S8) const;

  template <class S>
  static InvokeableBase *NewInvokeable(S callback)
  {
   return new Caller<S>(callback);
  }
 };


 template<class R,
  class S1,
  class S2,
  class S3,
  class S4,
  class S5,
  class S6,
  class S7>
 class Invokeable<R, S1, S2, S3, S4, S5, S6, S7>
 {
  template<class S>
  class Caller : public InvokeableBase
  {
  public:
   Caller(S callback) : callback_(callback) {};

   virtual Handle<Value> Call(T *cpp_object, const Arguments &args)
   {
    return CallCallback<R>(cpp_object, args);
   }

  private:
   template <class R>
   inline Handle<Value> CallCallback(T *cpp_object, const Arguments &args)
   {
    return ToV8Value<R>((cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args),
     GetArgument<S6, 5>(args),
     GetArgument<S7, 6>(args)));
   }

   template < >
   inline Handle<Value> CallCallback<void>(T *cpp_object, const Arguments &args)
   {
    (cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args),
     GetArgument<S6, 5>(args),
     GetArgument<S7, 6>(args));
    return Undefined();
   }

   S callback_;
  };

 public:
  typedef R (T::*Signature1)(S1, S2, S3, S4, S5, S6, S7);
  typedef R (T::*Signature2)(S1, S2, S3, S4, S5, S6, S7) const;

  template <class S>
  static InvokeableBase *NewInvokeable(S callback)
  {
   return new Caller<S>(callback);
  }
 };


 template<class R,
  class S1,
  class S2,
  class S3,
  class S4,
  class S5,
  class S6>
 class Invokeable<R, S1, S2, S3, S4, S5, S6>
 {
  template<class S>
  class Caller : public InvokeableBase
  {
  public:
   Caller(S callback) : callback_(callback) {};

   virtual Handle<Value> Call(T *cpp_object, const Arguments &args)
   {
    return CallCallback<R>(cpp_object, args);
   }

  private:
   template <class R>
   inline Handle<Value> CallCallback(T *cpp_object, const Arguments &args)
   {
    return ToV8Value<R>((cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args),
     GetArgument<S6, 5>(args)));
   }

   template < >
   inline Handle<Value> CallCallback<void>(T *cpp_object, const Arguments &args)
   {
    (cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args),
     GetArgument<S6, 5>(args));
    return Undefined();
   }

   S callback_;
  };

 public:
  typedef R (T::*Signature1)(S1, S2, S3, S4, S5, S6);
  typedef R (T::*Signature2)(S1, S2, S3, S4, S5, S6) const;

  template <class S>
  static InvokeableBase *NewInvokeable(S callback)
  {
   return new Caller<S>(callback);
  }
 };


 template<class R,
  class S1,
  class S2,
  class S3,
  class S4,
  class S5>
 class Invokeable<R, S1, S2, S3, S4, S5>
 {
  template<class S>
  class Caller : public InvokeableBase
  {
  public:
   Caller(S callback) : callback_(callback) {};

   virtual Handle<Value> Call(T *cpp_object, const Arguments &args)
   {
    return CallCallback<R>(cpp_object, args);
   }

  private:
   template <class R>
   inline Handle<Value> CallCallback(T *cpp_object, const Arguments &args)
   {
    return ToV8Value<R>((cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args)));
   }

   template < >
   inline Handle<Value> CallCallback<void>(T *cpp_object, const Arguments &args)
   {
    (cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args),
     GetArgument<S5, 4>(args));
    return Undefined();
   }

   S callback_;
  };

 public:
  typedef R (T::*Signature1)(S1, S2, S3, S4, S5);
  typedef R (T::*Signature2)(S1, S2, S3, S4, S5) const;

  template <class S>
  static InvokeableBase *NewInvokeable(S callback)
  {
   return new Caller<S>(callback);
  }
 };


 template<class R,
  class S1,
  class S2,
  class S3,
  class S4>
 class Invokeable<R, S1, S2, S3, S4>
 {
  template<class S>
  class Caller : public InvokeableBase
  {
  public:
   Caller(S callback) : callback_(callback) {};

   virtual Handle<Value> Call(T *cpp_object, const Arguments &args)
   {
    return CallCallback<R>(cpp_object, args);
   }

  private:
   template <class R>
   inline Handle<Value> CallCallback(T *cpp_object, const Arguments &args)
   {
    return ToV8Value<R>((cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args)));
   }

   template < >
   inline Handle<Value> CallCallback<void>(T *cpp_object, const Arguments &args)
   {
    (cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args),
     GetArgument<S4, 3>(args));
    return Undefined();
   }

   S callback_;
  };

 public:
  typedef R (T::*Signature1)(S1, S2, S3, S4);
  typedef R (T::*Signature2)(S1, S2, S3, S4) const;

  template <class S>
  static InvokeableBase *NewInvokeable(S callback)
  {
   return new Caller<S>(callback);
  }
 };


 template<class R,
  class S1,
  class S2,
  class S3>
 class Invokeable<R, S1, S2, S3>
 {
  template<class S>
  class Caller : public InvokeableBase
  {
  public:
   Caller(S callback) : callback_(callback) {};

   virtual Handle<Value> Call(T *cpp_object, const Arguments &args)
   {
    return CallCallback<R>(cpp_object, args);
   }

  private:
   template <class R>
   inline Handle<Value> CallCallback(T *cpp_object, const Arguments &args)
   {
    return ToV8Value<R>((cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args)));
   }

   template < >
   inline Handle<Value> CallCallback<void>(T *cpp_object, const Arguments &args)
   {
    (cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args),
     GetArgument<S3, 2>(args));
    return Undefined();
   }

   S callback_;
  };

 public:
  typedef R (T::*Signature1)(S1, S2, S3);
  typedef R (T::*Signature2)(S1, S2, S3) const;

  template <class S>
  static InvokeableBase *NewInvokeable(S callback)
  {
   return new Caller<S>(callback);
  }
 };


 template<class R,
  class S1,
  class S2>
 class Invokeable<R, S1, S2>
 {
  template<class S>
  class Caller : public InvokeableBase
  {
  public:
   Caller(S callback) : callback_(callback) {};

   virtual Handle<Value> Call(T *cpp_object, const Arguments &args)
   {
    return CallCallback<R>(cpp_object, args);
   }

  private:
   template <class R>
   inline Handle<Value> CallCallback(T *cpp_object, const Arguments &args)
   {
    return ToV8Value<R>((cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args)));
   }

   template < >
   inline Handle<Value> CallCallback<void>(T *cpp_object, const Arguments &args)
   {
    (cpp_object->*callback_)(
     GetArgument<S1, 0>(args),
     GetArgument<S2, 1>(args));
    return Undefined();
   }

   S callback_;
  };

 public:
  typedef R (T::*Signature1)(S1, S2);
  typedef R (T::*Signature2)(S1, S2) const;

  template <class S>
  static InvokeableBase *NewInvokeable(S callback)
  {
   return new Caller<S>(callback);
  }
 };


 template<class R,
  class S1>
 class Invokeable<R, S1>
 {
  template<class S>
  class Caller : public InvokeableBase
  {
  public:
   Caller(S callback) : callback_(callback) {};

   virtual Handle<Value> Call(T *cpp_object, const Arguments &args)
   {
    return CallCallback<R>(cpp_object, args);
   }

  private:
   template <class R>
   inline Handle<Value> CallCallback(T *cpp_object, const Arguments &args)
   {
    return ToV8Value<R>((cpp_object->*callback_)(
     GetArgument<S1, 0>(args)));
   }

   template < >
   inline Handle<Value> CallCallback<void>(T *cpp_object, const Arguments &args)
   {
    (cpp_object->*callback_)(
     GetArgument<S1, 0>(args));
    return Undefined();
   }

   S callback_;
  };

 public:
  typedef R (T::*Signature1)(S1);
  typedef R (T::*Signature2)(S1) const;

  template <class S>
  static InvokeableBase *NewInvokeable(S callback)
  {
   return new Caller<S>(callback);
  }
 };


 template<class R>
 class Invokeable<R>
 {
  template<class S>
  class Caller : public InvokeableBase
  {
  public:
   Caller(S callback) : callback_(callback) {};

   virtual Handle<Value> Call(T *cpp_object, const Arguments &args)
   {
    return internalCall<R>(cpp_object, args);
   }

   template <class R>
   inline Handle<Value> internalCall(T *cpp_object, const Arguments&)
   {
    return ToV8Value<R>((cpp_object->*callback_)());
   }

   template < >
   inline Handle<Value> internalCall<void>(T *cpp_object, const Arguments&)
   {
    (cpp_object->*callback_)();
    return Undefined();
   }

  private:
   S callback_;
  };

 public:
  typedef R (T::*Signature1)();
  typedef R (T::*Signature2)() const;

  template <class S>
  static InvokeableBase *NewInvokeable(S callback)
  {
   return new Caller<S>(callback);
  }
 };


 template <class S>
 static void WeakExternalReferenceCallback(Persistent<Object>, void *parameter)
 {
  if (S *cpp_object = static_cast<S*>(parameter))
   delete cpp_object;
 }

 template <class S>
 static Persistent<External> NewWeakExternal(S* parameter)
 {
  Persistent<External> ret = Persistent<External>::New(External::New(parameter));
  ret.MakeWeak(parameter, WeakExternalReferenceCallback<S>);
  return ret;
 }

 template<class S>
 static inline S UnwrapExternal(Handle<Value> value)
 {
  return static_cast<S>(External::Cast(*value)->Value());
 }

 static inline T* UnwrapCppObject(const AccessorInfo &info)
 {
  return UnwrapExternal<T*>(info.This()->GetInternalField(0));
 }

 static inline GetSetAccessors *UnwrapGetSetAccessors(const AccessorInfo &info)
 {
  return UnwrapExternal<GetSetAccessors*>(info.Data());
 }


 static Handle<Value> PrototypeAccessorGetter(Local<String>, const AccessorInfo &info)
 {
  T* cpp_object = UnwrapCppObject(info);
  GetSetAccessors *accessors = UnwrapGetSetAccessors(info);
  return accessors->Get(cpp_object);
 }

 static void PrototypeAccessorSetter(Local<String>, Local<Value> value, const AccessorInfo& info)
 {
  T* cpp_object = UnwrapCppObject(info);
  GetSetAccessors *accessors = UnwrapGetSetAccessors(info);
  return accessors->Set(cpp_object, value);
 }

 static Handle<Value> PrototypeInvocationCallback(const Arguments &args)
 {
  T* cpp_object = UnwrapExternal<T*>(args.Holder()->GetInternalField(0));
  InvokeableBase *invokaeable = UnwrapExternal<InvokeableBase*>(args.Data());
  return invokaeable->Call(cpp_object, args);
 }


 template <class S>
 inline void SetPrototypeAccessor(const char *name, GetAccessorBase *getter, SetAccessorBase *setter = 0)
 {
  template_->PrototypeTemplate()->SetAccessor(String::New(name), PrototypeAccessorGetter, PrototypeAccessorSetter,
   NewWeakExternal(new GetSetAccessors(getter, setter)));
 }

 template <class R>
 inline void SetPrototypeFunction(const char *name, InvokeableBase *parameter)
 {
  template_->PrototypeTemplate()->Set(String::New(name), FunctionTemplate::New(PrototypeInvocationCallback, NewWeakExternal(parameter)));
 }

 typedef T* (*NewFunction)(const Arguments& args);

 static Handle<Value> FunctionInvocationCallback(const Arguments &args)
 {
  if (!args.IsConstructCall())
   return Undefined();

  NewFunction newFunction = UnwrapExternal<NewFunction>(args.Data());

  T *cpp_object = newFunction(args);

  if (!cpp_object)
   return ThrowException(String::New("Can not create Object in C++"));

  args.Holder()->SetInternalField(0, NewWeakExternal(cpp_object));

  return Undefined();
 }

 static T *DefaultNewFunction(const Arguments &)
 {
  return new T();
 }

 Handle<FunctionTemplate> template_;

public:
 CppWrapper(NewFunction newFunction = DefaultNewFunction)
 {
  template_ = FunctionTemplate::New(&FunctionInvocationCallback, External::New(newFunction));
  template_->InstanceTemplate()->SetInternalFieldCount(1);
 }

 inline Handle<FunctionTemplate> NewFunctionTemplate() { return template_; }

 Local<Object> NewInstance(T *pObject, bool make_weak = true)
 {
  Local<Object> ret = template_->InstanceTemplate()->NewInstance();

  Handle<Value> internalField;

  if (make_weak)
   internalField = NewWeakExternal(pObject);
  else
   internalField = External::New(pObject);

  ret->SetInternalField(0, internalField);

  return ret;
 }


 template <class S>
 inline void SetAccessor(const char *name, typename Getter1<S>::Signature getter, typename Setter1<S>::Signature setter)
 {
  SetPrototypeAccessor<S>(name, new Getter1<S>(getter), new Setter1<S>(setter));
 }

 template <class S>
 inline void SetAccessor(const char *name, typename Getter1<S>::Signature getter, typename Setter2<S>::Signature setter)
 {
  SetPrototypeAccessor<S>(name, new Getter1<S>(getter), new Setter2<S>(setter));
 }

 template <class S>
 inline void SetAccessor(const char *name, typename Getter2<S>::Signature getter, typename Setter1<S>::Signature setter)
 {
  SetPrototypeAccessor<S>(name, new Getter2<S>(getter), new Setter1<S>(setter));
 }

 template <class S>
 inline void SetAccessor(const char *name, typename Getter2<S>::Signature getter, typename Setter2<S>::Signature setter)
 {
  SetPrototypeAccessor<S>(name, new Getter2<S>(getter), new Setter2<S>(setter));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5, class S6, class S7, class S8, class S9, class S10,
  class S11, class S12, class S13, class S14, class S15>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15>::Signature1 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5, class S6, class S7, class S8, class S9, class S10,
  class S11, class S12, class S13, class S14, class S15>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15>::Signature2 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14, S15>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5, class S6, class S7, class S8, class S9, class S10,
  class S11, class S12, class S13, class S14>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14>::Signature1 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5, class S6, class S7, class S8, class S9, class S10,
  class S11, class S12, class S13, class S14>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14>::Signature2 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13, S14>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5, class S6, class S7, class S8, class S9, class S10,
  class S11, class S12, class S13>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13>::Signature1 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5, class S6, class S7, class S8, class S9, class S10,
  class S11, class S12, class S13>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13>::Signature2 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12, S13>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5, class S6, class S7, class S8, class S9, class S10,
  class S11, class S12>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12>::Signature1 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5, class S6, class S7, class S8, class S9, class S10,
  class S11, class S12>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12>::Signature2 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, S12>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5, class S6, class S7, class S8, class S9, class S10,
  class S11>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11>::Signature1 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5, class S6, class S7, class S8, class S9, class S10,
  class S11>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11>::Signature2 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5, class S6, class S7, class S8, class S9, class S10>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10>::Signature1 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5, class S6, class S7, class S8, class S9, class S10>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10>::Signature2 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5, class S6, class S7, class S8, class S9>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9>::Signature1 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5, class S6, class S7, class S8, class S9>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9>::Signature2 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8, S9>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5, class S6, class S7, class S8>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8>::Signature1 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5, class S6, class S7, class S8>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8>::Signature2 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5, S6, S7, S8>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5, class S6, class S7>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5, S6, S7>::Signature1 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5, S6, S7>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5, class S6, class S7>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5, S6, S7>::Signature2 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5, S6, S7>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5, class S6>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5, S6>::Signature1 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5, S6>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5, class S6>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5, S6>::Signature2 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5, S6>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5>::Signature1 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4, class S5>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4, S5>::Signature2 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4, S5>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4>::Signature1 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3, class S4>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3, S4>::Signature2 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3, S4>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3>::Signature1 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2, class S3>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2, S3>::Signature2 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2, S3>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2>::Signature1 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2>::NewInvokeable(callback));
 }

 template <class R, class S1, class S2>
 inline void SetFunction(const char *name, typename Invokeable<R, S1, S2>::Signature2 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1, S2>::NewInvokeable(callback));
 }

 template <class R, class S1>
 inline void SetFunction(const char *name, typename Invokeable<R, S1>::Signature1 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1>::NewInvokeable(callback));
 }

 template <class R, class S1>
 inline void SetFunction(const char *name, typename Invokeable<R, S1>::Signature2 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R, S1>::NewInvokeable(callback));
 }

 template <class R>
 inline void SetFunction(const char *name, typename Invokeable<R>::Signature1 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R>::NewInvokeable(callback));
 }

 template <class R>
 inline void SetFunction(const char *name, typename Invokeable<R>::Signature2 callback)
 {
  SetPrototypeFunction<R>(name, Invokeable<R>::NewInvokeable(callback));
 }


 template <class S>
 static Handle<Value> ToV8Value(S value) { }

 template <class S>
 static S FromV8Value(Local<Value> value) { }



 template < >
 static Handle<Value> ToV8Value<bool>(bool value)
 {
  return Boolean::New(value);
 }

 template < >
 static Handle<Value> ToV8Value<double>(double value)
 {
  return Number::New(value);
 }

 template < >
 static Handle<Value> ToV8Value<int32_t>(int32_t value)
 {
  return Integer::New(value);
 }

 template < >
 static Handle<Value> ToV8Value<const char*>(const char *value)
 {
  return String::New(value);
 }

 template < >
 static Handle<Value> ToV8Value<const uint16_t*>(const uint16_t *value)
 {
  return String::New(value);
 }


 template < >
 static bool FromV8Value<bool>(Local<Value> value)
 {
  return value->BooleanValue();
 }

 template < >
 static double FromV8Value<double>(Local<Value> value)
 {
  return value->NumberValue();
 }

 template < >
 static int32_t FromV8Value<int32_t>(Local<Value> value)
 {
  return value->Int32Value();
 }

 template < >
 static uint32_t FromV8Value<uint32_t>(Local<Value> value)
 {
  return value->Uint32Value();
 }

 template < >
 static int64_t FromV8Value<int64_t>(Local<Value> value)
 {
  return value->IntegerValue();
 }
};

}  // namespace v8

#endif  // V8_CPPWRAPPER_H_