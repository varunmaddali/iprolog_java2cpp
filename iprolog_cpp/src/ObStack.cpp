
#include <vector>

namespace iProlog
{

	template<typename T>
	class ObStack : public std::vector<T>
	{

  private:
	  static constexpr long long serialVersionUID = 1LL;

  public:
	  T pop()
	  {
		constexpr int last = this->size() - 1;
		return this->remove(last);
	  }

	  void push(T const O)
	  {
		this->add(O);
	  }

	  T peek()
	  {
		return this->get(this->size() - 1);
	  }
	};
}

//.cpp file code:

namespace iProlog
{
}
