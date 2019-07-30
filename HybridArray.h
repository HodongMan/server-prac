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

private:
	int			m_count;
	int			m_maxSize;
	Type*		m_data;
	Type		m_staticData[staticSize];
};