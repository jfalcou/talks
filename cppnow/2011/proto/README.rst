===================================================================
Getting Jiggy with Proto - Boost'Con 2011 Tutorial Hands-on Session
===================================================================

.. contents:: Index

-----------------------
Contents and Objectives
-----------------------

Embedded Domain Specific Languages (EDSL) are actually rising as a design of choice to handle small to middle sized 
problem in a declarative and efficient way. Among others, C++ is actually a pretty interesting choice as a 
host language for such development. Idioms like Expression Templates have been demonstrated to be the technique
of choice for such situation. However, they always look like some dark arcane secrets and scare potential developers
away. 

Thanks to libraries like Boost.Proto, the design and development of Expression Templates is becoming easier and easier.
More than Expression Templates, the main strength of Proto is to enable compiler-like code to be written and applied
on lazily evaluable expression. Combined to the flexibility of C++ in terms of operator and function overloading, making
EDSL that works and are not a mess to maintain is possible.

This three hours tutorial will try to cover the basic and intermediate ground of Proto and will demonstrate that 
writing Proto enabled code is not **that** scary. The chosen subject is somethign simple : analytical derivation 
of functions and their evaluation. This is a subject I think many people here will be familliar of (or will be
quickly refreshed on) and yet give a lot of opportunity as a tutorial.

I strongly hope the ''Take Away Home'' element of this session will help spreading the use of EDSL as a C++ library
design technique and clarify what Proto is and is not. 

-------------------------
Structure of the Tutorial
-------------------------

Introduction - Boost.Proto in a (meta) nutshell
:::::::::::::::::::::::::::::::::::::::::::::::
This introduction will present the basic concepts behind Proto, how it can be used to 
model and implement EDSL within C++. Focus will be put on the notion of **Expression**,
**Grammar**, **Domain** and **Generator** which are the very basic building blocks of 
Boost.Proto. We end up this part by giving an example that will lead us to the hands-on 
part: designing a small grammar and expression system able to handle simple arithmetic
computations.

Part 1 - My Calculator is Rich
::::::::::::::::::::::::::::::
First hands-on part will be to extend the initial examples from the Introduction to produce
a working calculator. We'll introduce the notion of **Transform** and we'll build a transform 
to be able to evaluate a given arithmetic expression for a given value. At the end of this 
part, we should end up with a small analytical function EDSL able to evaluate arbitrary 
expressions. 

Part 2 - Computing Analytical Derivatives
:::::::::::::::::::::::::::::::::::::::::
The second part will look at how **Transforms** can be used not only to evaluate **Expressions**
but how they can actually restructure them. We'll tackle on the problem of computing the 
analytical derivative of a given expression using the good ol' derivation rules. We'll see how
various details of the derivation process will lead us to define new elements in our grammar and
how those simple rules can actually be extended to support partial derivation. After this part,
our small calculator should now support arbitrary partial derivative of multiple variables functions.

Conclusion - We Finally Made It !
:::::::::::::::::::::::::::::::::
At the end of the tutorial, we'll end up with a fully functional and extensible analytical
function EDSL supporting derivatives and partial derivatives, a way to simplify and
evaluate expressions and a small extension mechanism. This tutorial will have covered the
main parts of Boost.Proto how it interacts with other Boost components.

----------
Useful Links
----------

:Boost Getting Started: http://www.boost.org/doc/libs/release/more/getting_started/index.html
:Boost.Proto Documentation: http://www.boost.org/doc/libs/release/doc/html/proto.html
:Boost.Proto talk by Eric Niebler - Boost'Con 2010: http://boostcon.blip.tv/file/3970405/


