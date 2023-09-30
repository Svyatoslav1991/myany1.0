# myany1.0

`MyAny` is a C++ class that provides a mechanism to store and retrieve data of different types in a safe and type-aware manner. It can be useful in situations where you need to store values of various types in a single container.

## Features

- Supports storing data of different types in a single object.
- Safely extracts data with type checking.
- Utilizes RAII semantics (resource acquisition is initialization) for efficient resource management.
- Easily extendable and can store user-defined data types.

## Usage Example

MyAny value = 42;

if (value.isType<int>())
{
    int intValue = value.cast<int>();
    // Now you can work with intValue as an int.
}
else
{
    // Data type doesn't match.
}

API
Constructors
MyAny(): Default constructor, creates an empty MyAny object.
template <typename T> MyAny(const T& value): Constructor that initializes the MyAny object with a value of type T.

Methods
template<typename T> T cast() const: Retrieves the stored value, assuming type T. Throws a std::bad_cast exception if the types do not match.
template <typename T> bool isType() const: Checks if the type of the stored value matches the type T.

Notes
To use this class, you'll need the standard C++ library.
MyAny does not support polymorphic types (e.g., pointers to base classes).

License
This project is licensed under the MIT License - see the LICENSE file for details.
