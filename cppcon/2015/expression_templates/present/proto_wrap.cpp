#include <boost/proto/proto.hpp>

using boost::proto::_;
using boost::proto::or_;
using boost::proto::plus;
using boost::proto::multiplies;
using boost::proto::when;
using boost::proto::_value;
using boost::proto::otherwise;
using boost::proto::_default;
using boost::proto::terminal;

struct eval  : boost::proto::or_< when<terminal<_>,_value>
                                , otherwise< _default<eval> >
                                >
{};

struct epa  : boost::proto::or_ < terminal<_>
                                , plus<epa,epa>
                                , multiplies<epa,epa>
                                >
{};

template<typename AST> struct expr_;

struct  domain_ : boost::proto::domain< boost::proto::generator<expr_>, epa > {};

template<typename AST>
struct expr_ : boost::proto::extends<AST,expr_<AST>,domain_>
{
  typedef boost::proto::extends<AST,expr_<AST>,domain_> extendee;

  expr_(AST const& ast = AST()) : extendee(ast) {}

  BOOST_PROTO_EXTENDS_USING_ASSIGN(expr_)

  typedef double result_type;

  result_type operator()() const
  {
    eval callee;
    return callee(*this);
  }
};

template<typename T> struct variable : expr_<typename terminal<T>::type>
{
  variable(T const& v = T{}) { boost::proto::value(*this) = v; }

  template<typename X>
  variable operator=(expr_<X> const& x)
  {
    boost::proto::value(*this) = x();
    return *this;
  }
};

int main()
{
  variable<int> x{2}, y ;
  y = x+x*x+3;
  std::cout << y() << "\n";
}
