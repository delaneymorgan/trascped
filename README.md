# trascped
A C++ header-only utility for tracing code execution at runtime, using scoped pointers for exception safety.

Can't picture the calling sequence in a program?
Insert TRACE() instructions at the top of the functions/methods
in question and see the calling sequence explicitly displayed on stdout.

```
void SomeFunction() {
    TRACE();
    // pre-existing code
}
```

When the function is entered, and when it is left,
a message will be displayed on stdout.

If you need to check some values, use TRACE_CHECK():

```
void SomeFunction() {
    TRACE();
    // pre-existing code
    int value = 12345;
    TRACE_CHECK( "value: %d", value);
}
```

...using old-fashioned C printf behaviour.
