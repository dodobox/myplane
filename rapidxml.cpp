#include "rapidxml.h"
#include <assert.h>

void parse_error_handler( const char *what, void *where ){
    //        printf( "xml parse error %s\n", what );
}

memory_pool::memory_pool(){
    init();
}

memory_pool::~memory_pool(){
    clear();
}

xml_node *memory_pool::allocate_node( node_type type,
    const char *name, const char *value,
    size_t name_size, size_t value_size ){
    void *memory = allocate_aligned( sizeof( xml_node ) );
    xml_node *node = (xml_node*)memory;
    node->xml_node::xml_node( type );
    if( name ){
        if( name_size > 0 )
            node->name( name, name_size );
        else
            node->name( name );
    }
    if( value ){
        if( value_size > 0 )
            node->value( value, value_size );
        else
            node->value( value );
    }
    return node;
}

xml_attribute *memory_pool::allocate_attribute( const char *name, const char *value,
                                    size_t name_size, size_t value_size ){
    void *memory = allocate_aligned( sizeof( xml_attribute ) );
    xml_attribute *attribute = (xml_attribute*)memory;// new(memory) xml_attribute;
    attribute->xml_attribute::xml_attribute();
    if( name ){
        if( name_size > 0 )
            attribute->name( name, name_size );
        else
            attribute->name( name );
    }
    if( value ){
        if( value_size > 0 )
            attribute->value( value, value_size );
        else
            attribute->value( value );
    }
    return attribute;
}

char *memory_pool::allocate_string( const char *source, size_t size ){
    assert( source || size );     // Either source or size (or both) must be specified
    if( size == 0 )
        size = internal::measure( source ) + 1;
    char *result = static_cast<char *>(allocate_aligned( size * sizeof( char ) ));
    if( source )
        for( size_t i = 0; i < size; ++i )
            result[i] = source[i];
    return result;
}

xml_node *memory_pool::clone_node( const xml_node *source, xml_node *result ){
    // Prepare result node
    if( result ){
        result->remove_all_attributes();
        result->remove_all_nodes();
        result->type( source->type() );
    } else
        result = allocate_node( source->type() );

    // Clone name and value
    result->name( source->name(), source->name_size() );
    result->value( source->value(), source->value_size() );

    // Clone child nodes and attributes
    for( xml_node *child = source->first_node(); child; child = child->next_sibling() )
        result->append_node( clone_node( child ) );
    for( xml_attribute *attr = source->first_attribute(); attr; attr = attr->next_attribute() )
        result->append_attribute( allocate_attribute( attr->name(), attr->value(), attr->name_size(), attr->value_size() ) );

    return result;
}

void memory_pool::clear(){
    while( m_begin != m_static_memory ){
        char *previous_begin = reinterpret_cast<header *>(align( m_begin ))->previous_begin;
        FREE( m_begin );
        m_begin = previous_begin;
    }
    init();
}

void memory_pool::init(){
    m_begin = m_static_memory;
    m_ptr = align( m_begin );
    m_end = m_static_memory + sizeof( m_static_memory );
}

char *memory_pool::align( char *ptr ){
    size_t alignment = ((RAPIDXML_ALIGNMENT - (size_t( ptr ) & (RAPIDXML_ALIGNMENT - 1))) & (RAPIDXML_ALIGNMENT - 1));
    return ptr + alignment;
}

char *memory_pool::allocate_raw( size_t size ){
    void *memory = MALLOC( size );// new char[size];

    if( !memory )
        RAPIDXML_PARSE_ERROR( "out of memory", 0 );
    return static_cast<char *>(memory);
}

void *memory_pool::allocate_aligned( size_t size ){
    // Calculate aligned pointer
    char *result = align( m_ptr );

    // If not enough memory left in current pool, allocate a new pool
    if( result + size > m_end ){
        // Calculate required pool size (may be bigger than RAPIDXML_DYNAMIC_POOL_SIZE)
        size_t pool_size = RAPIDXML_DYNAMIC_POOL_SIZE;
        if( pool_size < size )
            pool_size = size;

        // Allocate
        size_t alloc_size = sizeof( header ) + (2 * RAPIDXML_ALIGNMENT - 2) + pool_size;     // 2 alignments required in worst case: one for header, one for actual allocation
        char *raw_memory = allocate_raw( alloc_size );

        // Setup new pool in allocated memory
        char *pool = align( raw_memory );
        header *new_header = reinterpret_cast<header *>(pool);
        new_header->previous_begin = m_begin;
        m_begin = raw_memory;
        m_ptr = pool + sizeof( header );
        m_end = raw_memory + alloc_size;

        // Calculate aligned pointer again using new pool
        result = align( m_ptr );
    }

    // Update pool and return aligned pointer
    m_ptr = result + size;
    return result;
}


/////////////////////////////////////////////////////////////////////////////////////////

xml_base::xml_base()
: m_name( 0 )
 , m_value( 0 )
 , m_parent( 0 ){
}

char *xml_base::name() const{
    return m_name ? m_name : nullstr();
}

size_t xml_base::name_size() const{
    return m_name ? m_name_size : 0;
}

char *xml_base::value() const{
    return m_value ? m_value : nullstr();
}


size_t xml_base::value_size() const{
    return m_value ? m_value_size : 0;
}

void xml_base::name( const char *name, size_t size ){
    m_name = const_cast<char *>(name);
    m_name_size = size;
}

void xml_base::name( const char *name ){
    this->name( name, internal::measure( name ) );
}

void xml_base::value( const char *value, size_t size ){
    m_value = const_cast<char *>(value);
    m_value_size = size;
}

void xml_base::value( const char *value ){
    this->value( value, internal::measure( value ) );
}

xml_node *xml_base::parent() const{
    return m_parent;
}


char *xml_base::nullstr(){
    static char zero = char( '\0' );
    return &zero;
}





///////////////////////////////////////////////////////////////////////////////////////

xml_attribute::xml_attribute(){
}
xml_document *xml_attribute::document() const{
    if( xml_node *node = this->parent() ){
        while( node->parent() )
            node = node->parent();
        return node->type() == node_document ? static_cast<xml_document *>(node) : 0;
    } else
        return 0;
}
xml_attribute *xml_attribute::previous_attribute( const char *name, size_t name_size, bool case_sensitive ) const{
    if( name ){
        if( name_size == 0 )
            name_size = internal::measure( name );
        for( xml_attribute *attribute = m_prev_attribute; attribute; attribute = attribute->m_prev_attribute )
            if( internal::compare( attribute->name(), attribute->name_size(), name, name_size, case_sensitive ) )
                return attribute;
        return 0;
    } else
        return this->m_parent ? m_prev_attribute : 0;
}
xml_attribute *xml_attribute::next_attribute( const char *name, size_t name_size, bool case_sensitive ) const{
    if( name ){
        if( name_size == 0 )
            name_size = internal::measure( name );
        for( xml_attribute *attribute = m_next_attribute; attribute; attribute = attribute->m_next_attribute )
            if( internal::compare( attribute->name(), attribute->name_size(), name, name_size, case_sensitive ) )
                return attribute;
        return 0;
    } else
        return this->m_parent ? m_next_attribute : 0;
}



xml_node::xml_node( node_type type )
        : m_type( type )
        , m_first_node( 0 )
        , m_first_attribute( 0 ){
    }

node_type xml_node::type() const{
    return m_type;
}

xml_document *xml_node::document() const{
    xml_node *node = const_cast<xml_node *>(this);
    while( node->parent() )
        node = node->parent();
    return node->type() == node_document ? static_cast<xml_document *>(node) : 0;
}

xml_node *xml_node::first_node( const char *name, size_t name_size, bool case_sensitive ) const{
    if( name ){
        if( name_size == 0 )
            name_size = internal::measure( name );
        for( xml_node *child = m_first_node; child; child = child->next_sibling() )
            if( internal::compare( child->name(), child->name_size(), name, name_size, case_sensitive ) )
                return child;
        return 0;
    } else
        return m_first_node;
}

xml_node *xml_node::last_node( const char *name, size_t name_size, bool case_sensitive ) const{
    assert( m_first_node );  // Cannot query for last child if node has no children
    if( name ){
        if( name_size == 0 )
            name_size = internal::measure( name );
        for( xml_node *child = m_last_node; child; child = child->previous_sibling() )
            if( internal::compare( child->name(), child->name_size(), name, name_size, case_sensitive ) )
                return child;
        return 0;
    } else
        return m_last_node;
}

xml_node *xml_node::previous_sibling( const char *name, size_t name_size, bool case_sensitive ) const{
    assert( this->m_parent );     // Cannot query for siblings if node has no parent
    if( name ){
        if( name_size == 0 )
            name_size = internal::measure( name );
        for( xml_node *sibling = m_prev_sibling; sibling; sibling = sibling->m_prev_sibling )
            if( internal::compare( sibling->name(), sibling->name_size(), name, name_size, case_sensitive ) )
                return sibling;
        return 0;
    } else
        return m_prev_sibling;
}

xml_node *xml_node::next_sibling( const char *name, size_t name_size, bool case_sensitive ) const{
    //            assert(this->m_parent);     // Cannot query for siblings if node has no parent
    if( name ){
        if( name_size == 0 )
            name_size = internal::measure( name );
        for( xml_node *sibling = m_next_sibling; sibling; sibling = sibling->m_next_sibling )
            if( internal::compare( sibling->name(), sibling->name_size(), name, name_size, case_sensitive ) )
                return sibling;
        return 0;
    } else
        return m_next_sibling;
}

xml_attribute *xml_node::first_attribute( const char *name, size_t name_size, bool case_sensitive ) const{
    if( name ){
        if( name_size == 0 )
            name_size = internal::measure( name );
        for( xml_attribute *attribute = m_first_attribute; attribute; attribute = attribute->m_next_attribute )
            if( internal::compare( attribute->name(), attribute->name_size(), name, name_size, case_sensitive ) )
                return attribute;
        return 0;
    } else
        return m_first_attribute;
}

xml_attribute *xml_node::last_attribute( const char *name, size_t name_size, bool case_sensitive ) const{
    if( name ){
        if( name_size == 0 )
            name_size = internal::measure( name );
        for( xml_attribute *attribute = m_last_attribute; attribute; attribute = attribute->m_prev_attribute )
            if( internal::compare( attribute->name(), attribute->name_size(), name, name_size, case_sensitive ) )
                return attribute;
        return 0;
    } else
        return m_first_attribute ? m_last_attribute : 0;
}


void xml_node::type( node_type type ){
    m_type = type;
}

void xml_node::prepend_node( xml_node *child ){
    //assert(child && !child->parent() && child->type() != node_document);
    if( first_node() ){
        child->m_next_sibling = m_first_node;
        m_first_node->m_prev_sibling = child;
    } else{
        child->m_next_sibling = 0;
        m_last_node = child;
    }
    m_first_node = child;
    child->m_parent = this;
    child->m_prev_sibling = 0;
}

void xml_node::append_node( xml_node *child ){
    //assert(child && !child->parent() && child->type() != node_document);
    if( first_node() ){
        child->m_prev_sibling = m_last_node;
        m_last_node->m_next_sibling = child;
    } else{
        child->m_prev_sibling = 0;
        m_first_node = child;
    }
    m_last_node = child;
    child->m_parent = this;
    child->m_next_sibling = 0;
}

void xml_node::insert_node( xml_node *where, xml_node *child ){
    //assert(!where || where->parent() == this);
    //assert(child && !child->parent() && child->type() != node_document);
    if( where == m_first_node )
        prepend_node( child );
    else if( where == 0 )
        append_node( child );
    else{
        child->m_prev_sibling = where->m_prev_sibling;
        child->m_next_sibling = where;
        where->m_prev_sibling->m_next_sibling = child;
        where->m_prev_sibling = child;
        child->m_parent = this;
    }
}

void xml_node::remove_first_node(){
    //assert(first_node());
    xml_node *child = m_first_node;
    m_first_node = child->m_next_sibling;
    if( child->m_next_sibling )
        child->m_next_sibling->m_prev_sibling = 0;
    else
        m_last_node = 0;
    child->m_parent = 0;
}

void xml_node::remove_last_node(){
    //assert(first_node());
    xml_node *child = m_last_node;
    if( child->m_prev_sibling ){
        m_last_node = child->m_prev_sibling;
        child->m_prev_sibling->m_next_sibling = 0;
    } else
        m_first_node = 0;
    child->m_parent = 0;
}

void xml_node::remove_node( xml_node *where ){
    //assert(where && where->parent() == this);
    //assert(first_node());
    if( where == m_first_node )
        remove_first_node();
    else if( where == m_last_node )
        remove_last_node();
    else{
        where->m_prev_sibling->m_next_sibling = where->m_next_sibling;
        where->m_next_sibling->m_prev_sibling = where->m_prev_sibling;
        where->m_parent = 0;
    }
}

void xml_node::remove_all_nodes(){
    for( xml_node *node = first_node(); node; node = node->m_next_sibling )
        node->m_parent = 0;
    m_first_node = 0;
}

//! Prepends a new attribute to the node.
//! \param attribute Attribute to prepend.
void xml_node::prepend_attribute( xml_attribute *attribute ){
    //assert(attribute && !attribute->parent());
    if( first_attribute() ){
        attribute->m_next_attribute = m_first_attribute;
        m_first_attribute->m_prev_attribute = attribute;
    } else{
        attribute->m_next_attribute = 0;
        m_last_attribute = attribute;
    }
    m_first_attribute = attribute;
    attribute->m_parent = this;
    attribute->m_prev_attribute = 0;
}

//! Appends a new attribute to the node.
//! \param attribute Attribute to append.
void xml_node::append_attribute( xml_attribute *attribute ){
    //assert(attribute && !attribute->parent());
    if( first_attribute() ){
        attribute->m_prev_attribute = m_last_attribute;
        m_last_attribute->m_next_attribute = attribute;
    } else{
        attribute->m_prev_attribute = 0;
        m_first_attribute = attribute;
    }
    m_last_attribute = attribute;
    attribute->m_parent = this;
    attribute->m_next_attribute = 0;
}

void xml_node::insert_attribute( xml_attribute *where, xml_attribute *attribute ){
    //assert(!where || where->parent() == this);
    //assert(attribute && !attribute->parent());
    if( where == m_first_attribute )
        prepend_attribute( attribute );
    else if( where == 0 )
        append_attribute( attribute );
    else{
        attribute->m_prev_attribute = where->m_prev_attribute;
        attribute->m_next_attribute = where;
        where->m_prev_attribute->m_next_attribute = attribute;
        where->m_prev_attribute = attribute;
        attribute->m_parent = this;
    }
}

void xml_node::remove_first_attribute(){
    //assert(first_attribute());
    xml_attribute *attribute = m_first_attribute;
    if( attribute->m_next_attribute ){
        attribute->m_next_attribute->m_prev_attribute = 0;
    } else
        m_last_attribute = 0;
    attribute->m_parent = 0;
    m_first_attribute = attribute->m_next_attribute;
}

void xml_node::remove_last_attribute(){
    //assert(first_attribute());
    xml_attribute *attribute = m_last_attribute;
    if( attribute->m_prev_attribute ){
        attribute->m_prev_attribute->m_next_attribute = 0;
        m_last_attribute = attribute->m_prev_attribute;
    } else
        m_first_attribute = 0;
    attribute->m_parent = 0;
}

void xml_node::remove_attribute( xml_attribute *where ){
    //assert(first_attribute() && where->parent() == this);
    if( where == m_first_attribute )
        remove_first_attribute();
    else if( where == m_last_attribute )
        remove_last_attribute();
    else{
        where->m_prev_attribute->m_next_attribute = where->m_next_attribute;
        where->m_next_attribute->m_prev_attribute = where->m_prev_attribute;
        where->m_parent = 0;
    }
}

void xml_node::remove_all_attributes(){
    for( xml_attribute *attribute = first_attribute(); attribute; attribute = attribute->m_next_attribute )
        attribute->m_parent = 0;
    m_first_attribute = 0;
}





//! \cond internal
namespace internal
{

    // Whitespace (space \n \r \t)
    const unsigned char lookup_tables::lookup_whitespace[256] =
    {
        // 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
        0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  1,  0,  0,  // 0
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // 1
        1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // 2
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // 3
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // 4
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // 5
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // 6
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // 7
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // 8
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // 9
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // A
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // B
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // C
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // D
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  // E
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0   // F
    };

    // Node name (anything but space \n \r \t / > ? \0)
    const unsigned char lookup_tables::lookup_node_name[256] =
    {
        // 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
        0,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  1,  0,  1,  1,  // 0
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 1
        0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  // 2
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  // 3
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 4
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 5
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 6
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 7
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 8
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 9
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // A
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // B
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // C
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // D
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // E
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1   // F
    };

    // Text (i.e. PCDATA) (anything but < \0)
    const unsigned char lookup_tables::lookup_text[256] =
    {
        // 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
        0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 0
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 1
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 2
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  // 3
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 4
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 5
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 6
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 7
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 8
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 9
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // A
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // B
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // C
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // D
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // E
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1   // F
    };

    // Text (i.e. PCDATA) that does not require processing when ws normalization is disabled 
    // (anything but < \0 &)
    const unsigned char lookup_tables::lookup_text_pure_no_ws[256] =
    {
        // 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
        0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 0
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 1
        1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 2
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  // 3
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 4
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 5
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 6
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 7
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 8
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 9
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // A
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // B
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // C
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // D
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // E
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1   // F
    };

    // Text (i.e. PCDATA) that does not require processing when ws normalizationis is enabled
    // (anything but < \0 & space \n \r \t)
    const unsigned char lookup_tables::lookup_text_pure_with_ws[256] =
    {
        // 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
        0,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  1,  0,  1,  1,  // 0
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 1
        0,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 2
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  // 3
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 4
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 5
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 6
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 7
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 8
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 9
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // A
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // B
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // C
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // D
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // E
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1   // F
    };

    // Attribute name (anything but space \n \r \t / < > = ? ! \0)
    const unsigned char lookup_tables::lookup_attribute_name[256] =
    {
        // 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
        0,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  1,  0,  1,  1,  // 0
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 1
        0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  // 2
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  // 3
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 4
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 5
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 6
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 7
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 8
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 9
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // A
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // B
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // C
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // D
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // E
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1   // F
    };

    // Attribute data with single quote (anything but ' \0)
    const unsigned char lookup_tables::lookup_attribute_data_1[256] =
    {
        // 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
        0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 0
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 1
        1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  // 2
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 3
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 4
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 5
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 6
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 7
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 8
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 9
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // A
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // B
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // C
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // D
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // E
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1   // F
    };

    // Attribute data with single quote that does not require processing (anything but ' \0 &)
    const unsigned char lookup_tables::lookup_attribute_data_1_pure[256] =
    {
        // 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
        0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 0
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 1
        1,  1,  1,  1,  1,  1,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  // 2
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 3
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 4
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 5
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 6
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 7
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 8
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 9
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // A
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // B
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // C
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // D
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // E
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1   // F
    };

    // Attribute data with double quote (anything but " \0)
    const unsigned char lookup_tables::lookup_attribute_data_2[256] =
    {
        // 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
        0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 0
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 1
        1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 2
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 3
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 4
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 5
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 6
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 7
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 8
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 9
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // A
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // B
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // C
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // D
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // E
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1   // F
    };

    // Attribute data with double quote that does not require processing (anything but " \0 &)
    const unsigned char lookup_tables::lookup_attribute_data_2_pure[256] =
    {
        // 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
        0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 0
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 1
        1,  1,  0,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 2
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 3
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 4
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 5
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 6
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 7
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 8
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // 9
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // A
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // B
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // C
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // D
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  // E
        1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1   // F
    };

    // Digits (dec and hex, 255 denotes end of numeric character reference)
    const unsigned char lookup_tables::lookup_digits[256] =
    {
        // 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
        255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  // 0
        255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  // 1
        255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  // 2
        0,  1,  2,  3,  4,  5,  6,  7,  8,  9,255,255,255,255,255,255,  // 3
        255, 10, 11, 12, 13, 14, 15,255,255,255,255,255,255,255,255,255,  // 4
        255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  // 5
        255, 10, 11, 12, 13, 14, 15,255,255,255,255,255,255,255,255,255,  // 6
        255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  // 7
        255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  // 8
        255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  // 9
        255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  // A
        255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  // B
        255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  // C
        255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  // D
        255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,  // E
        255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255   // F
    };

    // Upper case conversion
    const unsigned char lookup_tables::lookup_upcase[256] =
    {
        // 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  A   B   C   D   E   F
        0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,   // 0
        16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,   // 1
        32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,   // 2
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,   // 3
        64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,   // 4
        80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,   // 5
        96, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,   // 6
        80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 123,124,125,126,127,  // 7
        128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,  // 8
        144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,  // 9
        160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,  // A
        176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,  // B
        192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,  // C
        208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,  // D
        224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,  // E
        240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255   // F
    };
}

