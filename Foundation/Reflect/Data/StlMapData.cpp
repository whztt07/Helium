#include "Foundation/Reflect/Data/StlMapData.h"

#include "Foundation/Reflect/Data/DataDeduction.h"

using namespace Helium;
using namespace Helium::Reflect;

REFLECT_DEFINE_ABSTRACT(StlMapData)

// Tokenizer adapted from:
// http://www.oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
// str should contain a string with map element separated by the specified delimiters argument.
// str will be parsed into key-value pairs and each pair will be inserted into tokens.
template< typename TKey, typename TVal >
inline void Tokenize( const tstring& str, std::map< TKey, TVal >& tokens, const tstring& delimiters )
{
    // Skip delimiters at beginning.
    tstring::size_type lastPos = str.find_first_not_of( delimiters, 0 );
    // Find first "non-delimiter".
    tstring::size_type pos     = str.find_first_of( delimiters, lastPos );

    while ( tstring::npos != pos || tstring::npos != lastPos )
    {
        tstringstream kStream( str.substr( lastPos, pos - lastPos ) );

        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of( delimiters, pos );
        // Find next "non-delimiter"
        pos = str.find_first_of( delimiters, lastPos );

        if ( tstring::npos != pos || tstring::npos != lastPos )
        {
            tstringstream vStream( str.substr( lastPos, pos - lastPos ) );

            // At this point, we have the key and value.  Build the map entry.
            // Note that the stream operator stops at spaces.
            TKey k;
            kStream >> k;
            TVal v;
            vStream >> v;
            tokens.insert( std::map< TKey, TVal >::value_type( k, v ) );

            // Skip delimiters.  Note the "not_of"
            lastPos = str.find_first_not_of( delimiters, pos );

            // Find next "non-delimiter"
            pos = str.find_first_of( delimiters, lastPos );
        }
        else
        {
            // Delimited map is messed up. It should alternate key-value pairs, but there is
            // a key without a value.
            HELIUM_BREAK();
        }
    }
}

// Partial specialization for strings as TVal, that gets around the stream operator stopping
// at spaces by not using a stream at all.
template< typename TKey, typename TVal >
inline void Tokenize( const tstring& str, std::map< TKey, tstring >& tokens, const tstring& delimiters )
{
    // Skip delimiters at beginning.
    tstring::size_type lastPos = str.find_first_not_of( delimiters, 0 );
    // Find first "non-delimiter".
    tstring::size_type pos     = str.find_first_of( delimiters, lastPos );

    while ( tstring::npos != pos || tstring::npos != lastPos )
    {
        tstringstream kStream( str.substr( lastPos, pos - lastPos ) );

        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of( delimiters, pos );
        // Find next "non-delimiter"
        pos = str.find_first_of( delimiters, lastPos );

        if ( tstring::npos != pos || tstring::npos != lastPos )
        {
            // At this point, we have the key and value.  Build the map entry.
            TKey k;
            kStream >> k;
            tokens.insert( std::map< TKey, TVal >::value_type( k, str.substr( lastPos, pos - lastPos ) ) );

            // Skip delimiters.  Note the "not_of"
            lastPos = str.find_first_not_of( delimiters, pos );

            // Find next "non-delimiter"
            pos = str.find_first_of( delimiters, lastPos );
        }
        else
        {
            // Delimited map is messed up. It should alternate key-value pairs, but there is
            // a key without a value.
            HELIUM_BREAK();
        }
    }
}

// Partial specialization for strings as TKey, that gets around the stream operator stopping
// at spaces by not using a stream at all.
template< typename TKey, typename TVal >
inline void Tokenize( const tstring& str, std::map< tstring, TVal >& tokens, const tstring& delimiters )
{
    // Skip delimiters at beginning.
    tstring::size_type lastPos = str.find_first_not_of( delimiters, 0 );
    // Find first "non-delimiter".
    tstring::size_type pos     = str.find_first_of( delimiters, lastPos );

    while ( tstring::npos != pos || tstring::npos != lastPos )
    {
        tstring key( str.substr( lastPos, pos - lastPos ) );

        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of( delimiters, pos );
        // Find next "non-delimiter"
        pos = str.find_first_of( delimiters, lastPos );

        if ( tstring::npos != pos || tstring::npos != lastPos )
        {
            tstringstream vStream( str.substr( lastPos, pos - lastPos ) );

            // At this point, we have the key and value.  Build the map entry.
            TVal v;
            vStream >> v;
            tokens.insert( std::map< TKey, TVal >::value_type( key, v ) );

            // Skip delimiters.  Note the "not_of"
            lastPos = str.find_first_not_of( delimiters, pos );

            // Find next "non-delimiter"
            pos = str.find_first_of( delimiters, lastPos );
        }
        else
        {
            // Delimited map is messed up. It should alternate key-value pairs, but there is
            // a key without a value.
            HELIUM_BREAK();
        }
    }
}

// Explicit implementation for strings, that gets around the stream operator stopping
// at spaces by not using a stream at all.
template< typename TKey, typename TVal >
inline void Tokenize( const tstring& str, std::map< tstring, tstring >& tokens, const tstring& delimiters )
{
    // Skip delimiters at beginning.
    tstring::size_type lastPos = str.find_first_not_of( delimiters, 0 );
    // Find first "non-delimiter".
    tstring::size_type pos     = str.find_first_of( delimiters, lastPos );

    while ( tstring::npos != pos || tstring::npos != lastPos )
    {
        tstring key( str.substr( lastPos, pos - lastPos ) );

        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of( delimiters, pos );
        // Find next "non-delimiter"
        pos = str.find_first_of( delimiters, lastPos );

        if ( tstring::npos != pos || tstring::npos != lastPos )
        {
            // At this point, we have the key and value.  Build the map entry.
            tokens.insert( std::map< tstring, tstring >::value_type( key, str.substr( lastPos, pos - lastPos ) ) );

            // Skip delimiters.  Note the "not_of"
            lastPos = str.find_first_not_of( delimiters, pos );

            // Find next "non-delimiter"
            pos = str.find_first_of( delimiters, lastPos );
        }
        else
        {
            // Delimited map is messed up. It should alternate key-value pairs, but there is
            // a key without a value.
            HELIUM_BREAK();
        }
    }
}

template < class KeyT, class KeyClassT, class ValueT, class ValueClassT >
SimpleStlMapData<KeyT, KeyClassT, ValueT, ValueClassT>::SimpleStlMapData()
{

}

template < class KeyT, class KeyClassT, class ValueT, class ValueClassT >
SimpleStlMapData<KeyT, KeyClassT, ValueT, ValueClassT>::~SimpleStlMapData()
{

}

template < class KeyT, class KeyClassT, class ValueT, class ValueClassT >
size_t SimpleStlMapData<KeyT, KeyClassT, ValueT, ValueClassT>::GetSize() const
{
    return m_Data->size();
}

template < class KeyT, class KeyClassT, class ValueT, class ValueClassT >
void SimpleStlMapData<KeyT, KeyClassT, ValueT, ValueClassT>::Clear()
{
    return m_Data->clear();
}

template < class KeyT, class KeyClassT, class ValueT, class ValueClassT >
void SimpleStlMapData<KeyT, KeyClassT, ValueT, ValueClassT>::ConnectData(Helium::HybridPtr<void> data)
{
    __super::ConnectData( data );

    m_Data.Connect( Helium::HybridPtr<DataType> (data.Address(), data.State()) );
}

template < class KeyT, class KeyClassT, class ValueT, class ValueClassT >
const Class* SimpleStlMapData<KeyT, KeyClassT, ValueT, ValueClassT>::GetKeyClass() const
{
    return Reflect::GetDataClass<KeyT>();
}

template < class KeyT, class KeyClassT, class ValueT, class ValueClassT >
const Class* SimpleStlMapData<KeyT, KeyClassT, ValueT, ValueClassT>::GetValueClass() const
{
    return Reflect::GetDataClass<ValueT>();
}

template < class KeyT, class KeyClassT, class ValueT, class ValueClassT >
void SimpleStlMapData<KeyT, KeyClassT, ValueT, ValueClassT>::GetItems(V_ValueType& items)
{
    items.resize(m_Data->size());
    DataType::const_iterator itr = m_Data->begin();
    DataType::const_iterator end = m_Data->end();
    for ( size_t index=0; itr != end; ++itr, ++index )
    {
        items[index].first = static_cast< const ConstDataPtr& >( Data::Bind( itr->first, m_Instance, m_Field ) );
        items[index].second = static_cast< const ConstDataPtr& >( Data::Bind( itr->second, m_Instance, m_Field ) );
    }
}

template < class KeyT, class KeyClassT, class ValueT, class ValueClassT >
void SimpleStlMapData<KeyT, KeyClassT, ValueT, ValueClassT>::GetItems(V_ConstValueType& items) const
{
    items.resize(m_Data->size());
    DataType::const_iterator itr = m_Data->begin();
    DataType::const_iterator end = m_Data->end();
    for ( size_t index=0; itr != end; ++itr, ++index )
    {
        items[index].first = static_cast< const ConstDataPtr& >( Data::Bind( itr->first, m_Instance, m_Field ) );
        items[index].second = static_cast< const ConstDataPtr& >( Data::Bind( itr->second, m_Instance, m_Field ) );
    }
}

template < class KeyT, class KeyClassT, class ValueT, class ValueClassT >
DataPtr SimpleStlMapData<KeyT, KeyClassT, ValueT, ValueClassT>::GetItem(const Data* key)
{
    KeyT keyValue;
    Data::GetValue(key, keyValue);

    DataType::const_iterator found = m_Data->find( keyValue );
    if ( found != m_Data->end() )
    {
        return Data::Bind( found->second, m_Instance, m_Field );
    }

    return NULL;
}

template < class KeyT, class KeyClassT, class ValueT, class ValueClassT >
ConstDataPtr SimpleStlMapData<KeyT, KeyClassT, ValueT, ValueClassT>::GetItem(const Data* key) const
{
    KeyT keyValue;
    Data::GetValue(key, keyValue);

    DataType::const_iterator found = m_Data->find( keyValue );
    if ( found != m_Data->end() )
    {
        return Data::Bind( found->second, m_Instance, m_Field );
    }

    return NULL;
}

template < class KeyT, class KeyClassT, class ValueT, class ValueClassT >
void SimpleStlMapData<KeyT, KeyClassT, ValueT, ValueClassT>::SetItem(const Data* key, const Data* value)
{
    KeyT keyValue;
    Data::GetValue(key, keyValue);

    ValueT valueValue;
    Data::GetValue(value, valueValue);

    (m_Data.Ref())[keyValue] = valueValue;
}

template < class KeyT, class KeyClassT, class ValueT, class ValueClassT >
void SimpleStlMapData<KeyT, KeyClassT, ValueT, ValueClassT>::RemoveItem(const Data* key)
{
    KeyT keyValue;
    Data::GetValue(key, keyValue);

    (m_Data.Ref()).erase(keyValue);
}

template < class KeyT, class KeyClassT, class ValueT, class ValueClassT >
bool SimpleStlMapData<KeyT, KeyClassT, ValueT, ValueClassT>::Set(const Data* src, uint32_t flags)
{
    const StlMapDataT* rhs = ObjectCast<StlMapDataT>(src);
    if (!rhs)
    {
        return false;
    }

    m_Data.Set( rhs->m_Data.Get() );

    return true;
}

template < class KeyT, class KeyClassT, class ValueT, class ValueClassT >
bool SimpleStlMapData<KeyT, KeyClassT, ValueT, ValueClassT>::Equals(const Data* s) const
{
    const StlMapDataT* rhs = ObjectCast<StlMapDataT>(s);
    if (!rhs)
    {
        return false;
    }

    return m_Data.Get() == rhs->m_Data.Get();
}

template < class KeyT, class KeyClassT, class ValueT, class ValueClassT >
void SimpleStlMapData<KeyT, KeyClassT, ValueT, ValueClassT>::Serialize(Archive& archive) const
{
    int i = 0;
    std::vector< ObjectPtr > components;
    components.resize( m_Data->size() * 2 );

    {
        DataType::const_iterator itr = m_Data->begin();
        DataType::const_iterator end = m_Data->end();
        for ( ; itr != end; ++itr )
        {
            ObjectPtr keyElem;
            ObjectPtr dataElem;

            // query cache for a serializer of this type
            archive.GetCache().Create( Reflect::GetClass<KeyClassT>(), keyElem );
            archive.GetCache().Create( Reflect::GetClass<ValueClassT>(), dataElem );

            // downcast to serializer type
            KeyClassT* keySer = DangerousCast<KeyClassT>(keyElem);
            ValueClassT* dataSer = DangerousCast<ValueClassT>(dataElem);

            // connect to our map key memory address
            keySer->ConnectData(const_cast<KeyT*>(&(itr->first)));

            // connect to our map data memory address
            dataSer->ConnectData(const_cast<ValueT*>(&(itr->second)));

            // serialize to the archive stream
            components[i++] = keySer;
            components[i++] = dataSer;
        }
    }

    archive.Serialize(components);

    std::vector< ObjectPtr >::iterator itr = components.begin();
    std::vector< ObjectPtr >::iterator end = components.end();
    for ( ; itr != end; ++itr )
    {
        // downcast to serializer type
        Data* ser = DangerousCast<Data>(*itr);

        // disconnect from memory
        ser->Disconnect();

        // restore serializer to the cache
        archive.GetCache().Free( ser );
    }
}

template < class KeyT, class KeyClassT, class ValueT, class ValueClassT >
void SimpleStlMapData<KeyT, KeyClassT, ValueT, ValueClassT>::Deserialize(Archive& archive)
{
    std::vector< ObjectPtr > components;
    archive.Deserialize(components, ArchiveFlags::Sparse);

    if (components.size() % 2 != 0)
    {
        throw Reflect::DataFormatException( TXT( "Unmatched map objects" ) );
    }

    // if we are referring to a real field, clear its contents
    m_Data->clear();

    std::vector< ObjectPtr >::iterator itr = components.begin();
    std::vector< ObjectPtr >::iterator end = components.end();
    for ( ; itr != end; ++itr )
    {
        KeyClassT* key = ObjectCast<KeyClassT>( *itr );
        ValueClassT* value = ObjectCast<ValueClassT>( *(++itr) );

        if (key && value)
        {
            m_Data.Ref()[ key->m_Data.Get() ] = value->m_Data.Get();
        }
    }
}

template < class KeyT, class KeyClassT, class ValueT, class ValueClassT >
tostream& SimpleStlMapData<KeyT, KeyClassT, ValueT, ValueClassT>::operator>> (tostream& stream) const
{
    DataType::const_iterator itr = m_Data->begin();
    DataType::const_iterator end = m_Data->end();
    for ( ; itr != end; ++itr )
    {
        if ( itr != m_Data->begin() )
        {
            stream << s_ContainerItemDelimiter;
        }

        stream << itr->first << s_ContainerItemDelimiter << itr->second;
    }

    return stream;
}

template < class KeyT, class KeyClassT, class ValueT, class ValueClassT >
tistream& SimpleStlMapData<KeyT, KeyClassT, ValueT, ValueClassT>::operator<< (tistream& stream)
{
    m_Data->clear();

    tstring str;
    std::streamsize size = stream.rdbuf()->in_avail();
    str.resize( (size_t) size);
    stream.read( const_cast< tchar_t* >( str.c_str() ), size );

    Tokenize< KeyT, ValueT >( str, m_Data.Ref(), s_ContainerItemDelimiter );

    return stream;
}  

template SimpleStlMapData<tstring, StlStringData, tstring, StlStringData>;
template SimpleStlMapData<tstring, StlStringData, bool, BoolData>;
template SimpleStlMapData<tstring, StlStringData, uint32_t, UInt32Data>;
template SimpleStlMapData<tstring, StlStringData, int32_t, Int32Data>;

template SimpleStlMapData<uint32_t, UInt32Data, tstring, StlStringData>;
template SimpleStlMapData<uint32_t, UInt32Data, uint32_t, UInt32Data>;
template SimpleStlMapData<uint32_t, UInt32Data, int32_t, Int32Data>;
template SimpleStlMapData<uint32_t, UInt32Data, uint64_t, UInt64Data>;

template SimpleStlMapData<int32_t, Int32Data, tstring, StlStringData>;
template SimpleStlMapData<int32_t, Int32Data, uint32_t, UInt32Data>;
template SimpleStlMapData<int32_t, Int32Data, int32_t, Int32Data>;
template SimpleStlMapData<int32_t, Int32Data, uint64_t, UInt64Data>;

template SimpleStlMapData<uint64_t, UInt64Data, tstring, StlStringData>;
template SimpleStlMapData<uint64_t, UInt64Data, uint32_t, UInt32Data>;
template SimpleStlMapData<uint64_t, UInt64Data, uint64_t, UInt64Data>;
template SimpleStlMapData<uint64_t, UInt64Data, Matrix4, Matrix4Data>;

template SimpleStlMapData<Helium::GUID, GUIDData, uint32_t, UInt32Data>;
template SimpleStlMapData<Helium::GUID, GUIDData, Matrix4, Matrix4Data>;
template SimpleStlMapData<Helium::TUID, TUIDData, uint32_t, UInt32Data>;
template SimpleStlMapData<Helium::TUID, TUIDData, Matrix4, Matrix4Data>;

REFLECT_DEFINE_CLASS(StlStringStlStringStlMapData);
REFLECT_DEFINE_CLASS(StlStringBoolStlMapData);
REFLECT_DEFINE_CLASS(StlStringUInt32StlMapData);
REFLECT_DEFINE_CLASS(StlStringInt32StlMapData);

REFLECT_DEFINE_CLASS(UInt32StringStlMapData);
REFLECT_DEFINE_CLASS(UInt32UInt32StlMapData);
REFLECT_DEFINE_CLASS(UInt32Int32StlMapData);
REFLECT_DEFINE_CLASS(UInt32UInt64StlMapData);

REFLECT_DEFINE_CLASS(Int32StringStlMapData);
REFLECT_DEFINE_CLASS(Int32UInt32StlMapData);
REFLECT_DEFINE_CLASS(Int32Int32StlMapData);
REFLECT_DEFINE_CLASS(Int32UInt64StlMapData);

REFLECT_DEFINE_CLASS(UInt64StringStlMapData);
REFLECT_DEFINE_CLASS(UInt64UInt32StlMapData);
REFLECT_DEFINE_CLASS(UInt64UInt64StlMapData);
REFLECT_DEFINE_CLASS(UInt64Matrix4StlMapData);

REFLECT_DEFINE_CLASS(GUIDUInt32StlMapData);
REFLECT_DEFINE_CLASS(GUIDMatrix4StlMapData);
REFLECT_DEFINE_CLASS(TUIDUInt32StlMapData);
REFLECT_DEFINE_CLASS(TUIDMatrix4StlMapData);
