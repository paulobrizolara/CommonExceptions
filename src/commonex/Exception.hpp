/*
 * Exception.hpp
 *
 *  Created on: 10/10/2014
 *      Author: noface
 */

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <string>

namespace commonex {

class Exception : public std::exception{
private:
	std::string cause;
    std::string message;
public:
    Exception(const std::string & cause)
    : cause(cause)
    , message(std::string())
    {}

    Exception(const std::string & className, const std::string & message)
    : cause(generateMessage(className, message))
    , message(message)
    {}

    Exception(const std::string & className, const std::string & message, const std::exception & cause)
    : cause(generateMessage(className, message, &cause))
    , message(message)
    {}

    virtual ~Exception() throw() {}

    virtual const char* what() const throw(){
        return cause.c_str();
    }
    /** Return the message used to create this exception*/
    virtual const std::string & getMessage() const
    {
        return message;
    }

protected:
    static std::string generateMessage(const std::string & className
    , const std::string & message, const std::exception * cause=NULL)
    {
        std::string errMessage;
        if(!className.empty()){
            errMessage.append(className).append(": \t");
        }
        errMessage.append(message);

        if(cause != NULL && cause->what() != NULL){
            errMessage.append("\n");
            errMessage.append("Caused By:\n\t").append(cause->what());
        }

        return errMessage;
    }
};

#define COMMONEX_SUBCLASS(ClassName, SuperClass) \
class ClassName : public SuperClass{\
public:\
    ClassName(const std::string & message="")\
        : SuperClass(#ClassName, message) \
    {}\
    ClassName(const std::string & message, const std::exception & cause)\
        : SuperClass(#ClassName, message, cause) \
    {}\
\
protected:\
    ClassName(const std::string & className, const std::string & message)\
        : SuperClass(className, message) \
    {}\
    ClassName(const std::string & className, const std::string & message, const std::exception & cause)\
        : SuperClass(className, message, cause) \
    {}\
}

#define COMMONEX_CLASS(ClassName) COMMONEX_SUBCLASS(ClassName, ::commonex::Exception)

#define COMMON_EXC_toString(x) #x
#define COMMON_EXC_toString_(x) COMMON_EXC_toString(x)
#define COMMON_EXC__STRLINE__ COMMON_EXC_toString_(__LINE__)
#define COMMONEX_HERE __FILE__ "::" COMMON_EXC__STRLINE__

} /* namespace CommonExceptions */

#endif /* EXCEPTION_HPP_ */
