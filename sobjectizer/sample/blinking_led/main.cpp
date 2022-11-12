/*
 * An example of using composite agent state, on_enter/on_exit handlers and
 * time_limit for states.
 */
#include <iostream>

#include <so_5/all.hpp>

using namespace std::chrono_literals;

class blinking_led final : public so_5::agent_t
{
	state_t off{ this }, blinking{ this },
		blink_on{ initial_substate_of{ blinking } },
		blink_off{ substate_of{ blinking } };

public :
	struct turn_on_off final : public so_5::signal_t {};

	blinking_led( context_t ctx ) : so_5::agent_t{ ctx }
	{
		this >>= off;

		off.just_switch_to< turn_on_off >( blinking );

		blinking.just_switch_to< turn_on_off >( off );

		blink_on
			.on_enter( []{ std::cout << "ON" << std::endl; } )
			.on_exit( []{ std::cout << "off" << std::endl; } )
			.time_limit( std::chrono::milliseconds{1250}, blink_off );

		blink_off
			.time_limit( std::chrono::milliseconds{750}, blink_on );
	}
};

int main()
{
	try
	{
		so_5::launch( []( so_5::environment_t & env ) {
			auto m = env.introduce_coop( []( so_5::coop_t & coop ) {
					return coop.make_agent< blinking_led >()->so_direct_mbox();
				} );

			std::cout << "Turn blinking on for 10s" << std::endl;
			so_5::send< blinking_led::turn_on_off >( m );
			std::this_thread::sleep_for( 10s );

			std::cout << "Turn blinking off for 5s" << std::endl;
			so_5::send< blinking_led::turn_on_off >( m );
			std::this_thread::sleep_for( 5s );

			std::cout << "Turn blinking on for 5s" << std::endl;
			so_5::send< blinking_led::turn_on_off >( m );
			std::this_thread::sleep_for( 5s );

			std::cout << "Stopping..." << std::endl;
			env.stop();
		} );
	}
	catch( const std::exception & ex )
	{
		std::cerr << "Error: " << ex.what() << std::endl;
	}

	return 0;
}

