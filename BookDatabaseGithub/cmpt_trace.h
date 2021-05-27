// cmpt_trace.h

// By defining CMPT_TRACE_H, we avoid problems caused by including this file
// more than once: if CMPT_TRACE_H is already defined, then the code is *not*
// included.
#ifndef CMPT_TRACE_H
#define CMPT_TRACE_H

#include <iostream>
#include <string>

namespace cmpt {

////////////////////////////////////////////////////////////////////////////////
//
// Trace is a helper class meant to be used in functions as a simple debugging
// aid. When you put a Trace object at the start of a function, it will cause
// a message to be printed when the function is called, and also when the
// function ends. For example:
//
//    int fib(int n) {
//       cmpt::Trace trace("fib(" + to_string(n) + ")");
//       if (n == 0) return 1;       // base case 1
//       if (n == 1) return 1;       // base case 2
//       return fib(n-1) + fib(n-2); // recursive case
//     }
//
// The messages are indented according to how many times the function has been
// called, and the results can be useful (i.e. you get an idea of stack usage
// and the order in which functions are called).
//
////////////////////////////////////////////////////////////////////////////////

using namespace std;

enum class color {
    red, green, yellow, cyan, magenta, reset
};

string to_str(color c) {
    switch (c) {
        case color::red: return "\033[0;31m";
        case color::green: return "\033[1;32m";
        case color::yellow: return "\033[1;33m";
        case color::cyan: return "\033[0;36m";
        case color::magenta: return "\033[0;35m";
        case color::reset: return "\033[0m";
        default: return "\033[0m";
    }
}

class Trace {
private:
    static int indent; // current level of indentation; shared by all trace objects 

    void print(const string& s) const {
        if (colored_output) cout << to_str(msg_color);
        cout << s;
        if (colored_output) cout << to_str(color::reset);
    }

public:
    const string start_msg; // message to print when function entered
    const string end_msg;   // message to print when function exited

    static int indent_incr; // indent increment, i.e. amount to indent/dedent messages

    static bool colored_output;
    static color msg_color;

    Trace(const string& start_msg, const string& end_msg) 
    : start_msg(start_msg), end_msg(end_msg)
    {
        print(string(indent, ' ') + start_msg + " ...\n");
        indent += indent_incr;
    }

    Trace(const string& msg) 
    : Trace{msg, msg}
    { }

    ~Trace() {
        indent -= indent_incr;
        print(string(indent, ' ') + "... " + end_msg + "\n");
    }
}; // class Trace

//
// static variables are initialized outside their class
//
int Trace::indent_incr = 3;
int Trace::indent = 0;

bool Trace::colored_output = true;
color Trace::msg_color = color::red;

} // namespace cmpt

#endif
