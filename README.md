# pimpl_idiom

"Pointer to implementation" is a C++ programming technique that removes implementation details of a class from its object
representation by placing them in a separate class, accessed through an opaque pointer.

## Explanation
Because private data members of a class participate in its object representation, affecting size and layout, and because 
private member functions of a class participate in overload resolution (which takes place before member access checking),
any change to those implementation details requires recompilation of all users of the class. pImpl breaks this compilation dependency;
changes to the implementation do not cause recompilation. Consequently, if a library uses pImpl in its ABI, newer versions
of the library may change the implementation while remaining ABI-compatible with older versions.

## Trade-offs
The alternatives to the pImpl idiom are

* inline implementation: private members and public members are members of the same class
* pure abstract class (OOP factory): users obtain a unique pointer to a lightweight or abstract base class, 
  the implementation details are in the derived class that overrides its virtual member functions

## Runtime overhead
* Access overhead: In pImpl, each call to a private member function indirects through a pointer. Each access to a public member made by a private member indirects through another pointer. Both indirections cross translation unit boundaries and so can only be optimized out by link-time optimization. Note that OO factory requires indirection across translation units to access both public data and implementation detail, and offers even fewer opportunities for the link time optimizer due to virtual dispatch.
* Space overhead: pImpl adds one pointer to the public component and, if any private member needs access to a public member, another pointer is either added to the implementation component or passed as a parameter for each call to the private member that requires it. If stateful custom allocators are supported, the allocator instance also has to be stored.
* Lifetime management overhead: pImpl (as well as OO factory) place the implementation object on the heap, which imposes significant runtime overhead at construction and destruction. This may be partially offset by custom allocators, since allocation size for pImpl (but not OO factory) is known at compile time.
On the other hand, pImpl classes are move-friendly; refactoring a large class as movable pImpl may improve performance of algorithms that manipulate containers holding such objects, although movable pImpl has an additional source of runtime overhead: any public member function that is permitted on a moved-from object and needs access to private implementation incurs a null pointer check.

## Maintenance overhead
Use of pImpl requires a dedicated translation unit (a header-only library cannot use pImpl), introduces an additional class, a set of forwarding functions, and, if allocators are used, exposes the implementation detail of allocator use in the public interface.
Since virtual members are part of the interface component of pImpl, mocking a pImpl implies mocking the interface component alone. A testable pImpl is typically designed to allow full test coverage through the available interface.
