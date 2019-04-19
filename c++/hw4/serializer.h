#include<iostream>
#include <sstream>
#include <limits>

#pragma once

enum class Error{
    NoError,
    CorruptedArchive
};

class Serializer{
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out = std::cout):
        out_(out){}

    template<class T>
    Error save(T& object){
        return object.serialize(*this);
    }

    template<class... Args>
    Error operator()(Args&&... args){
        return process(std::forward<Args>(args)...);
    }

private:
    // process èñïîëüçóåò variadic templates

    std::ostream& out_;

    template <class T, class... Args>
    Error process(T&& val, Args&&... args){
        if(process(std::forward<T>(val)) == Error::CorruptedArchive) return Error::CorruptedArchive;
        return process(std::forward<Args>(args)...);
    }

    Error process(bool& value){
        if (value == true)
            out_ << "true" << Separator;
        else if (value == false)
            out_ << "false" << Separator;
        
        return Error::NoError;
    }

    Error process(uint64_t& value){
        out_ << value << Separator;
        return Error::NoError;
    }
    
    template <class T>
    Error process(T&& value){
        return Error::CorruptedArchive; //wrong argumen to read
    }

};

class Deserializer{
    std::istream& in_;
public:
    explicit Deserializer(std::istream& in = std::cin):
        in_(in){}

    template<class T>
    Error load(T& object){
        return object.serialize(*this);
    }

    template<class... Args>
    Error operator()(Args&&... args){
        return process(std::forward<Args>(args)...);
    }

private:

    template <class T, class... Args>
    Error process(T&& val, Args&&... args){
        if(process(std::forward<T>(val)) == Error::CorruptedArchive) return Error::CorruptedArchive;
        return process(std::forward<Args>(args)...);
    }

    Error process(bool& value){
        std::string text;
        in_ >> text;

        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else
            return Error::CorruptedArchive;
        return Error::NoError;
    }

    Error process(uint64_t& value){
        std::string text;
        in_ >> text;

        if (text[0] >= '0' && text[0] <= '9') value = std::stoull(text);
        else return Error::CorruptedArchive;
        return Error::NoError;
    }

};


//====================================================

