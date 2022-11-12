#include <iostream>
#include <cstdint>

#include <json_dto/pub.hpp>

struct vector_types_t
{
	std::vector< bool > m_bool{};

	std::vector< std::int8_t > m_int8{};
	std::vector< std::uint8_t > m_uint8{};

	std::vector< std::int16_t > m_int16{};
	std::vector< std::uint16_t > m_uint16{};

	std::vector< std::int32_t > m_int32{};
	std::vector< std::uint32_t > m_uint32{};

	std::vector< std::int64_t > m_int64{};
	std::vector< std::uint64_t > m_uint64{};
	std::vector< double > m_double{};

	std::vector< std::string > m_string{};
};

namespace json_dto
{

template< typename Json_Io >
void json_io( Json_Io & io, vector_types_t & obj )
{
	io & json_dto::mandatory( "bool", obj.m_bool )
		& json_dto::mandatory( "int8", obj.m_int8 )
		& json_dto::mandatory( "uint8", obj.m_uint8 )
		& json_dto::mandatory( "int16", obj.m_int16 )
		& json_dto::mandatory( "uint16", obj.m_uint16 )
		& json_dto::mandatory( "int32", obj.m_int32 )
		& json_dto::mandatory( "uint32", obj.m_uint32 )
		& json_dto::mandatory( "int64", obj.m_int64 )
		& json_dto::mandatory( "uint64", obj.m_uint64 )
		& json_dto::mandatory( "double", obj.m_double )
		& json_dto::mandatory( "string", obj.m_string );
}

} /* namespace json_dto */

const std::string json_data{
R"JSON({
	"bool" : [true, true, false],
	"int8" : [-8, -4, -2, -1, 0, 1, 2, 4, 8],
	"uint8" : [0, 1, 2, 4, 8],
	"uint16" : [2, 12, 42, 65000],
	"int16" : [-1, 0, 1],
	"uint16" : [2, 12, 42, 65000],
	"int32" : [-4],
	"uint32" : [],
	"int64" : [-16, 2016 ],
	"uint64" : [32, 33],
	"double" : [2.718281828, 3.14 ],
	"string" : [ "a", "bc", "def", "ghij", "klmno", "pqrstu", "vwxyz"]
})JSON" };

template< typename C, typename T >
void dump_to( std::ostream & o, const std::vector< T > & v )
{
	o << "[";

	for( size_t i = 0; i < v.size(); ++i )
	{
		if( 0 < i )
			o << ", ";

		o << C{ v[ i ] };
	}

	o << "]";
}

template < typename T >
std::ostream &
operator << ( std::ostream & o, const std::vector< T > & v )
{
	dump_to< T >( o, v );
	return o;
}

// std::int8_t can be handled just as a char, so use a special version.
std::ostream &
operator << ( std::ostream & o, const std::vector< std::int8_t > & v )
{
	dump_to< std::int16_t >( o, v );
	return o;
}

// std::int8_t can be handled just as a unsigned char, so use a special version.
std::ostream &
operator << ( std::ostream & o, const std::vector< std::uint8_t > & v )
{
	dump_to< std::uint16_t >( o, v );
	return o;
}

int
main( int , char *[] )
{
	try
	{
		{
			auto obj = json_dto::from_json< vector_types_t >( json_data );

			std::cout
				<< "Deserialized from JSON:\n"
				<< "\tbool: " << obj.m_bool << "\n"
				<< "\tint8: " << obj.m_int8 << "\n"
				<< "\tuint8: " << obj.m_uint8 << "\n"
				<< "\tint16: " << obj.m_int16 << "\n"
				<< "\tuint16: " << obj.m_uint16 << "\n"
				<< "\tint32: " << obj.m_int32 << "\n"
				<< "\tuint32: " << obj.m_uint32 << "\n"
				<< "\tint64: " << obj.m_int64 << "\n"
				<< "\tuint64: " << obj.m_uint64 << "\n"
				<< "\tdouble: " << obj.m_double << "\n"
				<< "\tstring: " << obj.m_string << "\n"
				<< std::endl;
		}

		{
			vector_types_t obj{};

			obj.m_bool.emplace_back( true );
			obj.m_bool.emplace_back( false );

			obj.m_int8.emplace_back( -11 );
			obj.m_int8.emplace_back( 11 );

			obj.m_uint8.emplace_back( 129 );

			obj.m_int16.emplace_back( 11 );
			obj.m_int16.emplace_back( 987 );

			obj.m_uint16.emplace_back( 1642 );

			obj.m_int32.emplace_back( 1410 );
			obj.m_int32.emplace_back( 8 );
			obj.m_int32.emplace_back( 15 );

			obj.m_uint32.emplace_back( 1494 );
			obj.m_int32.emplace_back( 0 );
			obj.m_int32.emplace_back( 0xFFFFFFFF );

			obj.m_int64.emplace_back( -111222333444 );

			obj.m_uint64.emplace_back( 0xFFFFFFFFFFFFFFFF );

			obj.m_double.emplace_back( 3.14 );
			obj.m_double.emplace_back( 2.718281828 );

			obj.m_string.emplace_back( "0123");
			obj.m_string.emplace_back( "456");
			obj.m_string.emplace_back( "78" );
			obj.m_string.emplace_back( "9" );

			std::cout
				<< "\nSerialized to JSON (default):\n"
				<< json_dto::to_json( obj )
				<< "\n\nSerialized to JSON (pretty-writer #1):\n"
				<< json_dto::to_json( obj,
						json_dto::pretty_writer_params_t{}
								.indent_char_count( 2u ) )
				<< "\n\nSerialized to JSON (pretty-writer #2):\n"
				<< json_dto::to_json( obj,
						json_dto::pretty_writer_params_t{}
								.indent_char( '\t' )
								.indent_char_count( 1u )
								.format_options( rapidjson::kFormatSingleLineArray ) )
				<< std::endl;

		}
	}
	catch( const std::exception & ex )
	{
		std::cerr << "Error: " << ex.what() << "." << std::endl;
		return 1;
	}

	return 0;
}
