#pragma once

#include <vector>

template <typename _T, typename _A = std::allocator<_T>>
class Grid
{
    /* Types definition */
    private :
        using _Container = std::vector<_T, _A>;
		using _Iterator = typename _Container::iterator;
		using _ConstIterator = typename _Container::const_iterator;
        using _SizeType = typename _Container::size_type;

    public :
        using size_type = _SizeType;

    /* Member functions definition */
    public :
        Grid() :
            _Width(0),
            _Height(0)
        {
        }

        _T const& at(_SizeType x, _SizeType y) const
        {
            return _Ctnr.at(x + y * _Width);
        }
        
        _T& at(_SizeType x, _SizeType y)
        {
            return _Ctnr.at(x + y * _Width);
        }

        _T const& operator()(_SizeType x, _SizeType y) const
        {
            return _Ctnr[x + y * _Width];
        }
        
        _T& operator()(_SizeType x, _SizeType y)
        {
            return _Ctnr[x + y * _Width];
        }
        
        Grid<_T, _A>& operator=(Grid<_T, _A> const& cpy)
        {
            _Width = cpy._Width;
            _Height = cpy._Height;
            _Ctnr = cpy._Ctnr;
            return *this;
        }
        
        void resize(_SizeType width, _SizeType height)
        {
            _Width = width;
            _Height = height;
            _Ctnr.resize(width * height);
        }

		_Iterator begin()
		{
			return _Ctnr.begin();
		}
        
		_Iterator end()
		{
			return _Ctnr.end();
		}

		_ConstIterator begin() const
		{
			return _Ctnr.begin();
		}

		_ConstIterator end() const
		{
			return _Ctnr.end();
		}

        inline _SizeType width() const     { return _Width; }
        inline _SizeType height() const    { return _Height; }
        
    /* Attributes definition */
    private :
        _SizeType _Width;
        _SizeType _Height;

        _Container _Ctnr;
};

