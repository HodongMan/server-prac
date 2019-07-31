#pragma once

template<typename Type, int staticSize>
class HybridArray
{
public:

	inline HybridArray( void )
	{
		m_data		= m_staticData;
		m_maxSize	= staticSize;
		m_count		= 0;
	}

	inline ~HybridArray( void )
	{
		if ( m_data != m_staticData )
		{
			delete[] myData;
		}
	}

	inline HybridArray( const HybridArray& rhs ) noexcept
	{
		m_maxSize	= rhs.m_maxSize;
		m_count		= rhs.m_count;

		if ( staticSize < m_count )
		{
			myData = new Type[m_maxSize];
		}
		else
		{
			m_Data = m_staticData;
		}

		for ( unsigned int i = 0; i < m_count; ++i )
		{
			m_data[i] = rhs.m_data[i];
		}

		validate();
	}

	inline void operator=( const HybridArray& rhs ) noexcept
	{
		validate();

		if ( this != &rhs )
		{
			if ( m_maxSize < rhs.myCount )
			{
				if ( m_data != m_staticData )
				{
					delete[] m_data;
				}
					
				m_maxSize = rhs.m_maxSize;
				m_data = new Type[m_maxSize];
			}

			m_count = rhs.m_count;
			for ( unsigned int i = 0; i < myCount; ++i )
			{
				m_data[i] = rhs.m_data[i];
			}
		}

		validate();
	}
	
	template<int otherSize> HybridArray( const HybridArray<Type, otherSize>& rhs ) noexcept
	{
		m_maxSize	= rhs.m_maxSize;
		m_count		= rhs.m_count;
		if ( staticSize < m_count )
		{
			m_data = new Type[m_maxSize];
		}
		else
		{
			m_data = m_staticData;
		}
			
		for ( unsigned int i = 0; i < m_count; ++i )
		{
			m_data[i] = rhs.m_data[i];
		}
			
		validate();
	}

	template <int otherSize> void operator=( const HybridArray<Type, otherSize>& rhs ) noexcept
	{
		validate();

		if ( this != &rhs )
		{
			if ( m_maxSize < rhs.myCount )
			{
				if ( m_data != m_staticData )
				{
					delete[] m_data;
				}
					
				m_maxSize = rhs.m_maxSize;
				m_data = new Type[m_maxSize];
			}

			m_count = rhs.m_count;
			for ( unsigned int i = 0; i < myCount; ++i )
			{
				m_data[i] = rhs.m_data[i];
			}
		}

		validate();
	}

	inline void validate( void ) noexcept
	{
		/*
		assert( 0 <= m_count );
		assert( staticSize <= myMaxSize );
		assert( m_count <= m_maxSize);
		assert( ( m_maxSize <= staticSize ) || ( m_data != m_staticData ) );
		*/
	}

	inline void add( const Type& item ) noexcept
	{
		validate();

		if ( m_count == m_maxSize )
		{
			const int newMaxSize = max( m_maxSize * 2, 2 );
			Type* newData = new Type[newMaxSize];

			for ( unsigned int i = 0; i < myCount; ++i )
			{
				newData[i] = my_data[i];
			}

			if( my_data != m_staticData )
			{
				delete[] m_data;
			}
				
			m_data = newData;
			m_maxSize = newMaxSize;
		}

		validate();

		m_data[m_count] = item;
		m_count++;
	}

	inline bool addUnique( const Type& item ) noexcept
	{
		validate();

		for ( unsigned int i = 0; i < myCount; ++i )
		{
			if ( m_data[i] == item )
			{
				return false;
			}
		}

		add( item );

		return true;
	}

	inline void removeLast( void ) noexcept
	{
		if ( 0 < m_count )
		{
			m_count -= 1;
		}

		validate();
	}

	inline Type& operator[] ( const unsigned int index ) noexcept
	{
		//assert( 0 <= index && index < m_count && "HybridArray BOUNDS ERROR!" );
		return m_data[index];
	}

	inline const Type& operator[] ( const unsigned int index ) noexcept
	{
		//assert( 0 <= index && index < m_count && "HybridArray BOUNDS ERROR!" );
		return m_data[index];
	}

	inline Type& getFirst( void ) noexcept
	{
		//assert( 0 <= index && index < m_count && "HybridArray BOUNDS ERROR!" );
		return m_data[0];
	}

	inline const Type& getFirst( void ) noexcept
	{
		//assert( 0 <= index && index < m_count && "HybridArray BOUNDS ERROR!" );
		return m_data[0];
	}

	inline Type& getLast( void ) noexcept
	{
		//assert( 0 <= index && index < m_count && "HybridArray BOUNDS ERROR!" );
		return m_data[m_count - 1];
	}

	inline const Type& getLast( void ) noexcept
	{
		//assert( 0 <= index && index < m_count && "HybridArray BOUNDS ERROR!" );
		return m_data[m_count - 1];
	}

	inline void removeAtIndex( const unsigned int index ) noexcept
	{
		//assert( 0 <= index && index < m_count && "HybridArray BOUNDS ERROR!" );

		for ( unsigned int i = index; i < ( m_count - 1 ); ++i )
		{
			m_data[i] = m_data[i + 1];
		}
		
		myCount -= 1;
	}

	inline void removeCyclicAtIndex( const unsigned int index ) noexcept
	{
		//assert( 0 <= index && index < m_count && "HybridArray BOUNDS ERROR!" );

		m_count -= 1;
		m_data[index] = m_data[m_count];
	}

	inline bool remove( const Type& item ) noexcept
	{
		for ( unsigned int i = 0; i < m_count; ++i )
		{
			if ( m_data[i] == item )
			{
				removeAtIndex( i );
				return true;
			}
		}

		return false;
	}

	inline void removeAll( void ) noexcept
	{
		m_count = 0;
	}


private:
	int			m_count;
	int			m_maxSize;
	Type*		m_data;
	Type		m_staticData[staticSize];
};