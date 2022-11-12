/*
 * An example of FIFO types for adv_thread_pool dispatcher.
 *
 * Two agents are registered in one coop on adv_thread_pool.
 * The first time agents use fifo_t::cooperation.
 * The second time agents use fifo_t::individual.
 *
 * At first time events A.e1 and B.e2 must be invoked at the same time,
 * then A.e3, then B.e2 and A.e1 again at the same time.
 *
 * At second time events A.e1, B.e2 and B.e2 must be invoked at the same time,
 * the A.e2, and only then A.1.
 */
#include <iostream>

#include <so_5/all.hpp>

// Logging infrastructure.
struct trace_msg
{
	const so_5::agent_t * m_who;
	std::string m_what;
	std::thread::id m_thread_id;
};

void create_logger( so_5::environment_t & env )
{
	class logger_actor final : public so_5::agent_t {
	public:
		logger_actor( context_t ctx ) : so_5::agent_t{ std::move(ctx) }
		{
			so_subscribe( so_environment().create_mbox( "log" ) )
				.event( [](mhood_t<trace_msg> cmd ) {
					std::cout << cmd->m_thread_id << ": (" << cmd->m_who
						<< ") " << cmd->m_what << std::endl;
				} );
		}
	};
	env.introduce_coop( [&]( so_5::coop_t & coop ) {
		coop.make_agent< logger_actor >();
	} );
}

void trace( const so_5::agent_t & agent, std::string what )
{
	so_5::send< trace_msg >( agent.so_environment().create_mbox( "log" ),
		&agent, std::move(what), std::this_thread::get_id() );
}

// Main part of the example.

struct M1 final : public so_5::signal_t {};
struct M2 final : public so_5::signal_t {};
struct M3 final : public so_5::signal_t {};

struct stop final : public so_5::signal_t {};

const std::chrono::milliseconds sleeping_time{ 200 };

class A final : public so_5::agent_t
{
public :
	A( context_t ctx ) : so_5::agent_t{ ctx }
	{
		so_subscribe( so_environment().create_mbox( "demo" ) )
			.event( [this]( mhood_t<M1> ) {
					trace( *this, "A.e1 started" );
					std::this_thread::sleep_for( sleeping_time );
					trace( *this, "A.e1 finished" );
				},
				so_5::thread_safe )
			.event( [this]( mhood_t<M3> ) {
					trace( *this, "A.e3 started" );
					std::this_thread::sleep_for( sleeping_time );
					trace( *this, "A.e3 finished" );
				} )
			.event( [this]( mhood_t<stop> ) { so_environment().stop(); } );
	}
};

class B final : public so_5::agent_t
{
public :
	B( context_t ctx ) : so_5::agent_t{ ctx }
	{
		so_subscribe( so_environment().create_mbox( "demo" ) )
			.event( [this]( mhood_t<M2> ) {
					trace( *this, "B.e2 started" );
					std::this_thread::sleep_for( sleeping_time );
					trace( *this, "B.e2 finished" );
				},
				so_5::thread_safe );
	}
};

void run_sample( so_5::disp::adv_thread_pool::fifo_t fifo_type )
{
	so_5::launch( [fifo_type]( so_5::environment_t & env ) {
		create_logger( env );

		namespace pool_disp = so_5::disp::adv_thread_pool;

		env.introduce_coop(
			pool_disp::make_dispatcher( env, 4 ).binder(
				pool_disp::bind_params_t{}.fifo( fifo_type ) ),
			[]( so_5::coop_t & coop )
			{
				coop.make_agent< A >();
				coop.make_agent< B >();
			} );

		const auto m = env.create_mbox( "demo" );
		so_5::send< M1 >( m );
		so_5::send< M2 >( m );
		so_5::send< M3 >( m );
		so_5::send< M2 >( m );
		so_5::send< M1 >( m );
		so_5::send< stop >( m );
	} );
}

int main()
{
	try
	{
		std::cout << "cooperation FIFO..." << std::endl;
		run_sample( so_5::disp::adv_thread_pool::fifo_t::cooperation );

		std::cout << "individual FIFO..." << std::endl;
		run_sample( so_5::disp::adv_thread_pool::fifo_t::individual );
	}
	catch( const std::exception & ex )
	{
		std::cerr << "Error: " << ex.what() << std::endl;
	}

	return 0;
}

