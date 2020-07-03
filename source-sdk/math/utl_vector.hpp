#pragma once
#include <assert.h>

template <class t, class a = int> class utl_memory {
	public:
	inline bool is_idx_valid( a i ) const {
		long x = i;
		return ( x >= 0 ) && ( x < allocation_count );
	}

	t &operator[]( a i );
	const t &operator[]( a i ) const;
	t *base() {
		return memory;
	}

	inline int num_allocated() const {
		return allocation_count;
	}

	void grow( int num ) {
		assert( num > 0 );

		auto old_allocation_count = allocation_count;
		int allocation_requested = allocation_count + num;
		int new_allocation_count = utl_memory_calc_new_allocation_count( allocation_count, grow_size, allocation_requested, sizeof( t ) );
		if ( ( int ) ( a ) new_allocation_count < allocation_requested ) {

			if ( ( int ) ( a ) new_allocation_count == 0 && ( int ) ( a ) ( new_allocation_count - 1 ) >= allocation_requested ) {
				--new_allocation_count;
			} else {
				if ( ( int ) ( a ) allocation_requested != allocation_requested ) {
					assert( 0 );
					return;
				}
				while ( ( int ) ( a ) new_allocation_count < allocation_requested ) {
					new_allocationCount = ( new_allocation_count + allocation_requested ) / 2;
				}
			}
		}
		allocation_count = new_allocation_count;
		if ( memory ) {
			auto ptr = new unsigned char[ allocation_count * sizeof( t ) ];
			memcpy( ptr, memory, old_allocation_count * sizeof( t ) );
			memory = ( t * ) ptr;
		} else
			memory = ( t * )new unsigned char[ allocation_count * sizeof( t ) ];
	}
	protected:
	t *memory;
	int allocation_count;
	int grow_size;
};

template< class t, class a >
inline t &utl_memory<t, a>::operator[]( a i ) {
	assert( is_idx_valid( i ) );
	return memory[ i ];
}

template< class t, class a >
inline const t &utl_memory<t, a>::operator[]( a i ) const {
	assert( is_idx_valid( i ) );
	return memory[ i ];
}

template< class t, class a = utl_memory<t> >
class utl_vector {
	typedef a c_allocator;
	typedef t *iterator;
	typedef const t *const_iterator;
public:
	t &operator[]( int i );

	const t &operator[]( int i ) const;

	t &element( int i ) {
		return memory[ i ];
	}

	t *base() {
		return memory.base();
	}

	int count() const {
		return size;
	}

	void remove_all() {
		for ( int i = size; --i >= 0; )
			destruct( &element( i ) );
		size = 0;
	}

	inline bool is_valid_index( int i ) const {
		return ( i >= 0 ) && ( i < size );
	}

	void grow_vector( int num = 1 ) {
		if ( size + num > memory.num_allocated() )
			memory.grow( size + num - memory.num_allocated() );
		size += num;
	}

	int insert_before( int elem ) {
		assert( ( elem == count() ) || is_valid_index( elem ) );

		grow_vector();
		construct( &element( elem ) );
		return elem;
	}

	inline int add_to_head() {
		return insert_before( 0 );
	}

	inline int add_to_tail() {
		return insert_before( size );
	}

	iterator begin() { return base(); }
	const_iterator begin() const { return base(); }
	iterator end() { return base() + count(); }
	const_iterator end() const { return base() + count(); }

	protected:
	c_allocator memory;
	int size;
	t *elements;
};

template< typename t, class a >
inline t &utl_vector<t, a>::operator[]( int i ) {
	assert( i < size );
	return memory[ i ];
}

template< typename t, class a >
inline const t &utl_vector<t, a>::operator[]( int i ) const {
	assert( i < size );
	return memory[ i ];
}
